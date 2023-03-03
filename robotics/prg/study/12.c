#include <GL/glut.h>

GLdouble vertex[][3] = {
  { 0.0, 0.0, 0.0 },/*A*/
  { 1.0, 0.0, 0.0 },/*B*/
  { 1.0, 1.0, 0.0 },/*C*/
  { 0.0, 1.0, 0.0 },/*D*/
  { 0.0, 0.0, 1.0 },/*E*/
  { 1.0, 0.0, 1.0 },/*F*/
  { 1.0, 1.0, 1.0 },/*G*/
  { 0.0, 1.0, 1.0 } /*H*/
};

int face[][4] = {
  { 0, 1, 2, 3 }, /* A-B-C-D を結ぶ面 */
  { 1, 5, 6, 2 },/* B-F-G-C を結ぶ面 */
  { 5, 4, 7, 6 },/* F-E-H-G を結ぶ面 */
  { 4, 0, 3, 7 },/* E-A-D-H を結ぶ面 */
  { 4, 5, 1, 0 },/* E-F-B-A を結ぶ面 */
  { 3, 2, 6, 7 } /* D-C-G-H を結ぶ面 */
};

//色の変わりに，陰影付けを計算するための法線ベクトル
GLdouble normal[][3] = {
  { 0.0, 0.0,-1.0 },
  { 1.0, 0.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  {-1.0, 0.0, 0.0 },
  { 0.0,-1.0, 0.0 },
  { 0.0, 1.0, 0.0 }
};

GLfloat light0pos[] = { 0.0, 3.0, 5.0, 1.0 };//0番目光源
GLfloat light1pos[] = { 5.0, 3.0, 0.0, 1.0 };//1番目光源
GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };//緑色
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };//赤色
GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };//青色

void cube(void)
{
  int i;
  int j;

  glBegin(GL_QUADS);
  for (j = 0; j < 6; ++j) {
    glNormal3dv(normal[j]);
    for (i = 0; i < 4; ++i) {
      glVertex3dv(vertex[face[j][i]]);
    }
  }
  glEnd();
}

void idle(void)
{
  glutPostRedisplay();//再描画イベントを発生させます
}

void display(void)
{
  int i;
  int j;
  static int r = 0; /* 回転角 */

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//デプスバッファのために引数を追加する

  glLoadIdentity();

  /* 視点位置と視線方向 */
  gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  /* 光源の位置設定 */
  glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
  glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

  /* モデルビュー変換行列の保存 */
  glPushMatrix();

  /* 図形の回転 */
  glRotated((double)r, 0.0, 1.0, 0.0);

  /* 図形の色 (赤)  */
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);

  /* 図形の描画 */
  cube();

  /* 二つ目の図形の描画 */
  glPushMatrix();//モデルビュー変換行列の保存
  glTranslated(1.0, 1.0, 1.0);//一番目の図形とずらす
  glRotated((double)(2 * r), 0.0, 1.0, 0.0);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
  cube();
  glPopMatrix();//モデルビュー変換行列の復帰

   /* モデルビュー変換行列の復帰 */
  glPopMatrix();

  glutSwapBuffers();

  /* 一周回ったら回転角を 0 に戻す */
  if (++r >= 360) r = 0;
}

void resize(int w, int h)
{
  glViewport(0, 0, w, h);

   /* 透視変換行列の設定 */
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);//透視変換行列
  
   /* モデルビュー変換行列の設定 */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void mouse(int button, int state, int x, int y)
{
  switch (button) {
  case GLUT_LEFT_BUTTON:
    if (state == GLUT_DOWN) {
      /* アニメーション開始 */
      glutIdleFunc(idle);
    }
    else {
      /* アニメーション停止 */
      glutIdleFunc(0);
    }
    break;
  case GLUT_RIGHT_BUTTON:
    if (state == GLUT_DOWN) {
      /* コマ送り (1ステップだけ進める) */
        glutPostRedisplay();
    }
    break;
  default:
    break;
  }
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
  case 'Q':
  case '\033':  /* '\033' は ESC の ASCII コード */
    exit(0);
  default:
    break;
  }
}

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST);//デプスバッファの実行

  glEnable(GL_CULL_FACE);//glCullFaceを有効にする
//glCullFace(GL_BACK);//back面を表示しないようにするのに，逆になった．
//面の表と裏は頂点をたどる順番で決定する．
  glCullFace(GL_FRONT);//front面を表示しない

    glEnable(GL_LIGHTING);//光源機能を有効
    glEnable(GL_LIGHT0);//0番目光源を有効
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
    glLightfv(GL_LIGHT1, GL_SPECULAR, green);
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();
  return 0;
}
