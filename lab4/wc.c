#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <getopt.h>
#include <ctype.h>
#include "flist.h"
#include <string.h>
#include "args.h"

unsigned long c_count = 0;
unsigned long w_count = 0;
unsigned long l_count = 0;
char buff[256] = {0};

flist_t* word_count(char* fname) {
    FILE* file;
    flist_t* file_wc;
    short count = 0;
    short i;

    if (fname[0] == '-' && fname[1] == 0) {
        file = stdin;
    } else {
        file = fopen(fname, "r");
        if (!file) {
            printf("cannot open file \"%s\", errno: %d\n", fname, errno);
            exit(1);
        } 
    }

    file_wc = new_flist(fname);

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
    flist_t* head = NULL;
    flist_t* tail = NULL;
    flist_t* total = NULL;
    args_list_t* args = new_args_from_argv(argc, argv);
    short flags = 0;
    char* opts = "lwc";
    int opt = getopt(argc, argv, opts);    
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
        opt = getopt(argc, argv, opts);
    }

    print_args_list(args);
    if (argc == 1) {
        head = word_count("-");
        tail = head;

    } else {
        total = new_flist("total");
        for (int i = 1; i < argc; ++i ) {
            if (check_args_list(args, i)) continue;
            printf("%s %d\n", argv[i], i);
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
