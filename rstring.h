/**
 * Implementação de funções que manipulam strings.
 * Esta biblioteca disponibiliza funções que removem espaços em determinadas
 *   posições de uma string e que separam a string em função de determinados
 *   caracteres.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file rstring.h
 * @version 2.0.1
 * @date 02/2009
 */
#ifndef _RSTRING_
#define _RSTRING_

#include "list.h"


/**
 * Remove espaços de uma string.
 * Remove os espaços no início de uma string.
 *
 * @param str string na qual vamos remover os espaços.
 *
 * @return tamanho da string resultante.
 */
int delISpaces(char* str);

/**
 * Remove espaços de uma string.
 * Remove espaço consecutivos de uma string.
 *
 * @param str string na qual vamos remover os espaços.
 *
 * @return tamanho da string resultante.
 */
int delCSpaces(char* str);

/**
 * Remove espaços de uma string.
 * Remove os espaços no fim de uma string.
 *
 * @param str string na qual vamos remover os espaços.
 *
 * @return tamanho da string resultante.
 */
int delESpaces(char* str);

/**
 * Remove espaços de uma string.
 * Remove os espaços no início e no fim de uma string e ainda espaços
 *   consecutivos entre palavras.
 *
 * @param str string na qual vamos remover os espaços.
 *
 * @return tamanho da string resultante.
 */
int delSpaces(char* str);

/**
 * Verifica se um carácter ocorre numa string.
 *
 * @param c   carácter que procuramos.
 * @param str string onde vamos procurar.
 *
 * @return 0 se o carácter não ocorrer na string;\n
 *         1 caso contrário.
 */
int charElem(char c,const char* str);

/**
 * Dada uma string, obtem a lista de palavras que a compõe.
 * A string original não é alterada.
 * Caso @a str seja NULL ou ocorra algum erro é devolvido NULL.
 *
 * @see List
 *
 * @param str string a separar.
 *
 * @return lista de palavras ou NULL.
 */
List words(const char* str);

/**
 * Divide uma string.
 * Cria uma lista de strings com as substrings da original delimitadas pelos
 *   caracteres pertencentes a @a delim.
 * A string original não é alterada.
 * Caso @a str seja NULL ou ocorra algum erro é devolvido NULL.
 *
 * @see List
 *
 * @param str   string a separar.
 * @param delim delimitadores.
 *
 * @return lista de substrings.
 */
List strSep(const char* str,const char* delim);

#endif
