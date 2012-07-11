/**
 * Implementation of an AVL tree (self-balancing binary search tree).
 *
 * @author Rui Carlos Gonçalves
 * @file treemap.c
 * @version 3.0
 * @date 07/2012
 */
#include <stdlib.h>
#include "treemap.h"

/**
 * Rotates a tree to left.
 *
 * @param tree the root of the tree to rotate
 *
 * @return
 * the new tree
 */
static TreeNode leftRotate(TreeNode tree)
{
  TreeNode aux=tree;
  if(tree&&tree->right)
  {
    aux=tree->right;
    tree->right=aux->left;
    aux->left=tree;
    aux->super=tree->super;
    tree->super=aux;
    if(tree->right) tree->right->super=tree;
  }
  return aux;
}

//==============================================================================

/**
 * Rotates a tree to right.
 *
 * @param tree the root of the tree to rotate
 *
 * @return
 * the new tree
 */
static TreeNode rightRotate(TreeNode tree)
{
  TreeNode aux=tree;
  if(tree&&tree->left)
  {
    aux=tree->left;
    tree->left=aux->right;
    aux->right=tree;

    aux->super=tree->super;
    tree->super=aux;
    if(tree->left) tree->left->super=tree;
  }
  return aux;
}

//==============================================================================

/**
 * Rebalances a tree that is balanced to the left as result of an insertion
 * operation.
 *
 * @param tree the root of the tree to rebalance
 *
 * @return
 * the new tree
 */
static TreeNode leftBalance(TreeNode tree)
{
  if(tree&&tree->left)
  {
    if(tree->left->bf==L)
    {
      tree=rightRotate(tree);
      tree->bf=E;
      tree->right->bf=E;
    }
    else
    {
      tree->left=leftRotate(tree->left);
      tree=rightRotate(tree);
      switch(tree->bf)
      {
        case L : tree->left->bf=E;
                 tree->right->bf=R;
                 break;
        case E : tree->left->bf=E;
                 tree->right->bf=E;
                 break;
        case R : tree->left->bf=L;
                 tree->right->bf=E;
                 break;
      }
      tree->bf=E;
    }
  }
  else
  {
    tree=rightRotate(tree);
    tree->right->bf=E;
    tree->left->bf=E;
  }
  return tree;
}

//==============================================================================

/**
 * Rebalances a tree that is balanced to the right as result of an insertion
 * operation.
 *
 * @param tree the root of the tree to rebalance
 *
 * @return
 * the new tree
 */
static TreeNode rightBalance(TreeNode tree)
{
  if(tree&&tree->right)
  {
    if(tree->right->bf==R)
    {
      tree=leftRotate(tree);
      tree->bf=E;
      tree->left->bf=E;
    }
    else
    {
      tree->right=rightRotate(tree->right);
      tree=leftRotate(tree);
      switch(tree->bf)
      {
        case L : tree->left->bf=E;
                 tree->right->bf=R;
                 break;
        case E : tree->left->bf=E;
                 tree->right->bf=E;
                 break;
        case R : tree->left->bf=L;
                 tree->right->bf=E;
                 break;
      }
      tree->bf=E;
    }
  }
  else
  {
    tree=rightRotate(tree);
    tree->left->bf=E;
    tree->right->bf=E;
  }
  return tree;
}

//=============================================================================

/**
 * Rebalances a tree that is balanced to the left as result of a remotion
 * operation.
 *
 * @param tree the root of the tree to rebalance
 * @param h    specifies whether the height of the tree changed
 *
 * @return
 * the new tree
 */
static TreeNode rLeftBalance(TreeNode tree,int* h)
{
  if(tree&&tree->left)
  {
    switch(tree->left->bf)
    {
      case L : tree=rightRotate(tree);
               tree->bf=E;
               tree->right->bf=E;
               break;
      case E : tree=rightRotate(tree);
               tree->bf=R;
               tree->bf=L;
               *h=2;
               break;
      case R : tree->left=leftRotate(tree->left);
               tree=rightRotate(tree);
               switch(tree->bf)
               {
                 case L : tree->left->bf=E;
                          tree->right->bf=E;
                          break;
                 case E : tree->left->bf=E;
                          tree->right->bf=E;
                          break;
                 case R : tree->left->bf=L;
                          tree->right->bf=E;
                          break;
               }
               tree->bf=E;
               break;
    }
  }
  return tree;
}

