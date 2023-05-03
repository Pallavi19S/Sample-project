#include<stdio.h>
#include<GL/glut.h>

int x, y, where_to_rotate = 0;
float translate_x = 0, translate_y = 0, r_angle = 0;

void myInit() {
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-800, 800, -800, 800);
	glMatrixMode(GL_MODELVIEW);
}

void drawPixel(float x, float y) {
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glFlush();
}

void triangle(int x, int y) {
	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + 400, y + 400);
	glVertex2f(x + 300, y + 0);
	glEnd();
	glFlush();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1, 0, 0);
	drawPixel(0, 0);
	if (where_to_rotate == 1) {
		translate_x = 0;
		translate_y = 0;
		r_angle += 0.08;
	}
	if (where_to_rotate == 2) {
		translate_x = x;
		translate_y = y;
		r_angle += 0.08;
		glColor3f(0, 0, 1);
		drawPixel(x, y);
	}
	glTranslatef(translate_x, translate_y, 0);
	glRotatef(r_angle, 0, 0, 1);
	glTranslatef(-translate_x, -translate_y, 0);

	triangle(x, y);

	glutPostRedisplay();
	glutSwapBuffers();
}

void rotate_menu(int option) {
	if (option == 1)
		where_to_rotate = 1;
	if (option == 2)
		where_to_rotate = 2;
	if (option == 3)
		where_to_rotate = 3;
	display();
}

int main(int argc, char** argv) {
	printf("enter fixed point for the rotation (x, y)");
	scanf_s("%d %d", &x, &y);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Rotate Triangle");
	myInit();

	glutDisplayFunc(display);
	glutCreateMenu(rotate_menu);
	glutAddMenuEntry("rotate around origin", 1);
	glutAddMenuEntry("rotate around fixed point", 2);
	glutAddMenuEntry("stop rotation", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}