#ifndef _header
#define _header

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct Node {
  void * data;
  struct Node * next;
};

struct Performance {
  unsigned int reads;
  unsigned int writes;
  unsigned int mallocs;
  unsigned int frees;
};

// basic functions
void readHead( struct Performance * performance, struct Node ** list_ptr, void * dest, unsigned int width );
void push( struct Performance * performance, struct Node ** list_ptr, void * src, unsigned int width );
void pop( struct Performance * performance, struct Node ** list_ptr, void * dest, unsigned int width );
struct Node ** next( struct Performance * performance, struct Node ** list_ptr );
int isEmpty( struct Performance * performance, struct Node ** list_ptr );
void copy_data( void * source, void * destination, int width );
struct Performance * newPerformance();

// derived functions
void insertItem( struct Performance * performance, struct Node ** list_ptr, unsigned int index, void * src, unsigned int width );
void readItem( struct Performance * performance, struct Node ** list_ptr, unsigned int index, void * dest, unsigned int width );
void prependItem( struct Performance * performance, struct Node ** list_ptr, void *src, unsigned int width );
void appendItem( struct Performance * performance, struct Node ** list_ptr, void * src, unsigned int width );
void deleteItem( struct Performance * performance, struct Node ** list_ptr, unsigned int index );
void freeList( struct Performance * performance, struct Node ** list_ptr );

int findItem( struct Performance * performance, struct Node ** list_ptr, int (*compar)(const void *, const void * ), void * target, unsigned int width );

#endif