/**
 * Implementação de uma stack como lista ligada.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file stack.c
 * @version 2.0.1
 * @date 02/2009
 */
#include <stdlib.h>
#include "stack.h"


Stack newStack()
{
  Stack stack=(Stack)malloc(sizeof(SStack));

  if(!stack) return NULL;
  else
  {
    stack->size=0;
    stack->top=NULL;
    return stack;
  }
}

//##############################################################################

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

//##############################################################################

int stackPush(Stack stack,void *inf)
{
  StackNode new;
  
  new=(StackNode)malloc(sizeof(SStackNode));
 
  if(new)
  {
    stack->size++;
    new->inf=inf;
    new->next=stack->top;
    stack->top=new;

    return 0;
  }
  else return 1;
}

//##############################################################################

int stackPop(Stack stack,void **inf)
{
  StackNode aux;
  
  if(!stack->size)
  {
    if(inf) *inf=NULL;
    return 1;
  }
  else
  {
    if(inf) *inf=stack->top->inf;
    aux=stack->top;
    stack->top=stack->top->next;
    free(aux);
    stack->size--;

    return 0;
  }
}

//##############################################################################

int stackTop(Stack stack,void **inf)
{
  if(!stack->size)
  {
    *inf=NULL;
    return 1;
  }
  else
  {
    *inf=stack->top->inf;
    return 0;
  }
}

//##############################################################################

int stackSize(Stack stack)
{
  return(stack->size);
}

//##############################################################################

int stackMap(Stack stack,void(*fun)(void*))
{
  StackNode aux;

  if(!stack->size) return 1;
  else
  {
    for(aux=stack->top;aux;aux=aux->next)
      fun(aux->inf);
    
    return 0;
  }
}

//##############################################################################

Iterator stackIterator(Stack stack)
{
  int ctrl;
  StackNode aux;
  Iterator it;
  
  it=newIt(stack->size);
  for(aux=stack->top,ctrl=0;aux&&!ctrl;aux=aux->next)
    ctrl=itAdd(it,aux->inf);

  if(ctrl)
  {
    itDelete(it);
    return NULL;
  }
  else return it;
}
