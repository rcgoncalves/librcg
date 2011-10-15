/**
 * Implementation of a dynamic array.
 *
 * This library provides functions to create a dynamic array with a desired
 * length.
 *
 * The array can resize itself whenever needed, while preserving the previous
 * values.
 *
 * @author Rui Carlos Gonçalves <rcgoncalves.pt@gmail.com>
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
  ///Current capacity of this.
  int capacity;
  ///Number of element of this array.
  int size;
  ///Array of pointers to this array elements.
  void** array;
}SArray;

/**
 * Array definition.
 */
typedef SArray* Array;

//##############################################################################

/**
 * Creates an empty array, with the specified initial capacity.
 *
 * The initial capacity must be a positive number.
 *
 * @param size the initial capacity of the array.
 *
 * @return
 * the new array, or <tt>NULL</tt> if an error occurs.
 */
Array newArray(int size);

/**
 * Deletes an array.
 *
 * @attention
 * This only frees the memory used by the array.  It does not free the memory
 * used by elements the array contains.
 *
 * @param array the array to be deleted.
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
 * @param array   the array.
 * @param index   the index at which the new element is to be inserted.
 * @param elem    the element to be inserted.
 * @param replace specify whether old value will be replaced.
 *
 * @return
 * 0 if the new element was inserted.\n
 * 1 if the position was already filled.\n
 * 2 if the position was not valid.\n
 * 3 if was not possible increase the array size.
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
 * @param array the array.
 * @param index the index of the element to be removed.
 * @param elem  pointer were the removed element should be put (or
 * <tt>NULL</tt>).
 *
 * @return
 * 0 if an element was removed from the specified position.\n
 * 1 otherwise.
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
 * @param array the array.
 * @param index the index of the element to provide.
 * @param elem  pointer were the element at the specified position will be put.
 *
 * @return
 * 0 if there is was an element at the specified position.\n
 * 1 otherwise.
 */
int arrayAt(Array array,int index,void** inf);

/**
 * Increases the capacity of an array.
 *
 * The new capacity must be greater than the current one.
 *
 * @param array the array.
 * @param size  the new capacity.
 *
 * @return
 * 0 if the capacity of the array was increased.\n
 * 1 if it was not possible change the array capacity.\n
 * 2 if the new capacity was less than the current one.
 */
int arrayResize(Array array,int size);

/**
 * Returns the size of an array.
 *
 * @param array the array.
 *
 * @return
 * the size of the array.
 */
int arraySize(Array array);

/**
 * Return the capacity of an array.
 *
 * @param array the array.
 *
 * @return
 * the capacity of the array.
 */
int arrayCapacity(Array array);

/**
 * Applies a function to the elements of an array.
 *
 * The function to be applied must be of type <tt>void fun(void*)</tt>.
 *
 * @param array the array.
 * @param fun   the function to be applied.
 *
 * @return
 * 0 if the array is empty.\n
 * 1 otherwise.
 */
int arrayMap(Array array,void(*fun)(void*));

/**
 * Creates an iterator from an array.
 *
 * @see Iterator
 *
 * @param array the array.
 *
 * @return
 * the iterator, or <tt>NULL</tt> if an error occurs.
 */
Iterator arrayIterator(Array array);

#endif
