// **************************************
// *** glwindow.c                     ***
// *** 図形や形，ウィンドや環境の設定 ***
// **************************************

#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "glwindow.h"
#include "invK3d.h"

// *** 物体の材質・色  ***
void setColor(enum color color_name )
{
	// 立体の材質を表す色の定義
	GLfloat ambient[3];	   // 環境色：基本となる色
	GLfloat diffuse[3];	   // 拡散色：拡散反射の色
	GLfloat specular[3];   // 鏡面色：鏡面反射の色
	GLfloat shininess[1];  // 鏡面反射の強さ

	switch(color_name){
		// 赤
		case myRED:			
		  ambient[0]=0.2f;  ambient[1]=0.0f;  ambient[2]=0.0f;
		  diffuse[0]=0.5f;  diffuse[1]=0.0f;  diffuse[2]=0.0f;
		 specular[0]=0.7f; specular[1]=0.6f; specular[2]=0.6f;
		shininess[0]=32.0f;
		break;
		// 緑
		case myGREEN:		
		  ambient[0]=0.0f;  ambient[1]=0.2f;  ambient[2]=0.0f;
		  diffuse[0]=0.0f;  diffuse[1]=0.5f;  diffuse[2]=0.0f;
		 specular[0]=0.6f; specular[1]=0.7f; specular[2]=0.6f;
		shininess[0]=32.0f;
		break;
		// 青
		case myBLUE:		
		  ambient[0]=0.0f;  ambient[1]=0.0f;  ambient[2]=0.2f;
		  diffuse[0]=0.0f;  diffuse[1]=0.0f;  diffuse[2]=0.5f;
		 specular[0]=0.6f; specular[1]=0.6f; specular[2]=0.7f;
		shininess[0]=32.0f;
		break;
		// 黄
		case myYELLOW:		
		  ambient[0]=0.33f;  ambient[1]=0.22f;  ambient[2]=0.03f;
		  diffuse[0]=0.78f;  diffuse[1]=0.57f;  diffuse[2]=0.11f;
		 specular[0]=0.99f; specular[1]=0.91f; specular[2]=0.81f;
		shininess[0]=27.8f;
		break;
		// 白
		case myWHITE:		
		  ambient[0]=0.31f;  ambient[1]=0.31f;  ambient[2]=0.31f;
		  diffuse[0]=0.31f;  diffuse[1]=0.31f;  diffuse[2]=0.31f;
		 specular[0]=0.31f; specular[1]=0.31f; specular[2]=0.31f;
		shininess[0]=32.f;
		break;
		// シアン
		case myCYAN:		
		  ambient[0]=0.f;   ambient[1]=0.3f;  ambient[2]=0.2f;
		  diffuse[0]=0.f;   diffuse[1]=0.4f;  diffuse[2]=0.3f;
		 specular[0]=0.6f; specular[1]=0.5f; specular[2]=0.4f;
		shininess[0]=32.0f;
		break;
		// オレンジ
		case myORANGE:
		  ambient[0]= 0.63f; ambient[1]= 0.12f; ambient[2]= 0.f;
		  diffuse[0]= 0.78f; diffuse[1]= 0.17f; diffuse[2]= 0.f;
		 specular[0]=0.99f; specular[1]=0.21f; specular[2]=0.f;
		shininess[0]=27.8f;
		break;

		default:
		exit(0);
    }

	glMaterialfv( GL_FRONT, GL_AMBIENT,   ambient   );
	glMaterialfv( GL_FRONT, GL_DIFFUSE,   diffuse   );
	glMaterialfv( GL_FRONT, GL_SPECULAR,  specular  );
	glMaterialfv( GL_FRONT, GL_SHININESS, shininess );
}

// *** 蓋付きの円柱 ***
void myCylinder( GLUquadricObj *qobj, GLdouble baseRadius, GLdouble topRadius,
	      GLdouble height, GLint slices, GLint stacks )
{
	// cylinder
	gluCylinder( qobj, baseRadius, topRadius, height, slices, stacks );
	// end cap
	glTranslatef( 0.0, 0.0, height );
	gluDisk( qobj, 0.0, topRadius, slices, stacks );
	// other end cap
	gluQuadricOrientation( qobj, GLU_INSIDE );
	glTranslatef( 0.0, 0.0, -height );
	gluDisk( qobj, 0.0, baseRadius, slices, stacks );
	gluQuadricOrientation( qobj, GLU_OUTSIDE );
}

