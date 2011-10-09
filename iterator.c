/**
 * Implementação de um iterador.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file iterator.c
 * @version 2.0.2
 * @date 02/2009
 */
#include <stdlib.h>
#include "iterator.h"


Iterator newIt(int size)
{
  Iterator it=(Iterator)malloc(sizeof(SIterator));

  if(it)
  {
    it->capacity=size;
    it->size=0;
    it->pos=0;
    it->values=(void**)calloc(size,sizeof(void*));

    if(it->values) return it;
    else
    {
      free(it);
      return NULL;
    }
  }
  else return NULL;
}

//##############################################################################

void itDelete(Iterator it)
{
  free(it->values);
  free(it);
}

//##############################################################################

int itAdd(Iterator it,void* val)
{
  if(it->capacity==it->size) return 1;
  else
  {
    it->values[it->size]=val;
    it->size++;
    return 0;
  }
}

//##############################################################################

int itNext(Iterator it,void** val)
{
  if(it->pos>=it->size)
  {
    *val=NULL;
    return 1;
  }
  else
  {
    *val=it->values[it->pos];
    it->pos++;
    return 0;
  }
}

//##############################################################################

int itHasNext(Iterator it)
{
  if((it->pos)<(it->size)) return 1;
  else return 0;
}

//##############################################################################

int itPrev(Iterator it,void** val)
{
  if(!it->pos)
  {
    *val=NULL;
    return 1;
  }
  else
  {
    it->pos--;
    *val=it->values[it->pos];
    return 0;
  }
}

//##############################################################################

int itHasPrev(Iterator it)
{
  if(!it->pos) return 0;
  else return 1;
}

//##############################################################################

int itAt(Iterator it,int n,void** val)
{
  if(n<0||n>=it->size)
  {
    *val=NULL;
    return 1;
  }
  else
  {
    *val=it->values[n];
    return 0;
  } 
}

//##############################################################################

int itSetPos(Iterator it,int n)
{
  int tmp;
  
  if(n<0||n>it->size) return(-1);
  else
  {
    tmp=it->pos;
    it->pos=n;
    return tmp;
  }
}

//##############################################################################

int itGetPos(Iterator it)
{
  return it->pos;
}
