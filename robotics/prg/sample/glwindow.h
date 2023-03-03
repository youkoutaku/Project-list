// ******************
// *** glwindow.h ***
// ******************

#ifndef _GL_WINDOW_H_
#define _GL_WINDOW_H_

// window�̃T�C�Y�ƈʒu, �P�ʂ�pixel
#define WINDOW_SIZE_X		450
#define WINDOW_SIZE_Y		400
#define WINDOW_POSITION_X	50
#define WINDOW_POSITION_Y	50

#ifndef X
#define X  0
#endif
#ifndef Y
#define Y  1
#endif
#ifndef Z
#define Z  2
#endif
#ifndef PI
#define PI 3.141592
#endif

#define ESC 27  // ESC key

// ���̂̐F
enum color{ myBLUE, myGREEN, myRED, myYELLOW, myWHITE, myCYAN, myORANGE };

typedef struct
{
	// �E�B���h�E�ϐ�
	int win_root;
	int width;
	int height;
	// ���_���i�ϐ�
	float slideX;
	float slideY;
	float slideZ;
	// ���_����ϐ�
	float rolX ;
	float rolY ;
	float rolZ ;

} GLW;

extern GLW *w;

void setColor( enum color color_name );
void myCylinder( GLUquadricObj *qobj, GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks );
void drawAxis( GLfloat size );
void windowInit( void );
void createWindow( void );
void defineLights( void );
void defineViewMatrix( void );
void onRenderWindow( void );
void displayObject( void );

#endif
