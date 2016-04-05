#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "my_malloc.h"


char *me;

static void usage();
static void out_of_mem(void);
static void detect_leaks(void);
static void detect_bad_free(void);
static void detect_buffer_overflow(void);

int main(int argc, char **argv) {
    me = argv[0];

    if (argc != 2) {
        usage();
    }
    
    if (strcmp("out_of_mem", argv[1]) == 0) {
        out_of_mem();
    } else if (strcmp("leaks", argv[1]) == 0) {
        detect_leaks();
    } else if (strcmp("bad_free", argv[1]) == 0) {
        detect_bad_free();
    } else if (strcmp("buffer_overflow", argv[1]) == 0) {
        detect_buffer_overflow();
    } else {
        fprintf(stderr, "unknown mode: '%s'\n", argv[1]);
        usage();
    }

    return 0;
}


static void usage() {
    fprintf(stderr, "usage: %s {out_of_mem|leaks|bad_free|buffer_overflow}\n", me);
    exit(1);
}


static void out_of_mem(void) {
    int     i;

    xinit(100000);

    for (i = 0; i < 100000; i++) {
        void *vp = xmalloc(100);
        if (vp == NULL) {
            printf("vp was null at %d (should have been 45)\n", i);
            break;
        }
    }

    xshutdown();

    xinit(100000);

    void *vp1 = xmalloc(0);
    void *vp2 = xmalloc(100);
    void *vp3 = xmalloc(1000);
    void *vp4 = xmalloc(7681);
    void *vp5 = xmalloc(10000);
    printf("vps are %p %p %p %p %p (last two should be 0x0)\n", vp1, vp2, vp3, vp4, vp5);

    xshutdown();
}

static void detect_leaks(void) {
    char *cp1[1],
         *cp2[2],
         *cp3[3];
    int  i,
         l1,
         l2,
         l3;

    xinit(100000);

    for (i = 0; i < 1; i++) {
        l1 = __LINE__ + 1;
        cp1[i] = xmalloc(1);
    }
    for (i = 0; i < 2; i++) {
        l2 = __LINE__ + 1;
        cp2[i] = xmalloc(2);
    }
    for (i = 0; i < 3; i++) {
        l3 = __LINE__ + 1;
        cp3[i] = xmalloc(3);
    }
    xfree(cp1[0]);
    xfree(cp2[0]);
    xfree(cp3[0]);

    printf("the following debug should show:\n");
    printf("\t1 unfreed 2 byte segment at line %d\n", l2);
    printf("\t2 unfreed 3 byte segments at line %d\n", l3);
    int r = xdebug();
    printf("result was %d, should be 3\n", r);

    xshutdown();
    
}

static void detect_bad_free(void) {
    char *cp1,
         *cp2,
         *cp3;

    xinit(100000);

    cp1 = xmalloc(5);
    cp2 = xmalloc(5);
    cp3 = xmalloc(5);

    printf("This free should work...\n");
    xfree(cp1);
    printf("This free should also work...\n");
    xfree(cp2);

    printf("This free should fail at line %d...\n", __LINE__+1);
    xfree(cp3+1);

    xshutdown();
    
}

static void detect_buffer_overflow(void) {
    char *cp1,
         *cp2,
         *cp3;
    int l;

    xinit(100000);

    cp1 = xmalloc(5);
    cp2 = xmalloc(5);
    cp3 = xmalloc(5);   l = __LINE__;

    printf("These first few frees should be fine...\n");
    strcpy(cp1, "foo");
    strcpy(cp2, "bar");
    xfree(cp1);
    xfree(cp2);

    printf("We will now overflow the memory allocated at line %d.\n", l);
    strcpy(cp3, "foobar");
    xfree(cp3);

    xshutdown();
    
}
