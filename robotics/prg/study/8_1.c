#include <GL/glut.h>

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glRotated(25.0, 0.0, 1.0, 0.0);//��]�ϊ��s��
  glBegin(GL_POLYGON);//�`��^�C�v�C���ӌ`
  glColor3d(1.0, 0.0, 0.0); /* �� */
  glVertex2d(-0.9, -0.9);
  glColor3d(0.0, 1.0, 0.0); /* �� */
  glVertex2d(0.9, -0.9);
  glColor3d(0.0, 0.0, 1.0); /* �� */
  glVertex2d(0.9, 0.9);
  glColor3d(1.0, 1.0, 0.0); /* �� */
  glVertex2d(-0.9, 0.9);
  //���_���ƂɐF���w�肷��
  glEnd();
  glFlush();
}

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
}
int main(int argc, char *argv[])
{
  glutInit(&argc, argv);//���������C������main�̈����̂܂�
  glutInitDisplayMode(GLUT_RGBA);//display�̕\��mode��ݒ肷��D�܂���[GLUT_INDEX]
  glutCreateWindow("���O");//window���J���D������window�̖��O
  glutDisplayFunc(display);//�}�`�\��(�`��)
  init();
  glutMainLoop();//�������[�v�C�C�x���g�҂���
  return 0;
}