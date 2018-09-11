
#ifndef TREE_H_
#define TREE_H_

#include <stdio.h> 

typedef struct treenode *tree;
typedef enum tree_e {BST,RBT} tree_t;
typedef enum colour_e {RED,BLACK} colour_t;

extern tree tree_new(tree_t tree_typ);
extern tree tree_insert(tree t,char *s);
extern int tree_search(tree t,char *s);
extern void tree_inorder(tree t,void f(char *s));
extern void tree_preorder(tree t,void f(int freq, char *s));
extern tree tree_remove(tree t,char *s);
extern tree tree_free(tree t);
extern void tree_output_dot(tree t, FILE *out);
extern int tree_depth(tree t);

#endif
