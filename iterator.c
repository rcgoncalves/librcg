/**
 * Implementation of an iterator.
 *
 * @author Rui Carlos Gonçalves <rcgoncalves.pt@gmail.com>
 * @file iterator.c
 * @version 3.0
 * @date 11/2011
 */
#include <stdlib.h>
#include "iterator.h"

Iterator newIt(int size)
{
  Iterator it=NULL;
  if(size>0)
  {
    it=(Iterator)malloc(sizeof(SIterator));
    if(it)
    {
      it->capacity=size;
      it->size=0;
      it->pos=0;
      it->values=(void**)calloc(size,sizeof(void*));
      if(!it->values)
      {
        free(it);
        it=NULL;
      }
    }
  }
  return it;
}

//==============================================================================

void itDelete(Iterator it)
{
  free(it->values);
  free(it);
}

//==============================================================================

int itAdd(Iterator it,void* val)
{
  int result=0;
  if(it->capacity==it->size) result=1;
  else
  {
    it->values[it->size]=val;
    it->size++;
  }
  return result;
}

//==============================================================================

int itNext(Iterator it,void** val)
{
  int result=0;
  if(it->pos>=it->size)
  {
    *val=NULL;
    result=1;
  }
  else
  {
    *val=it->values[it->pos];
    it->pos++;
  }
  return result;
}

//==============================================================================

int itHasNext(Iterator it)
{
  if((it->pos)<(it->size)) return 1;
  else return 0;
}

//==============================================================================

int itPrev(Iterator it,void** val)
{
  int result=0;
  if(!it->pos)
  {
    *val=NULL;
    result=1;
  }
  else
  {
    it->pos--;
    *val=it->values[it->pos];
  }
  return result;
}

//==============================================================================

int itHasPrev(Iterator it)
{
  if(!it->pos) return 0;
  else return 1;
}

//==============================================================================

int itAt(Iterator it,int n,void** val)
{
  int result=0;
  if(n<0||n>=it->size)
  {
    *val=NULL;
    result=1;
  }
  else *val=it->values[n]; 
  return result;
}

//==============================================================================

int itSetPos(Iterator it,int n)
{
  int result=-1;
  if(!n<0&&!n>it->size)
  {
    result=it->pos;
    it->pos=n;
  }
  return result;
}

//==============================================================================

int itGetPos(Iterator it)
{
  return it->pos;
}
