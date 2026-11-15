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

- 先阅读了[xv6 book](../../xv6%20book.md)第一章，然后完成了[sleep.c](../code/sleep.c)

- 在 Makefile 中注册sleep：  
  在 Makefile 中找到 `UPROGS=\` 这一段，在 `$U/_sh\` 后面加一行：`$U/\_sleep\`

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
  在 `Makefile` 中 `UPROGRS=\` 部分添加 `$U/\_sixfive\`

- 完成[sixfive.c](../code/sixfive.c)  
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
