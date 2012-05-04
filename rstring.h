/**
 * Implementation of functions to manipulate strings.
 *
 * @author Rui Carlos Gonçalves <rcgoncalves.pt@gmail.com>
 * @file rstring.h
 * @version 3.0
 * @date 05/2012
 */
#ifndef _RSTRING_H_
#define _RSTRING_H_

#include "list.h"

/**
 * Removes leading whitespaces of a string.
 *
 * @param str the string
 *
 * @return
 * the size of the resulting string
 */
int trimStart(char* str);

/**
 * Removes trailing whitespaces of a string.
 *
 * @param str the string
 *
 * @return
 * the size of the resulting string
 */
int trimEnd(char* str);

/**
 * Removes leading and trailing whitespaces of a string, as well as consecutive
 * whitespaces in the middle of a string.
 *
 * @param str the string
 *
 * @return
 * the size of the resulting string
 */
int trim(char* str);

/**
 * Checks if there is an occurrence of a specif character in a string.
 *
 * @param c   the character
 * @param str the string
 *
 * @return
 * 1 if there is an occurrence of the character in the string\n
 * 0 otherwise
 */
int charElem(char c,const char* str);

/**
 * Given a string, computes the list of words that the string contains.
 *
 * The original string is not changed.
 *
 * @see List
 *
 * @param str the string
 *
 * @return
 * list of words
 */
List words(const char* str);

/**
 * Splits a string.
 *
 * Computes a list of strings, each of which is a substring of the string formed
 * by splitting it on the boundaries defined by the specified delimiters
 * (<tt>delim</tt>).
 *
 * @see List
 *
 * @param str   the string
 * @param delim the delimiters
 *
 * @return
 * list of words resulting from split the string at occurrences of the specified
 * delimiters
 */
List strSep(const char* str,const char* delim);

#endif
