#include "args.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char opt_end[] = "--";

args_list_t* new_args() {
    args_list_t* args =(args_list_t*)malloc(sizeof(args_list_t));
    args->next = NULL;
    args->index = 0;
    return args;
}

int check_args_list(args_list_t* list, int index) {    
    while (list != NULL) {
        if (list->index == index) {
            return 1;
        } else {
            list = list->next;
        }
    }
    return 0;
}

args_list_t* add_arg(args_list_t* list, int index) {
    args_list_t* new_head = new_args();
    new_head->index = index;
    new_head->next = list;
    return new_head;
}

args_list_t* new_args_from_argv(int argc, char** argv) {
    int i = 1;
    args_list_t* list = NULL;
    do {
        if (argv[i][0] == '-' && argv[i][0] != 0) list = add_arg(list, i);
        else break;
    } while (i+1 < argc && strcmp(argv[i++], "--"));

    return list;
}

void print_args_list(args_list_t* list) {
    if (list == NULL) printf("List:NULL\n");
    while (list != NULL) {
        printf("%d\n", list->index);
        list = list->next;
    }
}
