// memcpy 和 memmove 练习

// 将 src 的前 n 个字节复制给 dst
void * mymemcpy(void * dst, const void * src, int n)
{
    // void * 不知道元素大小，不能直接解引用
    unsigned char * d = (unsigned char *) dst;
    const unsigned char * s = (const unsigned char *) src;
    for ( int i = 0; i < n; i++ )
        d[i] = s[i];

    return dst;
}

// 处理重叠部分
void * mymemmove(void * dst, const void * src, int n)
{
    unsigned char * d = (unsigned char *) dst;
    const unsigned char * s = (const unsigned char *) src;
    if ( d < s || d >= s + n )  // 从前往后复制
        return mymemcpy(dst, src, n);
    
    else    // 从后往前复制
    {
        for ( int i = n - 1; i >= 0; i-- )
            d[i] = s[i];

        return dst;
    }
}

// 支持任意类型的交换
void swap(void * p1, void * p2, int size)
{
    char tmp[size];     // 不可以直接定义一个指针，否则会向随机地址写东西报错
    mymemcpy(tmp, p1, size);
    mymemcpy(p1, p2, size);
    mymemcpy(p2, tmp, size);
}