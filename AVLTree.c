/*************************************************************************
	> File Name: AVLTree.c
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2014年03月19日 星期三 17时06分36秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct _record_type {

    int     key;
    char    other_data;
};

/* 平衡二叉树的节点 */
typedef struct _AVLTNODE {

    struct _record_type data;
    /* 平衡因子 */
    unsigned char   bf;
    struct _AVLTNODE    *LChild;
    struct _AVLTNODE    *RChild;
}AVLTNode, *AVLTree;

void AVLTPrint (const AVLTree root, int n); 
#define AVLT_print(root) \
    system ("clear"); \
    AVLTPrint (root, 0);

void AVLTPrint (const AVLTree root, int n) 
{
    if (!root) return ;
    AVLTPrint (root->RChild, n+1);
    int     i;
    for (i = 0; i < n; i++) 
        printf ("    ");
    printf ("%d\n", root->data.key);
    AVLTPrint (root->LChild, n+1); 
}

/* 平衡二叉树插入节点 */
void ins_AVLTree (AVLTree *avlt, int key)
{
    /* 初始化一个新节点 */
    AVLTNode    *S = (AVLTree)malloc (sizeof (AVLTNode));
    S->data.key = key;
    S->LChild = S->RChild = NULL;
    S->bf = 0;

    /* 插入 */
    if (!*avlt) 
        *avlt = S;
    else {
        /* 首先查找S的插入位置fp，同时记录距S的插入位置最近且
         * 平衡因子不等于0（等于-1或1）的节点A, A可能为失衡节点 */
        AVLTNode *A = *avlt, *FA = NULL;
        AVLTNode *p = *avlt, *fp = NULL;

        while (p) {
            if (p->bf) {
                A = p; 
                FA = fp;
            }
            fp = p;

            if (key < p->data.key) 
                p = p->LChild;
            else 
                p = p->RChild;
        }

        /* 插入S */
        if (key < fp->data.key) 
            fp->LChild = S; 
        else if (key > fp->data.key)
            fp->RChild = S; 
        else {
            free (S);
            return;
        }

        /* 确定节点B，并修改A的平衡因子 */ 
        AVLTNode    *B; 
        if (key < A->data.key) { 
            B = A->LChild; 
            A->bf += 1; 
        }else { 
            B = A->RChild; 
            A->bf -= 1; 
        }

        /* 修改B到S路径上各节点的平衡因子 */
        p = B; 
        while (p != S) { 
            if (key < p->data.key) { 
                p->bf = 1; 
                p = p->LChild; 
            }else { 
                p->bf = -1; 
                p = p->RChild; 
            }
        } 

        /* 判断失衡类型并做相应处理 */
        /* LL型 */
        if (2 == A->bf && 1 == B->bf) {
            /* A做一次顺时针旋转 */
            B = A->LChild;
            A->LChild = B->RChild;
            B->RChild = A;
            A->bf = B->bf = 0; 

            if (!FA) 
                *avlt = B;
            else if (A == FA->LChild)
                FA->LChild = B;
            else 
                FA->RChild = B;
        } /* LR型 */
        else if (2 == A->bf && -1 == B->bf) {
            AVLTNode *C;
            /* 先对B做一次逆时针旋转，再对A做一次顺时针旋转 */
            B = A->LChild;
            C = B->RChild;
            B->RChild = C->LChild;
            A->LChild = C->RChild;
            C->LChild = B;
            C->RChild = A;

            if (S->data.key < C->data.key) {
                A->bf = -1; B->bf = C->bf = 0;
            }else if (S->data.key > C->data.key) {
                B->bf = 1; A->bf = C->bf = 0;
            }else 
                A->bf = B->bf = 0; 

            if (!FA) 
                *avlt = S;
            else if (A == FA->LChild) 
                FA->LChild = C;
            else 
                FA->RChild = C;
        } /* RL型 */
        else if (-2 == A->bf && 1 == B->bf) {
            AVLTNode *C;
            /* 先对B做一次顺时针旋转，再对A做一次逆时针旋转 */ 
            B = A->RChild;
            C = B->LChild;
            B->LChild = C->RChild;
            A->RChild = C->LChild;
            C->LChild = A;
            C->RChild = B;

            if (S->data.key < C->data.key) {
                B->bf = -1; A->bf = C->bf = 0;
            }else if (S->data.key > C->data.key) {
                A->bf = 1; B->bf = C->bf = 0;
            }else 
                A->bf = B->bf = 0;

            if (!FA) 
                *avlt = S;
            else if (A == FA->LChild) 
                FA->LChild = C;
            else 
                FA->RChild = C;
        } /* RR 型 */
        else if (-2 == A->bf && -1 == B->bf) {
            /* 对A做一次逆时针旋转 */
            B = A->RChild;
            A->RChild = B->LChild;
            B->LChild = A;
            A->bf = B->bf = 0;

            if (!FA) 
                *avlt = B;
            else if (A == FA->LChild) 
                FA->LChild = B;
            else 
                FA->RChild = B;
        }
    }
}

void AVLT_create (AVLTree *avl)
{
    int     key;
    while (scanf ("%d", &key) && key != -1) {
        ins_AVLTree (avl, key);
        AVLT_print (*avl);
    }
}

void AVLT_destroy (AVLTree *avl) 
{
    if (!*avl) return;
    AVLT_destroy (&((*avl)->LChild));
    AVLT_destroy (&((*avl)->RChild));
    free (*avl);
    *avl = NULL;
}

int main (void)
{
    AVLTree     avl = NULL;

    AVLT_create (&avl);

    AVLT_destroy (&avl);
    return 0;
}
