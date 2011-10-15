/**
 * Implementation of a hash table.
 *
 * This library provides functions to create an manage a hash table.
 *
 * Collisions are handled using having a list for each buckets.  When the
 * number of elements is greater than a specified ratio of the number of buckets
 * the hash table is resized.
 *
 * To use this hash table you have to provide functions for the data type to be
 * used with the hash table.  The following functions are needed:
 *
 * <ul id="func">
 * <li><tt>int hash(void *)</tt>
 *
 * Função de hash (usada pelas funções <tt>@ref hashInsert</tt>, <tt>@ref
 * hashRemove</tt> e <tt>@ref hashGet</tt>). Associa a uma chave um número
 * único.
 *
 * E.g.:
<code>
int hash(void* key)
{
  int i,x;
  char* aux=key;
  for(i=0,x=0;i<32&&aux[i]!='\0';x+=aux[i],i++);

  return x;
}
</code>
 * </li>
 * 
 * <li><tt>int keyEquals(void* key1,void* key2)</tt>
 *
 * Função que compara duas chaves (usada pelas funções <tt>@ref hashInsert</tt>,
 * <tt>@ref hashRemove</tt> e <tt>@ref hashGet</tt>); deve devolver
 * 0 se @a key1 igual a @a key2 e um valor diferente de 0 caso contrário;
 * pode ser alterada através da função <tt>@ref hashSetEquals</tt>.
 *
 * E.g.:
<code>
int keyEquals(void* key1,void* key2)
{
  if(key1&&key2) return srtcmp((char*)key1,(char*)key2);
  else return 1;
}
</code>
 * </li>
 * </ul>
 * 
 * @author Rui Carlos Gonçalves <rcgoncalves.pt@gmail.com>
 * @file hashmap.h
 * @version 3.0
 * @date 10/2011
 */
#ifndef _HASHMAP_
#define _HASHMAP_

#include "iterator.h"

/**
 * Estrutura do nodo de uma tabela de hash.
 */
typedef struct sHashNode
{
  ///Apontador para a chave do nodo.
  void* key;
  ///Apontador para o valor associado ao nodo.
  void* value;
  ///Apontador para o próximo nodo.
  struct sHashNode*  next;
}SHashNode;

/**
 * Definição do apontador para os nodos da tabela de hash.
 */
typedef SHashNode* HashNode;

/**
 * Estrutura de uma tabela de hash.
 */
typedef struct sHashMap
{
  ///Função de hash.
  int(*hash)(void*);
  ///Função que compara duas chaves.
  int(*equals)(void*,void*);
  ///Número de elementos contidos na tabela.
  int size;
  ///Tamanho do array que constitui a tabela.
  int length;
  ///Factor de "reestruturação" da tabela.
  float factor;
  ///Tabela de apontadores.
  HashNode* elems;
}SHashMap;

/**
 * Definição da tabela de hash.
 */
typedef SHashMap* HashMap;

//##############################################################################

/**
 * Cria uma tabela de hash.
 * Se não for possível criar a tabela devolve NULL.
 * Têm que ser especificadas a função de hash e a função que compara chaves,
 *   caso contrário a tabela não será criada.
 * Estas funções podem ser alteradas a qualquer momento, utilizando as funções
 *   <tt>@ref hashSetHash</tt> e <tt>@ref hashSetEquals</tt>.
 *
 * @htmlonly (Ver <a href=#func>descrição das funções</a>)@endhtmlonly
 *
 * É ainda necessário indicar um valor (@a factor) que determina quando a
 *   dimensão da tabela deve ser aumentada; isso acontecerá quando:\n
 *   size>factor*length\n
 * Esta variável terá que ser superior a 0.1.
 *
 * @param size   dimensão inicial da tabela.
 * @param factor factor de "reestruturação" da tabela.
 * @param hash   função de hash.
 * @param equals função que compara duas chaves.
 *
 * @return tabela inicializada ou NULL.
 */
HashMap newHash(int size,float factor
               ,int(*hash)(void*)
               ,int(*equals)(void*,void*)
               );

/**
 * Altera a função de hash associada a uma tabela.
 * O valor de @a hash não pode ser NULL.
 *
 * @param hmap tabela de hash.
 * @param hash nova função.
 *
 * @return 1 se @a hash for NULL (não é efectuada qualquer alteração);\n
 *         0 caso contrário.
 */
