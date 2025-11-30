#include <stdio.h>
#include <stdlib.h>

/* ==================== Data Structures ==================== */

#define  TFOBJ_TYPE_INT 0
#define  TFOBJ_TYPE_STR 1
#define  TFOBJ_TYPE_BOOL 2
#define  TFOBJ_TYPE_LIST 3
#define  TFOBJ_TYPE_SYMBOL 4

// tfobj is the struct of the forth objects
// it has a referent count and a type
typedef struct tfobj {
    int refcount;
    int type;   // TFOBJ_TYPE_*
    union {
        int i;  // 'i' is used as an integer or a boolean
        struct {    // 'str' is used as a string or a symbol
            char *ptr;
            size_t len;
        } str;
        struct {
            struct tfobj **elements;
            size_t len;
        } list;
    };
} tfobj;

typedef struct tfparser {
    char *prg;  // The program to compile into a list
    char *p;    // Next token to parse
} tfparser;

// tfctx is the context of execution
typedef struct tfctx {
    tfobj *stack;
} tfctx;

/* ==================== Allocation Wrappers ==================== */

void *xmalloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Out of memory allocating %zu bytes\n", size);
        exit(1);
    }
    return ptr;
}

/* ==================== Object Related Functions ====================
 * The following functions allocate Toy Foth objects of different types */

// Allocate and initialize a new Toy Forth object
tfobj *createObject(int type) {
    tfobj *o = xmalloc(sizeof(tfobj));
        o->type = type;
        o->refcount = 1;
    return o;
}

tfobj *createStringObject(char *s, size_t len) {
    tfobj *o = createObject(TFOBJ_TYPE_STR);
    o->str.ptr = s;
    o->str.len = len;
    return o;
}

tfobj *createSymbolObject(char *s, size_t len) {
    tfobj *o = createStringObject(s, len);
    o->type = TFOBJ_TYPE_SYMBOL;
    return o;
}

tfobj *createIntObject(int i) {
    tfobj *o = createObject(TFOBJ_TYPE_INT);
    o->i = i;
    return o;
}

tfobj *createBoolObject(int i) {
    tfobj *o = createObject(TFOBJ_TYPE_BOOL);
    o->i = i;
    return o;
}

tfobj *createListObject(int i) {
    tfobj *o = createObject(TFOBJ_TYPE_LIST);
    o->list.elements = NULL;
    o->list.len = 0;
    return o;
}

/* ==================== Main ==================== */

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // tfobj *prg = compile(prgtext);
    // exec(prgtext);

    return 0;
}