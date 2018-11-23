#ifndef __ARGS__
#define __ARGS__

typedef struct args_list_t {
    int index;
    struct args_list_t* next;
} args_list_t;

args_list_t* new_args();
args_list_t* add_arg(args_list_t* list, int index);
args_list_t* new_args_from_argv(int argc, char** argv);
int check_args_list(args_list_t* list, int index);
void print_args_list(args_list_t* list);
#endif
