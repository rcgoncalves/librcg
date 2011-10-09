/**
 * Implementação de funções auxiliares básicas.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file util.c
 * @version 2.1.1
 * @date 02/2009
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"

/**
 * Tamanho do @a buffer inicial usado nas funções <tt>@ref rgets</tt> e
 *   <tt>@ref rgetsEOF</tt>
 */
#define BUFSIZE 32

/**
 * @e Semente da função <tt>@ref getRandom</tt>.
 */
long seed=0;

int rgets(char** str)
{
  char* str1,* str2;
  char tmp;
  int length,count;

  if(!str) return -2;
  else
  {
    length=BUFSIZE;
    str1=(char*)malloc((length+1)*sizeof(char));

    if(!str)
    {
      *str=NULL;
      return -1;
    }

    for(count=0;(tmp=getchar())!='\n';count++)
    {
      if(count>=length)
      {
        length*=2;
        str2=(char*)realloc(str1,length+1);
        if(!str2)
        {
          free(str1);
          *str=NULL;
          return -1;
        }
        else str1=str2;
      }

      str1[count]=tmp;
    }

    str1[count]='\0';
    *str=str1;
    return count;
  }
}

//##############################################################################

int rgetsEOF(char** str)
{
  char* str1,* str2;
  char tmp;
  int length,count;

  if(!str) return -2;
  else
  {
    length=BUFSIZE;
    str1=(char*)malloc((length+1)*sizeof(char));
    
    if(!str1)
    {
      *str=NULL;
      return -1;
    }

    for(count=0;(tmp=getchar())!=EOF;count++)
    {
      if(count>=length)
      {
        length*=2;
        str2=(char*)realloc(str1,length+1);
        if(!str2)
        {
          free(str1);
          *str=NULL;
          return -1;
        }
        else str1=str2;
      }

      str1[count]=tmp;
    }

    str1[count]='\0';
    *str=str1;
    return count;
  }
}

//##############################################################################

int rngets(char *str,int dim)
{
  int length;

  str[dim-1]=str[dim-2]=1;
  fgets(str,dim,stdin);

  if(str[dim-1]=='\0'&&str[dim-2]!='\n') 
  {
    while(getchar()!='\n');
    return -1;
  }
  else
  {
    length=strlen(str)-1;
    str[length]='\0';
    return length;
  }
}

//##############################################################################

int getRandom(int min,int max)
{
  int r;

  if(!seed)
  {
    time(&seed);
    srand((unsigned)seed);
  }

  r=min+rand()%(max-min+1);
  
  return r;
}

//##############################################################################

/**
 * Efectua a junção de duas partes (ordenadas) de um array.
 *
 * @param vals  array com os valores.
 * @param begin início da primeira parte do array.
 * @param midle início da segunda parte do array.
 * @param end   fim da segunda parte do array.
 * @param comp  função que compara os elementos do array.
 *
 * @return 1 se ocorrer algum erro;\n
 *         0 caso contrário.
 */
static int merge(void* vals[],int begin,int midle,int end,
    int(*comp)(void*,void*))
{
  int i,j,k;
  int sizeLeft=midle-begin;
  int sizeRight=end-midle+1;

  void** left=calloc(sizeLeft,sizeof(void*));
  void** right=calloc(sizeRight,sizeof(void*));

  if(!left||!right) return 1;
  else
  {
    for(i=0;i<sizeLeft;i++) left[i]=vals[begin+i];
    for(i=0;i<sizeRight;i++) right[i]=vals[midle+i];

    for(i=0,j=0,k=begin;k<=end;k++)
    {
      if(j>=sizeRight||(i<sizeLeft&&((*comp)(left[i],right[j])<0)))
      {
        vals[k]=left[i];
        i++;
      }
      else
      {
        vals[k]=right[j];
        j++;
      }
    }

    return 0;
  }
}

//==============================================================================

int mergeSort(void* vals[],int begin,int end,int(*comp)(void*,void*))
{
  int m,res;

  if(begin<end)
  {
    m=(begin+end)/2;
    res+=mergeSort(vals,begin,m,*comp);
    res+=mergeSort(vals,m+1,end,*comp);
    res+=merge(vals,begin,m+1,end,*comp);
  }

  return res;
}