//==============================================================================

/**
 * Rebalances a tree that is balanced to the right as result of a remotion
 * operation.
 *
 * @param tree the root of the tree to rebalance
 * @param h    specifies whether the height of the tree changed
 *
 * @return
 * the new tree
 */
static TreeNode rRightBalance(TreeNode tree,int* h)
{
  if(tree&&tree->right)
  {
    switch(tree->right->bf)
    {
      case L : tree->right=rightRotate(tree->right);
               tree=leftRotate(tree);
               switch(tree->bf)
               {
                 case L : tree->left->bf=E;
                          tree->right->bf=R;
                          break;
                 case E : tree->left->bf=E;
                          tree->right->bf=E;
                          break;
                 case R : tree->left->bf=L;
                          tree->right->bf=E;
                          break;
               }
               tree->bf=E;
               break;
      case E : tree=leftRotate(tree);
               tree->bf=L;
               tree->left->bf=R;
               *h=2;
               break;
      case R : tree=leftRotate(tree);
               tree->bf=E;
               tree->left->bf=E;
               break;
    }
  }
  return tree;
}

//==============================================================================

/**
 * Returns the node with the greatest key on the left subtree of a tree.
 *
 * @param tree the tree
 *
 * @return
 * the node with the greatest key on the left subtree of the tree
 */
static TreeNode upperLeft(TreeNode tree)
{
  while(tree->right) tree=tree->right;
  return tree;
}

//==============================================================================

TreeMap newTree(int(*keyComp)(void*,void*))
{
  TreeMap tree=NULL;
  if(keyComp)
  {
    tree=malloc(sizeof(STreeMap));
    if(tree)
    {
      tree->keyComp=*keyComp;
      tree->size=0;
      tree->root=NULL;
    }
  }
  return tree;
}

//==============================================================================

int treeSetKComp(TreeMap tree,int(*keyComp)(void*,void*))
{
  int result=0;
  if(!keyComp) result=1;
  else tree->keyComp=*keyComp;
  return result;
}

//==============================================================================

/**
 * Deletes a node of a tree and all of its children nodes.
 *
 * @param tree the tree
 */
static void treeDelAux(TreeNode tree)
{
  if(tree)
  {
    treeDelAux(tree->left);
    treeDelAux(tree->right);
    free(tree);
  }
}

//==============================================================================

void treeDelete(TreeMap tree)
{
  treeDelAux(tree->root);
  free(tree);
}

//==============================================================================

/**
 * Insertion auxiliary function.
 *
 * @param tree    the tree
 * @param key     the key
 * @param val     the value to be inserted
 * @param replace specifies whether an old value shall be replaced
 * @param h       specifies whether the height of the tree changed (h<0?), and
 * whether an error occurred (h>0?)
 * @param comp    key comparison function
 *
 * @return
 * new tree
 */
static TreeNode treeInsAux(TreeNode tree,void* key,void* val,int replace,int* h,
    int(*comp)(void*,void*))
{
  int sig;
  if(!tree)
  {
    tree=malloc(sizeof(STreeNode));
    if(tree)
    {
      tree->key=key;
      tree->value=val;
      tree->bf=E;
      tree->super=NULL;
      tree->left=NULL;
      tree->right=NULL;
      *h=0;
    }
    else *h=2;
  }
  else
  {
    sig=comp(key,tree->key);
    if(sig<0)
    {
      tree->left=treeInsAux(tree->left,key,val,replace,h,comp);
      if(!(*h))
      {
        tree->left->super=tree;
        switch(tree->bf)
        {
          case L : tree=leftBalance(tree);
                   tree->bf=E;
                   *h=-1;
                   break;
          case E : tree->bf=L;
                   break;
          case R : tree->bf=E;
                   *h=-1;
                   break;
        }
      }
    }
    else if(sig>0)
    {
      tree->right=treeInsAux(tree->right,key,val,replace,h,comp);
      if(!(*h))
      {
        tree->right->super=tree;
        switch(tree->bf)
        {
          case L : tree->bf=E;
                   *h=-1;
                   break;
          case E : tree->bf=R;
                   break;
          case R : tree=rightBalance(tree);
                   tree->bf=E;
                   *h=-1;
                   break;
        }
      }
    }
    else
    {
      if(replace) tree->value=val;
      *h=1;
    }
  }
  return tree;
}

