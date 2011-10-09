/**
 * Implementação de funções auxiliares básicas.
 * Esta biblioteca disponibiliza funções que permitem ler frases do teclado,
 *   gerar números aleatórios e ordenar vectores.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file util.h
 * @version 2.1.1
 * @date 02/2009
 */
#ifndef _UTIL_
#define _UTIL_


/**
 * Lê uma frase do stdin.
 * Lê todos o caracteres inseridos até encontrar o carácter @a \\n.
 * Esta função, ao contrário da @c rngets, recebe como argumento o endereço
 *   para uma variável do tipo @c char*, e não a própria variável.
 * Se ocorrer algum erro é colocado o valor NULL em @a str.
 *
 * @attention o espaço para a string onde será colocado o resultado é reservado
 *            pela função @c rgets, como tal @b não deve ser previamente
 *            alocado, pois se isso acontecer será perdido.
 *
 * @param str endereço da string onde será colocado o resultado.
 *
 * @return -2 se o endereço do resultado não for válido;\n
 *         -1 se ocorrer algum erro;\n
 *         tamanho da string caso contrário.
 */
int rgets(char** str);

/**
 * Lê uma frase do stdin.
 * Lê todos o caracteres inseridos até encontrar um EndOfFile.
 * Esta função, ao contrário da @c rngets, recebe como argumento o endereço
 *   para uma variável do tipo @c char*, e não a própria variável.
 * Se ocorrer algum erro é colocado o valor NULL em @a str.
 *
 * @attention o espaço para a string onde será colocado o resultado é reservado
 *             pela função @c rgetsEOF, como tal @b não deve ser previamente
 *             alocado, pois se isso acontecer será perdido.
 *
 * @param str endereço da string onde será colocado o resultado.
 *
 * @return -2 se o endereço do resultado não for válido;\n
 *         -1 se ocorrer algum erro;\n
 *         tamanho da string caso contrário.
 */
int rgetsEOF(char** str);

/**
 * Lê uma frase do stdin.
 * Verifica se a frase introduzida não excede a tamanho máximo (dim-2):
 * @li caso isto aconteça a frase é perdida;\n
 * @li caso contrário a frase é colocada na variável @a str (as frases lidas
 *     nunca têm o carácter @a \\n no fim).
 *
 * @attention o espaço referenciado por @a str tem que ser previamente alocado.
 *
 * @param str local onde é guardada a frase lida.
 * @param dim tamanho máximo da expressão é dim-2.
 *
 * @return tamanho da frase lida (ou -1 caso não seja lida nenhuma frase).
 */
int rngets(char* str,int dim);

/**
 * Gera um número aleatório entre dois valores.
 *
 * @attention o valor de min deve ser menor do que max.
 *
 * @param min valor mínimo que pode ser gerado.
 * @param max valor máximo que pode ser gerado.
 *
 * @return valor gerado.
 */
int getRandom(int min,int max);

/**
 * Ordena um array.
 * Utiliza o algoritmo @b Mergesort.\n
 * Ordena os elementos do array no intervalo [@a begin,@a end], usando como
 *   função de comparação @a comp.\n
 * A função @a comp tem que ser do tipo: <tt>int comp(void*,void*)</tt>.
 *
 * @param vals  array de apontadores para os elementos a ordenar.
 * @param begin posição onde começamos a ordenação.
 * @param end   posição onde termina a ordenação.
 * @param comp  função de comparação.
 *
 * @return número de erros detectados.
 */
int mergeSort(void* vals[],int begin,int end,int(*comp)(void*,void*));

#endif
