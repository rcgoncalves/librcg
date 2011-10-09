/**
 * Implementação de um array dinâmico.
 * Esta biblioteca disponibiliza funções que permitem alocar dinamicamente o
 *   array com o comprimento que desejarmos, tendo o comprimento do array
 *   disponível.\n
 * O array tem também a capacidade de se redimensionar sempre que necessário,
 *   mantendo toda a informação já existente.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file array.h
 * @version 2.0.2
 * @date 09/2009
 */
#ifndef _ARRAY_
#define _ARRAY_

#include "iterator.h"

/**
 * Definição da estrutura do array.
 */
typedef struct sArray
{
  ///Capacidade máxima de elementos do array.
  int capacity;
  ///Número de elementos do array.
  int size;
  ///Array de apontadores.
  void** array;
}SArray;

/**
 * Definição do array.
 */
typedef SArray* Array;

//##############################################################################

/**
 * Cria um array.
 * Um array trata-se de um vector de elementos associados a uma posição, posição
 *   essa a que podemos aceder em tempo linear.
 * Na criação do array é indicado a dimensão inicial, dimensão essa que pode
 *   posteriormente ser alterada através da função <tt>@ref arrayResize</tt>.\n
 * Se não for possível criar o array devolve NULL.
 *
 * @param size dimensão pretendida.
 *
 * @return array inicializado ou NULL.
 */
Array newArray(int size);

/**
 * Elimina um array.
 *
 * @attention apenas liberta a memória referente à estrutura do array; não
 *            liberta o espaço ocupado pelos elementos nele contidos.
 *
 * @param array array.
 */
void arrayDelete(Array array);

/**
 * Insere um elemento numa determinada posição de um array.
 * A posição, especificado pelo argumento @a index, tem que ser maior do que 0.
 *   Se o tamanho actual do array não permitir a inserção do novo elemento, o
 *   tamanho é aumentado e passa a ser igual ao valor de @a index+1 (se não for
 *   possível aumentar o tamanho do array o elemento não é inserido).
 * Caso a posição já esteja ocupada, a variável @a replace determina se o valor
 *   antigo é ou não substituido (caso seja 0 não há substituição, caso tenha
 *   outro valor o novo elemento é inserido).
 *
 * @attention se o elemento a inserir tiver o valor NULL, este não é inserido,
 *            não sendo, como tal, incrementado o número de elementos do array.
 *
 * @param array   array.
 * @param index   posição em que será inserido.
 * @param inf     endereço do elemento que queremos inserir.
 * @param replace variável que determina se elementos já existente são ou não
 *                substituídos.
 *
 * @return 0 se o elemento for inserido;\n
 *         1 se a posição já estava ocupada;\n
 *         2 se o valor de @a index não for válido;\n
 *         3 se não for possível aumentar o tamanho do array.
 */
int arrayInsert(Array array,int index,void* inf,int replace);

/**
 * Remove um elemento numa determinada posição de um array.
 * Permite devolver a informação do elemento removido, caso o valor de @a inf
 *   seja diferente de NULL.
 * Se o elemento pretendido não existir será colocado o valor NULL em @a inf.
 * Considera-se que não existe elemento numa posição do array, se o seu valor
 *   for NULL.\n
 *
 * @attention esta função não liberta a memória ocupada pela elemento removido.
 *
 * @param array array.
 * @param index posição do elemento que queremos remover.
 * @param inf   endereço onde é colocado o valor removido (ou NULL).
 *
 * @return 0 se o elemento for removido;\n
 *         1 se não existir elemento na posição indicada.
 */
int arrayRemove(Array array,int index,void** inf);

/**
 * Verifica qual o elemento numa determinada posição de um array.
 * Se não existir nenhum elemento na posição indicado é colocado o valor NULL
 *   em @a inf.
 * 
 * @attention esta função coloca em @a inf o endereço do elemento pretendido;
 *            depois de executar esta função é aconselhável fazer uma cópia da
 *            informação e passar a trabalhar com a cópia para que não haja
 *            problemas de partilha de referências.
 *
 * @param array array.
 * @param index posição do elemento que procuramos.
 * @param inf   endereço onde será colocado o resultado.
 *
 * @return 0 se existir elemento na posição pretendida;\n
 *         1 se não existir elemento na posição indicada.
 */
int arrayAt(Array array,int index,void** inf);

/**
 * Altera a capacidade do array.
 * Apenas permite aumentar a capacidade do array.
 *
 * @param array array.
 * @param size  nova capacidade do array.
 *
 * @return 0 se a dimensão for alterada;\n
 *         1 se ocorrer algum erro durante o redimensionamento do array;\n
 *         2 se o valor da nova dimensão for inferior à dimensão actual.
 */
int arrayResize(Array array,int size);

/**
 * Determina o número de elementos de um array.
 * Devolve o valor do campo @a size do array.
 *
 * @param array array.
 *
 * @return número de elementos do array.
 */
int arraySize(Array array);

/**
 * Determina a capacidade de um array.
 * Devolve o valor do campo @a capacity do array.
 *
 * @param array array.
 *
 * @return capacidade do array.
 */
int arrayCapacity(Array array);

/**
 * Aplica uma função aos elementos de um array.
 * A função @c fun tem que ser do tipo: <tt>void @c fun(void*)</tt>.
 *
 * @param array array.
 * @param fun   função a ser aplicada.
 *
 * @return 0 se o array não estiver vazio;\n
 *         1 se o array estiver vazio.
 */
int arrayMap(Array array,void(*fun)(void*));

/**
 * Cria um iterador a partir de um array.
 * Se ocorrer algum erro a função devolve NULL.
 *
 * @see Iterator
 *
 * @param array array.
 *
 * @return iterador criado ou NULL.
 */
Iterator arrayIterator(Array array);

#endif
