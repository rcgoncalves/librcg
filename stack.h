/**
 * Implementation of a stack as a linked list.
 *
 * Provides functions to create and manipulate stacks.
 *
 * @author Rui Carlos Gonçalves <rcgoncalves.pt@gmail.com>
 * @file stack.h
 * @version 3.0
 * @date 05/2012
 */
#ifndef _STACK_H_
#define _STACK_H_

#include "iterator.h"

/**
 * Stack node structure.
 */
typedef struct sStackNode
{
  ///Node's value.
  void* value;
  ///Next node.
  struct sStackNode *next;
}SStackNode;

/**
 * Stack node definition.
 */
typedef SStackNode* StackNode;

/**
 * Stack structure.
 */
typedef struct sStack
{
  ///Number of values of this stack.
  int size;
  ///Top node of this stack.
  StackNode top;
}SStack;

/**
 * Stack definition.
 */
typedef SStack* Stack;

//##############################################################################

/**
 * Creates a stack.
 *
 * @return
 * <tt>NULL</tt> if an error occurred\n
 * the new stack otherwise
 */
Stack newStack();

/**
 * Deletes a stack.
 *
 * @attention
 * This function only frees the memory used by the stack.  It does not free the
 * memory used by elements the stack contains.
 *
 * @param stack the stack to be deleted
 */
void stackDelete(Stack stack);

/**
 * Inserts an element at the top of the stack.
 *
 * @param stack the stack
 * @param value the value to be inserted
 *
 * @return
 * 0 if the new value was inserted\n
 * 1 if it was not possible to insert the new element
 */
int stackPush(Stack stack,void* value);

/**
 * Removes an elements from the top of a stack.
 *
 * Provides the value of the removed element if the value of <tt>value</tt> is
 * not <tt>NULL</tt>.
 *
 * @attention
 * This function does not free the memory used by the removed element.
 *
 * @param stack the stack
 * @param value pointer where the removed value should be put (or
 * <tt>NULL</tt>)
 *
 * @return
 * 0 if the element was removed\n
 * 1 if the stack was empty
 */
int stackPop(Stack stack,void** value);

/**
 * Provides the value of the element at the top of a stack.
 *
 * If the stack is empty, it will be put the value <tt>NULL</tt> at
 * <tt>value</tt>.
 *
 * @attention
 * This function puts at <tt>value</tt> a pointer to the value at the top.
 * Changes to this value will affect the element in the stack.
 *
 * @param stack the stack.
 * @param value pointer where the value at the first position will be put
 *
 * @return
 * 0 if the stack was not empty\n
 * 1 otherwise
 */
int stackTop(Stack stack,void** value);

/**
 * Returns the size of a stack.
 *
 * @param stack the stack
 *
 * @return
 * the size of the stack
 */
int stackSize(Stack stack);

/**
 * Applies a function to the elements of a stack.
 *
 * The function to be applied must be of type <tt>void fun(void*)</tt>.
 *
 * @param stack the stack
 * @param fun   the function to be applied
 *
 * @return
 * 0 if the stack was not empty\n
 * 1 otherwise
 */
int stackMap(Stack stack,void(*fun)(void*));

/**
 * Creates an iterator from a stack.
 *
 * @see Iterator
 *
 * @param stack the stack
 *
 * @return
 * <tt>NULL</tt> if an error occurred\n
 * the iterator otherwise
 */
Iterator stackIterator(Stack stack);

#endif
