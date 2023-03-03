// **************************************
// *** glwindow.c                     ***
// *** �}�`��`�C�E�B���h����̐ݒ� ***
// **************************************

#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "glwindow.h"
#include "invK3d.h"

// *** ���̂̍ގ��E�F  ***
void setColor(enum color color_name )
{
	// ���̂̍ގ���\���F�̒�`
	GLfloat ambient[3];	   // ���F�F��{�ƂȂ�F
	GLfloat diffuse[3];	   // �g�U�F�F�g�U���˂̐F
	GLfloat specular[3];   // ���ʐF�F���ʔ��˂̐F
	GLfloat shininess[1];  // ���ʔ��˂̋���

	switch(color_name){
		// ��
		case myRED:			
		  ambient[0]=0.2f;  ambient[1]=0.0f;  ambient[2]=0.0f;
		  diffuse[0]=0.5f;  diffuse[1]=0.0f;  diffuse[2]=0.0f;
		 specular[0]=0.7f; specular[1]=0.6f; specular[2]=0.6f;
		shininess[0]=32.0f;
		break;
		// ��
		case myGREEN:		
		  ambient[0]=0.0f;  ambient[1]=0.2f;  ambient[2]=0.0f;
		  diffuse[0]=0.0f;  diffuse[1]=0.5f;  diffuse[2]=0.0f;
		 specular[0]=0.6f; specular[1]=0.7f; specular[2]=0.6f;
		shininess[0]=32.0f;
		break;
		// ��
		case myBLUE:		
		  ambient[0]=0.0f;  ambient[1]=0.0f;  ambient[2]=0.2f;
		  diffuse[0]=0.0f;  diffuse[1]=0.0f;  diffuse[2]=0.5f;
		 specular[0]=0.6f; specular[1]=0.6f; specular[2]=0.7f;
		shininess[0]=32.0f;
		break;
		// ��
		case myYELLOW:		
		  ambient[0]=0.33f;  ambient[1]=0.22f;  ambient[2]=0.03f;
		  diffuse[0]=0.78f;  diffuse[1]=0.57f;  diffuse[2]=0.11f;
		 specular[0]=0.99f; specular[1]=0.91f; specular[2]=0.81f;
		shininess[0]=27.8f;
		break;
		// ��
		case myWHITE:		
		  ambient[0]=0.31f;  ambient[1]=0.31f;  ambient[2]=0.31f;
		  diffuse[0]=0.31f;  diffuse[1]=0.31f;  diffuse[2]=0.31f;
		 specular[0]=0.31f; specular[1]=0.31f; specular[2]=0.31f;
		shininess[0]=32.f;
		break;
		// �V�A��
		case myCYAN:		
		  ambient[0]=0.f;   ambient[1]=0.3f;  ambient[2]=0.2f;
		  diffuse[0]=0.f;   diffuse[1]=0.4f;  diffuse[2]=0.3f;
		 specular[0]=0.6f; specular[1]=0.5f; specular[2]=0.4f;
		shininess[0]=32.0f;
		break;
		// �I�����W
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

// *** �W�t���̉~�� ***
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

// *** ���W���̕`�� ***
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

	// glColor3f(0.0, 0.0, 0.0); ��
	// glColor3f(1.0, 0.0, 0.0); ��
	// glColor3f(0.0, 1.0, 0.0); ��
	// glColor3f(1.0, 1.0, 0.0); ��
	// glColor3f(0.0, 0.0, 1.0); ��
	// glColor3f(1.0, 0.0, 1.0); �}�[���^                  �@
	// glColor3f(0.0, 1.0, 1.0); �V�A��
	// glColor3f(1.0, 1.0, 1.0); ��

	for( i=0; i<3; i++ ){
		axis[i][i]*=size;
		if( i==0 ){
			glColor3f(0.0, 1.0, 1.0);  // X axis �V�A��
		}
		else if( i==1 ){
			glColor3f(1.0, 0.5, 0.0);  // Y axis �I�����W
		}
		else{
			glColor3f(1.0, 0.0, 1.0);  // Z axis �}�[���^ �@
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
	glColor3f(1.0, 0.0, 1.0);  // �}�[���^
	glTranslatef( 0.0, 0.0, size );
	glutSolidCone( base, height, slices, stacks );

	// for Y axis
	glColor3f(1.0, 0.5, 0.0);  // �I�����W
	glTranslatef( 0.0, size, -size );
	glRotatef( -90.0, 1.0, 0.0, 0.0 );
	glutSolidCone( base, height, slices, stacks );

	// for X axis
	glColor3f(0.0, 1.0, 1.0);  // �V�A��
	glTranslatef( size, 0.0, -size );
	glRotatef( 90.0, 0.0, 1.0, 0.0 );
	glutSolidCone( base, height, slices, stacks );

	glPopMatrix();

	glEnable( GL_CULL_FACE );
	glEnable( GL_LIGHTING );
}

// *** ����_�ʒu�̐ݒ� ***
void windowInit(void)
{
	w->slideX = 100.0;
	w->slideY =   0.0;
	w->slideZ =  20.0;
	w->rolX =     0.0;
	w->rolY =    20.0;
	w->rolZ =   -90.0;
}

// *** �Ɩ��̒�` ***
void defineLights(void)
{
	// ����������̈ʒu�Ɩ��邳�C�F�����̒�`
	GLfloat   model_ambient[4] = {2.0f, 2.0f, 2.0f, 1.0f};
	GLfloat light_position0[4] = {1.0f, 0.0f, 1.0f, 0.0f};
	GLfloat    light_color0[4] = {1.0f, 1.0f, 1.0f, 1.0f};

	// �����̐ݒ�D�S�̂𖾂邭�Ɩ�����
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, model_ambient );

	// ���C�g�̐ݒ�
	glLightfv( GL_LIGHT0, GL_POSITION, light_position0 );

	// ���C�g�̐F�DR, G, B, ���̊����ŐF���`
	glLightfv( GL_LIGHT0, GL_DIFFUSE, light_color0 );

	// ����ON
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
}

// *** �}�`�̓��e�p�̍s����`����֐� ***
void defineViewMatrix(void)
{
	int i;
	GLfloat fovy = 30.0f;  // ��p

	//	���_�ƒ����_�̈ʒu �����_�͌��_�ɌŒ肷��
	GLfloat    eye[3] = {150.0, 0.0, 0.0};
	GLfloat center[3] = {  0.0, 0.0, 0.0};

	// ���������Ȃ�
	GLfloat dir[3];
	GLfloat  up[3];
	GLfloat dist, norm;

	eye[X]+=w->slideX; center[X]+=w->slideX;
	eye[Y]+=w->slideY; center[Y]+=w->slideY;
	eye[Z]+=w->slideZ; center[Z]+=w->slideZ;

	// ���e�p�̍s��̏�����
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	// �������e�����p�̍s��̐���
	gluPerspective(fovy, (GLfloat)w->width/w->height, 1.0, 1000.0);

	// �r���[�|�[�g�ϊ�
	glViewport(0, 0, w->width, w->height);

	// ���f���\���p�̍s��̏�����
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	// ���_���璍���_�ւ̐��K�����ꂽ�x�N�g���̐���
	for( i = 0; i<3; i++ ){
		dir[i] = center[i] - eye[i];
	}
    dist=sqrt(dir[X]*dir[X]+dir[Y]*dir[Y]+dir[Z]*dir[Z]);
	for( i = 0; i<3; i++ ){
		dir[i] /= dist;
	}

	// �㑤���w���x�N�g����ݒ�
	up[X] = - dir[X] * dir[Z];
	up[Y] = - dir[Y] * dir[Z];
	up[Z] = dir[X] * dir[X] + dir[Y] * dir[Y];
	norm = sqrt( up[X] * up[X] + up[Y] * up[Y] + up[Z] * up[Z]);
	for( i=0; i<3; i++){
		up[i] /= norm;
	}

	// ���_�ʒu�̐ݒ�
	gluLookAt( eye[X], eye[Y], eye[Z], center[X], center[Y], center[Z], up[X], up[Y], up[Z] );
}

// *** Window���_�ύX�� �̃R�[���o�b�N�֐� ***
void onRenderWindow(void)
{
	// �t���[���o�b�t�@�ƃf�v�X�o�b�t�@�̏�����
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// ���_�̕��s�ړ��i���_�ʒu�Ē�`)
	defineViewMatrix();

	glPushMatrix();

	// ���_�̉�]�ړ��i�x�[�X���W�̉�]�ϊ��j
	glRotatef( w->rolY, 0.0, 1.0, 0.0 );
	glRotatef( w->rolZ, 0.0, 0.0, 1.0 );

	// ���̂̔z�u
	displayObject();

	glPopMatrix();

	// �摜�̕`��
	glutSwapBuffers();
}

// *** �E�B���h�̏��� ***
void destroyWindow(void)
{
	destInvK3d();
	glutDestroyWindow( w->win_root );
	free(w);

	exit(0);
}

// *** Key���� �̃R�[���o�b�N�֐� ***
void onHitKey( unsigned char key, int x, int y )
{
	float deltaS = 3.0;

	switch( key ){
		case 'd': w->slideX -= deltaS; break;
		case 'D': w->slideX += deltaS; break;
		case 's': w->slideY -= deltaS; break;
		case 'f': w->slideY += deltaS; break;
		case 'c': w->slideZ -= deltaS; break;
		case 'e': w->slideZ += deltaS; break;
		case '0': windowInit(); break;
		default: break;
	}
	if( key == ESC )  destroyWindow();

	// �ĕ`��
	glutPostRedisplay();
}

// *** Key�R�}���h�̐ݒ� ***
void onHitSpecialKey( int key, int x, int y )
{
	static int event_go = FALSE;  // �A�j���[�V���� �N���E��~ �t���O
	double deltaR = 3.0;

	switch (key) {

		case GLUT_KEY_UP	: w->rolY += deltaR; break;
		case GLUT_KEY_DOWN	: w->rolY -= deltaR; break;
		case GLUT_KEY_LEFT	: w->rolZ += deltaR; break;
		case GLUT_KEY_RIGHT : w->rolZ -= deltaR; break;
		case GLUT_KEY_HOME	: event_go = !event_go;

		if( event_go == TRUE ){
			glutIdleFunc( invK3d );
		}
		else{
			glutIdleFunc( NULL );
		}
		break;

		default:	break;
	}
	
	glutPostRedisplay();  // �ĕ`��
}

// Window�T�C�Y�ύX�� �̃R�[���o�b�N�֐�
void onReshapeWindow(int ww, int hh)
{
	// ��ʂ̑傫�� �m��
	w->width  = ww;
	w->height = hh;

	// ���e�s��Ɋւ���v�Z
	defineViewMatrix();

	// �Ɩ��Ɋւ����`
	defineLights();
}

// Window �̍쐬
void createWindow(void)
{
	// �����ݒ�
	windowInit();

	// window  �^�C�v
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

	// window  �傫��
	glutInitWindowSize( WINDOW_SIZE_X, WINDOW_SIZE_Y );

	// window  �ʒu
	glutInitWindowPosition( WINDOW_POSITION_X, WINDOW_POSITION_Y );

	// window  ���O
	w->win_root = glutCreateWindow( "invK3d" );

	// window  �w�i�F
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0 );

	// �B�ʏ���
	glEnable( GL_DEPTH_TEST );

	// �C�x���g���ɌĂяo�����֐��̓o�^
	glutKeyboardFunc( onHitKey );
	glutSpecialFunc(  onHitSpecialKey );
	glutDisplayFunc(  onRenderWindow );
	glutReshapeFunc(  onReshapeWindow );
}
