#include <GL/glut.h>

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glRotated(25.0, 0.0, 1.0, 0.0);//回転変換行列
  glBegin(GL_POLYGON);//描画タイプ，多辺形
  glColor3d(1.0, 0.0, 0.0); /* 赤 */
  glVertex2d(-0.9, -0.9);
  glColor3d(0.0, 1.0, 0.0); /* 緑 */
  glVertex2d(0.9, -0.9);
  glColor3d(0.0, 0.0, 1.0); /* 青 */
  glVertex2d(0.9, 0.9);
  glColor3d(1.0, 1.0, 0.0); /* 黄 */
  glVertex2d(-0.9, 0.9);
  //頂点ごとに色を指定する
  glEnd();
  glFlush();
}

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
}
int main(int argc, char *argv[])
{
  glutInit(&argc, argv);//環境初期化，引数はmainの引数のまま
  glutInitDisplayMode(GLUT_RGBA);//displayの表示modeを設定する．または[GLUT_INDEX]
  glutCreateWindow("名前");//windowを開く．引数はwindowの名前
  glutDisplayFunc(display);//図形表示(描画)
  init();
  glutMainLoop();//無限ループ，イベント待ち受け
  return 0;
}