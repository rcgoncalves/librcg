/**
 * Implementação de uma stack como lista ligada.
 * Esta biblioteca disponibiliza um conjunto de funções que permitem manipular
 *   uma stack.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file stack.h
 * @version 2.0.1
 * @date 02/2009
 */
#ifndef _STACK_
#define _STACK_

#include "iterator.h"

/**
 * Estrutura do nodo de uma stack.
 */
typedef struct sStackNode
{
  ///Apontador para a informação do nodo.
  void* inf;
  ///Apontador para o nodo seguinte.
  struct sStackNode *next;
}SStackNode;

/**
 * Definição do apontador para os nodos da stack.
 */
typedef SStackNode* StackNode;

/**
 * Estrutura de uma stack.
 */
typedef struct sStack
{
  ///Número de elementos da stack.
  int size;
  ///Apontador para o topo da stack.
  StackNode top;
}SStack;

/**
 * Definição da stack.
 */
typedef SStack* Stack;

//##############################################################################

/**
 * Cria uma stack.
 * Se não for possível criar a stack devolve NULL.
 *
 * @return stack inicializada ou NULL.
 */
Stack newStack();

/**
 * Elemina uma stack.
 *
 * @attention apenas liberta a memória referente à estrutura da stack; não
 *            liberta o espaço ocupado pelos elementos nela contidos.
 *
 * @param stack stack.
 */
void stackDelete(Stack stack);

/**
 * Insere um elemento numa stack.
 * Verifica se é possível inserir o novo elemento, devolvendo 1 caso não seja
 *   possível.
 *
 * @param stack stack.
 * @param inf   endereço do elemento que queremos inserir.
 *
 * @return 0 se o elemento for inserido;\n
 *         1 caso não seja possível alocar memória para o novo elemento. 
 */
int stackPush(Stack stack,void* inf);

/**
 * Remove o elemento que está no topo de uma stack.
 * Permite devolver o elemento removido, caso o valor de @a inf seja diferente
 *   de NULL.
 * Se a stack estiver vazia é colocado o valor NULL em @a inf.\n
 *
 * @attention esta função não liberta o espaço ocupado pelo elemento removido.
 *
 * @param stack stack.
 * @param inf   endereço onde é colocado o elemento removido (ou NULL).
 *
 * @return 0 se o elemento for removido;\n
 *         1 se a stack estiver vazia.
 */
int stackPop(Stack stack,void** inf);

/**
 * Verifica qual o elemento no topo de uma stack.
 * Se a stack estiver vazia é colocado o valor NULL em @a inf.
 *
 * @attention esta função coloca em @a inf o endereço da informação que está no
 *            topo da stack; depois de executar esta função é aconselhável fazer
 *            uma cópia da informação e passar a trabalhar com a cópia para que
 *            não haja problemas de partilha de referências.
 *
 * @param stack stack.
 * @param inf   endereço onde é colocado o resultado.
 *
 * @return 0 se a stack não estiver vazia;\n
 *         1 se a stack estiver vazia.
 */
int stackTop(Stack stack,void** inf);

/**
 * Determina o tamanho de uma stack.
 * Devolve o valor do campo @a size da stack.
 *
 * @param stack stack.
 *
 * @return número de elementos da stack.
 */
int stackSize(Stack stack);

/**
 * Aplica uma função aos elementos de uma stack começando no topo.
 * A função @c fun tem que ser do tipo: <tt> void @c fun(void*)</tt>.
 *
 * @param stack stack.
 * @param fun   função a ser aplicada.
 *
 * @return 0 se a stack não estiver vazia;\n
 *         1 se a stack estiver vazia.
 */
int stackMap(Stack stack,void(*fun)(void*));

/**
 * Cria um iterador a partir de uma stack.
 * Se ocorrer algum erro a função devolve NULL.
 *
 * @see Iterator
 *
 * @param stack stack.
 *
 * @return iterador criado ou NULL.
 */
Iterator stackIterator(Stack stack);

#endif
