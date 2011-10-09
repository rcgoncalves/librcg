/**
 * Implementação de uma tabela de hash.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file hashmap.c
 * @version 2.0.2
 * @date 02/2009
 */
#include <stdlib.h>
#include "hashmap.h"


/**
 * Redimensiona uma tabela de hash.
 * Duplica a dimensão do array que suporta a tabela e recoloca os elementos
 *   contidos na tabela antiga na nova tabela.
 *
 * @param hmap tabela de hash.
 *
 * @return 1 se a alocação de espaço para a nova tabela falhar;\n
 *         0 caso contrário.
 */
static int reHash(HashMap hmap)
{
  int i,index;
  HashNode* new;
  HashNode this,next;
  
  new=(HashNode*)calloc(hmap->length*2,sizeof(HashNode));

  if(!new) return 1;
  else
  {
    for(i=0;i<hmap->length*2;i++)
      new[i]=NULL;

    for(i=0;i<hmap->length;i++)
    {
      for(this=hmap->elems[i];this;this=next)
      {
        next=this->next;
        index=(hmap->hash)(this->key)%(hmap->length*2);
        this->next=new[index];
        new[index]=this;
      }
    }

    free(hmap->elems);
    hmap->elems=new;
    hmap->length=2*hmap->length;

    return 0;
  }
}

//##############################################################################

HashMap newHash(int size,float factor
               ,int(*hash)(void*)
               ,int(*equals)(void*,void*)
               )
{
  if(!hash||!equals) return NULL;
  else
  {
    HashMap hmap=(HashMap)malloc(sizeof(SHashMap));

    if(!hmap) return NULL;
    else
    {
      hmap->size=0;
      hmap->length=size;
      hmap->factor=factor;
      hmap->hash=*hash;
      hmap->equals=*equals;
      hmap->elems=(HashNode*)calloc(size,sizeof(HashNode));

      if(hmap->elems) return hmap;
      else return NULL;
    }
  }
}

//##############################################################################

int hashSetHash(HashMap hmap,int(*hash)(void*))
{
  if(!hash) return 1;
  else
  {
    hmap->hash=*hash;
    return 0;
  }
}

//##############################################################################

int hashSetEquals(HashMap hmap,int(*equals)(void*,void*))
{
  if(!equals) return 1;
  else
  {
    hmap->equals=*equals;
    return 0;
  }
}

//##############################################################################

int hashSetFactor(HashMap hmap,int factor)
{
  if(factor<0.1) return 1;
  else
  {
    hmap->factor=factor;
    return 0;
  }
}

//##############################################################################

void hashDelete(HashMap hmap)
{
  int i;
  HashNode p,aux;

  for(i=0;i<hmap->length;i++)
    for(p=hmap->elems[i];p;)
    {
      aux=p;
      p=p->next;
      free(aux);
    }

  free(hmap->elems);
  free(hmap);
}

//##############################################################################

int hashInsert(HashMap hmap,void* key,void* value,int replace)
{
  int h,stop;
  HashNode aux;

  if(hmap->size>hmap->factor*hmap->length) reHash(hmap);
  
  h=(hmap->hash)(key)%hmap->length;
  for(aux=hmap->elems[h],stop=1;aux&&stop;aux=aux->next)
  {
    if(!(hmap->equals)(aux->key,key))
    {
      if(replace) aux->value=value;
      stop=0;
    }
  }

  if(stop)
  {
    aux=(HashNode)malloc(sizeof(SHashNode));

    if(aux)
    {
      aux->key=key;
      aux->value=value;
      aux->next=hmap->elems[h];
      hmap->elems[h]=aux;

      hmap->size++;

      return 0;
    }
    else return 2;
  }
  else return 1;
}

//##############################################################################

int hashRemove(HashMap hmap,void* key,void** value,void(*del)(void*))
{
  int index;
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

    return 0;
  }
  else
  {
    if(value) *value=NULL;
    return 1;
  }
}

//##############################################################################

int hashGet(HashMap hmap,void* key,void** value)
{
  HashNode aux;

  for(aux=hmap->elems[(hmap->hash)(key)%hmap->length];
      aux&&(hmap->equals)(key,aux->key);
      aux=aux->next);

  if(aux)
  {
    *value=aux->value;
    return 0;
  }
  else
  {
    *value=NULL;
    return 1;
  }
}

//##############################################################################

int hashSize(HashMap hmap)
{
  return(hmap->size);
}

//##############################################################################

Iterator hashKeys(HashMap hmap)
{
  int i,erro;
  HashNode aux;
  Iterator it=newIt(hmap->size);
  if(!it) return NULL;
  else
  {
    for(i=0,erro=0;i<hmap->length&&!erro;i++)
      for(aux=hmap->elems[i];aux&&!erro;aux=aux->next)
        erro=itAdd(it,aux->key);

    if(erro)
    {
      itDelete(it);
      return NULL;
    }
    else return it;
  }
}

//##############################################################################

Iterator hashValues(HashMap hmap)
{
  int i,erro;
  HashNode aux;
  Iterator it=newIt(hmap->size);
  if(!it) return NULL;
  else
  {
    for(i=0,erro=0;i<hmap->length&&!erro;i++)
      for(aux=hmap->elems[i];aux&&!erro;aux=aux->next)
        erro=itAdd(it,aux->value);

    if(erro)
    {
      itDelete(it);
      return NULL;
    }
    else return it;
  }
}