//==============================================================================

int treeInsert(TreeMap tree,void* key,void* val,int replace)
{
  int h,result=0;
  tree->root=treeInsAux(tree->root,key,val,replace,&h,tree->keyComp);
  if(h<1) tree->size++;
  else result=h;
  return result;
}

//==============================================================================

/**
 * Remotion auxiliary function.
 *
 * @param tree    the tree
 * @param key     key whose mapping is to be removed
 * @param value   pointer where the removed element shall be put (or
 * <tt>NULL</tt>)
 * @param del     function to free the memory used by the key (or <tt>NULL</tt>)
 * @param h       specifies whether the height of the tree changed
 * @param comp    key comparison function
 *
 * @return
 * new tree
 */
static TreeNode treeRemAux(TreeNode tree,void* key,void** value,
    void(*del)(void*),int* h,int(*comp)(void*,void*))
{
  int sig;
  TreeNode aux;
  if(!tree)
  {
    if(value) *value=NULL;
    *h=1;
    aux=NULL;
  }
  else
  {
    sig=comp(key,tree->key);
    if(sig<0)
    {
      tree->left=treeRemAux(tree->left,key,value,del,h,comp);
      if(!(*h))
      {
        switch(tree->bf)
        {
          case L : tree->bf=E;
                   break;
          case E : tree->bf=R;
                   *h=2;
                   break;
          case R : tree=rRightBalance(tree,h);
                   break;
        }
      }
      aux=tree;
    }
    else if(sig>0)
    {
      tree->right=treeRemAux(tree->right,key,value,del,h,comp);
      if(!(*h))
      {
        switch(tree->bf)
        {
          case L : tree=rLeftBalance(tree,h);
                   break;
          case E : tree->bf=L;
                   *h=2;
                   break;
          case R : tree->bf=E;
                   break;
        }
      }
      aux=tree;
    }
    else
    {
      if(!tree->right)
      {
        aux=tree->left;
        if(aux) aux->super=tree->super;
        if(del) del(tree->key);
        if(value) *value=tree->value;
        free(tree);
        *h=0;
      }
      else if(!tree->left)
      {
        aux=tree->right;
        if(aux) aux->super=tree->super;
        if(del) del(tree->key);
        if(value) *value=tree->value;
        free(tree);
        *h=0;
      }
      else
      {
        if(del) del(tree->key);
        if(value) *value=tree->value;
        aux=upperLeft(tree->left);
        tree->key=aux->key;
        tree->value=aux->value;
        aux->value=NULL;
        tree->left=treeRemAux(tree->left,aux->key,NULL,NULL,h,comp);
        if(!(*h))
        {
          switch(tree->bf)
          {
            case L : tree->bf=E;
                     break;
            case E : tree->bf=R;
                     *h=2;
                     break;
            case R : tree=rRightBalance(tree,h);
                     break;
          }
        }
        aux=tree;
      }
    }
  }
  return aux;
}

//=============================================================================

int treeRemove(TreeMap tree,void* key,void** value,void(*del)(void*))
{
  int h,result=0;
  tree->root=treeRemAux(tree->root,key,value,del,&h,tree->keyComp);
  if(h==1) result=1;
  else tree->size--;
  return result;
}

//==============================================================================

int treeGet(TreeMap tree,void* key,void** value)
{
  TreeNode aux;
  int r,result=0;
  for(r=-1,aux=tree->root;
      aux&&(r=(*tree->keyComp)(key,aux->key));
      aux=r<0?aux->left:aux->right);
  if(r)
  {
    *value=NULL;
    result=1;
  }
  else *value=aux->value;
  return result;
}

//==============================================================================

/**
 * Checks if a tree is balanced.
 *
 * @param tree the tree
 *
 * @return
 * -1 is the tree is not balanced\n
 * tree height otherwise
 */
int treeIsBalancedAux(TreeNode tree)
{
  int left,right,result=0;
  if(tree)
  {
    left=treeIsBalancedAux(tree->left);
    right=treeIsBalancedAux(tree->right);
    if(left<0||right<0) result=-1;
    else if(left>right) result=left-right>1?-1:++left;
    else result=right-left>1?-1:++right;
  }
  return result;
}

