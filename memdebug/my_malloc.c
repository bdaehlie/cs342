#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/*
 * The total amount of allocated memory.
 */
#define     MEMORY_SIZE             100000


/*
 * A linked list of chunks of available memory.
 * Note that all the memory (e.g. the begin pointers) are
 * allocated out of a single contiguous block of memory.
 */
struct memory {
    struct memory *next;    /* Next chunk of memory */
    int     bytes_used,     /* Num currently used bytes, or -1 if it is free */
            bytes_max,      /* Max num bytes that can be used in this chunk */
            line_num;       /* The line number which allocated the memory */
    char    *begin,         /* Beginning of the chunk (starts with padding) */
            *ubegin;        /* Usable beginning (after padding). */
};


/*
 * Number of bytes of padding before and after memory.
 */
#define     PADDING_SIZE            256


/*
 * The byte to be used for all padding segments.
 */
#define     PADDING_BYTE            0x55


/*
 * Four sizes for memory chunks.
 */
static int CHUNK_SIZES[] = { 1024, 2048, 4096, 8192 };

/*
 * Size of previous array.
 */
#define NUM_CHUNK_SIZES     4



/*
 * The root of the linked list of memory chunks.
 */
static struct memory *first_chunk = NULL;


/*
 * The single block of memory allocated and available.
 * Note: this will be the same as first_chunk->beg.
 */
static char *block = NULL;


static struct memory *create_chunk(char *begin, int bytes);


void xinit() {
    struct memory *last_chunk = NULL;
    char *upper_limit;
    char *cp;
    int  i;

    block = malloc(MEMORY_SIZE);
    upper_limit = block;
    cp = block;

    for (i = 0; i < NUM_CHUNK_SIZES; i++) {
        int chunk_size = CHUNK_SIZES[i];
        upper_limit += MEMORY_SIZE / 4;

        while (cp + chunk_size <= upper_limit) {
            struct memory *chunk = create_chunk(cp, chunk_size);
            if (first_chunk == NULL) {
                first_chunk = chunk;
            } else {
                last_chunk->next = chunk;
            }
            last_chunk = chunk;
            cp += chunk_size;
        }
    }
}

void xshutdown() {
    free(block);
    block = NULL;

    struct memory *this = first_chunk,
                  *next;

    while (this != NULL) {
        next = this->next;
        free(this);
        this = next;
    }
    first_chunk = NULL;
}


void *_xmalloc(int nbytes, int line_num) {
}


void _xfree(void *vp, int line_num) {
}


int xdebug() {
}


static struct memory *create_chunk(char *begin, int bytes) {
    char            *cp;
    struct memory   *mp = malloc(sizeof(struct memory));

    mp->bytes_used = -1;
    mp->line_num = 0;
    mp->bytes_max = bytes - 2 * PADDING_SIZE;
    mp->next = NULL;
    mp->begin = begin;
    mp->ubegin = begin + PADDING_SIZE;

    for (cp = mp->begin; cp < mp->ubegin; cp++) {
        *cp = PADDING_BYTE;
    }

    return mp;
}
