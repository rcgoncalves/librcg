/**
 * Implementação de uma pqueue como lista ligada.
 * 
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file pqueue.c
 * @version 1.0.1
 * @date 02/2009
 */
#include <stdlib.h>
#include "pqueue.h"


PQueue newPQueue(int(*comp)(void*,void*))
{
  PQueue pqueue=(PQueue)malloc(sizeof(SPQueue));

  if(!pqueue) return NULL;
  else
  {
    pqueue->comp=*comp;
    pqueue->size=0;
    pqueue->head=NULL;
    return pqueue;
  }
}

//##############################################################################

int pqueueSetComp(PQueue pqueue,int(*comp)(void*,void*))
{
  if(!comp) return 1;
  else
  {
    pqueue->comp=*comp;
    return 0;
  }
}

//##############################################################################

void pqueueDelete(PQueue pqueue)
{
  PQueueNode aux1,aux2;
    
  if(!pqueue->size)
    free(pqueue);
  else
  {
    for(aux1=pqueue->head;aux1;)
    {
      aux2=aux1;
      aux1=aux1->next;
      free(aux2);
    }
    free(pqueue);
  }
}

//##############################################################################

int pqueueInsert(PQueue pqueue,void *inf)
{
  PQueueNode new,this,prev;
  new=(PQueueNode)malloc(sizeof(SPQueueNode));

  if(new)
  {
    new->inf=inf;

    if(!pqueue->size)
    {
      new->next=NULL;
      pqueue->head=new;
      pqueue->size++;
    }
    else
    {
      for(this=pqueue->head,prev=NULL;
          this&&((pqueue->comp)(this->inf,inf)<=0);
          prev=this,this=this->next);

      if(prev)
      {
        new->next=prev->next;
        prev->next=new;
      }
      else
      {
        new->next=pqueue->head;
        pqueue->head=new;
      }
      pqueue->size++;
    }

    return 0;
  }
  else return 1;
}

//##############################################################################

int pqueueRemove(PQueue pqueue,void **inf)
{
  PQueueNode aux;
  
  if(!pqueue->size)
  {
    if(inf) *inf=NULL;
    return 1;
  }
  else
  {
    if(inf) *inf=pqueue->head->inf;

    if(pqueue->size==1)
    {
      free(pqueue->head);
      pqueue->head=NULL;
    }
    else
    {
      aux=pqueue->head;
      pqueue->head=pqueue->head->next;
      free(aux);
    }

    pqueue->size--;
    return 0;
  }
}

//##############################################################################

int pqueueConsult(PQueue pqueue,void **inf)
{
  if(!pqueue->size)
  {
    *inf=NULL;
    return 1;
  }
  else
  {
    *inf=pqueue->head->inf;
    return 0;
  }
}

//##############################################################################

int pqueueSize(PQueue pqueue)
{
  return(pqueue->size);
}

//##############################################################################

int pqueueMap(PQueue pqueue,void(*fun)(void*))
{
  PQueueNode aux;
  
  if(pqueue->size==0) return 1;
  else
  {
    for(aux=pqueue->head;aux;aux=aux->next)
      fun(aux->inf);
    
    return 0;
  }
}

//##############################################################################

Iterator pqueueIterator(PQueue pqueue)
{
  int ctrl;
  PQueueNode aux;
  Iterator it;
  
  it=newIt(pqueue->size);
  for(aux=pqueue->head,ctrl=0;aux&&!ctrl;aux=aux->next)
    ctrl=itAdd(it,aux->inf);

  if(ctrl)
  {
    itDelete(it);
    return NULL;
  }
  else return it;
}
