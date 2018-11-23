#ifndef __FLIST__
#define __FLIST__

typedef struct flist_t {
    struct flist_t* next;
    unsigned long c;
    unsigned long w;
    unsigned long l;
    char* fname;
} flist_t;

void print_list(flist_t* head, short flags);
flist_t* new_flist(char* fname);

#endif