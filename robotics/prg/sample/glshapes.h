// ******************
// *** glshapes.h ***
// ******************

#ifndef _SHAPE_H_
#define _SHAPE_H_

#define SCALE  30         // スケール
#define R0  (SCALE*0.09)  // リンク0半径
#define R1  (SCALE*0.18)  // リンク1半径
#define R2  (SCALE*0.18)  // リンク2半径

void displayTrajectory( double *posInt, double *posEnd );
void displayRobot( double *ll, double *theta );
void displayWallFace( GLfloat floorSize );
void displayWallLine( GLint num, GLfloat floorSize );
void displayWall( void );

#endif
