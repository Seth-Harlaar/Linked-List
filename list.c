#include "list.h"

// ************ basic functions *******************

// create a new performance struct
struct Performance * newPerformance(){
  struct Performance * newPerformance = malloc( sizeof( struct Performance ) );

  // check if not null  
  if( newPerformance != NULL ){
    newPerformance->reads = 0;
    newPerformance->writes  = 0;
    newPerformance->mallocs  = 0;
    newPerformance->frees = 0;
    
    return newPerformance;  
  } else {
    fprintf( stderr, "Error mallocing new Performance Structure" );
    exit(0);
  }
  
}

// support function to copy data to the location specified 
void copy_data( void * source, void * destination, int width ){
  int i;
  char * src = src;
  char * dest = destination;

  for( i = 0; i < width; i++ ){
    *dest = *src;
    src++;
    dest++;
  }
}


// push a new node to the front of the linked list
void push( struct Performance * performance, struct Node ** list_ptr, void * src, unsigned int width ){

  struct Node * new_node = malloc( sizeof( struct Node ) );

  if( new_node == NULL ){
    fprintf( stderr, "Error mallocing a new node \n" );
    exit(0);
  }

  new_node->data = malloc( width );
  if( new_node->data == NULL ){
    fprintf(stderr, "Error mallocing data for a new node \n" );
    exit(0);
  }
  
  copy_data( src, new_node->data, width );

  new_node->next = *list_ptr;
  *list_ptr = new_node;

  performance->mallocs++;
  performance->writes++;
}

// read the data from the first node and copy it into dest
void readHead( struct Performance * performance, struct Node ** list_ptr, void * dest, unsigned int width ){
  
  if( *list_ptr == NULL ){
    fprintf( stderr, "readHead - ERROR, list is empty" );
    exit(0);
  }
  copy_data( (*list_ptr)->data, dest, width);

  performance->reads++;
}

// remove the first node in the list, and copy the data into destination
void pop( struct Performance * performance, struct Node ** list_ptr, void * dest, unsigned int width ){
  
  if( *list_ptr == NULL ){
    fprintf( stderr, "pop - ERROR, list is empty" );
    exit(0);
  }
  struct Node * old_head = *list_ptr;

  copy_data( (*list_ptr)->data, dest, width );

  *list_ptr = old_head->next;

  free( old_head->data );
  free( old_head );

  performance->frees++;
  performance->reads++;
}

// return the adress of the node next in line to the one pointed to by list_ptr
struct Node ** next( struct Performance * performance, struct Node ** list_ptr ){

  if( *list_ptr == NULL ){
    fprintf( stderr, "next - ERROR, list is empty\n" );
    exit(0);
  }

  performance->reads++;

  return &( (*list_ptr)->next );
}

// check if the list is empty
int isEmpty( struct Performance * performance, struct Node ** list_ptr ){

  if( *list_ptr == NULL ){
    return 1;
  }
  return 0;
}



// ************ derived functions *******************

// free the entire list
void freeList( struct Performance * performance, struct Node ** list_ptr ){

  while( *list_ptr != NULL ){
    pop( performance, list_ptr, NULL, 0 );
  }
}

// read a specific item at index from list
void readItem( struct Performance * performance, struct Node ** list_ptr, unsigned int index, void * dest, unsigned int width ){
  int i;  

  for ( i = 0; i < index; i++){
    list_ptr = next( performance, list_ptr );
  }
  
  readHead( performance, list_ptr, dest, width );

}

// add an item to the end of the list
void appendItem( struct Performance * performance, struct Node ** list_ptr, void * src, unsigned int width ){

  struct Node ** temp_list = list_ptr;

  while( isEmpty( performance, temp_list ) != 1 ){
    temp_list = next( performance, temp_list );
  }

  push( performance, temp_list, src, width );
}

// insert an item at an index
void insertItem( struct Performance * performance, struct Node ** list_ptr, unsigned int index, void * src, unsigned int width ){
  int i;  

  if( index == 0 ){
    push( performance, list_ptr, src, width );
  } else {

    for ( i = 0; i < index; i++){
      list_ptr = next( performance, list_ptr );
    }

    push( performance, list_ptr, src, width );
  }
}

void prependItem( struct Performance * performance, struct Node ** list_ptr, void *src, unsigned int width ){
  insertItem( performance, list_ptr, 0, src, width );
}

void deleteItem( struct Performance * performance, struct Node ** list_ptr, unsigned int index ){
  int i;

  if( index == 0 ){
    pop( performance, list_ptr, NULL, 0 );
  } else {

    for ( i = 0; i < index; i++){
      list_ptr = next( performance, list_ptr );
    }

    pop( performance, list_ptr, NULL, 0 );
  }
}

// retrieve an element from list
int findItem( struct Performance * performance, struct Node ** list_ptr, int (*compar)(const void *, const void * ), void * target, unsigned int width ){
  int i = 0;
  
  void * data = malloc( sizeof( width ) );

  while( isEmpty( performance, list_ptr ) != 1 ){

    readHead( performance, list_ptr, data, width );
    
    if( compar( data, target ) == 0 ){
      return i;
    }
    i++;

    list_ptr = next( performance, list_ptr );

  }

  return -1;
}


