/**Main File**/
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mylib.h"
#include "htable.h"
#include "tree.h"

#define DEFAULT_TABLE_SIZE 113

static int first_prime(int i) {
    int j = i;
    int temp;
    int k;

    if (j == 1 || j == 2) {
        return j;
    }
    for (;;) {
        temp = j;
        for (k = 2; k < j; k++) {
            if (j % k == 0) {
                j++;
                break;
            }
        }
        if (temp == j) {
            return j; 
        }
    }
}

static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

static void print_help(){
}

int main(int argc, char **argv){
    
    hashing_t method = LINEAR_P;
    tree_t treetype = BST;
    int table_size  = DEFAULT_TABLE_SIZE;
    int treeoption = 0;
    int hash= 1;
    int spellcheck = 0;
    int contents = 0;
    int treedot = 0;
    int tablesize = 0;
    int freq_words = 1;
    int print_stats = 0;
    int snapshots = 0;
    clock_t start, end;
    double fill_time = 0.0;
    double search_time = 0.0;
    htable h = NULL;
    tree t = NULL;
    int num_stats = 0;
    char word[256];
    char filename[256];
    FILE *file;
    FILE *dot;
    int unknown_word_count = 0;
    int x = 0;
    

    const char *optstring = "Tc:deoprs:t:h";
    char option;
    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'T':
                treeoption = 1;
                t = tree_new(treetype);
                hash = 0;
                break;
            case 'c':
                strcpy(filename, optarg);
                spellcheck = 1;
                freq_words = 0;
                break;
            case 'd':
                method = DOUBLE_H;
                break;
            case 'e':
                contents = 1;
                
                break;
            case 'o':
                treedot = 1;
                break;
            case 'p':
                print_stats = 1;
                freq_words = 0;
                break;
            case 'r':
                treetype = RBT;
                break;
            case 's':
                if(print_stats == 1){
                    snapshots = 1;
                    num_stats = atoi(optarg);
                }
                break;
            case 't':
                table_size = first_prime(atoi(optarg));
                break;
            case 'h':
                print_help();
                exit(EXIT_SUCCESS);
                break;
            default:
                print_help();
                exit(EXIT_SUCCESS);
                break;
        }
    }
   
   
    if(hash == 1){
        h = htable_new(table_size, method);
    }

    while (getword(word, sizeof word, stdin) != EOF) {
       
        if(hash == 1){
            htable_insert(h, word);
        }
        if(treeoption == 1){
            tree_insert(t,word);
        }
       
    }
    
    if(contents == 1){
        htable_print_entire_table(h,stderr);
    }
    
    if(freq_words == 1 && hash == 1){
        htable_print(h,stdout);
        
    }
    
    if(freq_words == 1 && treeoption == 1){
        tree_preorder(t, print_info);
    }
    
    if(treedot == 1){
        tree_output_dot(t,dot);
    }
    if(print_stats == 1){
        htable_print_stats(h, stdout, table_size);
    }
    if(snapshots == 1){
        htable_print_stats(h,stdout, table_size);
    }

    /*  if(spellcheck = 1){
        file = fopen(filename, "r");

        while (getword(word, sizeof word, file) != EOF) {
            start = clock();

            if (htable_search(h, word) == 0) {
                fprintf(stderr, "%s\n", word);
                unknown_word_count++;
                    
            }
            end = clock();
            search_time += (clock() - start) / (double) CLOCKS_PER_SEC;
        } 
        printf("Fill time     : %f\n", fill_time);
        printf("Search time   : %f\n", search_time);
        printf("Unknown words = %d\n", unknown_word_count);
        }*/

    
    tree_free(t);            
    htable_free(h);
             
    return EXIT_SUCCESS;

    
}
    

                
                
                
            
            
                    
                