int hashSetHash(HashMap hmap,int(*hash)(void*));

/**
 * Altera a função que compara duas chaves de uma tabela.
 * O valor de @a equals não pode ser NULL.
 *
 * @param hmap   tabela de hash.
 * @param equals nova função.
 *
 * @return 1 se @a equals for NULL (não é efectuada qualquer alteração);\n
 *         0 caso contrário.
 */
int hashSetEquals(HashMap hmap,int(*equals)(void*,void*));

/**
 * Altera o factor de "reestruturação" da tabela.
 * O novo valor tem que ser maior do 0.1.
 *
 * @param hmap   tabela de hash.
 * @param factor novo valor.
 *
 * @return 1 se @a factor for menor do que 0.1;\n
 *         0 caso contrário.
 */
int hashSetFactor(HashMap hmap,int factor);

/**
 * Elimina uma tabela de hash.
 *
 * @attention apenas liberta a memória referente à estrutura da tabela; não
 *            liberta o espaço ocupado pelos elementos nela contidos.
 *
 * @param hmap tabela de hash.
 */
void hashDelete(HashMap hmap);

/**
 * Insere um par chave/valor numa tabela de hash.
 * Caso a chave já exista, a variável @a replace determina se o valor antigo é
 *   ou não substituído (caso seja 0 não há substituição, caso tenha outro valor
 *   o novo elemento é inserido).
 *
 * @param hmap    tabela de hash.
 * @param key     chave.
 * @param value   valor associado à chave.
 * @param replace variável que determina se elementos já existente são ou não
 *                substituídos.
 *
 * @return 0 se o elemento for inserido;\n
 *         1 se a tabela já possuia a chave indicada;\n
 *         2 se não for possível alocar memória para o novo elemento.
 */
int hashInsert(HashMap hmap,void* key,void* value,int replace);

/**
 * Remove um elemento de uma tabela de hash.
 * Permite devolver o valor removido, caso o valor de @a value seja diferente de
 *   NULL.
 * Se a chave não existir ou o elemento não for removido é colocado o valor NULL
 *   em @a value.
 *
 * @attention esta função não liberta o espaço ocupado pelo valor associado à
 *            chave; já o espaço ocupado pela chave removida, se @a del for
 *            diferente de NULL, será libertado.
 *
 * @param hmap  tabela de hash.
 * @param key   chave que queremos remover.
 * @param value endereço onde é colocado o elemento removido (ou NULL).
 * @param del   função que elimina uma chave (ou NULL).
 *
 * @return 0 se o elemento for removido;\n
 *         1 se a chave não existir.
 */
int hashRemove(HashMap hmap,void* key,void** value,void(*del)(void*));

/**
 * Procura um elemento numa tabela de hash.
 * Devolve o valor associado a uma chave se ela existir.
 * Se a chave não existir é colocado o valor NULL em @a value.
 *
 * @attention esta função coloca em @a value o endereço do valor pretendido;
 *            depois de executar esta função é aconselhável fazer uma cópia do
 *            mesmo e passar a trabalhar com a cópia para que não haja problemas
 *            de partilha de referências.
 *
 * @param hmap  tabela de hash.
 * @param key   chave que procuramos.
 * @param value endereço onde é colocado o resultado.
 *
 * @return 0 se o elemento existir;\n
 *         1 se o elemento não existir.
 */
int hashGet(HashMap hmap,void* key,void** value);

/**
 * Determina o número de elementos de uma tabela de hash.
 * Devolve o valor do campo @a size da tabela.
 *
 * @param hmap tabela de hash.
 *
 * @return número de elementos da tabela.
 */
int hashSize(HashMap hmap);

/**
 * Cria um iterador a partir das chaves de uma tabela de hash.
 * Coloca as referência para as chaves num iterador.
 * Se ocorrer algum erro devolve NULL.
 *
 * @see Iterator
 *
 * @param hmap tabela de hash.
 *
 * @return iterador criado ou NULL.
 */
Iterator hashKeys(HashMap hmap);

/**
 * Cria um iterador a partir dos valores associados às chaves de uma tabela de
 *   hash.
 * Coloca as referências para os "valores" num iterador.
 * Se ocorrer algum erro a função devolve NULL.
 *
 * @see Iterator
 *
 * @param hmap tabela de hash.
 *
 * @return iterador criado ou NULL.
 */
Iterator hashValues(HashMap hmap);

#endif
