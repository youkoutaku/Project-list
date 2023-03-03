// ***********************************
// *** invK3d_l.c                  ***
// *** 先端位置とヤコビ行列の設定  ***
// *** (3-D Simulation)            ***
// *** CopyRight Shugen MA 98/5/16 ***
// *** modified by mori-zen        ***
// ***********************************
//yang 4+1 link 2023/1/22

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "invK3d.h"
#include "glshapes.h"

//yang 4軸5リンクロボットアーム　逆運動学

// *** 先端位置 ***
void endPosition( len, tht, pos ) //始点・終点に関わる
	double *len;  //  Link length : L0, L1, L2, L3, L4, "L5"  
	double *tht;  //  Joint theta :     J1, J2, J3, J4, "J5"
	double *pos;  // End position :  X,  Y,	 Z
{	
	pos[X] = ( len[L2]*cos(tht[J2]) + len[L3]*cos(tht[J2]+tht[J3]) + len[L4]*cos(tht[J2]+tht[J3]+tht[J4]) )*cos(tht[J1]);
	pos[Y] = ( len[L2]*cos(tht[J2]) + len[L3]*cos(tht[J2]+tht[J3]) + len[L4]*cos(tht[J2]+tht[J3]+tht[J4]) )*sin(tht[J1]);
	pos[Z] = len[L1] + len[L2]*sin(tht[J2]) + len[L3]*sin(tht[J2]+tht[J3]) + len[L4]*sin(tht[J2]+tht[J3]+tht[J4]);
}

// *** ヤコビ行列 ***
void jacobianMatrix( len, tht, Jaco )
	double *len;
	double *tht;
	MAT *Jaco;
{
	MATelem(*Jaco,1,1)= -( len[L2]*cos(tht[J2]) + len[L3]*cos(tht[J2]+tht[J3]) + len[L4]*cos(tht[J2]+tht[J3]+tht[J4]) ) * sin(tht[J1]);
	MATelem(*Jaco,1,2)= -( len[L2]*sin(tht[J2]) + len[L3]*sin(tht[J2]+tht[J3]) + len[L4]*sin(tht[J2]+tht[J3]+tht[J4]) ) * cos(tht[J1]);
	MATelem(*Jaco,1,3)= -( len[L3]*sin(tht[J2]+tht[J3]) + len[L4]*sin(tht[J2]+tht[J3]+tht[J4]) ) * cos(tht[J1]);
	MATelem(*Jaco,1,4)= -len[L4]*sin(tht[J2]+tht[J3]+tht[J4]) * cos(tht[J1] );


	MATelem(*Jaco,2,1)=  ( len[L2]*cos(tht[J2]) + len[L3]*cos(tht[J2]+tht[J3]) + len[L4]*cos(tht[J2]+tht[J3]+tht[J4]) ) * cos(tht[J1]);
	MATelem(*Jaco,2,2)= -( len[L2]*sin(tht[J2]) + len[L3]*sin(tht[J2]+tht[J3]) + len[L4]*sin(tht[J2]+tht[J3]+tht[J4]) ) * sin(tht[J1]);
	MATelem(*Jaco,2,3)= -( len[L3]*sin(tht[J2]+tht[J3]) + len[L4]*sin(tht[J2]+tht[J3]+tht[J4]) ) * sin(tht[J1]);
	MATelem(*Jaco,2,4)= -len[L4]*sin(tht[J2]+tht[J3]+tht[J4]) * sin(tht[J1]);


	MATelem(*Jaco,3,1)= 0;
	MATelem(*Jaco,3,2)= len[L2]*cos(tht[J2]) + len[L3]*cos(tht[J2]+tht[J3]) + len[L4]*cos(tht[J2]+tht[J3]+tht[J4]);
	MATelem(*Jaco,3,3)= len[L3]*cos(tht[J2]+tht[J3]) + len[L4]*cos(tht[J2]+tht[J3]+tht[J4]);
	MATelem(*Jaco,3,4)= len[L4]*cos(tht[J2]+tht[J3]+tht[J4]);


}

// *** 先端速度 ***
void endVelocity( Jaco, dTht, dPos )
	MAT *Jaco;
	double *dTht;
	double *dPos;
{
	register int i, j;
	int mm, nn;

	mm = MATheight( *Jaco );
	nn = MATwidth(  *Jaco );

	for( i=0; i<mm; i++ ){
		dPos[i] = 0.0;
		for( j=0; j<nn; j++ ){
			dPos[i] +=(MATelem(*Jaco,i+1,j+1) * dTht[j]);
		}
	}
}

