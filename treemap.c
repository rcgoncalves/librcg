/**
 * Implementação de uma árvore binária de pesquisa equilibrada.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file treemap.c
 * @version 2.0.2
 * @date 02/2009
 */
#include <stdlib.h>
#include "treemap.h"

/**
 * Efectua uma rotação à esquerda.
 *
 * @param tree raiz da (sub)árvore que vamos rodar.
 *
 * @return nova árvore.
 */
static TreeNode leftRotate(TreeNode tree)
{
  TreeNode aux;
  
  if(tree&&tree->right)
  {
    aux=tree->right;
    tree->right=aux->left;
    aux->left=tree;

    aux->super=tree->super;
    tree->super=aux;
    if(tree->right) tree->right->super=tree;
    return aux;
  }
  else return tree;
}

//==============================================================================

/**
 * Efectua uma rotação à direita.
 *
 * @param tree raiz da (sub)árvore que vamos rodar.
 *
 * @return nova árvore.
 */
static TreeNode rightRotate(TreeNode tree)
{
  TreeNode aux;

  if(tree&&tree->left)
  {
    aux=tree->left;
    tree->left=aux->right;
    aux->right=tree;

    aux->super=tree->super;
    tree->super=aux;
    if(tree->left) tree->left->super=tree;
    return aux;
  }
  else return tree;
}

//==============================================================================

/**
 * Efectua as rotações necessária a uma árvore que está balanceada para a
 *   esquerda.
 * Esta função destina-se a (sub)árvores cujo desiquilíbrio resulte do processo
 *   de inserção de um novo elemento.
 *
 * @param tree raiz da (sub)árvore que vamos equilibrar.
 *
 * @return árvore equilibrada.
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
 * Efectua as rotações necessária a uma árvore que está balanceada para a
 *   direita.
 * Esta função destina-se a (sub)árvores cujo desiquilíbrio resulte do processo
 *   de inserção de um novo elemento.
 *
 * @param tree raiz da (sub)árvore que vamos equilibrar.
 *
 * @return árvore equilibrada.
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
 * Efectua as rotações necessária a uma árvore que está balanceada para a
 *   esquerda.
 * Esta função destina-se a (sub)árvores cujo desiquilíbrio resulte do processo
 *   de remoção de um novo elemento.
 *
 * @param tree raiz da (sub)árvore que vamos equilibrar.
 * @param h    indica se a altura da árvore foi alterada ou não.
 *
 * @return árvore equilibrada.
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
 * Efectua as rotações necessária a uma árvore que está balanceada para a
 *   direita.
 * Esta função destina-se a (sub)árvores cujo desiquilíbrio resulte do processo
 *   de remoção de um novo elemento.
 *
 * @param tree raiz da (sub)árvore que vamos equilibrar.
 * @param h    indica se a altura da árvore foi ou não alterada.
 *
 * @return árvore equilibrada.
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
 * Determina o nodo com maior chave na subárvores esquerda da árvore dada.
 *
 * @param tree árvore.
 *
 * @return maior elemento da esquerda.
 */
static TreeNode upperLeft(TreeNode tree)
{
  while(tree->right)
    tree=tree->right;

  return tree;
}

//##############################################################################

TreeMap newTree(int(*keyComp)(void*,void*))
{
  if(!keyComp) return NULL;
  else
  {
    TreeMap tree=(TreeMap)malloc(sizeof(STreeMap));
    if(!tree) return NULL;
    else
    {
      tree->keyComp=*keyComp;
      tree->size=0;
      tree->root=NULL;
      return tree;
    }
  }
}

//##############################################################################

int treeSetKComp(TreeMap tree,int(*keyComp)(void*,void*))
{
  if(!keyComp) return 1;
  else
  {
    tree->keyComp=*keyComp;
    return 0;
  }
}

//##############################################################################

