/**
 * Implementation of a linked list.
 *
 * @author Rui Carlos Gonçalves
 * @file list.c
 * @version 3.0.1
 * @date 01/2014
 */
#include <stdlib.h>
#include "list.h"


List newList(void)
{
  List list=malloc(sizeof(SList));
  if(list)
  {
    list->size=0;
    list->first=NULL;
    list->last=NULL;
  }
  return list;
}

//==============================================================================

void listDelete(List list)
{
  ListNode this,next;
  if(!list->size) free(list);
  else
  {
    for(this=list->first,next=this->next;next;this=next,next=next->next)
      free(this);
    free(this);
    free(list);
  }
}

//==============================================================================

int listInsertFst(List list,void* value)
{
  int result=0;
  ListNode new;
  if(!list->size)
  {
    new=malloc(sizeof(SListNode));
    if(new)
    {
      new->value=value;
      new->next=NULL;
      new->prev=NULL;
      list->size++;
      list->first=new;
      list->last=new;
    }
    else result=1;
  }
  else
  {
    new=malloc(sizeof(SListNode));
    if(new)
    {
      new->value=value;
      new->next=list->first;
      new->prev=NULL;
      list->size++;
      list->first->prev=new;
      list->first=new;
    }
    else result=1;
  }
  return result;
}

//==============================================================================

int listInsertLst(List list,void* value)
{
  int result=0;
  ListNode new;
  if(!list->size)
  {
    new=malloc(sizeof(SListNode));
    if(new)
    {
      new->value=value;
      new->next=NULL;
      new->prev=NULL;
      list->size++;
      list->first=new;
      list->last=new;
    }
    else result=1;
  }
  else
  {
    new=malloc(sizeof(SListNode));
    if(new)
    {
      new->value=value;
      new->next=NULL;
      new->prev=list->last;
      list->size++;
      list->last->next=new;
      list->last=new;
    }
    else result=1;
  }
  return result;
}

//==============================================================================

int listInsertAt(List list,int index,void* value)
{
  int size=listSize(list),result=0;
  ListNode aux,new;
  if(index<0||index>size) result=1;
  else if(!index) result=listInsertFst(list,value);
  else if(index==size) result=listInsertLst(list,value);
  else if(index>size/2)
  {
    for(index=size-index,aux=list->last;index>0;index--,aux=aux->prev);
    new=malloc(sizeof(SListNode));
    if(new)
    {
      new->value=value;
      new->next=aux->next;
      new->prev=aux;
      list->size++;
      aux->next->prev=new;
      aux->next=new;
    }
    else result=1;
  }
  else
  {
    for(aux=list->first;index>0;index--,aux=aux->next);
    new=malloc(sizeof(SListNode));
    if(new)
    {
      new->value=value;
      new->next=aux;
      new->prev=aux->prev;
      list->size++;
      aux->prev->next=new;
      aux->prev=new;
    }
    else result=0;
  }
  return result;
}

//==============================================================================

int listRemoveFst(List list,void** value)
{
  int result=0;
  ListNode aux;
  if(!list->size)
  {
    if(value) *value=NULL;
    result=1;
  }
  else if(list->size==1)
  {
    if(value) *value=list->first->value;
    free(list->first);
    list->first=NULL;
    list->last=NULL;
    list->size=0;
  }
  else
  {
    if(value) *value=list->first->value;
    aux=list->first;
    list->first->next->prev=NULL;
    list->first=list->first->next;
    free(aux);
    list->size--;
  }
  return result;
}

//==============================================================================

int listRemoveLst(List list,void** value)
{
  int result=0;
  ListNode aux;
  if(!list->size)
  {
    if(value) *value=NULL;
    result=1;
  }
  else if(list->size==1)
  {
    if(value) *value=list->last->value;
    free(list->last);
    list->first=NULL;
    list->last=NULL;
    list->size=0;
  }
  else
  {
    if(value) *value=list->last->value;
    aux=list->last;
    list->last->prev->next=NULL;
    list->last=list->last->prev;
    free(aux);
    list->size--;
  }
  return result;
}

//==============================================================================

int listRemoveAt(List list,int index,void** value)
{
  int size=listSize(list),result=0;
  ListNode aux;
  if(index<0||index>size-1) result=1;
  else if(index==0) result=listRemoveFst(list,value);
  else if(index==size-1) result=listRemoveLst(list,value);
  else if(index>size/2)
  {
    for(aux=list->last,index=size-index-1;index>0;index--,aux=aux->prev);
    if(value) *value=aux->value;
    aux->prev->next=aux->next;
    aux->next->prev=aux->prev;
    free(aux);
    list->size--;
  }
  else
  {
    for(aux=list->first;index>0;index--,aux=aux->next);
    if(value) *value=aux->value;
    aux->prev->next=aux->next;
    aux->next->prev=aux->prev;
    free(aux);
    list->size--;
  }
  return result;
}

//==============================================================================

int listFst(List list,void** value)
{
  int result=0;
  if(!list->size)
  {
    *value=NULL;
    result=1;
  }
  else *value=list->first->value;
  return result;
}

//==============================================================================

int listLst(List list,void** value)
{
  int result=0;
  if(!list->size)
  {
    *value=NULL;
    result=1;
  }
  else *value=list->last->value;
  return result;
}

//==============================================================================

int listAt(List list,int index,void** value)
{
  int size=listSize(list),result=0;
  ListNode aux;
  if(index<0||index>size-1)
  {
    *value=NULL;
    result=1;
  }
  else
  {
    if(index>size/2) for(index=size-index-1,aux=list->last;index>0;index--,aux=aux->prev);
    else for(aux=list->first;index>0;index--,aux=aux->next);
    *value=aux->value;
  }
  return result;
}

//==============================================================================

int listSize(List list)
{
  return list->size;
}

//==============================================================================

int listMap(List list,void(*fun)(void*))
{
  int result=0;
  ListNode aux;
  if(!list->size) result=1;
  else
  {
    for(aux=list->first;aux;aux=aux->next)
      fun(aux->value);
  }
  return result;
}

//==============================================================================

Iterator listIterator(List list)
{
  int ctrl;
  ListNode aux;
  Iterator it;
  it=newIt(list->size);
  for(aux=list->first,ctrl=0;aux&&!ctrl;aux=aux->next)
    ctrl=itAdd(it,aux->value);
  if(ctrl)
  {
    itDelete(it);
    it=NULL;
  }
  return it;
}
