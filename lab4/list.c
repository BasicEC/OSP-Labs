#include "list.h"
#include <stdio.h>

char* format_s3 = "%15lu %15lu %15lu  %s\n";
char* format_s2 = "%15lu %15lu  %s\n";
char* format_s1 = "%15lu  %s\n";

void print_list(list_t* head, short flags) {
    if (!head) return;
    //sorry
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
    print_list(head->next, flags);
}