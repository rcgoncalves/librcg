/**
 * Implementation of a dynamic array.
 *
 * This library provides functions to create a dynamic array with a desired
 * length.
 *
 * This array can resize itself whenever needed, while preserving the previous
 * values.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file array.h
 * @version 3.0
 * @date 10/2011
 */
#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "iterator.h"

/**
 * Array structure.
 */
typedef struct sArray
{
  ///Current capacity of this.
  int capacity;
  ///Number of element of this array.
  int size;
  ///Array of pointers to this array elements.
  void** array;
}SArray;

/**
 * Array definition.
 */
typedef SArray* Array;

//##############################################################################

/**
 * Creates an empty array, with the specified initial capacity.
 *
 * The initial capacity must be a positive number.
 *
 * @param size initial capacity of the array.
 *
 * @return the new array, or <tt>NULL</tt> if an error occurs.
 */
Array newArray(int size);

/**
 * Deletes an array.
 *
 * @attention
 * This only frees the memory used by the array.  It does not free the memory
 * used by elements the array contains.
 *
 * @param array the array to be deleted.
 */
void arrayDelete(Array array);

/**
 * Insert an new element at the specified position of an array.
 *
 * The position, specified by argument <tt>index</tt>, must be a non negative
 * integer.  If necessary, the capacity of the array will be increased to
 * <tt>index+1</tt>.
 *
 * If the position is already filled, the <tt>replace</tt> argument specifies
 * whether the new element should be added (it will be added only if
 * <tt>replace!=0</tt>).
 *
 * @attention
 * If the new element is <tt>NULL</tt>, it will not be inserted, and the size
 * of the array will not change.
 *
 * @param array   the array.
 * @param index   index at which the new element is to be inserted.
 * @param elem    element to be inserted.
 * @param replace specify whether old value will be replaced.
 *
 * @return
 * 0 if the new element was inserted.
 * 1 if the position was already filled.
 * 2 if the position was not valid.
 * 3 if was not possible increase the array size.
 */
int arrayInsert(Array array,int index,void* elem,int replace);

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
