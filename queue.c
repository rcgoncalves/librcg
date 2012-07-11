/**
 * Implementation of a queue as linked list.
 * 
 * @author Rui Carlos Gonçalves
 * @file queue.c
 * @version 3.0
 * @date 05/2012
 */
#include <stdlib.h>
#include "queue.h"

Queue newQueue()
{
  Queue queue=malloc(sizeof(SQueue));
  if(queue)
  {
    queue->size=0;
    queue->head=NULL;
    queue->last=NULL;
  }
  return queue;
}

//==============================================================================

void queueDelete(Queue queue)
{
  QueueNode aux1,aux2;
  if(!queue->size) free(queue);
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

//==============================================================================

int queueInsert(Queue queue,void* value)
{
  int result=0;
  QueueNode new;
  new=malloc(sizeof(SQueueNode));
  if(new)
  {
    new->value=value;
    new->next=NULL;
    if(!queue->size) queue->head=new;
    else queue->last->next=new;
    queue->last=new;
    queue->size++;
  }
  else result=1;
  return result;
}

//==============================================================================

int queueRemove(Queue queue,void** value)
{
  int result=0;
  QueueNode aux;
  if(!queue->size)
  {
    if(value) *value=NULL;
    result=1;
  }
  else
  {
    if(value) *value=queue->head->value;
    if(queue->size==1)
    {
      free(queue->head);
      queue->last=NULL;
      queue->head=NULL;
    }
    else
    {
      aux=queue->head;
      queue->head=queue->head->next;
      free(aux);
    }
    queue->size--;
  }
  return result;
}

//==============================================================================

int queueConsult(Queue queue,void** value)
{
  int result=0;
  if(!queue->size)
  {
    *value=NULL;
    result=1;
  }
  else *value=queue->head->value;
  return result;
}

//==============================================================================

int queueSize(Queue queue)
{
  return queue->size;
}

//==============================================================================

int queueMap(Queue queue,void(*fun)(void*))
{
  int result=0;
  QueueNode aux;
  if(queue->size==0) result=1;
  else
  {
    for(aux=queue->head;aux;aux=aux->next)
      fun(aux->value);
  }
  return result;
}

//==============================================================================

Iterator queueIterator(Queue queue)
{
  int ctrl;
  QueueNode aux;
  Iterator it;
  it=newIt(queue->size);
  for(aux=queue->head,ctrl=0;aux&&!ctrl;aux=aux->next)
    ctrl=itAdd(it,aux->value);
  if(ctrl)
  {
    itDelete(it);
    it=NULL;
  }
  return it;
}
