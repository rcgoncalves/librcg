/**
 * Implementação de uma queue como lista ligada.
 * 
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file queue.c
 * @version 2.0.1
 * @date 08/2007
 */
#include <stdlib.h>
#include "queue.h"


Queue newQueue()
{
  Queue queue=(Queue)malloc(sizeof(SQueue));

  if(!queue) return NULL;
  else
  {
    queue->size=0;
    queue->head=NULL;
    queue->last=NULL;
    return queue;
  }
}

//##############################################################################

void queueDelete(Queue queue)
{
  QueueNode aux1,aux2;
    
  if(!queue->size)
    free(queue);
  else
  {
    for(aux1=queue->head;aux1;)
    {
      aux2=aux1;
      aux1=aux1->next;
      free(aux2);
    }
    free(queue);
  }
}

//##############################################################################

int queueInsert(Queue queue,void *inf)
{
  QueueNode new;
  new=(QueueNode)malloc(sizeof(SQueueNode));

  if(new)
  {
    new->inf=inf;
    new->next=NULL;

    if(!queue->size) queue->head=new;
    else queue->last->next=new;
    
    queue->last=new;
    queue->size++;
    return 0;
  }
  else return 1;
}

//##############################################################################

int queueRemove(Queue queue,void **inf)
{
  QueueNode aux;
  
  if(!queue->size)
  {
    if(inf) *inf=NULL;
    return 1;
  }
  else
  {
    if(inf) *inf=queue->head->inf;

    if(queue->size==1)
    {
      queue->last=NULL;
      free(queue->head);
      queue->head=NULL;
    }
    else
    {
      aux=queue->head;
      queue->head=queue->head->next;
      free(aux);
    }

    queue->size--;
    return 0;
  }
}

//##############################################################################

int queueConsult(Queue queue,void **inf)
{
  if(!queue->size)
  {
    *inf=NULL;
    return 1;
  }
  else
  {
    *inf=queue->head->inf;
    return 0;
  }
}

//##############################################################################

int queueSize(Queue queue)
{
  return(queue->size);
}

//##############################################################################

int queueMap(Queue queue,void(*fun)(void*))
{
  QueueNode aux;
  
  if(queue->size==0) return 1;
  else
  {
    for(aux=queue->head;aux;aux=aux->next)
      fun(aux->inf);
    
    return 0;
  }
}

//##############################################################################

Iterator queueIterator(Queue queue)
{
  int ctrl;
  QueueNode aux;
  Iterator it;
  
  it=newIt(queue->size);
  for(aux=queue->head,ctrl=0;aux&&!ctrl;aux=aux->next)
    ctrl=itAdd(it,aux->inf);

  if(ctrl)
  {
    itDelete(it);
    return NULL;
  }
  else return it;
}
