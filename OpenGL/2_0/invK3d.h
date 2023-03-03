// *********************************************
// *** invK3d.h                              ***
// *** CopyRight (c) Shugen MA, May 16, 1998 ***
// *** modified by mori-zen                  ***
// *********************************************

#ifndef _INVK3D_H_
#define _INVK3D_H_

#define PI 3.141592  // PEI number

#define TRUE   1
#define FAULT  0
#define FALSE  0

#define SWAP(a,b) {double tmp; tmp=a; a=b; b=tmp;}

// Defination for Matrix calculation
typedef struct {
	int m;  // height 行数
	int n;  // width  列数
	double *x;
} MAT;

// Coordinates
#define  Cnum  3 //三次元
#define  X  0
#define  Y  1
#define  Z  2 //z軸

// Joints
#define  Jnum 5 //ジョイントの数
#define  J1  0
#define  J2  1
#define  J3  2
#define  J4  3
#define  J5  4

// Links 
#define  Lnum  6 //リンクの数
#define  L0  0
#define  L1  1
#define  L2  2
#define  L3  3
#define  L4  4
#define  L5  5

// Structure of PARAMETER
struct PARA{
	double tht[Jnum];
	double len[Lnum];
};

#define MATheight( mat )	((mat).m)
#define MATwidth(  mat )	((mat).n)
#define MATelem( mat,i,j )	((mat).x[((i)-1)*MATwidth(mat)+(j)-1])
//

int  MATalloc( MAT*, int, int );
void MATassign( MAT *, MAT * );
void MATfree( MAT * );
int  MATinvgauss( MAT *, MAT * );
void MATsquare( MAT * );
void MATdisp( MAT * );
void MATtrans( MAT *, MAT * );
void MATmulti( MAT *, MAT *, MAT * );
int  MATpse_invgauss( MAT *, MAT * );

// 関数のプロトタイプ宣言
void invK3d( void );
void initInvK3d( void );
void destInvK3d( void );
void inputData(  void );
void readArmParameters( struct PARA * );
void endPosition( double *, double *, double * );
void jacobianMatrix( double *, double *, MAT * );
void endVelocity( MAT *, double *, double * );
int  demandInput( int, double, double *, double *, double *, double, double, double *, double * );
int  jointRotateVelocity( MAT *, double *, double * );

#endif
