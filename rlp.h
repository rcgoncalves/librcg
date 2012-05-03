/**
 * Implementation of linear programming functions.
 *
 * @author Rui Carlos Gonçalves <rcgoncalves.pt@gmail.com>
 * @file rlp.h
 * @version 3.0
 * @date 05/2012
 */
#ifndef _RLP_H_
#define _RLP_H_

/**
 * Applies the <em>Simplex Algorithm</em> to an optimization problem.
 *
 * Given a problem with <em>n</em> variables (<em>x<sub>1</sub></em>, ...,
 * <em>x<sub>n</sub></em>) and <em>m</em> conditions (<em>c<sub>1</sub> =
 * b<sub>1</sub></em>, ..., <em>c<sub>m</sub> = b<sub>m</sub></em>), the
 * function must receive a matrix <tt>a</tt> of size <em>(m+1)*(n+m+2)</em>,
 * containing:
 * <ul>
 *   <li>at <tt>a[0][i-1]</tt> (for <em>i</em> in <em>[1, n]</em>) the
 *   coefficient of variable <em>x<sub>i</sub></em> in the expression to
 *   minimize;</li>
 *   <li>at <tt>a[0][i]</tt> (for <em>i</em> in <em>[n, n+m+1]</em>) the value
 *   0;</li>
 *   <li>at <tt>a[i][j-1]</tt> (for <em>i</em> in <em>[1, m]</em>, and for
 *   <em>j</em> in <em>[1, n]</em>) the coefficient of variable
 *   <em>x<sub>j</sub></em> in condition <em>c<sub>i</sub></em>;</li>
 *   <li>at <tt>a[i][j]</tt> (for <em>i</em> in <em>[1, m]</em>, and for
 *   <em>j</em> in <em>[n, n+m-1]</em>) the identity matrix;</li>
 *   <li>at <tt>a[i][n+m]</tt> (for <em>i</em> in <em>[1, m]</em>) the value of
 *   <em>b<sub>i</sub></em>;</li>
 *   <li>at <tt>a[i][n+m+1]</tt> (for <em>i</em> in <em>[1, m]</em>) the value
 *   of <em>n+i</em>.</li>
 * </ul>
 *
 * Allows to specify the file where the table resulting from the application of
 * the algorithm (using the parameter <em>file</em>).
 *
 * @param a    matrix that represents the problem
 * @param n    number of variable of the function
 * @param m    number restrictions
 * @param file file where the tables will be saved (or <tt>NULL</tt>)
 *
 * @return
 * 0 if it is possible to solve the problem\n
 * 1 otherwise
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
