/**
 * Implementation of an AVL tree (self-balancing binary search tree).
 *
 * Provides functions to create and manipulate an AVL tree.
 *
 * To use this tree you have to provide the following function for the date type
 * used for keys:
 *
 * <tt>int keyComp(void* key1,void* key2)</tt>
 * Compares two keys (used by <tt>@ref treeInsert</tt>,
 * <tt>@ref treeRemove</tt>, and <tt>@ref treeGet</tt>). It should return 0 if
 * <tt>key1</tt> is equal to <tt>key2</tt>, a value less than 0 if <tt>key1</tt>
 * is less than <tt>key2</tt>, and a value greater than 0 if <tt>key1</tt> is
 * greater than 0.  This function can be changed using function
 * <tt>@ref treeSetKComp</tt>.
 *
\code
int keyComp(void* key1,void* key2)
{
  if(key1&&key2) return strcmp((char*)key1,(char*)key2);
  else return 0;
}
\endcode
 *
 * @author Rui Carlos Gonçalves
 * @file treemap.h
 * @version 3.0
 * @date 07/2012
 */
#ifndef _TREEMAP_H_
#define _TREEMAP_H_

#include "iterator.h"

/**
 * Type that defines the balance factor of a tree.
 */
typedef enum eBFactor{L,E,R}BFactor;

/**
 * Tree node structure.
 */
typedef struct sTreeNode
{
  ///Node's key.
  void* key;
  ///Node's value.
  void* value;
  ///Node's balance factor.
  BFactor bf;
  ///Node's parent.
  struct sTreeNode* super;
  ///Node's left subtree.
  struct sTreeNode* left;
  ///Node's right subtree.
  struct sTreeNode* right;
}STreeNode;

/**
 * Tree node definition.
 */
typedef STreeNode* TreeNode;

/**
 * Tree structure.
 */
typedef struct sTreeMap
{
  ///Key comparison function of this tree.
  int(*keyComp)(void*,void*);
  ///Number of elements of this tree.
  int size;
  ///Root node of this tree.
  TreeNode root;
}STreeMap;

/**
 * Tree definition.
 */
typedef STreeMap* TreeMap;

//==============================================================================

/**
 * Creates a tree.
 *
 * @param keyComp the comparison function
 *
 * @return
 * <tt>NULL</tt> if an error occurred\n
 * the new tree otherwise

 */
TreeMap newTree(int(*keyComp)(void*,void*));

/**
 * Sets the comparison function of this tree.
 *
 * @param tree    the tree
 * @param keyComp the new comparison function
 *
 * @return
 * 1 if <tt>keyComp</tt> was equal to <tt>NULL</tt> (no change was made)\n
 * 0 otherwise
 */
int treeSetKComp(TreeMap tree,int(*keyComp)(void*,void*));

/**
 * Deletes a tree.
 *
 * @attention
 * This function only free the memory used by the tree.  It does not free the
 * memory used by elements the tree contains.
 *
 * @param tree the tree to be deleted
 */
void treeDelete(TreeMap tree);

/**
 * Associates a value to a key in a tree.
 *
 * If the key already had a value, the <tt>replace</tt> argument specifies
 * whether the new element should be added (it will be added only if
 * <tt>replace!=0</tt>).
 *
 * @param tree    the tree
 * @param key     the key
 * @param value   the value to be inserted
 * @param replace specifies whether an old value shall be replaced
 *
 * @return
 * 0 if the value was inserted\n
 * 1 if the key already had a value\n
 * 2 if an error occurred
 */
int treeInsert(TreeMap tree,void* key,void* value,int replace);

/**
 * Removes the mapping for a key from a tree.
 *
 * Provides the value of the removed element if the value of <tt>elem</tt> is
 * not <tt>NULL</tt>.
 *
 * @attention
 * This function does not free the memory used by the removed element.
 * To free the memory used by its key, you have to provide the argument
 * <tt>del</tt>.
 *
 * @param tree  the tree
 * @param key   key whose mapping is to be removed
 * @param value pointer where the removed element shall be put (or
 * <tt>NULL</tt>)
 * @param del   function to free the memory used by the key (or <tt>NULL</tt>)
 *
 * @return
 * 0 if an element was removed from the specified position\n
 * 1 otherwise
 */
int treeRemove(TreeMap tree,void* key,void** value,void(*del)(void*));

/**
 * Provides the mapping for a key from a tree.
 *
 * If there is no mapping for the specified key, it will be put the value
 * <tt>NULL</tt> at <tt>value</tt>.  However, the <tt>NULL</tt> value may also
 * say that the mapping for the specified key was <tt>NULL</tt>.  Check the
 * returned value in order to know whether the key was in the tree.
 *
 * @attention
 * This function puts at <tt>value</tt> a pointer to the mapping of the
 * specified key.  Changes to this value will affect the value in the tree.
 *
 * @param tree  the tree
 * @param key   key whose mapping is to be provided
 * @param value pointer where the mapping value will be put
 *
 * @return
 * 0 if there was a mapping for the specified key\n
 * 1 otherwise
 */
int treeGet(TreeMap tree,void* key,void** value);

/**
 * Checks if a tree is balanced.
 *
 * A tree is balanced if, for each node of the tree, the difference between the
 * height of the left subtree and the height of right subtree is not greater than
 * 1.
 *
 * @param tree the tree
 *
 * @return
 * 0 if the tree is not balanced\n
 * 1 otherwise
 */
int treeIsBalanced(TreeMap tree);

/**
 * Returns the height of a tree.
 *
 * @param tree the tree
 *
 * @return
 * the height of the tree
 */
int treeHeight(TreeMap tree);

/**
 * Returns the number of elements present in a tree. 
 *
 * @param tree the tree
 *
 * @return
 * the number of elements present in the tree.
 */
int treeSize(TreeMap tree);

/**
 * Applies a function to the elements of an tree (inorder traversal).
 *
 * The function to be applied must be of type <tt>void fun(void*,void*)</tt>.
 *
 * @param tree the tree
 * @param fun  the function to be applied
 *
 * @return
 * 0 if the array was not empty\n
 * 1 otherwise
 */
int treeInOrder(TreeMap tree,void(*fun)(void*,void*));

/**
 * Applies a function to the elements of an tree (preorder traversal).
 *
 * The function to be applied must be of type <tt>void fun(void*,void*)</tt>.
 *
 * @param tree the tree
 * @param fun  the function to be applied
 *
 * @return
 * 0 if the array was not empty\n
 * 1 otherwise
 */
int treePreOrder(TreeMap tree,void(*fun)(void*,void*));

/**
 * Applies a function to the elements of an tree (postorder traversal).
 *
 * The function to be applied must be of type <tt>void fun(void*,void*)</tt>.
 *
 * @param tree the tree
 * @param fun  the function to be applied
 *
 * @return
 * 0 if the array was not empty\n
 * 1 otherwise
 */
int treePostOrder(TreeMap tree,void(*fun)(void*,void*));

/**
 * Creates an iterator from the keys of a tree.
 *
 * @see Iterator
 *
 * @param tree the tree
 *
 * @return
 * <tt>NULL</tt> if an error occurred\n
 * the iterator otherwise
 */
Iterator treeKeys(TreeMap tree);

/**
 * Creates an iterator from the values of a tree.
 *
 * @see Iterator
 *
 * @param tree the tree
 *
 * @return
 * <tt>NULL</tt> if an error occurred\n
 * the iterator otherwise
 */
Iterator treeValues(TreeMap tree);

#endif