// *** 座標軸の描画 ***
void drawAxis(GLfloat size)
{
	int i;
	GLfloat origin[] = { 0.0, 0.0, 0.0 };
	GLfloat axis[][3] = { { 1.0, 0.0, 0.0 },
						  { 0.0, 1.0, 0.0 },
						  { 0.0, 0.0, 1.0 }};
	// arrow of axis
	GLfloat height = 2.0;
	GLfloat base = height*tan( 20*PI/180.0 );
	GLint slices = 16;
	GLint stacks = 16;

	glDisable( GL_LIGHTING );

	// *** draw axes ***
	glLineWidth( 2.0 );
	glBegin( GL_LINES );

	// glColor3f(0.0, 0.0, 0.0); 黒
	// glColor3f(1.0, 0.0, 0.0); 赤
	// glColor3f(0.0, 1.0, 0.0); 緑
	// glColor3f(1.0, 1.0, 0.0); 黄
	// glColor3f(0.0, 0.0, 1.0); 青
	// glColor3f(1.0, 0.0, 1.0); マゼンタ                  　
	// glColor3f(0.0, 1.0, 1.0); シアン
	// glColor3f(1.0, 1.0, 1.0); 白

	for( i=0; i<3; i++ ){
		axis[i][i]*=size;
		if( i==0 ){
			glColor3f(0.0, 1.0, 1.0);  // X axis シアン
		}
		else if( i==1 ){
			glColor3f(1.0, 0.5, 0.0);  // Y axis オレンジ
		}
		else{
			glColor3f(1.0, 0.0, 1.0);  // Z axis マゼンタ 　
		}
		glVertex3fv( origin );
		glVertex3fv( axis[i] );
    }
	glLineWidth( 1.0 );

	glEnd();

	// *** draw arrows ***
	glDisable( GL_CULL_FACE );

	glPushMatrix();

	// for Z axis
	glColor3f(1.0, 0.0, 1.0);  // マゼンタ
	glTranslatef( 0.0, 0.0, size );
	glutSolidCone( base, height, slices, stacks );

	// for Y axis
	glColor3f(1.0, 0.5, 0.0);  // オレンジ
	glTranslatef( 0.0, size, -size );
	glRotatef( -90.0, 1.0, 0.0, 0.0 );
	glutSolidCone( base, height, slices, stacks );

	// for X axis
	glColor3f(0.0, 1.0, 1.0);  // シアン
	glTranslatef( size, 0.0, -size );
	glRotatef( 90.0, 0.0, 1.0, 0.0 );
	glutSolidCone( base, height, slices, stacks );

	glPopMatrix();

	glEnable( GL_CULL_FACE );
	glEnable( GL_LIGHTING );
}

// *** 基準視点位置の設定 ***
void windowInit(void)
{
	w->slideX = 100.0;
	w->slideY =   0.0;
	w->slideZ =  20.0;
	w->rolX =     0.0;
	w->rolY =    20.0;
	w->rolZ =   -90.0;
}

// *** 照明の定義 ***
void defineLights(void)
{
	// 環境光や光源の位置と明るさ，色合いの定義
	GLfloat   model_ambient[4] = {2.0f, 2.0f, 2.0f, 1.0f};
	GLfloat light_position0[4] = {1.0f, 0.0f, 1.0f, 0.0f};
	GLfloat    light_color0[4] = {1.0f, 1.0f, 1.0f, 1.0f};

	// 環境光の設定．全体を明るく照明する
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, model_ambient );

	// ライトの設定
	glLightfv( GL_LIGHT0, GL_POSITION, light_position0 );

	// ライトの色．R, G, B, αの割合で色を定義
	glLightfv( GL_LIGHT0, GL_DIFFUSE, light_color0 );

	// 光源ON
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
}

