/**
 * Implementation of a dynamic array.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file array.c
 * @version 3.0
 * @date 10/2011
 */
#include <stdlib.h>
#include "array.h"

Array newArray(int size)
{
  Array array=NULL;
  if(size>0)
  {
    array=(Array)malloc(sizeof(SArray));
    if(array)
    {
      array->capacity=size;
      array->size=0;
      array->array=(void**)calloc(size,sizeof(void*));
      if(!array->array)
      {
        free(array);
	array=NULL;
      }
    }
  }
  return array;
}

//##############################################################################

void arrayDelete(Array array)
{
  free(array->array);
  free(array);
}

//##############################################################################

int arrayInsert(Array array,int index,void* elem,int replace)
{
  int result=0;
  if(index<0) result=2;
  else if(index>=array->capacity)
  {
    if(arrayResize(array,index+1)) result=3;
    else
    {
      array->size++;
      array->array[index]=elem;
    }
  }
  else if(array->array[index])
  {
    if(replace) array->array[index]=elem;
    result=1;
  }
  else 
  {
    array->size++;
    array->array[index]=elem;
  }
  return result;
}

//##############################################################################

int arrayRemove(Array array,int index,void** inf)
{
  if(index<0||index>=array->capacity)
  {
    if(inf) *inf=NULL;
    return 1;
  }
  else if(!array->array[index])
  {
    if(inf) *inf=NULL;
    return 1;
  }
  else
  {
    if(inf) *inf=array->array[index];
    array->array[index]=NULL;
    array->size--;
    return 0;
  }
}

//##############################################################################

int arrayAt(Array array,int index,void** inf)
{
  if(index<0||index>=array->capacity)
  {
    *inf=NULL;
    return 1;
  }
  else if(!array->array[index])
  {
    *inf=NULL;
    return 1;
  }
  else
  {
    *inf=array->array[index];
    return 0;
  }
}

//##############################################################################

int arrayResize(Array array,int size)
{
  int i;
  void** newarray;

  if(array->capacity>=size) return 2;
  else
  {
    newarray=(void**)realloc(array->array,size*sizeof(void*));

    if(newarray)
    {
      for(i=array->capacity;i<size;i++)
        newarray[i]=NULL;

      array->array=newarray;
      array->capacity=size;

      return 0;
    }
    else return 1;
  }
}

//##############################################################################

int arraySize(Array array)
{
  return(array->size);
}

//##############################################################################

int arrayCapacity(Array array)
{
  return(array->capacity);
}

//##############################################################################

int arrayMap(Array array,void(*fun)(void*))
{
  int i,j;

  if(!array->size) return 1;
  else
  {
    for(i=0,j=0;i<array->capacity&&j<array->size;i++)
      if(array->array[i])
      {
        fun(array->array[i]);
        j++;
      }

    return 0;
  }
}

//##############################################################################

Iterator arrayIterator(Array array)
{
  int ctrl,i,j;
  Iterator it;

  it=newIt(array->size);
  for(ctrl=0,i=0,j=0;i<array->capacity&&j<array->size&&!ctrl;i++)
    if(array->array[i])
    {
      ctrl=itAdd(it,array->array[i]);
      j++;
    }

  if(ctrl)
  {
    itDelete(it);
    return NULL;
  }
  else return it;
}