//=============================================================================

int treeIsBalanced(TreeMap tree)
{
  return treeIsBalancedAux(tree->root)==-1?0:1;
}

//==============================================================================

/**
 * Returns the height of a tree.
 *
 * @param tree the tree
 *
 * @return
 * the height of the tree
 */
static int treeHightAux(TreeNode tree)
{
  int hLeft,hRight,result=0;
  if(tree)
  {
    hLeft=treeHightAux(tree->left);
    hRight=treeHightAux(tree->right);
    result=hLeft>hRight?++hLeft:++hRight;
  }
  return result;
}

//=============================================================================

int treeHeight(TreeMap tree)
{
  return treeHightAux(tree->root);
}

//==============================================================================

int treeSize(TreeMap tree)
{
  return tree->size;
}

//==============================================================================

/**
 * Inorder traversal auxiliary function.
 *
 * @param tree the tree
 * @param fun  the function to be applied
 */
static void treeInOAux(TreeNode tree,void(*fun)(void*,void*))
{
  if(tree)
  {
    treeInOAux(tree->left,fun);
    fun(tree->key,tree->value);
    treeInOAux(tree->right,fun);
  }
}

//=============================================================================

int treeInOrder(TreeMap tree,void(*fun)(void*,void*))
{
  int result=0;
  if(!tree->size) result=1;
  else treeInOAux(tree->root,fun);
  return result;
}

//==============================================================================

/**
 * Preorder traversal auxiliary function.
 *
 * @param tree the tree
 * @param fun  the function to be applied
 */

static void treePreOrderAux(TreeNode tree,void(*fun)(void*,void*))
{
  if(tree)
  {
    fun(tree->key,tree->value);
    treePreOrderAux(tree->left,fun);
    treePreOrderAux(tree->right,fun);
  }
}

//=============================================================================

int treePreOrder(TreeMap tree,void(*fun)(void*,void*))
{
  int result=0;
  if(!tree->size) result=1;
  else treePreOrderAux(tree->root,fun);
  return result;
}

//==============================================================================

/**
 * Postorder traversal auxiliary function.
 *
 * @param tree the tree
 * @param fun  the function to be applied
 */
static void treePostOrderAux(TreeNode tree,void(*fun)(void*,void*))
{
  if(tree)
  {
    treePostOrderAux(tree->left,fun);
    treePostOrderAux(tree->right,fun);
    fun(tree->key,tree->value);
  }
}

//=============================================================================

int treePostOrder(TreeMap tree,void(*fun)(void*,void*))
{
  int result=0;
  if(!tree->size) result=1;
  else treePostOrderAux(tree->root,fun);
  return result;
}

//=============================================================================

/**
 * Traverses a tree and adds the keys to an iterator.
 *
 * @param tree the tree
 * @param it   the iterator
 *
 * @return
 * 1 if an error occurred\n
 * 0 otherwise
 */
static int treeKAux(TreeNode tree,Iterator it)
{
  int result=0;
  if(tree)
  {
    result=treeKAux(tree->left,it);
    result=result||itAdd(it,tree->key);
    result=result||treeKAux(tree->right,it);
  }
  return result;
}

//=============================================================================

Iterator treeKeys(TreeMap tree)
{
  Iterator it=newIt(tree->size);
  if(it&&treeKAux(tree->root,it))
  {
    itDelete(it);
    it=NULL;
  }
  return it;
}

//=============================================================================

/**
 * Traverses a tree and adds the values to an iterator.
 *
 * @param tree the tree
 * @param it   the iterator
 *
 * @return
 * 1 if an error occurred\n
 * 0 otherwise
 */

static int treeVAux(TreeNode tree,Iterator it)
{
  int result=0;
  if(tree)
  {
    result=treeVAux(tree->left,it);
    result=result||itAdd(it,tree->value);
    result=result||treeVAux(tree->right,it);
  }
  return result;
}

//=============================================================================

Iterator treeValues(TreeMap tree)
{
  Iterator it=newIt(tree->size);
  if(it&&treeVAux(tree->root,it))
  {
    itDelete(it);
    it=NULL;
  }
  return it;
}
