# Lab: system calls

先区分两个概念：  
**utility:** 用户程序，如`sleep`,`find`  
**system calls:** 程序接口，如`read`,`write`

切换分支：

```bash
git fetch
git checkout syscall
make clean   # 清理另一个分支的编译产物
```

## 使用 gdb

先让一个终端打开连接 gdb 的 QEMU

```bash
make qemu-gdb
```

另一个终端打开 gdb

```bash
gdb-multiarch
```

以下是在 gdb 中的操作

```bash
file kernel/kernel              # 配置参数
target remote localhost:26000   # 远程连接

b syscall    # 给系统调用设置断点
c            # 继续
p x          # 打印变量或表达式的值
q            # 退出
```

## Sandbox a command

**实验目标：**

给进程一张系统调用黑名单，内核在分发系统调用前查这张黑名单，命中就返回 -1。

**前置知识：**

- 每个系统调用都有一个系统调用号，写在 `kernel/syscall.h` 中。
- `a0–a7` 是 RISC-V 的函数参数寄存器，`a7` 放系统调用号，`a0–a5` 放参数。`a0` 同时还是返回值寄存器。
- `.S` 是汇编文件，`.pl` 是一种脚本。

**实验步骤：**

- 注册  
在 `Makefile` 中 `UPROGS` 部分添加：

```
$U/_sandbox\
$U/_sbtest\
```

- 给 `struct proc` 添加新成员

```c
uint64 syscall_mask;
```

- 把 mask 存进当前进程  
在 kernel/sysproc.c 中添加 sys_interpose 函数

```c
uint64
sys_interpose()
{
  int mask;

  argint(0, &mask);   // 把当前系统调用的第 0 个参数取出来，存到 mask 里面
  myproc()->syscall_mask = (uint64)mask;    
  // myproc() 返回当前执行系统调用的进程，写入 mask
  
  return 0;
}
```

- fork 时把 mask 复制给子进程  
在 kernel/proc.c 中的 kfork 函数添加

```c
np->syscall_mask = p->syscall_mask;
```

关于 p 与 np：

```c
struct proc *p = myproc();       // 父进程：谁调用了 fork
struct proc *np = allocproc();   // 子进程
```

在 kernel/proc.c 中的 allocproc 函数做初始化

```c
struct proc *p;      // 原有
p->syscall_mask = 0;
```

三个函数的关系：  
用户调 `fork(user/user.h)`  
内核 `sys_fork(kernel/sysproc.c)` 转手  
真正干活的是 `kfork(kernel/proc.c)`

- 评测

```bash
./grade-lab-syscall sandbox_mask
```

- 提交

```bash
git commit -am "syscall: interpose sandbox mask"
```

**逻辑链复盘：**

- 在 xv6 中：

```bash
sandbox 32768 - cat README  # 输入
cat: cannot open README     # 输出
```

这里用户输入 2 的幂是为了方便用位图，单参数输入多个想要禁用的系统调用。

- 用户调用 `sandbox` 在 `user/sandbox.c` 中实现
- `user/sandbox.c` 中调用 `interpose(32768, "-")` 函数
- `interpose` 函数在 `user/user.h` 中声明:

```c
interpose(int mask, char * path);
```

在 `user/usys.S` 中实现，由 `user/usys.pl` 生成，内容是将 `a7` 设置为 `interpose` 的系统调用号 23 并 `ecall`

- CPU 进入内核，调用 `kernel/syscall.c` 中的 `syscall()` 函数
- 根据 `a7` 查表，找到 `kernel/sysproc.c` 中的 `sys_interpose()` 函数

## Sandbox with allowed pathnames

**实验目标：**

给 `interpose` 添加一个白名单路径，禁用系统调用的同时还会判断，如果被禁用的是 `open` 或 `exec` 且在白名单路径中，就放行给定路径。

**前置知识：**

xv6 自带一些类似于标准库的函数，声明在 `kernel/defs.h` 中。  
本次实验主要用到两个字符串操作：

```c
char* safestrcpy(char*, const char*, int);
int strncmp(const char*, const char*, uint);
```

**实验步骤：**

- 在 `kernel/proc.h` 中给 `struct proc` 添加新成员

```c
char allowed_path[MAXPATH];
```

- 在 `kernel/sysproc.c` 中修改 `sys_interpose()` 函数

```c
argstr(1, buf, MAXPATH);
safestrcpy(myproc()->allowed_path, buf, sizeof(buf));  
```

- 在 `kernel/proc.c` 中写入白名单路径

```c
p->allowed_path[0] = '\0';
safestrcpy(np->allowed_path, p->allowed_path, sizeof(p->allowed_path));
```

- 在 `kernel/syscall.c` 中完善判断机制

```c
char path[MAXPATH];
argstr(0, path, MAXPATH);

if (num > 0 && num < 64 && (p->syscall_mask & (1ULL << num)))
{
   if (!((num == SYS_exec || num == SYS_open) && (strncmp(path, p-                  >allowed_path, sizeof(p->allowed_path)) == 0)))
   {
     p->trapframe->a0 = -1;
     return;
   }
}
```

- 测评

```bash
./grade-lab-syscall sandbox_path
```

- 提交

```bash
git commit -am "syscall: interpose path whitelist"
```
