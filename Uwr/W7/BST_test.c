//
// Created by i300791 on 06.12.17.
//

#include "BinaryTree.h"
#include <stdio.h>

int main() {
    int t1[] = {2, 5, 3, 7, 8, 9, 12};
    /*    .----2----.
     * .--5--.   .--3--.
     * 7     8   9     12
     */
    int t2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    /*         .-----1-----.
     *     .---2---.   .---3---.
     *  .--4--. .--5   6       7
     *  8     9 10
     */

    int t3[] = {1, 2, 3, -4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, -15};
    /*         .-----1-----.
     *         2-.       .-3----.
     *         .-5-.   .-6-.  .-7
     *         10  11  12  13 14
     *
     */

    BST *bst1 = BST_alloc();
    BST *bst2 = BST_alloc();
    BST *bst3 = BST_alloc();

    BST_init(bst1, t1, 7);
    BST_init(bst2, t2, 10);
    BST_init(bst3, t3, 15);

    BST_printInorder(bst1);
    printf("\n");
    BST_printInorder(bst2);
    printf("\n");
    BST_printInorder(bst3);
    printf("\n");

    BST_free(bst1);
    BST_free(bst2);
    BST_free(bst3);
    return 0;
}