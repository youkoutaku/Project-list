// *********************************************
// *** invK3d.c                              ***
// *** �A�[���̖ڕW�ʒu�̐ݒ�                ***
// *** (Inverse Kinematics)                  ***
// *** CopyRight (c) Shugen MA, June 5, 1998 ***
// *** modified by mori-zen                  ***
// *********************************************

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>
#include "glwindow.h"
#include "glshapes.h"
#include "invK3d.h"

#define MY_GL_CUT 5  // �`��J�b�g��

// *** �O���ϐ� ***
GLW *w;             // �E�C���h�E�^�\����
struct PARA Arm;    // �A�[���p�����[�^�\����
double PosInt[Cnum], PosEnd[Cnum];	// �O�� �n�_�E�I�_
double DPos[Cnum];  // �֐ߑ��x
double DTht[Jnum];  // �֐ߊp���x
double SampTime;    // �T���v�����O�^�C��
double  SimTime;    // ����
double LastTime;    // �쓮����
double KP;          // �Q�C��
int    Count;       // �J�E���g�ϐ�
MAT    Jaco;        // ���R�r�s��
FILE  *FpTht;       // �֐ߊp�t�@�C���|���^

// *** �ϐ��������֐� ***
void initInvK3d( void )
{
	int i;

	// ���̓f�[�^�i�K�v�f�[�^�j�̓ǂݍ���
	inputData();

	// �s��i�傫���j�̊m��
	if( MATalloc( &Jaco, Cnum, Jnum ) == FAULT ){
		exit(FAULT);
	}

	// �p�x�t�@�C����Open
	if( (FpTht = fopen("angles.dat", "w")) == NULL ){
		fprintf(stderr, "Can not open <Angles File>!\n");
		exit(FAULT);
	}

	// �A�[���p�����[�^�̓ǂݍ��݂ƃA�[���p���̏�����
	readArmParameters( &Arm );
	endPosition( Arm.len, Arm.tht, PosInt );

	for( i=J1; i<=J2; i++){
		DTht[i] = 0.0;
	}

	Count   = 0;
	SimTime = 0.0;
}

// *** �̈��� ***
void destInvK3d( void )
{
	MATfree( &Jaco );
}

// *** �t�^���w ***
void invK3d( void )
{
	int i;

	// ��[�����x�w�߂̗U��
	demandInput( Cnum, KP, PosInt, PosEnd, Arm.len, SimTime, LastTime, Arm.tht, DPos );

	// ���R�r�s��̌v�Z
	jacobianMatrix( Arm.len, Arm.tht, &Jaco );

	// �֐ߊp���x�̌v�Z
	if( jointRotateVelocity(&Jaco, DPos, DTht) == FAULT ){
		exit( FAULT );
	}

	// �֐ߊp�̃t�@�C���ւ̕ۑ�
	if( FpTht != NULL ){
		fprintf(FpTht, "%4.3f	", SimTime);
		for( i=J1; i<=J2; i++ ){
			fprintf(FpTht, " %8.5f", Arm.tht[i]);
		}
		fprintf(FpTht, "\n");
    }

	// ���̃X�e�b�v�̎��Ԑݒ�
	SimTime += SampTime;

	// �V�~�����[�^�̂��߂̊֐ߊp�x
	for( i=J1; i<=J2; i++ ){
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

	// �ĕ`��
	if( Count == MY_GL_CUT ){
		Count = 0;
		glutPostRedisplay();
	}
	else{
		Count ++;
	}
}

// *** �f�[�^�̓��͊֐� ***
void inputData()
{
	// �A�[����[�̖ڕW�ʒu
	PosEnd[X] = 0.0;
	PosEnd[Y] = 1.2;

	// �T���v�����O���Ԃ̐ݒ�
	SampTime = 0.005;

	// �쓮�i�^���j����
	LastTime = 10.0;

	// �d�݌W���̐ݒ�
	KP = 20.0;
}

// *** �A�[���p�����[�^�̓ǂݍ��݂Ɛݒ�֐� ***
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
	fscanf(fpPara, "%s", dummy);
	fscanf(fpPara, "%s", dummy);
	for( i=L0; i<=L2; i++ ){
		fscanf(fpPara, "%lf", (arm->len+i));
	}

	fscanf(fpPara, "%s", dummy);
	for( i=J1; i<=J2; i++ ){
		fscanf(fpPara, "%lf", (arm->tht+i));
		arm->tht[i] *= PI / 180.0;
	}

	fclose( fpPara );
}

// *** ��ʂɏo�������镨�̌Q�̔z�u ***
void displayObject( void )
{
	// ��
	displayWall();

	// �O��
	displayTrajectory( PosInt, PosEnd );

	// ���{�b�g
	displayRobot( Arm.len, Arm.tht );

	// ���W��
	//drawAxis( 10.0 );
}

// *** ���C���֐� ***
int main( int argc, char **argv )
{
	if( (w = calloc(1, sizeof(GLW))) == NULL ){
		exit(1);
	}

	// �����ݒ�
	glutInit( &argc, argv );
	initInvK3d();

	// �E�C���h�E�̍쐬
	createWindow();

	// ���Z�ƕ`��
	glutMainLoop();

	return 0;
}
