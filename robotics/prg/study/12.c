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

//�F�̕ς��ɁC�A�e�t�����v�Z���邽�߂̖@���x�N�g��
GLdouble normal[][3] = {
  { 0.0, 0.0,-1.0 },
  { 1.0, 0.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  {-1.0, 0.0, 0.0 },
  { 0.0,-1.0, 0.0 },
  { 0.0, 1.0, 0.0 }
};

GLfloat light0pos[] = { 0.0, 3.0, 5.0, 1.0 };//0�Ԗڌ���
GLfloat light1pos[] = { 5.0, 3.0, 0.0, 1.0 };//1�Ԗڌ���
GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };//�ΐF
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };//�ԐF
GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };//�F

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

  /* �����̈ʒu�ݒ� */
  glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
  glLightfv(GL_LIGHT1, GL_POSITION, light1pos);

  /* ���f���r���[�ϊ��s��̕ۑ� */
  glPushMatrix();

  /* �}�`�̉�] */
  glRotated((double)r, 0.0, 1.0, 0.0);

  /* �}�`�̐F (��)  */
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);

  /* �}�`�̕`�� */
  cube();

  /* ��ڂ̐}�`�̕`�� */
  glPushMatrix();//���f���r���[�ϊ��s��̕ۑ�
  glTranslated(1.0, 1.0, 1.0);//��Ԗڂ̐}�`�Ƃ��炷
  glRotated((double)(2 * r), 0.0, 1.0, 0.0);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
  cube();
  glPopMatrix();//���f���r���[�ϊ��s��̕��A

   /* ���f���r���[�ϊ��s��̕��A */
  glPopMatrix();

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
  glLoadIdentity();
  gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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

    glEnable(GL_LIGHTING);//�����@�\��L��
    glEnable(GL_LIGHT0);//0�Ԗڌ�����L��
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
