/**
 * Implementation of linear programming functions.
 *
 * @author Rui Carlos Gonçalves
 * @file rlp.h
 * @version 3.0
 * @date 07/2012
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
 * Applies the <em>Simplex algorithm</em> to a primal optimization problem.
 *
 * The input matrix (<tt>a</tt>) must follow the format defined in function
 * <tt><ref>simplex</ref></tt>.
 *
 * Allows to specify the file where the table resulting from the application of
 * the algorithm (using the parameter <em>file</em>).
 *
 * @param a    matrix that represents the problem
 * @param n    number of variables of the function
 * @param m    number restrictions
 * @param pos  position of the minimum value of the restrictions' column (it
 * 	       must be a negative value)
 * @param file file where the tables will be saved (or <tt>NULL</tt>)
 *
 * @return
 * 0 if it is possible to solve the problem\n
 * 1 otherwise
 */
int simplexp(double* a,int n,int m,int pos,FILE* file);

/**
 * Applies the <em>Simplex algorithm</em> to a dual optimization problem.
 *
 * The input matrix (<tt>a</tt>) must follow the format defined in function
 * <tt><ref>simplex</ref></tt>.
 *
 * Allows to specify the file where the table resulting from the application of
 * the algorithm (using the parameter <em>file</em>).
 *
 * @param a    matrix that represents the problem
 * @param n    number of variables of the function
 * @param m    number restrictions
 * @param pos  position of the minimum value of the first row (it must be a
 *             negative value)
 * @param file file where the tables will be saved (or <tt>NULL</tt>)
 *
 * @return
 * 0 if it is possible to solve the problem\n
 * 1 otherwise
 */
int simplexd(double* a,int n,int m,int pos,FILE* file);

#endif
