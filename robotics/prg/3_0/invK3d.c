// *********************************************
// *** invK3d.c                              ***
// *** アームの目標位置の設定                ***
// *** (Inverse Kinematics)                  ***
// *** CopyRight (c) Shugen MA, June 5, 1998 ***
// *** modified by mori-zen                  ***
// *********************************************
//yang 4+1 link 2023/1/22

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>
#include "glwindow.h"
#include "glshapes.h"
#include "invK3d.h"

#define MY_GL_CUT 7  // 描画カット数

// *** 外部変数 ***
GLW *w;             // ウインドウ型構造体
struct PARA Arm;    // アームパラメータ構造体
double PosInt[Cnum], PosEnd[Cnum];	// 軌道 始点・終点
double DPos[Cnum];  // 関節速度
double DTht[Jnum];  // 関節角速度
double SampTime;    // サンプリングタイム
double  SimTime;    // 時間
double LastTime;    // 駆動時間
double KP;          // ゲイン
int    Count;       // カウント変数
MAT    Jaco;        // ヤコビ行列
FILE  *FpTht;       // 関節角ファイルポンタ

// *** 変数初期化関数 ***
void initInvK3d( void )
{
	int i;

	// 入力データ（必要データ）の読み込み
	inputData();

	// 行列（大きさ）の確保
	if( MATalloc( &Jaco, Cnum, Jnum ) == FAULT ){
		exit(FAULT);
	}

	// 角度ファイルのOpen
	if( (FpTht = fopen("angles.dat", "w")) == NULL ){
		fprintf(stderr, "Can not open <Angles File>!\n");
		exit(FAULT);
	}

	// アームパラメータの読み込みとアーム姿勢の初期化
	readArmParameters( &Arm );
	endPosition( Arm.len, Arm.tht, PosInt );

	for( i=J1; i<=Jnum-1; i++){// J2からJnumに変えた
		DTht[i] = 0.0;
	}

	Count   = 0;
	SimTime = 0.0;
}

// *** 領域解放 ***
void destInvK3d( void )
{
	MATfree( &Jaco );
}

// *** 逆運動学 ***
void invK3d( void )
{
	int i;

	// 先端加速度指令の誘導
	demandInput( Cnum, KP, PosInt, PosEnd, Arm.len, SimTime, LastTime, Arm.tht, DPos );

	// ヤコビ行列の計算
	jacobianMatrix( Arm.len, Arm.tht, &Jaco );

	// 関節角速度の計算
	if( jointRotateVelocity(&Jaco, DPos, DTht) == FAULT ){
		exit( FAULT );
	}

	// 関節角のファイルへの保存
	if( FpTht != NULL ){
		fprintf(FpTht, "%4.3f	", SimTime);
		for( i=J1; i<=Jnum-1; i++ ){// J2からJnumに変えた
			fprintf(FpTht, " %8.5f", Arm.tht[i]);
		}
		fprintf(FpTht, "\n");
    }

	// 次のステップの時間設定
	SimTime += SampTime;

	// シミュレータのための関節角度
	for( i=J1; i<=Jnum-1; i++ ){// J2からJnumに変えた
		Arm.tht[i] += DTht[i] * SampTime;
	}
    if( SimTime > LastTime ){
		if( FpTht != NULL ){
			fclose(FpTht);
		}
		FpTht = NULL;
		glutIdleFunc( NULL );
		return;
	}

	// 再描画
	if( Count == MY_GL_CUT ){
		Count = 0;
		glutPostRedisplay();
	}
	else{
		Count ++;
	}
}

// *** データの入力関数 ***
void inputData()
{
	// アーム先端の目標位置
	PosEnd[X] = 1.5;
	PosEnd[Y] = 1.0;
	PosEnd[Z] = 0.5;//z軸

	// サンプリング時間の設定
	SampTime = 0.005;

	// 駆動（運動）時間
	LastTime = 15.0;

	// 重み係数の設定
	KP = 20.0;
}

// *** アームパラメータの読み込みと設定関数 ***
void readArmParameters( struct PARA *arm )
{
	register int i;
	char dummy[80];
	FILE *fpPara;

	// Open parameter File
	if((fpPara = fopen("armIK.dat", "r")) == NULL){
		fprintf(stderr, "Can not open <Arm Parameter File>!\n");
		exit(FAULT);
	}

	// Read data from File
	//入力ファイルの数
	fscanf(fpPara, "%s", dummy);
	fscanf(fpPara, "%s", dummy);
	for( i=L0; i<=Lnum-1; i++ ){//L2からLnumに変えた
		fscanf(fpPara, "%lf", (arm->len+i));
	}

	fscanf(fpPara, "%s", dummy);
	for( i=J1; i<=Jnum-1; i++ ){//J2からJnumに変えた
		fscanf(fpPara, "%lf", (arm->tht+i));
		arm->tht[i] *= PI / 180.0;
	}

	fclose( fpPara );
}

// *** 画面に出現させる物体群の配置 ***
void displayObject( void )
{
	// 床
	displayWall();

	// 軌道
	displayTrajectory( PosInt, PosEnd );

	// ロボット
	displayRobot( Arm.len, Arm.tht );

	// 座標軸
	drawAxis( 10.0 );
}

// *** メイン関数 ***
int main( int argc, char **argv )
{
	if( (w = calloc(1, sizeof(GLW))) == NULL ){
		exit(1);
	}

	// 初期設定
	glutInit( &argc, argv );
	initInvK3d();

	// ウインドウの作成
	createWindow();

	// 演算と描画
	glutMainLoop();

	return 0;
}
