// 1.6 练习

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define N 10000

int main()
{
    int p2c[2];
    int c2p[2];
    pipe(p2c);
    pipe(c2p);
    
    int fd = fork();

    // 子进程先读后写
    if ( fd == 0 )
    {
        // 关闭父进程的端口
        close(p2c[1]);
        close(c2p[0]);
        
        char c;
        for ( int i = 0; i < N; i++ )
        {
            read(p2c[0], &c, 1);
            write(c2p[1], &c, 1);
        }
        exit(0);
    }

    // 父进程先写后读
    else if (fd > 0)
    {
        // 关闭子进程的端口
        close(p2c[0]);
        close(c2p[1]);

        char c = 'a';
        int start = uptime();

        for ( int i = 0; i < N; i++ )
        {
            write(p2c[1], &c, 1);
            read(c2p[0], &c, 1);
        }
        int end = uptime();
        wait(0);

        printf("%d exchanges, %d ticks\n", N, end - start);
    }

    // 创建子进程失败
    else
    {
        fprintf(2, "fork: error\n");
        exit(1);
    }
}
