## Boot xv6

**前置知识：**

xv6是MIT写的一个教学用的迷你的Unix操作系统。（太强了）

**实验步骤：**

- 编译 xv6 并在 QEMU 中启动

```bash
make qemu    
```

- 尝试 xv6 的基础命令

```bash
ls
echo
# 这两条命令与 bash 中有点区别

Ctrl + a x   # 退出 xv6
Ctrl + p     # 打印当前进程信息 
```

## sleep

**接口功能：**

休眠指定时间。

**实验步骤：**

- 先阅读了[xv6 book](../xv6%20book.md)第一章，然后完成了 [sleep.c](../code/DAY%201/sleep.c)

- 在 Makefile 中注册sleep：  
  在 Makefile 中找到 `UPROGS=\` 这一段，在 `$U/_sh\` 后面加一行：`$U/_sleep\`

- 运行 util lab 的自动评分脚本

```bash
./grade-lab-util sleep   # 看到 OK 就通过
```

- 用 git 提交

```bash
git add user/sleep.c Makefile
git commit -m "util: sleep"
```

## sixfive

**接口功能：**

读取分隔符之间的数字，如果它是5或6的倍数就输出，支持文件读入和`stdin`读入。

**实验步骤：**

- 注册  
  在 `Makefile` 中 `UPROGRS=\` 部分添加 `$U/_sixfive\`

- 完成 [sixfive.c](../code/DAY%201/sixfive.c)  
  我卡住的地方：

  - 判断输出条件：一开始我写了一个很复杂的单变量判断，后面在AI的提示下改为双变量判断，这是我认为本次实验最困难的部分。
  - read函数的调用：由于是第一次调用，一开始对功能很不熟悉，反复写错。后来我自己想到了一个死循环读入，读到 0 或 -1 才退出。
  - 识别数字：一开始我写的是判定为数字就打印，后面发现需要判断倍数关系就改为累加。

- 运行 util lab 的自动评分脚本

```bash
./grade-lab-util sixfive   
```

- 用 git 提交

```bash
git add user/sixfive.c Makefile
git commit -m "util: sixfive"
```

## memdump

**接口功能：**

根据不同的格式字符串 fmt 打印给定字符串。

| 格式字符 | 读入字节数 | 输出        |
| ---- | ----- | --------- |
| i    | 4     | 32位十进制整数  |
| p    | 8     | 64位16进制整数 |
| h    | 2     | 16位十进制整数  |
| c    | 1     | 一个字符      |
| s    | 8     | 该地址的内容    |
| S    | 剩余全部  | 剩余全部      |

**实验步骤：**

- 注册：  
  在 `Makefile` 中 `UPROGRS=\` 部分添加 `$U/_memdump\`

- 完成 [memdump.c](../code/DAY%201/memdump.c)  
  我卡住的地方：

  - 一开始对实验目的都还不是很清晰，第一次接触 memcpy 函数，对其功能和用法还很不熟悉。
  - 处理 s 的情况，被指针，内存和变量类型这些卡住了很久，最后还是在 AI 的帮助下才能理解。

- 评测

```bash
./grade-lab-util memdump
```

- 提交

```bash
git add user/memdump.c Makefile
git commit -m "util: memdump"
```

## find

**接口功能：**

```bash
find path name   # 从 path 出发打印所有叫作 name 的文件或目录的路径
```

**前置知识：**

文件信息的结构体：

```c
struct stat {
  int dev;      // 设备号
  uint ino;     // inode 编号
  short type;   // 文件类型
  short nlink;  // 链接数
  uint64 size;  // 字节大小
};

// 内核根据 fd 将信息填入 st
int fstat(int fd, struct stat *st);
```

其中 type 的值有：  
T_DIR     目录  
T_FILE    普通文件  
T_DEVICE  设备文件

目录项的结构体：

```c
struct dirent {
  ushort inum;       // inode 编号
  char name[DIRSIZ]; // 文件名
};
```

c的字符串操作比较原始

```c
strcmp(char * s1, char * s2);  // s1 - s2
strcpy(char * s1, char * s2);  // 将 s2 拷贝给 s1
```

**实验步骤：**

- 注册  
  在 `Makefile` 中 `UPROGRS=\` 部分添加 `$U/_find\`

- 完成 [find.c](../code/DAY%201/find.c)  
  我卡住的地方：

  - stat 和 dirent 这两个结构体还没接触过，理解其含义花了一些时间。
  - 取出当前路径的文件名不太会操作，这个直接让 AI 教我了。
  - 拼接当前路径和目录的名称没思路，也是让 AI 教我。

- 评测

```bash
./grade-lab-util find
```

- 提交

```bash
git add ../Makefile find.c
git commit -m "util: find"
```

## find with exec

**接口功能：**

```bash
find path name -exec cmd...   # 将路径当做最后一个参数传入
```

**实验步骤：**

- 修改 find.c  
  修改的地方：

  - find 传入参数添加 cmd，普通情况下 cmd = 0。
  - 判断路径的文件名称是否符合时，根据 cmd 的值判断后面走哪条路。

  我卡住的地方：

  - 给 exec 函数重新构建传入数组时，数组指针不需要也不能使用strcpy，直接赋值即可。
  - exec 里的子进程完成后会直接退出，所以需要补一个失败提示。

- 测评

```bash
./grade-lab-util exec
```

- 提交

```bash
git add user/find.c
git commit -m "util: find with -exec"
```

## 总结

作为第一个lab，对我来说难度是不低的。刚开始使用xv6感觉一头雾水，看xv6 book也很茫然。所以完成第一个接口`sleep`的时候我都感觉很艰难，一些命令基本都是死记硬背，做`sixfive`的时候更是感觉人都要麻了。其实主要原因是我没有利用好一些现成的函数，以及有一段时间没有写过C了，所以写起来很艰难。但写到后面三个任务就感觉好一些了，命令和代码都熟练了一些。  
对于不会写的代码，基本都是让 AI 提供思路，然后我再反复测试，修正我的代码，只有实在是不会写的才让 AI 写一部分。
