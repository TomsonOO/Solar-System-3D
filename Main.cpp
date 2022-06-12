#define _USE_MATH_DEFINES

#define GL_SILENCE_DEPRECATION

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <time.h>
#include <cstdio>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define segment 360
#define Sun_radius 0.4
#define Earth_radius 0.12
#define Mercury_radius 0.08
#define Venus_radius 0.11
#define Mars_radius 0.1
#define Jupiter_radius 0.25
#define Saturn_radius 0.2
#define Neptun_radius 0.18
#define alpha 1.0f

using namespace std;

void timer(int);

float lx = 0.0f, lz = -1.0f;// actual vector representing the camera's direction
float x = 0.0f, z = 5.0f;// XZ position of the camera
float y = 1.5f;
float ly = 0.5f;
float red = 1.0f, blue = 1.0f, green = 1.0f;

float angle = 0.0f;

class Planet {
public:
	GLfloat radius, orbit, speed, r, g, b;
	Planet(GLfloat Radius, GLfloat Orbit, GLfloat R, GLfloat G, GLfloat B) {
		radius = Radius;
		orbit = Orbit;
		r = R;
		g = G;
		b = B;
	}

	void DrawSun(GLfloat x, GLfloat y, GLfloat z) {

		glEnable(GL_COLOR_TABLE);

		glColor4f(r, g, b, alpha);

		glPushMatrix();
		glTranslatef(x, y, z);
		glutSolidSphere(radius, 30, 36);
		glPopMatrix();

		glDisable(GL_COLOR_TABLE);
	}

	void DrawPlanet(GLfloat x, GLfloat y, GLfloat z) {

		GLfloat DoublePi = 2.0f * M_PI;

		GLfloat circleXYZ[3];
		circleXYZ[0] = 0;
		circleXYZ[1] = 0;
		circleXYZ[2] = 0;


		glBegin(GL_LINES); // orbit drawing
		for (float i = 0.0f; i < DoublePi; i += 0.01) {
			float x1 = circleXYZ[0] + (cos(i) * orbit);
			float y1 = circleXYZ[1];
			float z1 = circleXYZ[2] + (sin(i) * orbit);
			glColor4f(1.0, 1.0, 1.0, alpha);
			glVertex3f(x1, y1, z1);
		}
		glEnd();

		glEnable(GL_COLOR_TABLE);

		glColor4f(r, g, b, alpha);
		glPushMatrix();
		glTranslatef(x, y, z);
		glutSolidSphere(radius, 30, 36);
		glPopMatrix();

		glDisable(GL_COLOR_TABLE);
	}

	void PlanetAnimation(GLfloat period, GLfloat time) {
		GLfloat w = (2.0f * M_PI) / period;
		GLfloat x = orbit * cos(w * time);
		GLfloat y = 0.0f;
		GLfloat z = orbit * sin(w * time);
		DrawPlanet(x, y, z);
	}

};
Planet Sun(Sun_radius, 0, 0.98f, 0.84f, 0.11f);
Planet Mercury(Mercury_radius, 0.9, 1.0f, 0.0f, 0.0f);
Planet Venus(Venus_radius, 1.2, 0.0f, 0.0f, 1.0f);
Planet Earth(Earth_radius, 1.45, 0.0f, 1.0f, 0.0f);
Planet Mars(Mars_radius, 1.7, 1.0f, 0.5f, 0.0f);
Planet Jupiter(Jupiter_radius, 2.2, 1.0f, 0.7f, 0.2f);
Planet Saturn(Saturn_radius, 2.7, 1.0f, 0.0f, 0.2f);
Planet Neptune(Neptun_radius, 3.2, 0.0f, 0.8f, 1.0f);

void changeSize(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION); // Use the Projection Matrix
	glLoadIdentity();	// Reset Matrix
	glViewport(0, 0, w, h);	// Set the viewport to be the entire window
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);	// Set the correct perspective.
	glMatrixMode(GL_MODELVIEW);	// Get Back to the Modelview
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear Color and Depth Buffers
	GLfloat time = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME)) / 1000;

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, y, z,
		x + lx, y + ly - 0.5f, z + lz,
		0.0f, 0.1f, 0.0f);

	Sun.DrawSun(0.0, 0.0f, 0.0f);
	Mercury.PlanetAnimation(8.8f, time);
	Venus.PlanetAnimation(22.465f, time);
	Earth.PlanetAnimation(36.5, time);
	Mars.PlanetAnimation(68.7, time);
	Jupiter.PlanetAnimation(433, time);
	Saturn.PlanetAnimation(1075.9, time);
	Neptune.PlanetAnimation(6015.2, time);
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {
	// camera movement settings
	float fraction = 0.4f;
	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.1f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.1f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	case GLUT_KEY_PAGE_UP:
		y += ly * fraction;
		break;
	case GLUT_KEY_PAGE_DOWN:
		y -= ly * fraction;
		break;
	}
}

int main(int argc, char** argv) {
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 800);
	glutCreateWindow("Solar System");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}