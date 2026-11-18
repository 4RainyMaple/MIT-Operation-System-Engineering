// 字符串练习

int mystrlen(char * s)
{
    int len = 0;
    for (; s[len] != '\0'; len++ );
    return len;
}

int mystrcmp(char * s1, char * s2)
{
    int i = 0;
    for (; s1[i] != '\0' && s2[i] != '\0'; i++ )
    {
        if ( s1[i] - s2[i] < 0 )
            return -1;
        else if ( s1[i] - s2[i] > 0 )
            return 1;
    }
    if ( s1[i] != '\0' )
        return 1;
    else if ( s2[i] != '\0' )
        return -1;
    else 
        return 0;
}

void mystrcpy(char * dst, const char * src)
{
    int i = 0;
    for (; src[i] != '\0'; i++ )
        dst[i] = src[i];
    dst[i] = '\0';  // 注意补 \0
}

void mystrcat(char * dst, const char * src)
{
    int len = 0, i = 0;
    while ( dst[len] != '\0' )
        len++;
    for (; src[i] != '\0'; i++ )
        dst[i + len] = src[i];
    dst[i + len] = '\0';    // 注意补 \0
}