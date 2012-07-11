/**
 * Implementation of a stack as a linked list.
 *
 * @author Rui Carlos Gonçalves
 * @file stack.c
 * @version 3.0
 * @date 05/2012
 */
#include <stdlib.h>
#include "stack.h"


Stack newStack()
{
  Stack stack=malloc(sizeof(SStack));
  if(stack)
  {
    stack->size=0;
    stack->top=NULL;
  }
  return stack;
}

//==============================================================================

void stackDelete(Stack stack)
{
  StackNode aux1,aux2;
  if(stack->size) free(stack);
  else
  {
    for(aux1=stack->top;aux1;)
    {
      aux2=aux1;
      aux1=aux1->next;
      free(aux2);
    }
    free(stack);
  }
}

//==============================================================================

int stackPush(Stack stack,void* value)
{
  int result=0;
  StackNode new;
  new=malloc(sizeof(SStackNode));
  if(new)
  {
    stack->size++;
    new->value=value;
    new->next=stack->top;
    stack->top=new;
  }
  else result=1;
  return result;
}

//==============================================================================

int stackPop(Stack stack,void** value)
{
  int result=0;
  StackNode aux;
  if(!stack->size)
  {
    if(value) *value=NULL;
    result=1;
  }
  else
  {
    if(value) *value=stack->top->value;
    aux=stack->top;
    stack->top=stack->top->next;
    free(aux);
    stack->size--;
  }
  return result;
}

//==============================================================================

int stackTop(Stack stack,void** value)
{
  int result=0;
  if(!stack->size)
  {
    *value=NULL;
    result=1;
  }
  else *value=stack->top->value;
  return result;
}

//==============================================================================

int stackSize(Stack stack)
{
  return stack->size;
}

//==============================================================================

int stackMap(Stack stack,void(*fun)(void*))
{
  int result=0;
  StackNode aux;
  if(!stack->size) result=1;
  else
  {
    for(aux=stack->top;aux;aux=aux->next)
    {
      fun(aux->value);
    }
  }
  return result;
}

//==============================================================================

Iterator stackIterator(Stack stack)
{
  int ctrl;
  StackNode aux;
  Iterator it;
  it=newIt(stack->size);
  for(aux=stack->top,ctrl=0;aux&&!ctrl;aux=aux->next)
  {
    ctrl=itAdd(it,aux->value);
  }
  if(ctrl)
  {
    itDelete(it);
    it=NULL;
  }
  return it;
}
