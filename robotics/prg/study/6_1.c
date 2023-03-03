//6.2まで
#include <GL/glut.h>

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
    //ウィンドウを塗りつぶす.
    //GL_COLOR_BUFFER_BIT を指定したときは, カラーバッファだけが塗りつぶされます

    glBegin(GL_LINE_LOOP);
    glColor3d(1.0, 0.0, 0.0);//glColor3dはこれから描画するものの色(double)．また，glColor3f(float),glColor3i(int)
    glVertex2d(-0.9, -0.9);
    glVertex2d(0.9, -0.9);
    glVertex2d(0.9, 0.9);
    glVertex2d(-0.9, 0.9);
    //glVertex2dは二次元の座標値(double)．また，glVertex2f(float),glVertex2i(int)
    glEnd();
    //glBegin()~glEnd()の間に図形の頂点の座標値を設定する．
    //glBegin()の引数modeは，描画する図形のタイプ
    
    glFlush();
    //glFlush()はまだ実行されていない OpenGL の命令を全部実行
    //glFinish()はglFlushの機能に加えて,それがすべて完了するのを待ちます.
}

void resize(int w, int h)
{
  /* ウィンドウ全体をビューポートにする */
  glViewport(0, 0, w, h);

  /* 変換行列の初期化 */
  glLoadIdentity();

  /* スクリーン上の表示領域をビューポートの大きさに比例させる */
  glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0);
}

void init(void)
{
  glClearColor(0.0, 0.0, 1.0, 1.0);//[R,G,B,透明度]0~1
}

int main(int argc, char *argv[])
{
    glutInitWindowPosition(100, 100);//windosを開く初期位置
    glutInitWindowSize(320, 240);//windosを開く初期サイズ
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);//
  init();
  glutMainLoop();
  return 0;
}