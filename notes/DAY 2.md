本次课程内容为C语言拓展，难度不大。

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

## 指针

**字符串函数** [str.c](../code/DAY%202/str.c)

```c
int mystrlen(char * s);
int mystrcmp(char * s1, char * s2);
void mystrcpy(char * dst, const char * src);
void mystrcat(char * dst, const char * src);
```

**复制函数** [memcpy.c](../code/DAY%202/memcpy.c)

```c
void * mymemcpy(void * dst, const void * src, int n);
void * mymemmove(void * dst, const void * src, int n);
```

**结构体指针** [node.c](../code/DAY%202/node.c)

```c
struct node *push_front(struct node *head, int pid, char *name);
struct node *find(struct node *head, int pid);
struct node *remove_node(struct node *head, int pid);
void print_list(struct node *head);
void free_list(struct node *head);
```
