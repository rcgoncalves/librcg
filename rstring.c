/**
 * Implementation of functions to manipulate strings.
 *
 * @author Rui Carlos Gonçalves <rcgoncalves.pt@gmail.com>
 * @file rstring.c
 * @version 3.0
 * @date 05/2012
 */
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "rstring.h"

int trimStart(char* str)
{
  int i,j,result;
  if(!str) result=-1;
  else
  {
    for(j=0;isspace(str[j]);j++);
    if(j)
    {
      for(i=0;str[j];i++,j++)
      {
        str[i]=str[j];
      }
      str[i]=str[j];
      result=i;
    }
    else result=strlen(str);
  }
  return result;
}

//==============================================================================

int trimEnd(char* str)
{
  int i,result=0;
  if(!str) result=-1;
  else
  {
    for(i=strlen(str);isspace(str[i-1]);i--)
    {
      str[i-1]='\0';
    }
    result=i;
  }
  return result;
}

//==============================================================================

int trim(char* str)
{
  int i,j,result=0;
  if(!str) result=-1;
  else
  {
    for(i=0;isspace(str[i]);i++);
    for(j=0;str[i];i++)
    {
      if(!isspace(str[i])||!isspace(str[j-1]))
      {
        str[j]=str[i];
        j++;
      }
    }
    if(isspace(str[j-1]))
    {
      str[j-1]='\0';
      result=j-1;
    }
    else
    {
      str[j]='\0';
      result=j;
    }
  }
  return result;
}

//==============================================================================

int charElem(char c,const char* str)
{
  int i,result=0;
  if(str)
  {
    for(i=0;str[i]&&!result;i++)
    {
      result=(c==str[i]);
    }
  }
  return result;
}

//==============================================================================

List words(const char* str)
{
  List l;
  char *aux,*sub,*tmp;
  int i,err;
  if(!str) l=NULL;
  else if(!str[0]) l=newList();
  else
  {
    aux=strdup(str);
    trim(aux);
    sub=&aux[0];
    l=newList();
    for(i=0,err=0;aux[i]&&!err;i++)
    {
      if(isspace(aux[i]))
      {
        aux[i]='\0';
        tmp=strdup(sub);
        err=listInsertLst(l,tmp);
        sub=&aux[i+1];
      }
    }
    tmp=strdup(sub);
    err=listInsertLst(l,tmp)&&err;
    if(err)
    {
      listMap(l,free);
      listDelete(l);
      l=NULL;
    }
    else free(aux);
  }
  return l;
}

//==============================================================================

List strSep(const char* str,const char* delim)
{
  List l;
  char *aux,*tmp,*sub;
  int i,err;
  if(!str) l=NULL;
  else if(!str[0]) l=newList();
  else
  {
    aux=strdup(str);
    sub=&aux[0];
    l=newList();
    for(i=0,err=0;aux[i]&&!err;i++)
    {
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
      l=NULL;
    }
    else free(aux);
  }
  return l;
}
