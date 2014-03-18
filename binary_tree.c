/*************************************************************************
	> File Name: binary_tree.c
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年03月18日 星期二 16时22分59秒
 ************************************************************************/

#include <stdio.h> 
#include <stdlib.h>

/* 键和用户数据类型的结构体 */ 
typedef struct {
    int     key;
    char    other_data; 
}RecordType; 

/* 顺序链的结构 */
typedef struct _node {
    RecordType  data;
    struct _node    *LChild;
    struct _node    *RChild;
}BSTNode, *BSTree;

void BSTPrint (const BSTree root, int n); 
#define BST_print(root) \
    system ("clear"); \
    BSTPrint (root, 0);

/* 二叉排序树插入结点 */
void insert_BST (BSTree *root, int key)
{
    if (!*root) {
        BSTNode *s = (BSTree)malloc (sizeof (BSTNode));
        s->data.key = key;
        s->LChild = s->RChild = NULL;
        *root = s;
    }else if (key < (*root)->data.key) 
        insert_BST (&((*root)->LChild), key);
    else if (key > (*root)->data.key) 
        insert_BST (&((*root)->RChild), key);
}

/* 创建二叉排序树 */
void create_BST (BSTree *root)
{
    *root = NULL;

    int     key, i;
    for (i = 0; i < 10; i++) {
        key = random () % 10;
        insert_BST (root, key); 
    }

/*
    while (scanf ("%d", &key) && key != -1) {
        insert_BST (root, key); 
        BST_print (*root);
    }
    */
}

/* 二叉排序树的查找 */
BSTree BST_search (const BSTree root, int key) 
{
    if (!root) return NULL; 
    else if (root->data.key == key) 
        return root; 
    else if (key < root->data.key) 
        return BST_search (root->LChild, key); 
    else 
        return BST_search (root->RChild, key); 
}

/* 销毁二叉排序树 */
void BST_destroy (BSTree *root)
{
    if (!*root) return;
    BST_destroy (&(*root)->LChild);
    BST_destroy (&(*root)->RChild);
    free (*root);
    *root = NULL;
}

void BSTPrint (const BSTree root, int n) 
{
    if (!root) return ;
    BSTPrint (root->RChild, n+1);
    int     i;
    for (i = 0; i < n; i++) 
        printf ("    ");
    printf ("%d\n", root->data.key);
    BSTPrint (root->LChild, n+1); 
}

int main (void)
{
    BSTree  root;
    create_BST (&root);
    BST_print (root);

    BSTree  node = BST_search (root, 5);
    node ? 
        printf ("find : key = %d\n", node->data.key) :
        printf ("haven't find!\n"); 

    BST_destroy (&root);
    return 0;
}
