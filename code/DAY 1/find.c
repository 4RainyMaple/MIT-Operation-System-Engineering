#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

void find(char * path, char * name)
{
    int fd = open(path, O_RDONLY);
    struct stat st;     // 文件信息
    struct dirent de;   // 目录中的 “ 文件名 + inode ”

    // 文件打不开
    if ( fd < 0 )
    {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    // 文件能打开，但不能获取里面的信息
    if ( fstat(fd, &st) < 0 )
    {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);  // 文件已经打开了，记得关闭
        return;
    }

    // 取出当前路径的文件名进行比较，若相等就输出
    char * filename = path;     // 这里必须给个初始值，防止 path 里面没有 / 的情况
    for ( char * p = path; *p != '\0'; p++ )
        if ( *p == '/' )
            filename = p + 1;

    if ( strcmp(filename, name) == 0 )
        printf("%s\n", path);
    
    // 如果是目录的话就递归
    if (st.type == T_DIR)
        while ( read(fd, &de, sizeof(de)) == sizeof(de) )
        {
            if ( de.inum == 0 ) continue;   // 空槽跳过
            if ( strcmp(de.name, ".") == 0 ) continue;  // 原地跳过
            if ( strcmp(de.name, "..") == 0 ) continue; // 父目录跳过
            
            // 拼接
            char child[128];
            strcpy(child, path);    // 把 path 拷贝给 child
            int n = strlen(child);
            child[n] = '/';
            strcpy(child + n + 1, de.name);     // 从下标 n + 1 开始把 de.name 拷贝给 child
            find(child, name);
        }
    close(fd);
}

int main(int argc, char * argv[])
{
    if ( argc != 3 )
    {
        fprintf(2, "usage: find path name\n");
        exit(1);
    }

    find(argv[1], argv[2]);
    exit(0);
}
