/**
 * Implementação de uma queue com prioridades.
 * Esta biblioteca disponibiliza um conjunto de funções que permitem manipular
 *   uma queue onde os elementos são inseridos ordenadamente.
 *
 * Na criação de uma pqueue é necessário especificar a função que compara as
 *   os elementos.
 * @htmlonly <a id="func" name="func"></a>@endhtmlonly
 *
 * <tt>int comp(void* key1,void* key2)</tt>\n
 * (usada pela função <tt>@ref pqueueInsert</tt>); esta função permite indicar
 * qual o elemento a ser removido: será o menor valor contido na pqueue;
 * pode ser alterada através da função <tt>@ref pqueueSetComp</tt>.
@code
int comp(void* x1,void* x2)
{
  if(x1&&x2) return strcmp((char*)x1,(char*)x2);
  else return 0;
}
@endcode
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file pqueue.h
 * @version 1.0.1
 * @date 02/2009
 */
#ifndef _PQUEUE_
#define _PQUEUE_

#include "iterator.h"

/**
 * Estrutura do nodo da pqueue.
 */
typedef struct sPQueueNode
{
  ///Apontador para a informação do nodo.
  void *inf;
  ///Apontador para o nodo seguinte.
  struct sPQueueNode *next;
}SPQueueNode;

/**
 * Definição do apontador para os nodos da pqueue.
 */
typedef SPQueueNode* PQueueNode;

/**
 * Estrutura da pqueue.
 */
typedef struct sPQueue
{
  ///Função que compara dois elementos.
  int(*comp)(void*,void*);
  ///Número de elementos da pqueue.
  int size;
  ///Apontador para o início da pqueue.
  PQueueNode head;
}SPQueue;

/**
 * Definição da pqueue.
 */
typedef SPQueue* PQueue;

//##############################################################################

/**
 * Cria uma pqueue.
 * Se não for possível criar a pqueue devolve NULL.
 * Tem que ser especificada a função que compara os elementos da pqueue.
 * Esta função pode ser alterada a qualquer momento, utilizando a função
 *   <tt>@ref pqueueSetComp</tt>.
 *
 * @htmlonly (Ver <a href=#func>descrição das funções</a>)@endhtmlonly
 *
 * @param comp função que compara dois elementos.
 *
 * @return pqueue inicializada ou NULL.
 */
PQueue newPQueue(int(*comp)(void*,void*));

/**
 * Altera a função que compara os elementos de uma árvore.
 * O valor de @a comp não pode ser NULL.
 *
 * @param pqueue pqueue.
 * @param comp   nova função.
 *
 * @return 1 se @a comp for NULL (não é efectuada qualquer alteração);\n
 *         0 caso contrário.
 */
int pqueueSetComp(PQueue pqueue,int(*comp)(void*,void*));

/**
 * Elemina uma pqueue.
 *
 * @attention apenas liberta a memória ocupada pela estrutura da pqueue; não
 *            liberta o espaço ocupado pelos elementos nela contidos.
 * 
 * @param pqueue pqueue.
 */
void pqueueDelete(PQueue pqueue);

/**
 * Insere um elemento numa pqueue.
 * Verifica se é possível inserir o novo elemento, devolvendo 1 caso não seja
 *   possível.
 *
 * @param pqueue pqueue.
 * @param inf    endereço do elemento que queremos inserir.
 *
 * @return 0 se o elemento for inserido;\n
 *         1 se não for possível alocar espaço para o novo elemento.
 */
int pqueueInsert(PQueue pqueue,void *inf);

/**
 * Remove um elemento de uma pqueue.
 * Permite devolver o elemento removido, caso o valor de @a inf seja diferente
 *   de NULL.
 * Se a pqueue estiver vazia é colocado o valor NULL em @a inf.
 *
 * @attention esta função não liberta o espaço ocupado pelo elemento removido.
 *
 * @param pqueue pqueue.
 * @param inf    endereço onde é colocado o elemento removido (ou NULL).
 *
 * @return 0 se o elemento for removido;\n
 *         1 se a pqueue estiver vazia.
 */
int pqueueRemove(PQueue pqueue,void** inf);

/**
 * Verifica qual o elemento na cabeça de uma pqueue.
 * Se a pqueue estiver vazia é colocado o valor NULL em @a inf.
 *
 * @attention esta função coloca em @a inf o endereço da informação que está na
 *            cabeça da pqueue; depois de executar esta função é aconselhável
 *            fazer uma cópia da informação e passar a trabalhar com a cópia
 *            para que não haja problemas de partilha de referências.
 *
 * @param pqueue pqueue.
 * @param inf    endereço onde é colocado o resultado.
 *
 * @return 0 se a pqueue não estiver vazia;\n
 *         1 se a pqueue estiver vazia.
 */
int pqueueConsult(PQueue pqueue,void **inf);

/**
 * Determina o tamanho de uma pqueue.
 * Devolve o valor do campo @a size da pqueue.
 *
 * @param pqueue pqueue.
 *
 * @return número de elementos da pqueue.
 */
int pqueueSize(PQueue pqueue);

/**
 * Aplica uma função aos elementos de uma pqueue começando pela cabeça.
 * A função @c fun tem que ser do tipo: @c void @c fun(void*).
 *
 * @param pqueue pqueue.
 * @param fun    função a ser aplicada.
 *
 * @return 0 se a pqueue não estiver vazia;\n
 *         1 se a pqueue estiver vazia.
 */
int pqueueMap(PQueue pqueue,void(*fun)(void*));

/**
 * Cria um iterador a partir da pqueue.
 * Se ocorrer algum erro a função devolve NULL.
 *
 * @see Iterator
 *
 * @param pqueue pqueue.
 *
 * @return iterador criado ou NULL.
 */
Iterator pqueueIterator(PQueue pqueue);

#endif
