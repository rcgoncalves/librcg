/**
 * Implementation of an iterator.
 * Iterators contain a sequence of pointers to the elements to be iterated.
 *
 * @author Rui Carlos Gonçalves <rcgoncalves.pt@gmail.com>
 * @file iterator.h
 * @version 3.0
 * @date 12/2011
 */
#ifndef _ITERATOR_H_
#define _ITERATOR_H_

/**
 * Iterator structure.
 */
typedef struct sIterator
{
  ///Capacity of this iterator..
  int capacity;
  ///Number of elements of this iterator.
  int size;
  ///Current position of this iterator.
  int pos;
  ///Elements of this iterator.
  void** values;
}SIterator;

/**
 * Iterator definition.
 */
typedef SIterator* Iterator;

//==============================================================================

/**
 * Creates an iterator.
 *
 * @param size the capacity
 *
 * @return
 * <tt>NULL</tt> if an error occurred\n
 * the new iterator otherwise
 */
Iterator newIt(int size);

/**
 * Deletes an iterator.
 * 
 * @param it the iterator to be deleted
 */
void itDelete(Iterator it);

/**
 * Adds an element to an iterator.
 * In case the iterator is full, the element is not added.
 *
 * @param it  the iterator
 * @param val the value to be added
 *
 * @return
 * 0 if the value was added\n
 * 1 if the iterator was full
 */
int itAdd(Iterator it,void* val);

/**
 * Provides the next element of an iterator.
 *
 * @param it  the iterator
 * @param val pointer were the next element should be put
 *
 * @return
 * 0 if the next element was provided\n
 * 1 otherwise
 */
int itNext(Iterator it,void** val);

/**
 * Checks if there is "next".
 *
 * @param it the iterator.
 *
 * @return
 * 1 if there is "next"\n
 * 0 otherwise
 */
int itHasNext(Iterator it);

/**
 * Provides the previous element of an iterator.
 *
 * @param it  the iterator
 * @param val pointer were the previous element should be put
 *
 * @return
 * 0 if the previous element was provided\n
 * 1 otherwise
 */
int itPrev(Iterator it,void** val);

/**
 * Checks if there is "previous".
 *
 * @param it the iterator.
 *
 * @return
 * 1 if there is "previous"\n
 * 0 otherwise
 */
int itHasPrev(Iterator it);

/**
 * Provides the element at the specified position of an iterator.
 * Verifica qual o elemento numa determinada posição do array de valores de um
 *   iterador.
 *
 * @param it    the iterator
 * @param index the position
 * @param elem  pointer were the element at the specified position will be put
 *
 * @return
 * 0 if there was an element at the specified position\n
 * 1 otherwise
 */
int itAt(Iterator it,int index,void** elem);

/**
 * Sets the current position of an iterator.
 * It changes the value of field <tt>pos</tt> of an iterator (if the value og
 * <tt>n</tt> is valid).
 * 
 * @param it the iterator
 * @param n  the new position
 *
 * @return
 * -1 if the value of the new position is invalid\n
 * the old position otherwise
 */
int itSetPos(Iterator it,int n);

/**
 * Provides the current position of an iterator.
 *
 * @param it the iterator
 *
 * @return
 * the current position of the iterator
 */
int itGetPos(Iterator it);

#endif
