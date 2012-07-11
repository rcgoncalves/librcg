/**
 * Implementation of a hash table.
 *
 * Provides functions to create and manipulate a hash table.
 *
 * Collisions are handled using having a list for each buckets.  When the
 * number of elements is greater than a specified ratio of the number of buckets
 * the hash table is resized.
 *
 * To use this hash table you have to provide the following functions for the
 * data type used for keys:
 *
 * <ul id="func">
 * <li><tt>int hash(void *)</tt>
 *
 * Hash function (used by <tt>@ref hashInsert</tt>, <tt>@ref hashRemove</tt>,
 * and <tt>@ref hashGet</tt>).  Generates a unique hash to a key.  This function
 * can be changed using function <tt>@ref hashSetHash</tt>.
 *
 * E.g.:
\code
int hash(void* key)
{
  int i,x;
  char* aux=key;
  for(i=0,x=0;i<32&&aux[i]!='\0';x+=aux[i],i++);
  return x;
}
\endcode
 * </li>
 * 
 * <li><tt>int keyEquals(void* key1,void* key2)</tt>
 *
 * Compares two keys (used by <tt>@ref hashInsert</tt>,
 * <tt>@ref hashRemove</tt>, and <tt>@ref hashGet</tt>). It should return 0 if
 * <tt>key1</tt> is equal to <tt>key2</tt>, and a value different from 0
 * otherwise.  This function can be changed using function
 * <tt>@ref hashSetEquals</tt>.
 *
 * E.g.:
\code
int keyEquals(void* key1,void* key2)
{
  if(key1&&key2) return srtcmp((char*)key1,(char*)key2);
  else !(key1==key2);
}
\endcode
 * </li>
 * </ul>
 * 
 * @author Rui Carlos Gonçalves
 * @file hashmap.h
 * @version 3.0
 * @date 10/2011
 */
#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include "iterator.h"

/**
 * Hash table node structure.
 */
typedef struct sHashNode
{
  ///Node's key.
  void* key;
  ///Node's value.
  void* value;
  ///Next node.
  struct sHashNode*  next;
}SHashNode;

/**
 * Hash table node definition.
 */
typedef SHashNode* HashNode;

/**
 * Hash table structure.
 */
typedef struct sHashMap
{
  ///Hash function of this hash table.
  int(*hash)(void*);
  ///Comparison function of this hash table.
  int(*equals)(void*,void*);
  ///Number of elements of this hash table.
  int size;
  ///Number of buckets of this hash table.
  int length;
  ///Load factor.
  float factor;
  ///Buckets of this hash table.
  HashNode* elems;
}SHashMap;

/**
 * Hash table definition.
 */
typedef SHashMap* HashMap;

//==============================================================================

/**
 * Creates a hash table.
 *
 * The load factor (<tt>factor</tt>) specifies when the number of buckets should
 * be increased (it will be increased when <tt>size > factor*length</tt>).  The
 * load factor must be greater than or equal to 0.1 (otherwise value 0.1 will be
 * used).
 *
 * @param size   the initial number of buckets
 * @param factor the load factor
 * @param hash   the hash function
 * @param equals the comparison function
 *
 * @return
 * <tt>NULL</tt> if an error occurred\n
 * the new hash table otherwise
 */
HashMap newHash(int size,float factor
               ,int(*hash)(void*)
               ,int(*equals)(void*,void*)
               );

/**
 * Sets the hash function of a hash table.
 *
 * @param hmap the hash table
 * @param hash the new hash function
 *
 * @return
 * 1 if <tt>hash</tt> was equal to <tt>NULL</tt> (no change was made)\n
 * 0 otherwise
 */
int hashSetHash(HashMap hmap,int(*hash)(void*));

/**
 * Sets the comparison function of a hash table.
 *
 * @param hmap   the hash table
 * @param equals the new comparison function
 *
 * @return 
 * 1 if <tt>equals</tt> was equal to <tt>NULL</tt> (no change was made)\n
 * 0 otherwise
 */
int hashSetEquals(HashMap hmap,int(*equals)(void*,void*));

/**
 * Sets the load factor of a hash table.
 *
 * The new value must be greater than or equal to 0.1.
 *
 * @param hmap   the hash table
 * @param factor the new load factor
 *
 * @return
 * 1 if <tt>factor</tt> was less than 0.1 (no change was made)\n
 * 0 otherwise
 */
int hashSetFactor(HashMap hmap,int factor);

/**
 * Deletes an hash table.
 *
 * @attention
 * This function only free the memory used by the hash table.  It does not free
 * the memory used by elements the hash table contains.
 *
 * @param hmap the hash table to be deleted
 */
void hashDelete(HashMap hmap);

/**
 * Associates a value to a key in a hash table.
 *
 * If the key already had a value, the <tt>replace</tt> argument specifies
 * whether the new element should be added (it will be added only if
 * <tt>replace!=0</tt>).
 *
 * @param hmap    the hash table
 * @param key     the key
 * @param value   the value to be inserted
 * @param replace specifies whether an old value shall be replaced
 *
 * @return
 * 0 if the value was inserted\n
 * 1 if the key already had a value\n
 * 2 if an error occurred
 */
int hashInsert(HashMap hmap,void* key,void* value,int replace);

/**
 * Removes the mapping for a key from an hash table.
 *
 * Provides the value of the removed element if the value of <tt>elem</tt> is
 * not <tt>NULL</tt>.
 *
 * @attention
 * This function does not free the memory used by the removed element.
 * To free the memory used by its key, you have to provide the argument
 * <tt>del</tt>.
 *
 * @param hmap  the hash table
 * @param key   key whose mapping is to be removed
 * @param value pointer where the removed element shall be put (or
 * <tt>NULL</tt>)
 * @param del   function to free the memory used by the key (or <tt>NULL</tt>)
 *
 * @return
 * 0 if an element was removed from the specified position\n
 * 1 otherwise
 */
int hashRemove(HashMap hmap,void* key,void** value,void(*del)(void*));

/**
 * Provides the mapping for a key from a hash table.
 *
 * If there is no mapping for the specified key, it will be put the value
 * <tt>NULL</tt> at <tt>value</tt>.  However, the <tt>NULL</tt> value may also
 * say that the mapping for the specified key was <tt>NULL</tt>.  Check the
 * returned value in order to know whether the key was in the hash table.
 *
 * @attention
 * This function puts at <tt>value</tt> a pointer to the mapping of the
 * specified key.  Changes to this value will affect the value in the hash
 * table.
 *
 * @param hmap  the hash table
 * @param key   key whose mapping is to be provided
 * @param value pointer where the mapping value will be put
 *
 * @return
 * 0 if there was a mapping for the specified key\n
 * 1 otherwise
 */
int hashGet(HashMap hmap,void* key,void** value);

/**
 * Returns the number of elements present in a hash table.
 *
 * @param hmap the hash table
 *
 * @return
 * the number of elements present in the hash table
 */
int hashSize(HashMap hmap);

/**
 * Creates an iterator from the keys of an hash table.
 *
 * @see Iterator
 *
 * @param hmap the hash map
 *
 * @return
 * <tt>NULL</tt> if an error occurred\n
 * the iterator otherwise
 */
Iterator hashKeys(HashMap hmap);

/**
 * Creates an iterator from the values of an hash table.
 *
 * @see Iterator
 *
 * @param hmap the hash table
 *
 * @return
 * <tt>NULL</tt> if an error occurred\n
 * the iterator otherwise
 */
Iterator hashValues(HashMap hmap);

#endif
