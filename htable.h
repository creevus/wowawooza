

#ifndef HTABLE_H_
#define HTABLE_H_

#include <stdio.h>

typedef enum hashing_e {LINEAR_P, DOUBLE_H} hashing_t;
typedef struct htablerec *htable;

extern htable htable_new(int capacity,hashing_t hash);
extern int htable_insert(htable h,char *s);
extern int htable_search(htable h,char *s);
extern void htable_print(htable h, FILE *stream);
extern void htable_free(htable h);
extern void htable_print_stats(htable h, FILE *stream,int num_stats);
extern void htable_print_entire_table(htable h, FILE *stream);

#endif
