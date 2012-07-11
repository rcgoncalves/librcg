/**
 * Implementation of linear programming functions.
 *
 * @author Rui Carlos Gonçalves
 * @file rlp.c
 * @version 3.0
 * @date 07/2012
 */
#include <stdio.h>
#include <float.h>
#include <math.h>
#include "rlp.h"

/**
 * Given a row (<tt>R</tt>), a column (<tt>C</tt>), and the number of columns
 * (<tt>NC</tt>) of a matrix, computes an equivalent 1D position.
 */
#define POS(R,C,NC) ((R)*(NC)+(C))

/**
 * Prints a matrix associated to an optimization problem.
 *
 * The file <tt>file</tt>, where the matrix will be printed, must be opened
 * before calling this function.
 *
 * @param matrix the matrix to print
 * @param nrows  the number of rows
 * @param ncols  the number of columns
 * @param file where the tables will be printed
 */
static void fmprint(double* matrix,int nrows,int ncols,FILE* file)
{
  int i,j;
  fprintf(file,"\n  +");
  for(i=0;i<ncols;i++)
  {
    fprintf(file,"--------------+");
  }
  fputs("\n",file);
  for(i=0;i<nrows;i++)
  {
    fprintf(file,"  |");
    for(j=0;j<ncols;j++)
    {
      fprintf(file," %12.4f |",matrix[POS(i,j,ncols)]);
    }
    fputs("\n",file);
  }
  fprintf(file,"  +");
  for(i=0;i<ncols;i++)
  {
    fprintf(file,"--------------+");
  }
  fputs("\n\n",file);
}

//==============================================================================

/**
 * Finds the minimum value of a matrix's column.
 *
 * @param matrix the matrix
 * @param nrows  the number of rows
 * @param ncols  the number of columns
 * @param col    the column index
 * @param row    pointer where the row that contains the minimum value will be
 *               put
 *
 * @return
 * minimum value of the specified column
 */
static double minimumc(double* matrix,int nrows,int ncols,int col,int* row)
{
  int i;
  double res=DBL_MAX;
  for(i=0;i<nrows;i++)
  {
    if(matrix[POS(i,col,ncols)]<res)
    {
      res=matrix[POS(i,col,ncols)];
      *row=i;
    }
  }
  return res;
}

//==============================================================================

/**
 * Finds the minimum value of a matrix's row.
 *
 * @param matrix the matrix row
 * @param ncols  the number of columns
 * @param row    the row index
 * @param col    pointer where the row that contains the minimum value will be
 *               put
 *
 * @return
 * minimum value of the specified row
 */
static double minimumr(double* matrix,int ncols,int row,int* col)
{
  int i;
  double res=DBL_MAX;
  for(i=0;i<ncols;i++)
  {
    if(matrix[POS(row,i,ncols)]<res)
    {
      res=matrix[POS(row,i,ncols)];
      *col=i;
    }
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
  if(!err)
  {
    aux=minimumr(a,nm2,0,&pos);
    if(aux<0) err=simplexp(a,n,m,pos,file);
  }
  return err;
}

//==============================================================================

int simplexp(double* a,int n,int m,int pos,FILE* file)
{
  int nm,pivotc,pivotr,i,j,k,result=0;
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
    {
      if(a[POS(i,pivotc,k)]>0)
      {
        r=a[POS(i,nm,k)]/a[POS(i,pivotc,k)];
        if(r<aux)
        {
          aux=r;
          pivotr=i;
        }
      }
    }
    if(pivotr==-1) result=1;
    else
    {
      pivot=a[POS(pivotr,pivotc,k)];
      for(i=0;i<nm+1;i++)
      {
        a[POS(pivotr,i,k)]/=pivot;
      }
      for(i=1;i<m+1;i++)
      {
        if(i!=pivotr)
        {
          coef=-a[POS(i,pivotc,k)];
          for(j=0;j<nm+1;j++)
            a[POS(i,j,k)]+=coef*a[POS(pivotr,j,k)];
        }
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
  }
  return result;
}

//==============================================================================

int simplexd(double* a,int n,int m,int pos,FILE* file)
{
  int pivotc,pivotr,nm,i,j,k,result=0;
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
    {
      if(a[POS(pivotr,i,k)]<0)
      {
        r=a[POS(0,i,k)]/a[POS(pivotr,i,k)];
        if(fabs(r)<aux)
        {
          aux=r;
          pivotc=i;
        }
      }
    }
    if(pivotc==-1) result=1;
    else 
    {
      pivot=a[POS(pivotr,pivotc,k)];
      for(i=0;i<nm+1;i++)
      {
        a[POS(pivotr,i,k)]/=pivot;
      }
      aux=a[POS(pivotr,nm,k)];
      for(i=0;i<m+1;i++)
      {
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
      }
      a[POS(pivotr,nm+1,k)]=pivotc;
      if(file) fmprint(a,m+1,k,file);
    }
  }
  return result;
}
