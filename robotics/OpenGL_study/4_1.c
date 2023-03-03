//5.3までのテスト
#include <GL/glut.h>

void display(void){
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
void init(void){
    glClearColor(0.0, 0.0, 1.0, 1.0);//[R,G,B,透明度]0~1
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