## Boot xv6

xv6是MIT写的一个教学用的迷你的Unix操作系统。（太强了）

```bash
make qemu    # 编译 xv6 并在 QEMU 中启动

# 以下是 xv6 中的操作
ls
echo
# 这两条命令与 bash 中有点区别
Ctrl + a x   # 退出 xv6
Ctrl + p     # 打印当前进程信息 
```

## sleep

先阅读了[xv6 book](../../xv6%20book.md)第一章，然后完成了[sleep.c](../code/sleep.c)

在 Makefile 中注册sleep：  
在 Makefile 中找到 `UPROGS=\` 这一段，在 `$U/_sh\` 后面加一行：$U/\_sleep\

运行 util lab 的自动评分脚本

```bash
./grade-lab-util sleep   # 看到 OK 就通过
```

用 git 提交

```bash
git add user/sleep.c Makefile
git commit -m "util: sleep"
```
