//
// Created by i300791 on 06.12.17.
//

#ifndef CUWR_BINARYTREE_H
#define CUWR_BINARYTREE_H

#include <stdbool.h>

typedef struct BST_struct BST;
typedef int BST_TYPE;

BST *BST_alloc();

bool BST_isEmpty(BST *bst);

void BST_init(BST *bst, BST_TYPE *tab, unsigned int tab_size);

void BST_free(BST *bst);

void BST_printInorder(BST *bst);

#endif //CUWR_BINARYTREE_H
