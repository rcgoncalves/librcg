/**
 * Implementação de funções de programação linear.
 *
 * @author Rui Carlos A. Gonçalves <rcgoncalves.pt@gmail.com>
 * @file rlp.c
 * @version 2.1.1
 * @date 02/2009
 */
#include <stdio.h>
#include <float.h>
#include <math.h>
#include "rlp.h"

/**
 * Dado a linha, a coluna e o número de colunas de um array de duas dimensões
 *   obtém o índice dessa posição assumindo que o array é de uma dimensão.
 */
#define POS(L,C,NC) ((L)*(NC)+(C))

/**
 * Imprime uma matriz associada a um problema de programação linear.
 * A matriz é impressa no ficheiro @a file (que deverá ter sido previamente
 *   aberto).
 *
 * @param matrix matriz que vamos imprimir.
 * @param nrows  número de linhas.
 * @param ncols  número de colunas.
 * @param file   ficheiro onde a matriz será impressa.
 */
static void fmprint(double* matrix,int nrows,int ncols,FILE* file)
{
  int i,j;

  fprintf(file,"\n  +");
  for(i=0;i<ncols;i++)
    fprintf(file,"--------------+");

  fputs("\n",file);

  for(i=0;i<nrows;i++)
  {
    fprintf(file,"  |");
    for(j=0;j<ncols;j++)
      fprintf(file," %12.4f |",matrix[POS(i,j,ncols)]);

    fputs("\n",file);
  }

  fprintf(file,"  +");
  for(i=0;i<ncols;i++)
    fprintf(file,"--------------+");

  fputs("\n\n",file);
}

//==============================================================================

/**
 * Determina o menor valor de uma coluna de uma matriz.
 *
 * @param matrix matriz onde procuramos o valor.
 * @param nrows  número de linhas da matriz.
 * @param ncols  número de colunas da matriz.
 * @param col    coluna onde vamos procurar.
 * @param row    local onde é colocado o índice da linha em que o elemento
 *               ocorreu.
 *
 * @return mínimo valor encontrado na coluna @a col da matriz @a matrix.
 */
static double minimumc(double* matrix,int nrows,int ncols,int col,int* row)
{
  int i;
  double res=DBL_MAX;

  for(i=0;i<nrows;i++)
    if(matrix[POS(i,col,ncols)]<res)
    {
      res=matrix[POS(i,col,ncols)];
      *row=i;
    }

  return res;
}

//==============================================================================

/**
 * Determina o menor valor de uma linha de uma matriz.
 *
 * @param matrix matriz onde procuramos o valor.
 * @param ncols  número de colunas da matriz.
 * @param row    linha onde vamos procurar.
 * @param col    local onde é colocado o índice da coluna em que o elemento
 *               ocorreu.
 *
 * @return mínimo valor encontrado na linha @a row da matriz @a matrix.
 */
static double minimumr(double* matrix,int ncols,int row,int* col)
{
  int i;
  double res=DBL_MAX;

  for(i=0;i<ncols;i++)
    if(matrix[POS(row,i,ncols)]<res)
    {
      res=matrix[POS(row,i,ncols)];
      *col=i;
    }

  return res;
}

//==============================================================================

int simplex(double* a,int n,int m,FILE* file)
{
  double aux;
  int pos,nm2,err;

  nm2=n+m+2;

  aux=minimumc(&a[nm2],m,nm2,n+m,&pos);
  err=0;

  if(file) fmprint(a,m+1,nm2,file);

  if(aux<0) err=simplexd(a,n,m,pos+1,file);

  if(err) return err;
  else
  {
    aux=minimumr(a,nm2,0,&pos);

    if(aux<0) err=simplexp(a,n,m,pos,file);

    if(err) return err;
    else return 0;
  }
}

//##############################################################################

int simplexp(double* a,int n,int m,int pos,FILE* file)
{
  int nm,pivotc,pivotr,i,j,k;
  double pivot,coef,aux,r;

  nm=n+m;
  k=nm+2;
  aux=-1;
  pivotc=pos;

  while(aux<0)
  {
    pivotr=-1;
    aux=DBL_MAX;

    for(i=1;i<m+1;i++)
      if(a[POS(i,pivotc,k)]>0)
      {
        r=a[POS(i,nm,k)]/a[POS(i,pivotc,k)];
        if(r<aux)
        {
          aux=r;
          pivotr=i;
        }
      }

    if(pivotr==-1) return 1;

    pivot=a[POS(pivotr,pivotc,k)];

    for(i=0;i<nm+1;i++)
      a[POS(pivotr,i,k)]/=pivot;

    for(i=1;i<m+1;i++)
      if(i!=pivotr)
      {
        coef=-a[POS(i,pivotc,k)];
        for(j=0;j<nm+1;j++)
          a[POS(i,j,k)]+=coef*a[POS(pivotr,j,k)];
      }

    aux=DBL_MAX;
    coef=-a[POS(0,pivotc,k)];

    a[POS(pivotr,nm+1,k)]=pivotc;

    for(i=0;i<nm+1;i++)
    {
      a[POS(0,i,k)]+=coef*a[POS(pivotr,i,k)];
      if(a[POS(0,i,k)]<aux)
      {
        aux=a[POS(0,i,k)];
        pivotc=i;
      }
    }

    if(file) fmprint(a,m+1,k,file);
  }

  return 0;
}

//##############################################################################

int simplexd(double* a,int n,int m,int pos,FILE* file)
{
  int pivotc,pivotr,nm,i,j,k;
  double aux,pivot,r,coef;

  nm=n+m;
  k=nm+2;

  aux=-1;
  pivotr=pos;

  while(aux<0)
  {
    pivotc=-1;
    aux=DBL_MAX;

    for(i=0;i<nm;i++)
      if(a[POS(pivotr,i,k)]<0)
      {
        r=a[POS(0,i,k)]/a[POS(pivotr,i,k)];
        if(fabs(r)<aux)
        {
          aux=r;
          pivotc=i;
        }
      }

    if(pivotc==-1) return 1;

    pivot=a[POS(pivotr,pivotc,k)];

    for(i=0;i<nm+1;i++)
      a[POS(pivotr,i,k)]/=pivot;

    aux=a[POS(pivotr,nm,k)];

    for(i=0;i<m+1;i++)
      if(i!=pivotr)
      {
        coef=a[POS(i,pivotc,k)]>0?a[POS(i,pivotc,k)]:-a[POS(i,pivotc,k)];
        for(j=0;j<nm+1;j++)
        {
          a[POS(i,j,k)]+=coef*a[POS(pivotr,j,k)];
        }

        if(a[POS(i,nm,k)]<aux)
        {
          aux=a[POS(i,nm,k)];
          pivotr=i;
        }
      }

    a[POS(pivotr,nm+1,k)]=pivotc;

    if(file) fmprint(a,m+1,k,file);
  }

  return 0;
}
