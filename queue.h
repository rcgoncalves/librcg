/**
 * Implementation of a queue as linked list.
 *
 * Provides functions to create and manipulate a queue.
 *
 * @author Rui Carlos Gonçalves <rcgoncalves.pt@gmail.com>
 * @file queue.h
 * @version 3.0
 * @date 05/2012
 */
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "iterator.h"

/**
 * Queue node structure.
 */
typedef struct sQueueNode
{
  ///Node's value.
  void* value;
  ///Next node.
  struct sQueueNode* next;
}SQueueNode;

/**
 * Queue node definition.
 */
typedef SQueueNode* QueueNode;

/**
 * Queue structure.
 */
typedef struct sQueue
{
  ///Number of elements of this queue.
  int size;
  ///Apontador para o início da queue.
  ///First node.
  QueueNode head;
  ///Last node.
  QueueNode last;
}SQueue;

/**
 * Queue definition.
 */
typedef SQueue* Queue;

//==============================================================================

/**
 * Creates a queue.
 *
 * @return
 * <tt>NULL</tt> if an error occurred\n
 * the new queue otherwise
 */
Queue newQueue();

/**
 * Deletes a queue.
 *
 * @attention
 * This function only frees the memory used by the queue.  It does not free the
 * memory used by elements the queue contains.
 * 
 * @param queue the queue to be deleted
 */
void queueDelete(Queue queue);

/**
 * Inserts an element in a queue.
 *
 * @param queue the queue
 * @param value the value to be inserted
 *
 * @return
 * 0 if the new value was inserted\n
 * 1 if it was not possible to insert the new element
 */
int queueInsert(Queue queue,void* value);

/**
 * Removes an element from a queue.
 *
 * Provides the value of the removed element if the value of <tt>value</tt> is
 * not <tt>NULL</tt>.
 *
 * @attention
 * This function does not free the memory used by the removed element.
 *
 * @param queue the queue
 * @param value pointer where the removed value should be put (or
 * <tt>NULL</tt>)
 *
 * @return
 * 0 if an element was removed\n
 * 1 if the queue was empty
 */
int queueRemove(Queue queue,void** value);

/**
 * Provides the value at the head of a queue.
 *
 * If the queue is empty, it will be put the value <tt>NULL</tt> at
 * <tt>value</tt>.
 * 
 * @attention
 * This function puts at <tt>value</tt> a pointer to the value at the first
 * position.  Changes to this value will affect the element in the list.
 *
 * @param queue the queue
 * @param value pointer where the value at the last position will be put
 *
 * @return
 * 0 if the queue was not empty\n
 * 1 otherwise
 */
int queueConsult(Queue queue,void** value);

/** 
 * Returns the size of a queue.
 *
 * @param queue the queue
 *
 * @return
 * the size of the queue
 */
int queueSize(Queue queue);

/**
 * Applies a function to the elements of a queue.
 *
 * The function to be applied must be of type <tt>void fun(void*)</tt>.
 *
 * @param queue the queue
 * @param fun   the function to be applied
 *
 * @return
 * 0 if the queue was not empty\n
 * 1 otherwise
 */
int queueMap(Queue queue,void(*fun)(void*));

/**
 * Creates an iterator from a queue.
 *
 * @see Iterator
 *
 * @param queu the queue
 *
 * @return
 * <tt>NULL</tt> if an error occurred\n
 * the iterator otherwise
 */
Iterator queueIterator(Queue queue);

#endif
