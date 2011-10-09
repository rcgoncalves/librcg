/**
 * Implementação de funções de programação linear.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file rlp.h
 * @version 2.1.1
 * @date 02/2009
 */
#ifndef _RLP_
#define _RLP_

/**
 * Aplica o @a Algoritmo @a Simplex a um problema de optimização (programação
 *   linear).
 * Dado um problema de @a n variáveis (@a x1 , ... , @a xn ) e @a m condições
 *   (@a c1=b1 , ... , @a cm=bm ), a função deve receber uma matriz @a a de
 *   dimensão (m+1)*(n+m+2) contendo:
 * @li em a[0][i-1] (para @a i de @a 1 até @a n ) o coeficiente da variável @a
 *     xi na expressão a minimizar;
 * @li em a[0][i] (para @a i de @a n até @a n+m+1 ) o valor 0;
 * @li em a[i][j-1] (para @a i de @a 1 até @a m e @a j de @a 1 até @a n ) o
 *     coeficiente da variável @a xj na condição @a ci;
 * @li em a[i][j] (para @a i de @a 1 até @a m e @a j de @a n até @a n+m-1 ) a
 *     matriz identidade;
 * @li em a[i][n+m] (para @a i de 1 até @a m ) o valor @a bi;
 * @li em a[i][n+m+1] (para @a i de 1 até @a m ) o valor @a n+i.
 *
 * Permite definir um ficheiro onde são colocadas as várias tabelas resultantes
 *   da aplicação do algoritmo (através da variável @a file).
 *
 * @param a    matriz que representa o problema (conforme a descrição acima).
 * @param n    número de variáveis da função objectivo.
 * @param m    número de condições.
 * @param file ficheiro onde as tabelas serão impressas (ou NULL).
 *
 * @return 0 se for possível determinar um resultado.
 *         1 caso contrário.
 */
int simplex(double* a,int n,int m,FILE* file);

/**
 * Aplica o @a Algoritmo @a Simplex primal a um problema de programação linear.
 * A matriz de entrada (@a a) segue o formato da matriz de entrada da função
 *   <tt>@ref simplex</tt>.\n
 * Permite definir um ficheiro onde são colocadas as várias tabelas resultantes
 *   da aplicação do algoritmo (através da variável @a file).
 *
 * @param a    matriz que representa o problema.
 * @param n    número de variáveis da função objectivo.
 * @param m    número de condições.
 * @param pos  posição em que se encontra o menor valor da última coluna das
 *             restrições (sendo que o menor valor terá que ser obrigatoriamente
 *             negativo).
 * @param file ficheiro onde as tabelas serão impressas (ou NULL).
 *
 * @return 0 se for possível determinar um resultado.
 *         1 caso contrário.
 */
int simplexp(double* a,int n,int m,int pos,FILE* file);

/**
 * Aplica o @a Algoritmo @a Simplex dual a um problema de programação linear.
 * A matriz de entrada (@a a) segue o formato da matriz de entrada da função
 *   <tt>@ref simplex</tt>.\n
 * Permite definir um ficheiro onde são colocadas as várias tabelas resultantes
 *   da aplicação do algoritmo (através da variável @a file).
 *
 * @param a    matriz que representa o problema.
 * @param n    número de variáveis da função objectivo.
 * @param m    número de condições.
 * @param pos  posição em que se encontra o menor valor da primeira linha (sendo
 *             que o menor valor terá que ser obrigatoriamente negativo).
 * @param file ficheiro onde as tabelas serão impressas (ou NULL).
 *
 * @return 0 se for possível determinar um resultado.
 *         1 caso contrário.
 */
int simplexd(double* a,int n,int m,int pos,FILE* file);

#endif
