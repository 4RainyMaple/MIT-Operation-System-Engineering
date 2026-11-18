本次课程内容为C语言拓展。

## 位运算

**&|^运算符**

不管是什么进制输入，都是转换为二进制做运算，仅支持整数类型。  
异或运算：相同为0，不同为1。

```c
char x = 12;   # 00001100
char y = 11;   # 00001011
x & y = 8      # 00001000
x | y = 15     # 00001111
x ^ y = 7      # 00000111
x << 2 = 48    # 00110000
y >> 2 = 2     # 00000010

```

**练习** [bitwise.c](../code/DAY%202/bitwise.c)

```c
// 把 y 的最低 n 位放到 x 的 p 到 p - n + 1 位
unsigned int setbits(unsigned int x, int p, int n, unsigned int y);
```

卡住的地方：把 p 位当做是低位，实际上应该是 p - n + 1 位。

```c
// 把 x 从第 p 位开始的 n 位取反
unsigned int invert(unsigned int x, int p, int n);
```

```c
// 把 x 从第 p 位开始的 n 位取反
unsigned int invert(unsigned int x, int p, int n);
```