// *** 先端速度の目標入力値 ***
int demandInput( cnum, kP, Pint, Pend, len, time, lastTime, tht, dP ) //始点・終点に関わる
	int cnum;
	double kP;
	double *Pint, *Pend;
	double *len;
	double time, lastTime;
	double *tht;
	double *dP;
{
	register int i;
	double str;
	double cxyz[3];
	double Amp;
	double stD, veD;
	double *p, *q;

	if( (p = (double *)calloc(cnum, sizeof(double))) == NULL ){
		return FAULT;
	}
	if( (q = (double *)calloc(cnum, sizeof(double))) == NULL ){
		return FAULT;
	}

 	str = 1.0;

	for( i=0; i<cnum; i++ ){
		cxyz[i]= (Pend[i] - Pint[i])/str;
	}

	// 3次多項式で，軌道を生成
	Amp = 6.0*str/pow(lastTime, 2.0); //A
	veD = Amp*time - Amp*pow(time, 2.0)/(lastTime); //d(u)/dt
	stD = Amp*pow(time, 2.0)/2.0 - Amp*pow(time, 3.0)/(lastTime*3.0); //u

	endPosition( len, tht, p );
	for( i=0; i<cnum; i++ ){
		 q[i] = Pint[i] + stD * cxyz[i];
		dP[i] = veD * cxyz[i] + kP*(q[i] - p[i]);
	}
	free(p);
	free(q);

	return TRUE;
}

// *** 関節角速度 ***
int jointRotateVelocity( Jaco, dPos, dTht )
	MAT *Jaco;
	double *dPos;
	double *dTht;
{
	register int i, j;
	int cnum, jnum;
	MAT invJaco;  // Jの逆行列

	cnum = MATheight(*Jaco);
	jnum = MATwidth(*Jaco);

	if( MATalloc( &invJaco, jnum, cnum ) == FAULT ){
		return( FAULT );
	}
	if( MATpse_invgauss(&invJaco, Jaco) == FAULT ){//疑似逆運動学を変えた
		fprintf(stderr, "Error on p_inverse of Jacobian Matrix\n");
		exit(777);
	}
	for( i=0; i<jnum; i++ ){
		dTht[i] = 0.0;
		for( j=0; j<cnum; j++ ){
			dTht[i] += MATelem(invJaco, i+1, j+1) * dPos[j];
		}
	}
	MATfree( &invJaco );

	return TRUE;
}


// **************************
// *** 行列計算ライブラリ ***
// **************************
#define swap(x,y) {double t; t = x; x = y; y = t;}

double MATeps = 1.0e-6;
int	maxNR = 500;

// *** 配列の確保 ***
int MATalloc( MAT *mat, int m, int n )
{
	if( (mat->x = (double *)calloc(m*n, sizeof(double))) != NULL ){
		MATheight(*mat) = m;
		MATwidth( *mat) = n;
		return (TRUE);
	}
	MATwidth(*mat) = MATheight(*mat) = 0;
	return (FAULT);
}

// *** メモリの開放 ***
void MATfree( MAT *mat )
{
	free( mat->x );
}

// *** 単位行列の生成 ***
void MATsquare( MAT *mat )
{
	register int i, j;

	if( MATwidth(*mat) == MATheight(*mat) ){
		for( i=1; i<=MATheight(*mat); i++ ){
			for( j=1; j<=MATwidth(*mat); j++ ){
				MATelem(*mat,i,j) = 0.0;
			}
			MATelem(*mat,i,i) = 1.0;
		}
	}
}

// *** 行列のコピー（正方行列の場合）***
void MATassign( MAT *mat1, MAT *mat2 )
{
	register int i, j;

	if( MATheight(*mat1) == MATheight(*mat2) &&
		MATwidth( *mat1) == MATwidth( *mat2)){
		for( i=1; i<=MATheight(*mat1); i++ ){
			for( j=1; j<=MATwidth(*mat1); j++ ){
				MATelem(*mat1,i,j) = MATelem(*mat2,i,j);
			}
		}
	}
}

