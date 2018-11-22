#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <getopt.h>
#include <ctype.h>
#include "list.h"
#include <string.h>

unsigned long c_count = 0;
unsigned long w_count = 0;
unsigned long l_count = 0;
char buff[256] = {0};

list_t* word_count(char* fname) {

    FILE* file;
    list_t* file_wc;
    short count = 0;
    short i;

    if (fname[0] == '-') {
        file = stdin;
    } else {
        file = fopen(fname, "r");
        if (!file) {
            printf("cannot open file \"%s\", errno: %d\n", fname, errno);
            exit(1);
        } 
    }

    file_wc = (list_t*)malloc(sizeof(list_t));
    file_wc->next = NULL;
    file_wc->fname = fname;
    file_wc->c = 0;
    file_wc->w = 0;
    file_wc->l = 0;

    count = 256;

    while(count == 256) {        
        count = fread(buff, sizeof(char), 256, file);
        file_wc->c += count;
        i = 1;
        while (i <= count) {
            while (isspace(buff[i]) && i <= count) {
                if (buff[i++] == 10) ++file_wc->l;
            }
            if (i > count) break;
            ++file_wc->w;
            while (!isspace(buff[i]) && i++ <= count);
        }
    }
   if (fname[0] != '-') fclose(file);
   return file_wc;
}
int main( int argc, char *argv[] ) {
    list_t* head = NULL;
    list_t* tail = NULL;
    list_t* total = malloc(sizeof(list_t));
    short flags = 0;
    int opt = getopt(argc, argv, "lwc");

    while (opt != -1) {
        switch (opt) {
            case 'l':
                flags = flags | 1;
                break;
            case 'w':
                flags = flags | 2;
                break;
            case 'c':
                flags = flags | 4;
                break;
        }
        opt = getopt( argc, argv, "lwc" );
    }

    if (argc == 1) {
        word_count("-");
    } else {
        total->next = NULL;
        total->c = 0;
        total->w = 0;
        total->l = 0;
        total->fname = "total";

        for (int i = 1; i < argc; ++i ) {
            if (argv[i][0] == '-' && argv[i][1] != 0) continue;
            if (!head) {
                head = word_count(argv[i]);
                tail = head;
            } else {
                tail->next = word_count(argv[i]);

                total->c += tail->c;
                total->w += tail->w;
                total->l += tail->l;

                tail = tail->next;
            }
        }
        total->c += tail->c;
        total->w += tail->w;
        total->l += tail->l;
    }

    if (tail != head) tail->next = total;
    print_list(head, flags);
        
    return 0;
}
