//6.2�܂�
#include <GL/glut.h>

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
    //�E�B���h�E��h��Ԃ�.
    //GL_COLOR_BUFFER_BIT ���w�肵���Ƃ���, �J���[�o�b�t�@�������h��Ԃ���܂�

    glBegin(GL_LINE_LOOP);
    glColor3d(1.0, 0.0, 0.0);//glColor3d�͂��ꂩ��`�悷����̂̐F(double)�D�܂��CglColor3f(float),glColor3i(int)
    glVertex2d(-0.9, -0.9);
    glVertex2d(0.9, -0.9);
    glVertex2d(0.9, 0.9);
    glVertex2d(-0.9, 0.9);
    //glVertex2d�͓񎟌��̍��W�l(double)�D�܂��CglVertex2f(float),glVertex2i(int)
    glEnd();
    //glBegin()~glEnd()�̊Ԃɐ}�`�̒��_�̍��W�l��ݒ肷��D
    //glBegin()�̈���mode�́C�`�悷��}�`�̃^�C�v
    
    glFlush();
    //glFlush()�͂܂����s����Ă��Ȃ� OpenGL �̖��߂�S�����s
    //glFinish()��glFlush�̋@�\�ɉ�����,���ꂪ���ׂĊ�������̂�҂��܂�.
}

void resize(int w, int h)
{
  /* �E�B���h�E�S�̂��r���[�|�[�g�ɂ��� */
  glViewport(0, 0, w, h);

  /* �ϊ��s��̏����� */
  glLoadIdentity();

  /* �X�N���[����̕\���̈���r���[�|�[�g�̑傫���ɔ�Ⴓ���� */
  glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0);
}

void init(void)
{
  glClearColor(0.0, 0.0, 1.0, 1.0);//[R,G,B,�����x]0~1
}

int main(int argc, char *argv[])
{
    glutInitWindowPosition(100, 100);//windos���J�������ʒu
    glutInitWindowSize(320, 240);//windos���J�������T�C�Y
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);//
  init();
  glutMainLoop();
  return 0;
}