// *** 逆行列の計算 ***
int MATinvgauss( MAT *ia, MAT *x )
{
	register int i, j, k, n, mx;
	double temp;
	MAT a;

	n = MATheight(*ia);

	if( MATalloc(&a,n,n) == FAULT ){
		return FAULT;
	}
	MATassign( &a, x );
	MATsquare( ia );
	for( k=1; k<=n-1; k++ ){
		for( i=k+1, mx=k; i<=n; i++ ){
			if( fabs(MATelem(a,i,k)) > fabs(MATelem(a,mx,k)) ){
				mx = i;
			}
		}
		if( fabs(MATelem(a,mx,k)) < MATeps ){
			return FAULT;
		}
		if( mx != k ){
			for( j=k; j<=n; j++ ){
				swap(MATelem(a,k,j), MATelem(a,mx,j));
			}
			for( j=1; j<=n; j++ ){
				swap(MATelem(*ia,k,j), MATelem(*ia,mx,j));
			}
		}
		for( i=k+1; i<=n; i++ ){
			temp = MATelem(a,i,k) / MATelem(a,k,k);
			for( j=1; j<=n; j++ ){
				MATelem(a,i,j) -= temp * MATelem(a,k,j);
			}
			for( j=1; j<=n; j++ ){
				MATelem(*ia,i,j) -= temp * MATelem(*ia,k,j);
			}
		}
	}
	for( k=n; k>=1; k-- ){
		for( j=1; j<=n; j++ ){
			MATelem(*ia,k,j) /= MATelem(a,k,k);
		}
		for( i=k-1; i>=1; i-- ){
			for( j=1; j<=n; j++ ){
				MATelem(*ia,i,j) -= MATelem(*ia,k,j)*MATelem(a,i,k);
			}
		}
	}
	MATfree(&a);

	return TRUE;
}

// *** 行列の表示 ***
void MATdisp( MAT *mat )
{
	register int i, j;

	printf("\n");

	for( i=1; i<=MATheight(*mat); i++ ){
		for( j=1; j<=MATwidth(*mat); j++ ){
			printf("%f ", MATelem(*mat,i,j) );
		}
		printf("\n");
	}	
}

// *** 転置行列の生成 ***
void MATtrans( MAT *ta, MAT *x )
{
	register int i, j;
	register int n, m;

	m = MATheight(*x);  // 行数
	n = MATwidth( *x);  // 列数

	for( i=1; i<=m; i++ ){
		for( j=1; j<=n; j++ ){
			MATelem(*ta,j,i) = MATelem(*x,i,j);
		}
	}
}

// *** 行列の積 ***
void MATmulti( MAT *ma, MAT *mat1, MAT *mat2 )
{
	register int i, j, k;
	register int m1, n1, n2;

	m1 = MATheight(*mat1);  // mat1の行数
	n1 = MATwidth( *mat1);  // mat1の列数 = mat2の行数
	n2 = MATwidth( *mat2);  // mat2の列数

	for( i=1; i<=m1; i++ ){
		for( j=1; j<=n2; j++ ){
			for( k=1; k<=n1; k++ ){
				MATelem(*ma,i,j) += MATelem(*mat1,i,k) * MATelem(*mat2,k,j);
			}
		}
	}
}

// *** 擬似逆行列の計算 ***
int MATpse_invgauss( MAT *pia, MAT *x )
{
	// 擬似逆行列の算出  pseudo-inverse matrix
	MAT JT;           // J^T (Jの転置)
	MAT J_JT;         // J・JT
	MAT inv_J_JT;     // (J・JT)^1 (J・JTの逆行列）

	if( MATalloc( &JT, MATwidth(*x), MATheight(*x) ) == FAULT ){
		return( FAULT );
	}
	if( MATalloc( &J_JT, MATheight(*x), MATheight(*x) ) == FAULT ){
		return( FAULT );
	}
	if( MATalloc( &inv_J_JT, MATheight(*x), MATheight(*x) ) == FAULT ){
		return( FAULT );
	}

	// Jacobi行列 の表示
	//MATdisp(x);

	// JT (Jの転置行列)を求める
	MATtrans( &JT, x );  
	//MATdisp( &JT );

	// J・JT を計算
	MATmulti( &J_JT, x, &JT );
	//MATdisp( &J_JT );

	// J・JTの逆行列 を求める
	MATinvgauss( &inv_J_JT, &J_JT );
	//MATdisp( &inv_J_JT );

	// JT・(J・JT)^1 (Jの擬似逆行列)を求める
	MATmulti( pia, &JT, &inv_J_JT );
	//MATdisp( pia );

	MATfree( &JT );
	MATfree( &J_JT );
	MATfree( &inv_J_JT );

	return TRUE;
}