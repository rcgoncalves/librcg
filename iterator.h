/**
 * Implementação de um iterador.
 * O iterador será um array de apontadores.
 * O campo @a pos de um iterador indica uma posição entre o elemento devolvido
 *   pela função @c itNext e a função @c itPrev.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file iterator.h
 * @version 2.0.2
 * @date 02/2009
 */
#ifndef _ITERATOR_
#define _ITERATOR_

/**
 * Estrutura do iterador.
 */
typedef struct sIterator
{
  ///Dimensão do iterador.
  int capacity;
  ///Número de elementos.
  int size;
  ///Posição actual.
  int pos;
  ///Apontadores para os elementos do iterador.
  void** values;
}SIterator;

/**
 * Definição do iterador
 */
typedef SIterator* Iterator;

//##############################################################################

/**
 * Cria um iterador.
 * Se não for possível criar o iterador devolve NULL.
 *
 * @param size capacidade do iterador.
 *
 * @return iterador inicializado ou NULL.
 */
Iterator newIt(int size);

/**
 * Elimina um iterador.
 * Esta função limita-se a libertar o espaço ocupado pelo array de apontadores e
 *   pela estrutura do iterador.
 * 
 * @param it iterador.
 */
void itDelete(Iterator it);

/**
 * Adiciona um elemento a um iterador.
 * Verifica se a capacidade do iterador já foi atingida, em caso afirmativo o
 *   elemento não é adicionado e é devolvido o valor 1.
 *
 * @param it  iterador.
 * @param val valor a inserir.
 *
 * @return 0 se o valor for adicionado;\n
 *         1 se o iterador não tiver espaço livre.
 */
int itAdd(Iterator it,void* val);

/**
 * Devolve o próximo elemento de um iterador.
 * Devolve o elemento que está imediatamente a seguir a @a pos e incrementa o
 *   seu valor.
 * Caso ocorra algum erro é colocado o valor NULL em @a val.
 *
 * @param it  iterador.
 * @param val endereço onde será colocado o resultado
 *
 * @return 0 se for devolvido um elemento;\n
 *         1 se não existir próximo elemento.
 */
int itNext(Iterator it,void** val);

/**
 * Verifica se existe "próximo" elemento num iterador.
 *
 * @param it iterador.
 *
 * @return 1 se existir;\n
 *         0 se não existir.
 */
int itHasNext(Iterator it);

/**
 * Devolve o anterior elemento de um iterador.
 * Devolve o elemento que está imediatamente antes de @a pos e decrementa o seu
 *   valor.
 * Caso ocorra algum erro é colocado o valor NULL em @a val.
 *
 * @param it  iterador.
 * @param val endereço onde será colocado o resultado.
 *
 * @return 0 se for devolvido um elemento;\n
 *         1 se não existir próximo elemento.
 */
int itPrev(Iterator it,void** val);

/**
 * Verifica se existe elemento "anterior" num iterador.
 *
 * @param it iterador.
 *
 * @return 1 se existir;\n
 *         0 se não existir.
 */
int itHasPrev(Iterator it);

/**
 * Verifica qual o elemento numa determinada posição do array de valores de um
 *   iterador.
 * Se o valor de @a index não for válido é colocado o valor NULL em @a val.
 *
 * @param it    iterador.
 * @param index posição pretendida.
 * @param val   local onde será colocado o resultado.
 *
 * @return 0 se o elemento existir;\n
 *         1 se o valor de @a index não for válido.
 */
int itAt(Iterator it,int index,void** val);

/**
 * Altera a posição actual do iterador.
 * É alterado o valor do campo @a pos do iterador (se o valor de @a index for
 *   válido).
 * 
 * @param it iterador.
 * @param n  novo valor para a posição.
 *
 * @return -1 se o valor de @a n não for válido;\n
 *         0 caso contrário.
 */
int itSetPos(Iterator it,int n);

/**
 * Determina a posição actual do iterador.
 * Devolve o valor do campo @a pos do iterador.
 *
 * @param it iterador.
 *
 * @return posição do iterador.
 */
int itGetPos(Iterator it);

#endif