/**
 * Elimina um nodo de uma (sub)árvore e todos os seus descendentes.
 *
 * @param tree raiz da árvore.
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

//##############################################################################

/**
 * Função auxiliar da função de inserção.
 *
 * @param tree    árvore onde vamos fazer a inserção.
 * @param key     chave do elemento a inserir.
 * @param val     valor associado à chave.
 * @param replace variável que indica se valores já existentes são ou não
 *                substituídos.
 * @param h       variável que permite saber se a inserção aumentou o tamanho da
 *                árvore.
 * @param comp    função que permite comparar duas chaves.
 *
 * @return nova árvore.
 */
static TreeNode treeInsAux(TreeNode tree,void* key,void* val,int replace,int* h,
    int(*comp)(void*,void*))
{
  int sig;
  
  if(!tree)
  {
    TreeNode new;
    new=(TreeNode)malloc(sizeof(STreeNode));

    if(new)
    {
      new->key=key;
      new->value=val;
      new->bf=E;
      new->super=NULL;
      new->left=NULL;
      new->right=NULL;

      *h=0;
      return new;
    }
    else
    {
      *h=2;
      return NULL;
    }
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
    return tree;
  }
}

//==============================================================================

int treeInsert(TreeMap tree,void* key,void* val,int replace)
{
  int h;
  tree->root=treeInsAux(tree->root,key,val,replace,&h,tree->keyComp);

  if(h<1)
  {
    tree->size++;
    return 0;
  }
  else return h;
}

//#############################################################################

/**
 * Função auxiliar da função de remoção.
 *
 * @param tree    árvore onde vamos fazer a inserção.
 * @param key     chave do elemento a inserir.
 * @param value   local onde será colocada a informação associada ao elemento
 *                removido.
 * @param del     função que elimina um chave.
 * @param h       variável que permite saber se a remoção aumentou o tamanho da
 *                árvore.
 * @param comp    função que permite comparar duas chaves.
 *
 * @return nova árvore.
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
    return NULL;
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
      return tree;
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
      return tree;
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
        return aux;
      }
      else if(!tree->left)
      {
        aux=tree->right;
        if(aux) aux->super=tree->super;

        if(del) del(tree->key);
        if(value) *value=tree->value;

        free(tree);
        *h=0;
        return aux;
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
        return tree;
      }
    }
  }
}

//=============================================================================

int treeRemove(TreeMap tree,void* key,void** value,void(*del)(void*))
{
  int h;
  tree->root=treeRemAux(tree->root,key,value,del,&h,tree->keyComp);

  if(h==1) return 1;
  else
  {
    tree->size--;
    return 0;
  }
}

//#############################################################################

int treeGet(TreeMap tree,void* key,void** value)
{
  TreeNode aux;
  int r;

  for(r=-1,aux=tree->root;
      aux&&(r=(*tree->keyComp)(key,aux->key));
      aux=r<0?aux->left:aux->right);

  if(r)
  {
    *value=NULL;
    return 1;
  }
  else
  {
    *value=aux->value;
    return 0;
  }
}

//#############################################################################

/**
 * Verifica se uma (sub)árvore está equilibrada na raiz e se todas as suas
 *   subárvores também estão.
 *
 * @param tree árvore.
 *
 * @return -1 se não está equilibrada;\n
 *         altura da árvore caso contrário.
 */
int treeIsAVLAux(TreeNode tree)
{
  int left,right;
  
  if(!tree) return 0;
  else
  {
    left=treeIsAVLAux(tree->left);
    right=treeIsAVLAux(tree->right);

    if(left<0||right<0) return -1;
    else if(left>right) return left-right>1?-1:++left;
    else return right-left>1?-1:++right;
  }
}

//=============================================================================

int treeIsAVL(TreeMap tree)
{
  return(treeIsAVLAux(tree->root)==-1?0:1);
}

//#############################################################################

/**
 * Determina a altura de uma (sub)árvore.
 *
 * @param tree árvore.
 *
 * @return altura da árvore.
 */
