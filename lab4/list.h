#ifndef __LIST__
#define __LIST__

typedef struct list_t {
    struct list_t* next;
    unsigned long c;
    unsigned long w;
    unsigned long l;
    char* fname;
} list_t;

void print_list(list_t* head, short flags);

#endif