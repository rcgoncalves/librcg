/**
 * Implementation of a linked list.
 *
 * This library provides functions to create linked lists.
 *
 * @author Rui Carlos Gonçalves <rcgoncalves.pt@gmail.com>
 * @file list.h
 * @version 3.0
 * @date 05/2012
 */
#ifndef _LIST_H_
#define _LIST_H_

#include "iterator.h"

/**
 * Linked list node structure.
 */
typedef struct sListNode
{
  ///Node's value.
  void* value;
  ///Previous node.
  struct sListNode* prev;
  ///Next node.
  struct sListNode* next;
}SListNode;

/**
 * Linked list node definition.
 */
typedef SListNode* ListNode;

/**
 * Linked list structure.
 */
typedef struct sList
{
  ///Number of elements of this linked list.
  int size;
  ///First node.
  ListNode first;
  ///Last node.
  ListNode last;
}SList;

/**
 * Linked list definition.
 */
typedef SList* List;

//==============================================================================

/**
 * Creates a list.
 *
 * @return
 * <tt>NULL</tt> if an error occurred\n
 * the new list otherwise
 */
List newList();

/**
 * Deletes a list.
 *
 * @attention
 * This function only frees the memory used by the list.  It does not free the
 * memory used by elements the list contains.
 *
 * @param list the list to be deleted
 */
void listDelete(List list);

/**
 * Inserts an element at the beginning of a list.
 *
 * @param list  the list
 * @param value the value to be inserted
 *
 * @return
 * 0 if the new value was inserted\n
 * 1 if it was not possible to insert the new element
 */
int listInsertFst(List list,void* value);

/**
 * Inserts an element at the end of a list.
 *
 * @param list  the list
 * @param value the value to be inserted
 *
 * @return
 * 0 if the new value was inserted\n
 * 1 if it was not possible to insert the new element
 */
int listInsertLst(List list,void* value);

/**
 * Inserts an new element at the specified position of a list.
 *
 * The position, specified by argument <tt>index</tt>, must be a non negative
 * integer, and less than the current size of the list.
 *
 * @param list  the list
 * @param index the index at which the new value is to be inserted
 * @param value the value to be inserted
 *
 * @return
 * 0 if the new value was inserted\n
 * 1 if the position was not valid\n
 * 2 if it was not possible to insert the new element
 */
int listInsertAt(List list,int index,void* value);

/**
 * Removes the first element of a list.
 *
 * Provides the value of the removed element if the value of <tt>value</tt> is
 * not <tt>NULL</tt>.
 *
 * @attention
 * This function does not free the memory used by the removed element.
 *
 * @param list  the list.
 * @param value pointer where the removed value should be put (or
 * <tt>NULL</tt>)
 *
 * @return
 * 0 if the element was removed\n
 * 1 if the list was empty
 */
int listRemoveFst(List list,void** value);

/**
 * Removes the last element of a list.
 *
 * Provides the value of the removed element if the value of <tt>value</tt> is
 * not <tt>NULL</tt>.
 *
 * @attention
 * This function does not free the memory used by the removed element.
 *
 * @param list  the list.
 * @param value pointer where the removed value should be put (or
 * <tt>NULL</tt>)
 *
 * @return
 * 0 if the element was removed\n
 * 1 if the list was empty
 */

int listRemoveLst(List list,void** value);

/**
 * Removes the element at the specified position of a list.
 *
 * Provides the value of the removed element if the value of <tt>value</tt> is
 * not <tt>NULL</tt>.
 *
 * @attention
 * This function does not free the memory used by the removed element.
 *
 * @param list  the list.
 * @param index the index of the element to be removed
 * @param value pointer where the removed value should be put (or
 * <tt>NULL</tt>)
 *
 * @return
 * 0 if the element was removed\n
 * 1 if the value of <tt>index</tt> was invalid
 */
int listRemoveAt(List list,int index,void** value);

/**
 * Provides the value at the first position of a list.
 *
 * If the list is empty, it will be put the value <tt>NULL</tt> at
 * <tt>value</tt>.
 * 
 * @attention
 * This function puts at <tt>value</tt> a pointer to the value at the first
 * position.  Changes to this value will affect the element in the list.
 *
 * @param list  the list
 * @param value pointer where the value at the first position will be put
 *
 * @return
 * 0 if the list was not empty\n
 * 1 otherwise
 */
int listFst(List list,void** value);

/**
 * Provides the value at the last position of a list.
 *
 * If the list is empty, it will be put the value <tt>NULL</tt> at
 * <tt>value</tt>.
 * 
 * @attention
 * This function puts at <tt>value</tt> a pointer to the value at the last
 * position.  Changes to this value will affect the element in the list.
 *
 * @param list  the list
 * @param value pointer where the value at the last position will be put
 *
 * @return
 * 0 if the list was not empty\n
 * 1 otherwise
 */
int listLst(List list,void** value);

/**
 * Provides the element at the specified position of a list.
 *
 * If there is no element at the specified position, it will be put the value
 * <tt>NULL</tt> at <tt>value</tt>.
 *
 * @attention
 * This function puts at <tt>value</tt> a pointer to the value at the last
 * position.  Changes to this value will affect the element in the list.
 *
 * @param list  the list
 * @param index the index of the element to be provided
 * @param value pointer where the value at the specified position will be put
 *
 * @return
 * 0 if there was an elements at the specified position\n
 * 1 otherwise
 */
int listAt(List list,int index,void** value);

/**
 * Returns the size of a list.
 *
 * @param list the list
 *
 * @return
 * the size of the list
 */
int listSize(List list);

/**
 * Applies a function to the elements of a list.
 *
 * The function to be applied must be of type <tt>void fun(void*)</tt>.
 *
 * @param list the list
 * @param fun  the function to be applied
 *
 * @return
 * 0 if the list was not empty\n
 * 1 otherwise
 */
int listMap(List list,void(*fun)(void*));

/**
 * Creates an iterator from a list.
 *
 * @see Iterator
 *
 * @param list the list
 *
 * @return
 * <tt>NULL</tt> if an error occurred\n
 * the iterator otherwise
 */
Iterator listIterator(List list);

#endif
