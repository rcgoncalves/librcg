/**
 * Implementation of some utility functions.
 *
 * Provides functions to read text from de <em>stdin</em>, to generate random
 * numbers, and to sort arrays.
 *
 * @author Rui Carlos Gonçalves
 * @file util.h
 * @version 3.1
 * @date 01/2014
 */
#ifndef _UTIL_H_
#define _UTIL_H_

/**
 * Reads a line from the <em>stdin</em>.
 *
 * Reads all characters until a <tt>\\n</tt>.
 *
 * @attention
 * The memory space where the line read will be stored is allocated by this
 * function.  Therefore, it shall <strong>not</strong> be previously allocated.
 *
 * @param str pointer where a string containing the line read shall be put
 *
 * @return
 * -2 if the <tt>str</tt> is invalid\n
 * -1 if an error occur\n
 * the size of the string read otherwise
 */
int rgets(char** str);

/**
 * Reads a text from the <em>stdin</em>.
 *
 * Reads all characters until an <em>EndOfFile</em>.
 *
 * @attention
 * The memory space where the text read will be stored is allocated by this
 * function.  Therefore, it shall <strong>not</strong> be previously allocated.
 *
 * @param str pointer where a string containing the text read shall be put
 *
 * @return
 * -2 if the <tt>str</tt> is invalid\n
 * -1 if an error occur\n
 * the size of the string read otherwise
 */
int rgetsEOF(char** str);

/**
 * Reads a line from the <em>stdin</em>.
 *
 * Reads all characters until a <tt>\\n</tt>.
 * The line shall not exceed the size <em>dim-2</em> (the additional characters
 * will be lost).
 *
 * @attention
 * The memory location where the line read will be stored must be previously
 * allocated.
 *
 * @param str pointer where the text read shall be put
 * @param dim maximum size for the line to be read (the line shall not exceed
 * the size <em>dim-2</em>)
 *
 * @return
 * -1 if the line exceeded the maximum size allowed\n
 * the size of the line read otherwise
 */
int rngets(char* str,int dim);

/**
 * Generates a random number in a given interval.
 *
 * @attention
 * The value of <tt>max</tt> must be greater than <tt>min</tt>, otherwise
 * the function will return 0.
 *
 * @param min minimum allowed value
 * @param max maximum allowed value
 *
 * @return
 * 0 if <em>max<min</em>\n
 * a random number in the given interval otherwise
 */
int getRandom(int min,int max);

/**
 * Orders an array into ascending order, based on a given comparison function.
 *
 * Uses the algorithm <em>merge sort</em>.
 *
 * @param vals  array of pointer to the elements to sort
 * @param begin starting position
 * @param end   ending position
 * @param comp  comparison function
 *
 * @return
 * number of errors detected
 */
int mergeSort(void* vals[],int begin,int end,int(*comp)(void*,void*));

#endif
