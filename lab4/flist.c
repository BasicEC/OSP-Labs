#include "flist.h"
#include <stdio.h>
#include <stdlib.h>

char* format_s3 = "%15lu %15lu %15lu  %s\n";
char* format_s2 = "%15lu %15lu  %s\n";
char* format_s1 = "%15lu  %s\n";

void print_list(flist_t* head, short flags) {
    do {
        switch (flags) {
        case 0:
        case 7:
            printf(format_s3, head->l, head->w, head->c, head->fname);
            break;
        case 1:
            printf(format_s1, head->l, head->fname);
            break;
        case 2:
            printf(format_s1, head->w, head->fname);
            break;
        case 3:
            printf(format_s2, head->l, head->w, head->fname);
            break;
        case 4:
            printf(format_s1, head->c, head->fname);
            break;
        case 5:
            printf(format_s2, head->l, head->c, head->fname);
            break;
        case 6:
            printf(format_s2, head->w, head->c, head->fname);
            break;
        }
        head = head->next;
    } while (head != NULL);
}

flist_t* new_flist(char* fname) {
    flist_t* head = malloc(sizeof(flist_t));
    head->next = NULL;
    head->c = 0;
    head->w = 0;
    head->l = 0;
    head->fname = fname;
    return head;
}