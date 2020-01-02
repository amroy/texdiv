#include "gl_helper.h" 

namespace glh {

bool GLInit(int w, int h, const char * title_name) {
	int argc = 0;
	char **argv = NULL;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(w, h);      // ���ڳߴ�
	glutInitWindowPosition(100, 100);  // ����λ��
	glutCreateWindow(title_name);   // ���ڱ���

								 // ��ʼ��Ⱦ

								 // ���GLEW�Ƿ����������Ҫ��GLUT��ʼ��֮��
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		printf("Error: '%s'\n", glewGetErrorString(res));
		return false;
	}
	return true;
}

} //namespace glh