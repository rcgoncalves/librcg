/**
 * Implementação de uma árvore binária de pesquisa equilibrada.
 * Esta biblioteca disponibiliza um conjunto de funções que permitem manipular
 *   uma árvore binária de pesquisa equilibrada.\n
 *
 * Na criação de uma árvore é necessário especificar a função que compara as
 *   chaves.
 * @htmlonly <a id="func" name="func"></a>@endhtmlonly
 *
 * <tt>int keyComp(void* key1,void* key2)</tt>\n
 * (usada pelas funções <tt>@ref treeInsert</tt>, <tt>@ref treeRemove</tt> e 
 * <tt>@ref treeGet</tt>); deve devolver um valor menor do que 0 se @a key1 for
 * menor do que @a key2, um valor maior do que 0 se @a key1 for maior do que
 * @a key2 e 0 caso contrário; pode ser alterada através da função <tt>@ref
 * treeSetKComp</tt>.
@code
int keyComp(void* key1,void* key2)
{
  if(key1&&key2) return strcmp((char*)key1,(char*)key2);
  else return 0;
}
@endcode
 * 
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file treemap.h
 * @version 2.0.2
 * @date 02/2009
 */
#ifndef _TREEMAP_
#define _TREEMAP_

#include "iterator.h"

/**
 * Tipo que indica para onde uma árvore está balanceada.
 */
typedef enum eBFactor{L,E,R}BFactor;

/**
 * Estrutura do nodo da árvore.
 */
typedef struct sTreeNode
{
  ///Apontador para a chave do nodo.
  void* key;
  ///Apontador para o valor associado à chave.
  void* value;
  ///Factor de balanceamento.
  BFactor bf;
  ///Apontador para o nodo superior.
  struct sTreeNode* super;
  ///Apontador para a subárvore esquerda.
  struct sTreeNode* left;
  ///Apontador para a subárvore direita.
  struct sTreeNode* right;
}STreeNode;

/**
 * Definição do apontador para os nodos da árvore.
 */
typedef STreeNode* TreeNode;

/**
 * Estrutura de uma árvore.
 */
typedef struct sTreeMap
{
  ///Função que compara duas chaves.
  int(*keyComp)(void*,void*);
  ///Número de elementos da árvore.
  int size;
  ///Apontador para a raiz da árvore.
  TreeNode root;
}STreeMap;

/**
 * Definição da árvore.
 */
typedef STreeMap* TreeMap;

//##############################################################################

/**
 * Cria uma árvore.
 * Se não for possível criar a árvore devolve NULL.
 * Tem que ser especificada a função que compara chaves.
 * Esta função pode ser alterada a qualquer momento, utilizando a função
 *   <tt>@ref treeSetKComp</tt>.
 *
 * @htmlonly (Ver <a href=#func>descrição das funções</a>)@endhtmlonly
 *
 * @param keyComp função que compara duas chaves.
 *
 * @return árvore inicializada ou NULL.
 */
TreeMap newTree(int(*keyComp)(void*,void*));

/**
 * Altera a função que compara as chaves de uma árvore.
 * O valor de @a keyComp não pode ser NULL.
 *
 * @param tree    árvore.
 * @param keyComp nova função.
 *
 * @return 1 se @a keyComp for NULL (não é efectuada qualquer alteração);\n
 *         0 caso contrário.
 */
int treeSetKComp(TreeMap tree,int(*keyComp)(void*,void*));

/**
 * Elimina uma árvore.
 *
 * @attention apenas liberta a memória referente à estrutura da árvore; não
 *            liberta o espaço ocupado pelos elementos nela contidos.
 *
 * @param tree árvore.
 */
void treeDelete(TreeMap tree);

/**
 * Insere um par chave/valor numa árvore.
 * Caso a chave já exista, a variável @a replace determina se o valor antigo é
 *   ou não substituído (caso seja não há substituição, caso tenha outro valor
 *   o novo elemento é inserido).
 *
 * @param tree    árvore.
 * @param key     chave.
 * @param value   valor associado à chave.
 * @param replace variável que determina se os elementos já existentes são ou
 *                não substituídos.
 *
 * @return 0 se o elemento for inserido;\n
 *         1 se a árvore já possuia a chave indicada;\n
 *         2 caso não seja possível alocar memória para o novo elemento.
 */
int treeInsert(TreeMap tree,void* key,void* value,int replace);

