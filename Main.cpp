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

Planet Sun(Sun_radius, 0, 1.0f, 0.8f, 0.0f);
Planet Mercury(Mercury_radius, 0.9, 1.0f, 0.0f, 0.0f);
Planet Venus(Venus_radius, 1.2, 0.0f, 0.0f, 1.0f);
Planet Earth(Earth_radius, 1.45, 0.0f, 1.0f, 0.0f);
Planet Mars(Mars_radius, 1.7, 1.0f, 0.5f, 0.0f);
Planet Jupiter(Jupiter_radius, 2.2, 1.0f, 0.7f, 0.2f);
Planet Saturn(Saturn_radius, 2.7, 1.0f, 0.0f, 0.2f);
Planet Neptune(Neptun_radius, 3.2, 0.0f, 0.8f, 1.0f);

void init(void){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void SolarSystem(void) // render function
{
    glClear(GL_COLOR_BUFFER_BIT);
    GLfloat time = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME)) / 1000;
    
    Sun.DrawSun(0.0, 0.0f, 0.0f);
    Mercury.PlanetAnimation(8.8f, time);
    Venus.PlanetAnimation(22.465f, time);
    Earth.PlanetAnimation(36.5, time);
    Mars.PlanetAnimation(68.7, time);
    Jupiter.PlanetAnimation(433, time);
    Saturn.PlanetAnimation(1075.9, time);
    Neptune.PlanetAnimation(6015.2, time);
    glutPostRedisplay();

    glutSwapBuffers();
}

void reshape(int w, int h){
    glMatrixMode(GL_PROJECTION);
    gluPerspective(50.0, w / (GLfloat)h, 3.0, 90.0);
    gluLookAt(2.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("SolarSystem");
    
    init();
    glutDisplayFunc(SolarSystem);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}