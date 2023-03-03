// ****************************
// *** glshapes.c           ***
// *** ���{�b�g�A�[���̕`�� ***
// ****************************

#include <GL/glut.h>
#include "glwindow.h"
#include "glshapes.h"
#include "invK3d.h"

// *** �O���̕`�� ***
void displayTrajectory( double *posI, double *posE )
{
	int i;
	double posInt[3], posEnd[3];

	// 2D�̏ꍇ��posEnd[Z]�̒l���s��ɂȂ邽��
	if( Cnum == 2){
		posE[Z] = 0.0;
	}
	for( i=0; i<3; i++ ){
		posInt[i] = SCALE * posI[i];
		posEnd[i] = SCALE * posE[i];
    }

	glDisable( GL_LIGHTING );

	glLineWidth( 2.0 );
	glColor3f( 1.0, 0.0, 0.0 );	 // �F�w��(R,G,B)

	glBegin( GL_LINES );

	glVertex3dv( posInt );
	glVertex3dv( posEnd );

	glEnd();
	glLineWidth( 1.0 );

	glEnable( GL_LIGHTING );
}

// *** ���{�b�g�`�� ***
void displayRobot( double *ll, double *theta )
{
	int i;
	double tht[Jnum];
	double len[Lnum];
	
	GLUquadricObj *qobj = gluNewQuadric();  // 2���Ȑ��I�u�W�F�N�g

	for( i=0; i<Jnum; i++ ){
		tht[i] = theta[i] * 180.0/PI;
	}
	for( i=0; i<Lnum; i++ ){
		len[i] = SCALE * ll[i];
	}

	// --- �����N 0 ---
	setColor( myWHITE );
	myCylinder( qobj, R0, R0, len[L0], 15, 1 );

	// --- �W���C���g 1 ---
	setColor( myRED );
	glPushMatrix();
	glTranslated( 0.0, 0.0, -R1 );
	myCylinder( qobj, R1, R1, 2*R1, 15, 1 );
	glPopMatrix();
	glRotated( tht[J1], 0, 0, 1 );

	// --- �����N 1 ---
	glPushMatrix();
	glRotated(   90.0, 0, 1, 0 );
	myCylinder( qobj, R1, R1, len[L1], 10, 1 );
	glPopMatrix();
	glTranslated( len[L1], 0.0, 0.0 );

	// --- �W���C���g 2 ---
	setColor( myBLUE );   
	glPushMatrix();
	glTranslated( 0.0, 0.0, -R2 );
	myCylinder( qobj, R2, R2, 2*R2, 15, 1 );
	glPopMatrix();
	glRotated( tht[J2], 0, 0, 1 );

	// --- �����N 2 ---
	glPushMatrix();
	glRotated(   90.0, 0, 1, 0 );
	myCylinder( qobj, R2, R2, len[L2], 10, 1 );
	glPopMatrix();
	glTranslated( len[L2], 0.0, 0.0 );
}

// *** ���̕`��	***
void displayWallFace( GLfloat floorSize )
{
	glDisable( GL_LIGHTING );

	glBegin( GL_QUADS );
	glVertex2f( floorSize, floorSize );
	glVertex2f(-floorSize, floorSize );
	glVertex2f(-floorSize,-floorSize );
	glVertex2f( floorSize,-floorSize );
	glEnd();

	glEnable( GL_LIGHTING );
}

// *** ���̐��̕`��	***
void displayWallLine( GLint num, GLfloat floorSize )
{
	int i;
	GLfloat tile = floorSize/num;
	GLfloat pos;

	glDisable( GL_LIGHTING );
	glLineWidth( 1 );

	glBegin( GL_LINES );
	for( i=-num; i<=num; i++ ){
		pos=tile*i;
		glVertex2f(-floorSize, pos);
		glVertex2f( floorSize, pos);
		glVertex2f(pos,-floorSize);
		glVertex2f(pos, floorSize);
	}
	glEnd();

	glEnable( GL_LIGHTING );
}

// *** ���̕`��	***
void displayWall(void)
{
	int unit = 7;		   // �^�C���̕�����
	GLfloat size = 100.0;  // ���ʂ̃T�C�Y

	glPushMatrix();
	glColor3f( 0.0f, 0.7f, 0.0f );
	displayWallLine( unit, size );
	glPopMatrix();
}
