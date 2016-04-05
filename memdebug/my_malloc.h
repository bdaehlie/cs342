/*
 * Header file 
 */

void xinit();
void xshutdown();

#define xmalloc(n)  _xmalloc(n, __LINE__)
#define xfree(vp)  _xfree(vp, __LINE__)

void *_xmalloc(int nbytes, int line_num);
void _xfree(void *vp, int line_num);

int xdebug();
