/**
 * Implementation of a hash table.
 *
 * @author Rui Carlos Gonçalves <rcgoncalves.pt@gmail.com>
 * @file hashmap.c
 * @version 3.0
 * @date 10/2011
 */
#include <stdlib.h>
#include "hashmap.h"

/**
 * Resizes a hash table.
 * 
 * Doubles the number of buckets of a hash table, and updates the positions of
 * the elements.
 *
 * @param hmap the hash table
 *
 * @return
 * 1 if an error occured\n
 * 0 otherwise
 */
static int reHash(HashMap hmap)
{
  int i,index,result=0;
  HashNode* new=NULL;
  HashNode this,next;
  new=(HashNode*)calloc(hmap->length*2,sizeof(HashNode));
  if(!new) result=1;
  else
  {
    hmap->length=2*hmap->length;
    for(i=0;i<hmap->length;i++)
    {
      for(this=hmap->elems[i];this;this=next)
      {
        next=this->next;
        index=(hmap->hash)(this->key)%(hmap->length);
        this->next=new[index];
        new[index]=this;
      }
    }
    free(hmap->elems);
    hmap->elems=new;
  }
  return result;
}

//==============================================================================

HashMap newHash(int size,float factor,int(*hash)(void*),
    int(*equals)(void*,void*))
{
  HashMap hmap=NULL;
  if(hash&&equals)
  {
    hmap=(HashMap)malloc(sizeof(SHashMap));
    if(hmap)
    {
      hmap->size=0;
      hmap->length=size;
      if(factor<0.1) hmap->factor=0.1;
      else hmap->factor=factor;
      hmap->hash=*hash;
      hmap->equals=*equals;
      hmap->elems=(HashNode*)calloc(size,sizeof(HashNode));
      if(!hmap->elems)
      {
	free(hmap);
	hmap=NULL;
      }
    }
  }
  return hmap;
}

//==============================================================================

int hashSetHash(HashMap hmap,int(*hash)(void*))
{
  int result=0;
  if(!hash) result=1;
  else hmap->hash=*hash;
  return result;
}

//==============================================================================

int hashSetEquals(HashMap hmap,int(*equals)(void*,void*))
{
  int result=0;
  if(!equals) result=1;
  else hmap->equals=*equals;
  return result;
}

//==============================================================================

int hashSetFactor(HashMap hmap,int factor)
{
  int result=0;
  if(factor<0.1) result=1;
  else hmap->factor=factor;
  return result;
}

//==============================================================================

void hashDelete(HashMap hmap)
{
  int i;
  HashNode p,aux;
  for(i=0;i<hmap->length;i++)
  {
    for(p=hmap->elems[i];p;)
    {
      aux=p;
      p=p->next;
      free(aux);
    }
  }
  free(hmap->elems);
  free(hmap);
}

//==============================================================================

int hashInsert(HashMap hmap,void* key,void* value,int replace)
{
  int h,stop,error,result=0;
  HashNode aux;
  if(hmap->size>hmap->factor*hmap->length) error=reHash(hmap);
  if(!error)
  {
    h=(hmap->hash)(key)%hmap->length;
    for(aux=hmap->elems[h],stop=0;aux&&!stop;aux=aux->next)
    {
      if(!(hmap->equals)(aux->key,key))
      {
        if(replace) aux->value=value;
        stop=1;
      }
    }
    if(!stop)
    {
      aux=(HashNode)malloc(sizeof(SHashNode));
      if(aux)
      {
        aux->key=key;
        aux->value=value;
        aux->next=hmap->elems[h];
        hmap->elems[h]=aux;
        hmap->size++;
        result=0;
      }
      else result=2;
    }
    else result=1;
  }
  else result=2;
  return result;
}

//==============================================================================

int hashRemove(HashMap hmap,void* key,void** value,void(*del)(void*))
{
  int index,result=0;
  HashNode aux,*last;
  index=(hmap->hash)(key)%hmap->length;
  for(aux=hmap->elems[index],last=&(hmap->elems[index]);
      aux&&(hmap->equals)(key,aux->key);
      last=&(aux->next),aux=aux->next);
  if(aux)
  {
    *last=aux->next;
    if(del) del(aux->key);
    if(*value) *value=aux->value;
    free(aux);
    hmap->size--;
  }
  else
  {
    if(value) *value=NULL;
    result=1;
  }
  return result;
}

//==============================================================================

int hashGet(HashMap hmap,void* key,void** value)
{
  int result=0;
  HashNode aux;
  for(aux=hmap->elems[(hmap->hash)(key)%hmap->length];
      aux&&(hmap->equals)(key,aux->key);
      aux=aux->next);
  if(aux) *value=aux->value;
  else
  {
    *value=NULL;
    result=1;
  }
  return result;
}

//==============================================================================

int hashSize(HashMap hmap)
{
  return(hmap->size);
}

//==============================================================================

Iterator hashKeys(HashMap hmap)
{
  int i,error;
  HashNode aux;
  Iterator it=newIt(hmap->size);
  if(it)
  {
    for(i=0,error=0;i<hmap->length&&!error;i++)
      for(aux=hmap->elems[i];aux&&!error;aux=aux->next)
        error=itAdd(it,aux->key);
    if(error)
    {
      itDelete(it);
      it=NULL;
    }
  }
  return it;
}

//==============================================================================

Iterator hashValues(HashMap hmap)
{
  int i,error;
  HashNode aux;
  Iterator it=newIt(hmap->size);
  if(it)
  {
    for(i=0,error=0;i<hmap->length&&!error;i++)
      for(aux=hmap->elems[i];aux&&!error;aux=aux->next)
        error=itAdd(it,aux->value);
    if(error)
    {
      itDelete(it);
      it=NULL;
    }
  }
  return it;
}
