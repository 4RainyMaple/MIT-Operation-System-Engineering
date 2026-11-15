#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void memdump(char *fmt, char *data, int len);

int
main(int argc, char *argv[])
{
  if (argc == 1) {
    printf("Example 1:\n");
    int a[2] = {61810, 2026};
    memdump("ii", (char *)a, sizeof(a));

    printf("Example 2:\n");
    memdump("S", "a string", sizeof("a string"));

    printf("Example 3:\n");
    char *s = "another";
    memdump("s", (char *)&s, sizeof(s));

    struct sss {
      char *ptr;
      int num1;
      short num2;
      char byte;
      char bytes[8];
    } example;

    example.ptr = "hello";
    example.num1 = 1819438967;
    example.num2 = 100;
    example.byte = 'z';
    strcpy(example.bytes, "xyzzy");

    printf("Example 4:\n");
    memdump("pihcS", (char *)&example, sizeof(example));

    printf("Example 5:\n");
    memdump("sccccc", (char *)&example, sizeof(example));
  } else if (argc == 2) {
    // format in argv[1], up to 512 bytes of data from standard input.
    char data[512];
    int n = 0;
    memset(data, '\0', sizeof(data));
    while (n < sizeof(data)) {
      int nn = read(0, data + n, sizeof(data) - n);
      if (nn <= 0)
        break;
      n += nn;
    }
    memdump(argv[1], data, n);
  } else {
    printf("Usage: memdump [format]\n");
    exit(1);
  }
  exit(0);
}

void
memdump(char *fmt, char *data, int len)
{
  // Your code here.  `data` holds `len` valid bytes.
  // 注意这里有 2 个遍历的变量，off 用于遍历 data，i 用于遍历 fmt
  int off = 0;
  for (int i = 0; fmt[i] != '\0'; i++)
  {
    switch(*(fmt + i))
    {
      // 读 4 字节，输出 32 位十进制整数
      case 'i': 
        if (off + 4 > len)  // 注意这里不需要取等
        {
          printf("memdump: not enough data for '%c'\n", fmt[i]);
          return;
        }
        int v1;
        memcpy(&v1, data + off, 4);
        printf("%d\n", v1);
        off += 4;
        break;
        
      // 读 8 字节，输出 16 进制 64 位整数
      case 'p': 
        if (off + 8 > len)
        {
          printf("memdump: not enough data for '%c'\n", fmt[i]);
          return;
        }
        long v2;
        memcpy(&v2, data + off, 8);
        printf("%lx\n", v2); 
        off += 8;
        break;

      // 读 2 字节，输出十进制 16 位整数
      case 'h': 
        if (off + 2 > len)
        {
          printf("memdump: not enough data for '%c'\n", fmt[i]);
          return;
        }
        short v3;
        memcpy(&v3, data + off, 2);
        printf("%d\n", v3);
        off += 2;
        break;

      // 读 1 字节，输出一个字符
      case 'c': 
        if (off + 1 > len)
        {
          printf("memdump: not enough data for '%c'\n", fmt[i]);
          return;
        }
        printf("%c\n", *(data + off));
        off++;
        break;

      // 读 8 字节，当做指针，打印指向的内容
      case 's': 
        if (off + 8 > len)
        {
          printf("memdump: not enough data for '%c'\n", fmt[i]);
          return;
        }
        char * v4;                    // 指针变量就是 8 字节
        memcpy(&v4, data + off, 8);   // 注意这里要操作 v4 所以还是要取地址
        printf("%s\n", v4);           // 打印字符串刚好就是传入一个字符指针
        off += 8;
        break;

      // 读写剩余所有内容
      case 'S': 
        for (; off < len && *(data + off) != '\0'; off++)
          printf("%c", *(data + off));
        printf("\n");   // 注意换行时机
        break;
      default: return;
    }
  }
} 
