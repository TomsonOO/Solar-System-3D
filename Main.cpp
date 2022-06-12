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
float lx = 0.0f, lz = -1.0f, ly = 0.5f;// actual vector representing the camera's direction
float x = 0.0f, z = 5.0f, y = 1.5f;// XZY position of the camera
float red = 1.0f, blue = 1.0f, green = 1.0f;
float angle = 0.0f;// angle for rotating triangle

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

	void PlanetAnimation(GLfloat period, GLfloat time){
		GLfloat w = (2.0f * M_PI) / period;
		GLfloat x = orbit * cos(w * time);
		GLfloat y = 0.0f;
		GLfloat z = orbit * sin(w * time);
		DrawPlanet(x, y, z);
	}
	void PlanetAnimationWithMoon(GLfloat period, GLfloat time, Planet Moon, GLfloat moon_period){
		GLfloat w = (2.0f * M_PI) / period;
		GLfloat x_planet = orbit * cos(w * time);
		GLfloat y = 0.0f;
		GLfloat z_planet = orbit * sin(w * time);
		DrawPlanet(x_planet, y, z_planet);

		GLfloat w2 = (2.0f * M_PI) / moon_period;
		GLfloat x_moon = x_planet + Moon.orbit * cos(w2 * time);
		GLfloat z_moon = z_planet + Moon.orbit * sin(w2 * time);
		Moon.DrawPlanet(x_moon, y, z_moon);
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
Planet Moon(0.03, 0.2, 0.7f, 0.7f, 0.7f);

void changeSize(int w, int h){
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);// Use the Projection Matrix
	glLoadIdentity();// Reset Matrix
	glViewport(0, 0, w, h);// Set the viewport to be the entire window
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);// Set the correct perspective.
	glMatrixMode(GL_MODELVIEW);// Get Back to the Modelview
}

void renderScene(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clear Color and Depth Buffers
	GLfloat time = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME)) / 1000;
	// Lighting set up - > needs refactoring
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHT6);
	glEnable(GL_LIGHT7);

	// Set lighting intensity and color
	GLfloat qaAmbientLight[] = { 0.1, 0.1, 0.1, 0.3 };
	GLfloat qaDiffuseLight[] = { 0.35, 0.35, 0.35, 0.2f };
	GLfloat qaSpecularLight[] = { 0.3, 0.3, 0.3, 0.3f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight);
	// Set the light position
	GLfloat qaLightPosition1[] = { 0.9f, 0.0f, 0.0f, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition1);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT2, GL_SPECULAR, qaSpecularLight);
	// Set the light position
	GLfloat qaLightPosition2[] = { -0.9f, 0.9f, 0.0f, 1.0 };
	glLightfv(GL_LIGHT2, GL_POSITION, qaLightPosition2);

	//
	glLightfv(GL_LIGHT3, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT3, GL_SPECULAR, qaSpecularLight);
	// Set the light position
	GLfloat qaLightPosition3[] = { 0.0f, -0.9f, 0.9f, 1.0 };
	glLightfv(GL_LIGHT3, GL_POSITION, qaLightPosition3);

	glLightfv(GL_LIGHT4, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT4, GL_SPECULAR, qaSpecularLight);
	// Set the light position
	GLfloat qaLightPosition4[] = { 0.0f, 0.0f, -1.8f, 1.0 };
	glLightfv(GL_LIGHT4, GL_POSITION, qaLightPosition4);

	glLightfv(GL_LIGHT5, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT5, GL_SPECULAR, qaSpecularLight);
	// Set the light position
	GLfloat qaLightPosition5[] = { 0.0f, -0.9f, 0.9f, 1.0 };
	glLightfv(GL_LIGHT5, GL_POSITION, qaLightPosition5);

	glLightfv(GL_LIGHT6, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT6, GL_SPECULAR, qaSpecularLight);
	// Set the light position
	GLfloat qaLightPosition6[] = { -0.9f, 0.9f, 0.0f, 1.0 };
	glLightfv(GL_LIGHT6, GL_POSITION, qaLightPosition6);

	glLightfv(GL_LIGHT7, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT7, GL_SPECULAR, qaSpecularLight);
	// Set the light position
	GLfloat qaLightPosition7[] = { 1.2f, 0.9f, 0.5f, 1.0 };
	glLightfv(GL_LIGHT7, GL_POSITION, qaLightPosition7);

	
	glLoadIdentity();// Reset transformations
	// Set the camera
	gluLookAt(x, y, z,
		x + lx, y + ly -0.5f, z + lz,
		0.0f, 0.1f, 0.0f);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	Sun.DrawSun(0.0, 0.0f, 0.0f);
	Mercury.PlanetAnimation(8.8f, time);
	Venus.PlanetAnimation(22.465f, time);
	Earth.PlanetAnimationWithMoon(36.5, time, Moon, 1);
	Mars.PlanetAnimation(68.7, time);
	Jupiter.PlanetAnimation(433, time);
	Saturn.PlanetAnimation(1075.9, time);
	Neptune.PlanetAnimation(6015.2, time);
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y){
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy){
	float fraction = 0.75f;
	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.4f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.4f;
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

int main(int argc, char** argv){
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