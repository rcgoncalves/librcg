/**
 * Implementation of some utility functions.
 *
 * @author Rui Carlos Gonçalves
 * @file util.c
 * @version 3.1
 * @date 01/2014
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"

/**
 * Size of the initial buffer to be used in functions <tt>rgets</tt> and
 * <tt>rgetsEOF</tt>.
 */
#define BUFSIZE 32

int rgets(char** str)
{
  char* str1,* str2;
  char tmp;
  int length,count,result=0;
  if(!str) result=-2;
  else
  {
    length=BUFSIZE;
    str1=malloc((length+1)*sizeof(char));
    if(!str)
    {
      *str=NULL;
      result=-1;
    }
    for(count=0;result>=0&&(tmp=getchar())!='\n';count++)
    {
      if(count>=length)
      {
        length*=2;
        str2=realloc(str1,length+1);
        if(!str2)
        {
          free(str1);
          *str=NULL;
          result=-1;
        }
        else str1=str2;
      }
      str1[count]=tmp;
    }
    str1[count]='\0';
    *str=str1;
    result=count;
  }
  return result;
}

//==============================================================================

int rgetsEOF(char** str)
{
  char* str1,* str2;
  char tmp;
  int length,count,result=0;
  if(!str) result=-2;
  else
  {
    length=BUFSIZE;
    str1=malloc((length+1)*sizeof(char));
    if(!str1)
    {
      *str=NULL;
      result=-1;
    }
    for(count=0;result>=0&&(tmp=getchar())!=EOF;count++)
    {
      if(count>=length)
      {
        length*=2;
        str2=realloc(str1,length+1);
        if(!str2)
        {
          free(str1);
          *str=NULL;
          result=-1;
        }
        else str1=str2;
      }
      str1[count]=tmp;
    }
    str1[count]='\0';
    *str=str1;
    result=count;
  }
  return result;
}

//==============================================================================

int rngets(char *str,int dim)
{
  int length;
  char *ret;
  str[dim-1]=str[dim-2]=1;
  ret=fgets(str,dim,stdin);
  if(ret==NULL||(str[dim-1]=='\0'&&str[dim-2]!='\n')) 
  {
    while(getchar()!='\n');
    length=-1;
  }
  else
  {
    length=strlen(str)-1;
    str[length]='\0';
  }
  return length;
}

//==============================================================================

int getRandom(int min,int max)
{
  static time_t seed = 0;
  int result;
  if(max<min) result=0;
  else
  {
    if(!seed)
    {
      time(&seed);
      srand((unsigned)seed);
    }
    result=min+rand()%(max-min+1);
  }
  return result;
}

//==============================================================================

/**
 * Merges two ordered parts of an array of pointers, based on a given comparison
 * function
 *
 * @param vals   the array
 * @param begin  beginning of the first part
 * @param middle beginning of the second part
 * @param end    end of the second part
 * @param comp   comparison function
 *
 * @return
 * 1 if an error occurred\n
 * 0 otherwise
 */
int merge(void* vals[],int begin,int middle,int end,
    int(*comp)(void*,void*))
{
  int i,j,k,result=0;
  int size=end-begin+1;
  int sizel=middle-begin;
  void** copy=malloc(size*sizeof(void*));
  if(!copy) result=1;
  else
  {
    for(i=0,k=begin;i<size;i++,k++) copy[i]=vals[k];
    for(i=0,j=sizel,k=begin;k<=end;k++)
    {
      if(j>=size||(i<sizel&&((*comp)(copy[i],copy[j])<0)))
      {
	vals[k]=copy[i];
	i++;
      }
      else
      {
	vals[k]=copy[j];
	j++;
      }
    }
  }
  return result;
}

//==============================================================================

int mergeSort(void* vals[],int begin,int end,int(*comp)(void*,void*))
{
  int m,result=0;
  if(begin<end)
  {
    m=(begin+end)/2;
    result+=mergeSort(vals,begin,m,*comp);
    result+=mergeSort(vals,m+1,end,*comp);
    result+=merge(vals,begin,m+1,end,*comp);
  }
  return result;
}
