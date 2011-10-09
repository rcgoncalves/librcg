/**
 * Implementação de funções que manipulam strings.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file rstring.c
 * @version 2.0.1
 * @date 02/2009
 */
#include <string.h>
#include <stdlib.h>
#include "rstring.h"


int delISpaces(char* str)
{
  int i,j;
    
  if(!str) return -1;
  else
  {
    for(j=0;str[j]==' ';j++);

    if(j)
    {
      for(i=0;str[j];i++,j++)
        str[i]=str[j];

      str[i]=str[j];

      return i;
    }
    else return strlen(str);
  }
}

//##############################################################################

int delCSpaces(char* str)
{
  int i,j;

  if(!str) return -1;
  else
  {
    for(i=0,j=1;str[i+1];i++)
      if(str[i]!=' '||str[i+1]!=' ')
      {
        str[j]=str[i+1];
        j++;
      }

    str[j]=str[i+1];

    return j;
  }
}

//##############################################################################

int delESpaces(char* str)
{
  int i;
    
  if(!str) return -1;
  else
  {
    for(i=strlen(str);str[i-1]==' ';i--)
      str[i-1]='\0';

    return i;
  }
}

//##############################################################################

int delSpaces(char* str)
{
  int i,j;

  if(!str) return -1;
  else
  {
    for(i=0;str[i]==' ';i++);

    for(j=0;str[i];i++)
      if(str[i]!=' '||str[i+1]!=' ')
      {
        str[j]=str[i];
        j++;
      }

    if(str[j-1]==' ')
    {
      str[j-1]='\0';
      return(j-1);
    }
    else
    {
      str[j]='\0';
      return j;
    }
  }
}

//##############################################################################

int charElem(char c,const char* str)
{
  int i,res;
  
  if(!str) return 0;
  else
  {
    for(i=0,res=0;str[i]&&!res;i++)
      res=(c==str[i]);

    return res;
  }
}

//##############################################################################

List words(const char* str)
{
  List l;
  char *aux,*sub,*tmp;
  int i,err;
  
  if(!str) return NULL;
  else if(!str[0]) return newList();
  else
  {
    aux=strdup(str);
    delSpaces(aux);
    sub=&aux[0];
    l=newList();

    for(i=0,err=0;aux[i]&&!err;i++)
      if(aux[i]==' ')
      {
        aux[i]='\0';
        tmp=strdup(sub);
        err=listInsertLst(l,tmp);
        sub=&aux[i+1];
      }
    tmp=strdup(sub);
    err=listInsertLst(l,tmp)&&err;

    if(err)
    {
      listMap(l,free);
      listDelete(l);
      return NULL;
    }
    else
    {
      free(aux);
      return l;
    }
  }
}

//##############################################################################

List strSep(const char* str,const char* delim)
{
  List l;
  char *aux,*tmp,*sub;
  int i,err;

  if(!str) return NULL;
  else if(!str[0]) return newList();
  else
  {
    aux=strdup(str);
    sub=&aux[0];
    l=newList();
    
    for(i=0,err=0;aux[i]&&!err;i++)
      if(1==charElem(aux[i],delim))
      {
        aux[i]='\0';
        if(sub[0]!=aux[i])
        {
          tmp=strdup(sub);
          err=listInsertLst(l,tmp);
        }
        sub=&aux[i+1];
      }
    if(sub[0]!=aux[i])
    {
      tmp=strdup(sub);
      err=listInsertLst(l,tmp)&&err;
    }

    if(err)
    {
      listMap(l,free);
      listDelete(l);
      return NULL;
    }
    else
    {
      free(aux);
      return l;
    }
  }
}
