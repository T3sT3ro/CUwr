//
// Created by i300791 on 06.12.17.
//

#include <malloc.h>
#include "BinaryTree.h"

typedef struct node_struct node__;

struct node_struct {
    BST_TYPE value;
    node__ *left;
    node__ *right;
};

struct BST_struct {
    unsigned int size;
    node__ *root__;
};

BST *BST_alloc() {
    BST *bst = malloc(sizeof(BST));
    bst->root__ = NULL;
    bst->size = 0;
    return bst;
}

bool BST_isEmpty(BST *bst) {
    return bst->size == 0;
}

void init_recurent__(BST_TYPE *tab, unsigned int tab_size, unsigned int index, node__ *current) {

    current->value = tab[index];

    if (index * 2 + 1 < tab_size && tab[index * 2 + 1] > 0) {
        current->left = malloc(sizeof(node__));
        current->left->left = NULL;
        current->left->right = NULL;
        init_recurent__(tab, tab_size, index * 2 + 1, current->left);
    }
    if (index * 2 + 2 < tab_size && tab[index * 2 + 2] > 0) {
        current->right = malloc(sizeof(node__));
        current->right->left = NULL;
        current->right->right = NULL;
        init_recurent__(tab, tab_size, index * 2 + 2, current->right);
    }
}

void BST_init(BST *bst, BST_TYPE *tab, unsigned int tab_size) {
    if (tab[0] < 0 || tab_size < 1) // puste drzewo na wejsciu
        return;

    if(bst->root__ == NULL)
        bst->root__ = malloc(sizeof(node__));
    bst->root__->left = NULL;
    bst->root__->right = NULL;
    init_recurent__(tab, tab_size, 0, bst->root__);

}

void BST_free(BST *bst) {
    free(bst);
}

void printInorder_recurrent_(node__ *current) {
    if(current->left != NULL)
        printInorder_recurrent_(current->left);
    printf("%d ", current->value);
    if(current->right != NULL)
        printInorder_recurrent_(current->right);
}

void BST_printInorder(BST *bst) {
    if (bst->root__ != NULL)
        printInorder_recurrent_(bst->root__);
}
