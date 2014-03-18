/*************************************************************************
	> File Name: block.c
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年03月18日 星期二 16时22分59秒
 ************************************************************************/

#include <stdio.h>

#define LIST_SIZE   21
#define BLOCK_SIZE  5

/* 键和用户数据类型的结构体 */
typedef struct {
    int     key;
    char    other_data;
}RecordType;

/* 顺序链的结构 */
typedef struct {
    RecordType  r[LIST_SIZE+1];
    int     list_s;
    int     list_e;
    int     length;
}RecordList;
RecordList  list;

/* 分块查找时，块的结构 */
typedef struct _BLOCK {
    int     addr;
    int     max_key;
}BlockType;

#define BlockList(n, b_l, name) \
    struct { \
        BlockType   r[n]; \
        int     block_length; \
        int     length; \
    }block_list ##name = {{0}, (b_l/n + (b_l%n ? 1 : 0)), n};
    


/* 创建一个链 */
void create_list (RecordList *l)
{
    int     i;
    for (i = 0; i < LIST_SIZE; i++) {
    //    printf ("(%d) input key and data : ", i+1);
    //    scanf ("%d %c", &(l->r[i].key), &(l->r[i].other_data)); 
        l->r[i].key = i+1;
        l->r[i].other_data = 'A' + 1;
        l->length++; 
    }

    l->list_s = 0;
    l->list_e = l->length;
}

/* 查找 key 键 */
int seq_search (RecordList l, int key) 
{
    /* 将键值设置在链的末端 */
    l.r[l.list_e].key = key;
    int     i;
    
    /* 顺序查找 */
    for (i = l.list_s; l.r[i].key != key; i++) ;
    return i;
}

int block_search (RecordList l, int key)
{
    BlockList (BLOCK_SIZE, l.length, 1); 

    int     i; 
    for (i = 0; i < block_list1.length; i++) {
        block_list1.r[i].addr = i * block_list1.block_length;
        block_list1.r[i].max_key = l.r[i*5].key;
    }

    for (i = 0; i < l.length; i++) 
        if (block_list1.r[i/5].max_key < l.r[i].key)
            block_list1.r[i/5].max_key = l.r[i].key;
    
    for (i = 0; i < block_list1.length; i++) {
        if (key < block_list1.r[i].max_key) {
            l.list_s = block_list1.r[i].addr;
            l.list_e = (i == block_list1.length-1 ? 
                        l.length : block_list1.r[i+1].addr-1);
            return seq_search (l, key);
        }
    }

    return l.length;
}

int main (void)
{
    create_list (&list);

    int     i = block_search (list, 4);

    i < list.length ? 
        printf ("key : %d, %c\n", list.r[i].key, list.r[i].other_data) :
        printf ("this key isn't exist!\n");

    return 0;
}
