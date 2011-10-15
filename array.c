/**
 * Implementation of a dynamic array.
 *
 * @author Rui Carlos Gonçalves <rcgoncalves.pt@gmail.com>
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

//==============================================================================

void arrayDelete(Array array)
{
  free(array->array);
  free(array);
}

//==============================================================================

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

//==============================================================================

int arrayRemove(Array array,int index,void** elem)
{
  int result=0;
  if(index<0||index>=array->capacity)
  {
    if(elem) *elem=NULL;
    result=1;
  }
  else if(!array->array[index])
  {
    if(elem) *elem=NULL;
    result=1;
  }
  else
  {
    if(elem) *elem=array->array[index];
    array->array[index]=NULL;
    array->size--;
  }
  return result;
}

//==============================================================================

int arrayAt(Array array,int index,void** elem)
{
  int result=0;
  if(index<0||index>=array->capacity)
  {
    *elem=NULL;
    result=1;
  }
  else if(!array->array[index])
  {
    *elem=NULL;
    result=1;
  }
  else *elem=array->array[index];
  return result;
}

//==============================================================================

int arrayResize(Array array,int size)
{
  int i,result=0;
  void** newarray;
  if(array->capacity>=size) result=2;
  else
  {
    newarray=(void**)realloc(array->array,size*sizeof(void*));
    if(!newarray) result=1;
    else
    {
      for(i=array->capacity;i<size;i++) newarray[i]=NULL;
      array->array=newarray;
      array->capacity=size;
    }
  }
  return result;
}

//==============================================================================

int arraySize(Array array)
{
  return array->size;
}

//==============================================================================

int arrayCapacity(Array array)
{
  return array->capacity;
}

//==============================================================================

int arrayMap(Array array,void(*fun)(void*))
{
  int i,j,result=0;
  if(!array->size) result=1;
  else
  {
    for(i=0,j=0;i<array->capacity&&j<array->size;i++)
    {
      if(array->array[i])
      {
        fun(array->array[i]);
        j++;
      }
    }
  }
  return result;
}

//==============================================================================

Iterator arrayIterator(Array array)
{
  int ctrl,i,j;
  Iterator it;
  it=newIt(array->size);
  for(ctrl=0,i=0,j=0;i<array->capacity&&j<array->size&&!ctrl;i++)
  {
    if(array->array[i])
    {
      ctrl=itAdd(it,array->array[i]);
      j++;
    }
  }
  if(ctrl)
  {
    itDelete(it);
    it=NULL;
  }
  return it;
}
