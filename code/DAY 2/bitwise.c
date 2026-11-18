// 位运算练习代码

// 把 y 的最低 n 位放到 x 的 p 到 p - n + 1 位
unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
    // y 的最低 n 位不变，其他变为 1
    y = y | (~0 << n);

    // y 左移 p - n + 1 位，此时最低 p 位为 0
    y = y << (p - n + 1);

    // y 的最低 p - n + 1 位变为 1
    y = y | ~(~0 << (p - n + 1));

    // 把 x 的 p 到 p - n + 1 位换为 1
    x = x | (~(~0 << n) << (p - n + 1));

    return x & y;
}

// 把 x 从第 p 位开始的 n 位取反
unsigned int invert(unsigned int x, int p, int n)
{
    // 把 x 的中间 n 位单独取出来取反
    unsigned int y = (~(~0 << n) << (p - n + 1));     // 中间 n 位为 1 其他为 0
    unsigned int tmp = y;
    y = x & y;      // 此时 y 为 x 的中间 n 位，其他为 0
    y = ~y;         // 此时 y 为 x 的中间 n 位取反，其他为 1

    // 把 x 中间 n 位变为 1
    x = tmp | x;
    return x & y;
}

// 把 x 循环位移 n 位
unsigned rightrot(unsigned x, int n)
{
    for ( int i = 0; i < n; i++ )
    {
        unsigned int tmp = x << 31;
        x = x >> 1;
        x = tmp | x;
    }
    return x;
}
