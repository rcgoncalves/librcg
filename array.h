/**
 * Implementation of a dynamic array.
 *
 * Provides functions to create and manipulate a dynamic array with a desired
 * length.
 *
 * The array can resize itself whenever needed, while preserving the previous
 * values.
 *
 * @author Rui Carlos Gonçalves
 * @file array.h
 * @version 3.0
 * @date 10/2011
 */
#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "iterator.h"

/**
 * Array structure.
 */
typedef struct sArray
{
  ///Current capacity of this array.
  int capacity;
  ///Number of element of this array.
  int size;
  ///Array of pointers to this array's elements.
  void** array;
}SArray;

/**
 * Array definition.
 */
typedef SArray* Array;

//==============================================================================

/**
 * Creates an empty array, with the specified initial capacity.
 *
 * The initial capacity must be a positive number.
 *
 * @param size the initial capacity of the array
 *
 * @return
 * <tt>NULL</tt> if an error occurred\n
 * the new array otherwise
 */
Array newArray(int size);

/**
 * Deletes an array.
 *
 * @attention
 * This function only frees the memory used by the array.  It does not free the
 * memory used by elements the array contains.
 *
 * @param array the array to be deleted
 */
void arrayDelete(Array array);

/**
 * Inserts an new element at the specified position of an array.
 *
 * The position, specified by argument <tt>index</tt>, must be a non negative
 * integer.  If necessary, the capacity of the array will be increased to
 * <tt>index+1</tt>.
 *
 * If the position is already filled, the <tt>replace</tt> argument specifies
 * whether the new element should be added (it will be added only if
 * <tt>replace!=0</tt>).
 *
 * @attention
 * If the new element is <tt>NULL</tt>, it will not be inserted, and the size
 * of the array will not change.
 *
 * @param array   the array
 * @param index   the index at which the new element is to be inserted
 * @param elem    the element to be inserted
 * @param replace specify whether old value will be replaced
 *
 * @return
 * 0 if the new element was inserted\n
 * 1 if the position was already filled\n
 * 2 if the position was not valid\n
 * 3 if it was not possible increase the array size
 */
int arrayInsert(Array array,int index,void* elem,int replace);

/**
 * Removes the element at the specified position of an array.
 *
 * Provides the value of the removed element if the value of <tt>elem</tt> is
 * not <tt>NULL</tt>.
 *
 * @attention
 * This function does not free the memory used by the removed element.
 *
 * @param array the array
 * @param index the index of the element to be removed
 * @param elem  pointer where the removed element should be put (or
 * <tt>NULL</tt>)
 *
 * @return
 * 0 if an element was removed from the specified position\n
 * 1 otherwise
 */
int arrayRemove(Array array,int index,void** elem);

/**
 * Provides the element at the specified position of an array.
 * 
 * If there is no element at the specified position, it will be put the value
 * <tt>NULL</tt> at <tt>elem</tt>.
 * 
 * @attention
 * This function puts at <tt>elem</tt> a pointer to the element at the specified
 * position.  Changes to this element will affect the element in the array.
 *
 * @param array the array
 * @param index the index of the element to be provided
 * @param elem  pointer where the element at the specified position will be put
 *
 * @return
 * 0 if there was an element at the specified position\n
 * 1 otherwise
 */
int arrayAt(Array array,int index,void** elem);

/**
 * Increases the capacity of an array.
 *
 * The new capacity must be greater than the current one.
 *
 * @param array the array
 * @param size  the new capacity
 *
 * @return
 * 0 if the capacity of the array was increased\n
 * 1 if it was not possible change the array capacity\n
 * 2 if the new capacity was less than the current one
 */
int arrayResize(Array array,int size);

/**
 * Returns the size of an array.
 *
 * @param array the array
 *
 * @return
 * the size of the array
 */
int arraySize(Array array);

/**
 * Return the capacity of an array.
 *
 * @param array the array
 *
 * @return
 * the capacity of the array
 */
int arrayCapacity(Array array);

/**
 * Applies a function to the elements of an array.
 *
 * The function to be applied must be of type <tt>void fun(void*)</tt>.
 *
 * @param array the array
 * @param fun   the function to be applied
 *
 * @return
 * 0 if the array was not empty\n
 * 1 otherwise
 */
int arrayMap(Array array,void(*fun)(void*));

/**
 * Creates an iterator from an array.
 *
 * @see Iterator
 *
 * @param array the array
 *
 * @return
 * <tt>NULL</tt> if an error occurred\n
 * the iterator otherwise
 */
Iterator arrayIterator(Array array);

#endif
