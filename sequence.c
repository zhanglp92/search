/*************************************************************************
	> File Name: sequence.c
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年03月18日 星期二 16时22分59秒
 ************************************************************************/

#include <stdio.h>

#define LIST_SIZE   5

/* 键和用户数据类型的结构体 */
typedef struct {
    int     key;
    char    other_data;
}RecordType;

/* 顺序链的结构 */
typedef struct {
    RecordType  r[LIST_SIZE+1];
    int     length;
}RecordList;
RecordList  list;

/* 创建一个链 */
void create_list (RecordList *l)
{
    int     i;
    for (i = 0; i < LIST_SIZE; i++) {
        printf ("(%d) input key and data : ", i+1);
        scanf ("%d %c", &(l->r[i].key), &(l->r[i].other_data)); 
        l->length++; 
    }
}

/* 查找 key 键 */
int seq_search (RecordList l, int key) 
{
    /* 将键值设置在链的末端 */
    l.r[l.length].key = key;
    int     i;
    
    /* 顺序查找 */
    for (i = 0; l.r[i].key != key; i++) ;
    return i;
}

int main (void)
{
    create_list (&list);
    int     i = seq_search (list, 4);

    i < list.length ? 
        printf ("key : %d, %c", list.r[i].key, list.r[i].other_data) :
        printf ("this key isn't exist!\n");

    return 0;
}
