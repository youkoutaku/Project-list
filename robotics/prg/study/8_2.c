//10.2

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
  { 0, 1, 2, 3 }, /* A-B-C-D �����Ԗ� */
  { 1, 5, 6, 2 },/* B-F-G-C �����Ԗ� */
  { 5, 4, 7, 6 },/* F-E-H-G �����Ԗ� */
  { 4, 0, 3, 7 },/* E-A-D-H �����Ԗ� */
  { 4, 5, 1, 0 },/* E-F-B-A �����Ԗ� */
  { 3, 2, 6, 7 } /* D-C-G-H �����Ԗ� */
};

GLdouble color[][3] = {
  { 1.0, 0.0, 0.0 },
  { 0.0, 1.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  { 1.0, 1.0, 0.0 },
  { 1.0, 0.0, 1.0 },
  { 0.0, 1.0, 1.0 }
};

void idle(void)
{
  glutPostRedisplay();//�ĕ`��C�x���g�𔭐������܂�
}

void display(void)
{
  int i;
  int j;
  static int r = 0; /* ��]�p */

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�f�v�X�o�b�t�@�̂��߂Ɉ�����ǉ�����

  glLoadIdentity();

  /* ���_�ʒu�Ǝ������� */
  gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  /* �}�`�̉�] */
  glRotated((double)r, 0.0, 1.0, 0.0);

  /* �}�`�̕`�� */
  glColor3d(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  for (j = 0; j < 6; ++j) {
    glColor3dv(color[j]);
    for (i = 0; i < 4; ++i) {
      glVertex3dv(vertex[face[j][i]]);
    }
  }
  glEnd();

  glutSwapBuffers();

  /* �����������]�p�� 0 �ɖ߂� */
  if (++r >= 360) r = 0;
}

void resize(int w, int h)
{
  glViewport(0, 0, w, h);

   /* �����ϊ��s��̐ݒ� */
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);//�����ϊ��s��
  
   /* ���f���r���[�ϊ��s��̐ݒ� */
  glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
  switch (button) {
  case GLUT_LEFT_BUTTON:
    if (state == GLUT_DOWN) {
      /* �A�j���[�V�����J�n */
      glutIdleFunc(idle);
    }
    else {
      /* �A�j���[�V������~ */
      glutIdleFunc(0);
    }
    break;
  case GLUT_RIGHT_BUTTON:
    if (state == GLUT_DOWN) {
      /* �R�}���� (1�X�e�b�v�����i�߂�) */
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
  case '\033':  /* '\033' �� ESC �� ASCII �R�[�h */
    exit(0);
  default:
    break;
  }
}

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST);//�f�v�X�o�b�t�@�̎��s

  glEnable(GL_CULL_FACE);//glCullFace��L���ɂ���
//glCullFace(GL_BACK);//back�ʂ�\�����Ȃ��悤�ɂ���̂ɁC�t�ɂȂ����D
//�ʂ̕\�Ɨ��͒��_�����ǂ鏇�ԂŌ��肷��D
  glCullFace(GL_FRONT);//front�ʂ�\�����Ȃ�
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
