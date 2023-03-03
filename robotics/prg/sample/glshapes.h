// ******************
// *** glshapes.h ***
// ******************

#ifndef _SHAPE_H_
#define _SHAPE_H_

#define SCALE  30         // �X�P�[��
#define R0  (SCALE*0.09)  // �����N0���a
#define R1  (SCALE*0.18)  // �����N1���a
#define R2  (SCALE*0.18)  // �����N2���a

void displayTrajectory( double *posInt, double *posEnd );
void displayRobot( double *ll, double *theta );
void displayWallFace( GLfloat floorSize );
void displayWallLine( GLint num, GLfloat floorSize );
void displayWall( void );

#endif
