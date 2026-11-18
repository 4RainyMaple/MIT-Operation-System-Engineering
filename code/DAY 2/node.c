// 结构体指针练习

#include<string.h>

struct Node{
    int pid;
    char name [16];
    struct Node * next;
};

struct Node * push_front(struct Node *head, int pid, const char *name)
{
    struct Node * node = malloc(sizeof(struct Node));
    if ( node == 0 )
        return 0;
    node->next = head;
    node->pid = pid;
    strcpy(node->name, name);   // 不能数组整体赋值
    return node;
}

struct Node *find(struct Node *head, int pid)
{
    struct Node * cur = head;
    while ( cur != 0 )
    {
        if ( cur->pid == pid )
            return cur;
        cur = cur->next;
    }
    return 0;
}

struct Node *remove_node(struct Node *head, int pid)
{
    struct Node dummy;  // 这里哨兵没有必要用结构体
    dummy.next = head;
    struct Node * cur = &dummy;

    while ( cur->next != 0 )    // 如果下一个为空就不需要检查了
    {
        if ( cur->next->pid == pid )
        {
            struct Node * tmp = cur->next;
            cur->next = tmp->next;
            free(tmp);
            break;
        }
        cur = cur->next;
    }
    return dummy.next;
}

void print_list(struct Node * head)
{
    struct Node * cur = head;
    while ( cur != 0 )
    {
        printf("pid = %d name = %s\n", cur->pid, cur->name);
        cur = cur->next;
    }
}

void free_list(struct Node * head)
{
    struct Node * cur = head;
    while ( cur != 0 )
    {
        struct Node * tmp = cur->next;
        free(cur);
        cur = tmp;
    }
}