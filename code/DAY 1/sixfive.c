#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int is_digit(char c)
{
    int n = (int)(c - '0');
    return 0 <= n && n <= 9;
}

int is_separator(char c)
{
    return c == '-' || c == '\r' || c == '\t' || c == '\n' || c == '.' || c == '/' || c == ' ' || c == ',';
}

void process(int fd)
{
    char c;         // 这里每次只读一个字符，就不需要数组了
    int in_num = 0; // 判断是否在累积数字
    int valid = 1;  // 判断是否输出，注意初始值为1
    long long num = 0;
    // 注意，每次 read 都会覆盖
    while (1)
    {
        int n = read(fd, &c, 1);
        if ( n == 1 )
        {
            if ( is_digit(c) )
            {
                num = num * 10 + (int)(c - '0');
                in_num = 1;
            }
            else
            {
                if ( is_separator(c) )
                {
                    if ( valid == 1 && in_num == 1 && (num % 5 == 0 || num % 6 == 0) ) 
                        fprintf(1, "%lld\n", num);
                    valid = 1;
                }
                else
                    valid = 0;

                num = 0;
                in_num = 0;
            }
        }
        else if ( n == 0 )
        {
            if ( valid == 1 && in_num == 1 && (num % 5 == 0 || num % 6 == 0) )
                fprintf(1, "%lld\n", num);
            return;
        }
        else
        {
            fprintf(2, "read: error\n");
            return;
        }
    }
}

// 输入 sixfive sixfive.txt
int main(int argc, char *argv[])
{
    // 参数不够从 stdin 读取
    if ( argc < 2 )
        process(0);

    // 依次打开文件
    else
    {
        for ( int i = 1; i < argc; i++ )
        {
            int fd = open(argv[i], O_RDONLY);
            if ( fd < 0 )
            {
                fprintf(2, "sixfive: cannot open %s\n", argv[i]);
                continue;
            }
            process(fd);
            close(fd);
        }
    }
    
    exit(0);
}