// *** 図形の投影用の行列を定義する関数 ***
void defineViewMatrix(void)
{
	int i;
	GLfloat fovy = 30.0f;  // 画角

	//	視点と注視点の位置 注視点は原点に固定する
	GLfloat    eye[3] = {150.0, 0.0, 0.0};
	GLfloat center[3] = {  0.0, 0.0, 0.0};

	// 視線方向など
	GLfloat dir[3];
	GLfloat  up[3];
	GLfloat dist, norm;

	eye[X]+=w->slideX; center[X]+=w->slideX;
	eye[Y]+=w->slideY; center[Y]+=w->slideY;
	eye[Z]+=w->slideZ; center[Z]+=w->slideZ;

	// 投影用の行列の初期化
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	// 透視投影処理用の行列の生成
	gluPerspective(fovy, (GLfloat)w->width/w->height, 1.0, 1000.0);

	// ビューポート変換
	glViewport(0, 0, w->width, w->height);

	// モデル表示用の行列の初期化
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	// 視点から注視点への正規化されたベクトルの生成
	for( i = 0; i<3; i++ ){
		dir[i] = center[i] - eye[i];
	}
    dist=sqrt(dir[X]*dir[X]+dir[Y]*dir[Y]+dir[Z]*dir[Z]);
	for( i = 0; i<3; i++ ){
		dir[i] /= dist;
	}

	// 上側を指すベクトルを設定
	up[X] = - dir[X] * dir[Z];
	up[Y] = - dir[Y] * dir[Z];
	up[Z] = dir[X] * dir[X] + dir[Y] * dir[Y];
	norm = sqrt( up[X] * up[X] + up[Y] * up[Y] + up[Z] * up[Z]);
	for( i=0; i<3; i++){
		up[i] /= norm;
	}

	// 視点位置の設定
	gluLookAt( eye[X], eye[Y], eye[Z], center[X], center[Y], center[Z], up[X], up[Y], up[Z] );
}

// *** Window視点変更時 のコールバック関数 ***
void onRenderWindow(void)
{
	// フレームバッファとデプスバッファの初期化
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// 視点の並行移動（視点位置再定義)
	defineViewMatrix();

	glPushMatrix();

	// 視点の回転移動（ベース座標の回転変換）
	glRotatef( w->rolY, 0.0, 1.0, 0.0 );
	glRotatef( w->rolZ, 0.0, 0.0, 1.0 );

	// 物体の配置
	displayObject();

	glPopMatrix();

	// 画像の描画
	glutSwapBuffers();
}

// *** ウィンドの消去 ***
void destroyWindow(void)
{
	destInvK3d();
	glutDestroyWindow( w->win_root );
	free(w);

	exit(0);
}

// *** Key入力 のコールバック関数 ***
void onHitKey( unsigned char key, int x, int y )
{
	float deltaS = 3.0;

	switch( key ){
		case 'w': w->slideX -= deltaS; break; //前
		case 's': w->slideX += deltaS; break; //後
		case 'a': w->slideY -= deltaS; break; //左
		case 'd': w->slideY += deltaS; break; //右
		case 'e': w->slideZ -= deltaS; break; //上
		case 'q': w->slideZ += deltaS; break; //下
		case '0': windowInit(); break;  //原点復帰
		default: break;
	}
	if( key == ESC )  destroyWindow();

	// 再描画
	glutPostRedisplay();
}

// *** Keyコマンドの設定 ***
void onHitSpecialKey( int key, int x, int y )
{
	static int event_go = FALSE;  // アニメーション 起動・停止 フラグ
	double deltaR = 3.0;

	switch (key) {

		case GLUT_KEY_UP	: w->rolY += deltaR; break;
		case GLUT_KEY_DOWN	: w->rolY -= deltaR; break;
		case GLUT_KEY_LEFT	: w->rolZ += deltaR; break;
		case GLUT_KEY_RIGHT    : w->rolZ -= deltaR; break;
		case GLUT_KEY_F1	: event_go = !event_go;   //アニメ起動するF1キーに変わる．ノートパソコンので，Homeキーがない．

		if( event_go == TRUE ){
			glutIdleFunc( invK3d );
		}
		else{
			glutIdleFunc( NULL );
		}
		break;

		default:	break;
	}
	
	glutPostRedisplay();  // 再描画
}

// Windowサイズ変更時 のコールバック関数
void onReshapeWindow(int ww, int hh)
{
	// 画面の大きさ 確保
	w->width  = ww;
	w->height = hh;

	// 投影行列に関する計算
	defineViewMatrix();

	// 照明に関する定義
	defineLights();
}

// Window の作成
void createWindow(void)
{
	// 初期設定
	windowInit();

	// window  タイプ
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

	// window  大きさ
	glutInitWindowSize( WINDOW_SIZE_X, WINDOW_SIZE_Y );

	// window  位置
	glutInitWindowPosition( WINDOW_POSITION_X, WINDOW_POSITION_Y );

	// window  名前
	w->win_root = glutCreateWindow( "invK3d" );

	// window  背景色
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0 );

	// 隠面消去
	glEnable( GL_DEPTH_TEST );

	// イベント時に呼び出される関数の登録
	glutKeyboardFunc( onHitKey );
	glutSpecialFunc(  onHitSpecialKey );
	glutDisplayFunc(  onRenderWindow );
	glutReshapeFunc(  onReshapeWindow );
}
