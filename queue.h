/**
 * Implementação de uma queue como lista ligada.
 * Esta biblioteca disponibiliza um conjunto de funções que permitem manipular
 *   uma queue.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file queue.h
 * @version 2.0.1
 * @date 02/2009
 */
#ifndef _QUEUE_
#define _QUEUE_

#include "iterator.h"

/**
 * Estrutura do nodo da queue.
 */
typedef struct sQueueNode
{
  ///Apontador para a informação do nodo.
  void *inf;
  ///Apontador para o nodo seguinte.
  struct sQueueNode *next;
}SQueueNode;

/**
 * Definição do apontador para os nodos da queue.
 */
typedef SQueueNode* QueueNode;

/**
 * Estrutura da queue.
 */
typedef struct sQueue
{
  ///Número de elementos da queue.
  int size;
  ///Apontador para o início da queue.
  QueueNode head;
  ///Apontador para o fim da queue.
  QueueNode last;
}SQueue;

/**
 * Definição da queue.
 */
typedef SQueue* Queue;

//##############################################################################

/**
 * Cria uma queue.
 * Se não for possível criar a queue devolve NULL.
 *
 * @return queue inicializada ou NULL.
 */
Queue newQueue();

/**
 * Elemina uma queue.
 *
 * @attention apenas liberta a memória ocupada pela estrutura da queue; não
 *            liberta o espaço ocupado pelos elementos nela contidos.
 * 
 * @param queue queue.
 */
void queueDelete(Queue queue);

/**
 * Insere um elemento numa queue.
 * Verifica se é possível inserir o novo elemento, devolvendo 1 caso não seja
 *   possível.
 *
 * @param queue queue.
 * @param inf   endereço do elemento que queremos inserir.
 *
 * @return 0 se o elemento for inserido;\n
 *         1 se não for possível alocar espaço para o novo elemento.
 */
int queueInsert(Queue queue,void *inf);

/**
 * Remove um elemento de uma queue.
 * Permite devolver o elemento removido, caso o valor de @a inf seja diferente
 *   de NULL.
 * Se a queue estiver vazia é colocado o valor NULL em @a inf.\n
 *
 * @attention esta função não liberta o espaço ocupado pelo elemento removido.
 *
 * @param queue queue.
 * @param inf   endereço onde é colocado o elemento removido (ou NULL).
 *
 * @return 0 se o elemento for removido;\n
 *         1 se a queue estiver vazia.
 */
int queueRemove(Queue queue,void** inf);

/**
 * Verifica qual o elemento na cabeça de uma queue.
 * Se a queue estiver vazia é colocado o valor NULL em @a inf.
 *
 * @attention esta função coloca em @a inf o endereço da informação que está na
 *            cabeça da queue; depois de executar esta função é aconselhável
 *            fazer uma cópia da informação e passar a trabalhar com a cópia
 *            para que não haja problemas de partilha de referências.
 *
 * @param queue queue.
 * @param inf   endereço onde é colocado o resultado.
 *
 * @return 0 se a queue não estiver vazia;\n
 *         1 se a queue estiver vazia.
 */
int queueConsult(Queue queue,void **inf);

/**
 * Determina o tamanho de uma queue.
 * Devolve o valor do campo @a size da queue.
 *
 * @param queue queue.
 *
 * @return número de elementos da queue.
 */
int queueSize(Queue queue);

/**
 * Aplica uma função aos elementos de uma queue começando pela cabeça.
 * A função @c fun tem que ser do tipo: @c void @c fun(void*).
 *
 * @param queue queue.
 * @param fun   função a ser aplicada.
 *
 * @return 0 se a queue não estiver vazia;\n
 *         1 se a queue estiver vazia.
 */
int queueMap(Queue queue,void(*fun)(void*));

/**
 * Cria um iterador a partir da queue.
 * Se ocorrer algum erro a função devolve NULL.
 *
 * @see Iterator
 *
 * @param queue queue.
 *
 * @return iterador criado ou NULL.
 */
Iterator queueIterator(Queue queue);

#endif