/**
 * Remove um elemento de uma árvore.
 * Permite devolver o valor removido, caso o valor de @a value seja diferente de
 *   NULL.
 * Se a chave não existir ou o elemento não for removido é colocado o valor NULL
 *   em @a value.
 *
 * @attention esta função não liberta o espaço ocupado pelo valor associado à
 *            chave; já o espaço ocupado pela chave removida, se @a del for
 *            diferente de NULL, será libertado.
 *
 * @param tree  árvore.
 * @param key   chave que queremos remover.
 * @param value endereço onde é colocado o elemento removido (ou NULL).
 * @param del   função que elimina uma chave (ou NULL).
 *
 * @return 0 se o elemento for removido;\n
 *         1 se a chave não existir;\n
 */
int treeRemove(TreeMap tree,void* key,void** value,void(*del)(void*));

/**
 * Procura um elemento numa árvore.
 * Devolve o valor associado a uma chave, se esta existir.
 * Se a chave não existir é colocado o valor NULL em @a value.
 *
 * @attention esta função coloca em @a value o endereço do valor pretendido;
 *            depois de executar esta função é aconselhável fazer uma cópia do
 *            mesmo e passar a trabalhar com a cópia para que não haja problemas
 *            de partilha de referências.
 * 
 * @param tree  árvore.
 * @param key   chave que procuramos.
 * @param value endereço onde é colocado o resultado.
 *
 * @return 0 se o elemento existir;\n
 *         1 se o elemento não existir.
 */
int treeGet(TreeMap tree,void* key,void** value);

/**
 * Verifica se uma árvore está equilibrada.
 * Considera-se que a árvore está equilibrada se a diferença entre a altura das
 *   subárvores esquerda e direita (em todos os nodos) não for superior a 1.
 *
 * @param tree árvore.
 *
 * @return 0 se a árvore não estiver equilibrada;\n
 *         1 caso contrário.
 */
int treeIsAVL(TreeMap tree);

/**
 * Determina a altura de uma árvore.
 *
 * @param tree árvore.
 *
 * @return altura da árvore.
 */
int treeHeight(TreeMap tree);

/**
 * Determina o número de elementos de uma árvore.
 * Devolve o valor do campo @a size da árvore.
 *
 * @param tree árvore.
 *
 * @return número de elementos da árvore.
 */
int treeSize(TreeMap tree);

/**
 * Efectua uma travessia @e In-Order de uma árvore.
 * Aplica a função @c fun a todos os elementos da árvore.\n
 * A função @c fun tem que ser do tipo: <tt>void fun(void*,void*)</tt>.
 * 
 * @param tree árvore.
 * @param fun  função a ser aplicada.
 *
 * @return 0 se a árvore não estiver vazia;\n
 *         1 se a árvore estiver vazia.
 */
int treeInOrder(TreeMap tree,void(*fun)(void*,void*));

/**
 * Efectua uma travessia @e Pre-Order de uma árvore.
 * Aplica a função @c fun a todos os elementos da árvore.\n
 * A função @c fun tem que ser do tipo: <tt>void fun(void*,void*)</tt>.
 * 
 * @param tree árvore.
 * @param fun  função a ser aplicada.
 *
 * @return 0 se a árvore não estiver vazia;\n
 *         1 se a árvore estiver vazia.
 */
int treePreOrder(TreeMap tree,void(*fun)(void*,void*));

/**
 * Efectua uma travessia @e Pos-Order de uma árvore.
 * Aplica a função @c fun a todos os elementos da árvore.\n
 * A função @c fun tem que ser do tipo: <tt>void fun(void*,void*)</tt>.
 * 
 * @param tree árvore.
 * @param fun  função a ser aplicada.
 *
 * @return 0 se a árvore não estiver vazia;\n
 *         1 se a árvore estiver vazia.
 */
int treePosOrder(TreeMap tree,void(*fun)(void*,void*));

/**
 * Cria um iterador a partir das chaves de uma árvore.
 * Faz uma travessia @e In-Order da árvore e "coloca" as referências para as
 *   chaves num iterador.
 * Se ocorrer algum erro a função devolve NULL.
 *
 * @see Iterator
 *
 * @param tree árvore.
 *
 * @return iterador criado ou NULL.
 */
Iterator treeKeys(TreeMap tree);

/**
 * Cria um iterador a partir dos valores associados às chaves de uma árvore.
 * Faz uma travessia @e In-Order da árvore e "coloca" as referências para os 
 *   "valores" num iterador.
 * Se ocorrer algum erro a função devolve NULL.
 *
 * @see Iterator
 *
 * @param tree árvore.
 *
 * @return iterador criado ou NULL.
 */
Iterator treeValues(TreeMap tree);

#endif