static int treeHightAux(TreeNode tree)
{
  int hLeft,hRight;
  
  if(!tree) return 0;
  else
  {
    hLeft=treeHightAux(tree->left);
    hRight=treeHightAux(tree->right);

    return(hLeft>hRight ? ++hLeft:++hRight);
  }
}

//=============================================================================

int treeHeight(TreeMap tree)
{
  if(!tree->size) return 0;
  else return treeHightAux(tree->root);
}

//#############################################################################

int treeSize(TreeMap tree)
{
  return(tree->size);
}
//#############################################################################

/**
 * Função auxiliar da função que efectua uma travessia @e In-Order da árvore.
 *
 * @param tree árvore.
 * @param fun  função que é aplicada aos elementos da árvore.
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
  if(!tree->size) return 1;
  else
  {
    treeInOAux(tree->root,fun);
    return 0;
  }
}

//#############################################################################

/**
 * Função auxiliar da função que efectua uma travessia @e Pre-Order da árvore.
 *
 * @param tree árvore.
 * @param fun  função que é aplicada aos elementos da árvore.
 */
static void treePrOAux(TreeNode tree,void(*fun)(void*,void*))
{
  if(tree)
  {
    fun(tree->key,tree->value);
    treePrOAux(tree->left,fun);
    treePrOAux(tree->right,fun);
  }
}

//=============================================================================

int treePreOrder(TreeMap tree,void(*fun)(void*,void*))
{
  if(!tree->size) return 1;
  else
  {
    treePrOAux(tree->root,fun);
    return 0;
  }
}

//#############################################################################

/**
 * Função auxiliar da função que efectua uma travessia @e Pos-Order da árvore.
 *
 * @param tree árvore.
 * @param fun  função que é aplicada aos elementos da árvore.
 */
static void treePsOAux(TreeNode tree,void(*fun)(void*,void*))
{
  if(tree)
  {
    treePsOAux(tree->left,fun);
    treePsOAux(tree->right,fun);
    fun(tree->key,tree->value);
  }
}

//=============================================================================

int treePosOrder(TreeMap tree,void(*fun)(void*,void*))
{
  if(!tree->size) return 1;
  else
  {
    treePsOAux(tree->root,fun);
    return 0;
  }
}

//#############################################################################

/**
 * Percorre uma (sub)árvore e adiciona as chaves a um iterador.
 *
 * @param tree árvore.
 * @param it   iterador onde são colocadas as chaves.
 *
 * @return 1 se ocorrer algum erro;\n
 *         0 caso contrário.
 */
static int treeKAux(TreeNode tree,Iterator it)
{
  int r=0;
  if(tree)
  {
    r=treeKAux(tree->left,it);
    r=r||itAdd(it,tree->key);
    r=r||treeKAux(tree->right,it);
  }

  return r;
}

//=============================================================================

Iterator treeKeys(TreeMap tree)
{
  Iterator it=newIt(tree->size);
  if(!it) return NULL;
  else if(treeKAux(tree->root,it))
  {
    itDelete(it);
    return NULL;
  }
  else return it;
}

//#############################################################################

/**
 * Percorre uma (sub)árvore e adiciona os valores associados às chaves a um
 *   iterador.
 *
 * @param tree árvore.
 * @param it   iterador onde são colocadas os valores associados às chaves.
 *
 * @return 1 se ocorrer algum erro;\n
 *         0 caso contrário.
 */
static int treeVAux(TreeNode tree,Iterator it)
{
  int r=0;
  if(tree)
  {
    r=treeVAux(tree->left,it);
    r=r||itAdd(it,tree->value);
    r=r||treeVAux(tree->right,it);
  }

  return r;
}

//=============================================================================

Iterator treeValues(TreeMap tree)
{
  Iterator it=newIt(tree->size);
  if(treeVAux(tree->root,it))
  {
    itDelete(it);
    return NULL;
  }
  else return it;
}
