#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// argc 表示参数数量，argv 表示参数字符串数组
// sleep 10 argc = 2, argv[0] = "sleep", argv[1] = "10"
int main(int argc, char *argv[])
{
    if ( argc != 2 )
    {
        fprintf(2, "usage: sleep ticks\n");
        exit(1);
    }

    // 1 tick 约为 0.1 秒
    int ticks = atoi(argv[1]);
    pause(ticks);
    exit(0);    // 不要写 return
}
