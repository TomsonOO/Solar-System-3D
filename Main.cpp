#define _USE_MATH_DEFINES

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <cmath>
#include <time.h>
#include <cstdio>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 1600
#define START_X 440
#define START_Y 880
#define z 0.0f
#define segment 360

#define Sun_radius 40
#define Earth_radius 9

#define Mercury_radius 4
#define Venus_radius 10
#define Mars_radius 12
#define Jupiter_radius 18
#define Saturn_radius 15
#define Neptun_radius 13


using namespace std;

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

    void DrawOrbit() {

        GLfloat x = START_X;
        GLfloat y = START_Y;

        GLint vertices = segment + 2;
        GLfloat DoublePi = 2.0f * M_PI;

        GLfloat circleX[segment + 2];
        GLfloat circleY[segment + 2];
        GLfloat circleZ[segment + 2];

        for (int i = 0; i < vertices; i++) {
            circleX[i] = x + (orbit * cos(i * DoublePi / segment));
            circleY[i] = y + (orbit * sin(i * DoublePi / segment));
            circleZ[i] = z;
        }

        GLfloat AllCircleVertices[(segment + 2) * 3];

        for (int i = 0; i < vertices; i++) {
            AllCircleVertices[i * 3] = circleX[i];
            AllCircleVertices[(i * 3) + 1] = circleY[i];
            AllCircleVertices[(i * 3) + 2] = circleZ[i];
        }

        glEnableClientState(GL_VERTEX_ARRAY);

        glColor3f(1.0f, 1.0f, 1.0f);

        glVertexPointer(3, GL_FLOAT, 0, AllCircleVertices);
        glDrawArrays(GL_LINE_STRIP, 0, vertices);

        glDisableClientState(GL_VERTEX_ARRAY);
    }

    void DrawPlanet(GLfloat x, GLfloat y) {

        GLint vertices = segment + 2;
        GLfloat DoublePi = 2.0f * M_PI;

        GLfloat circleX[segment + 2];
        GLfloat circleY[segment + 2];
        GLfloat circleZ[segment + 2];

        circleX[0] = x;
        circleY[0] = y;
        circleZ[0] = z;

        for (int i = 1; i < vertices; i++) {
            circleX[i] = x + (radius * cos(i * DoublePi / segment));
            circleY[i] = y + (radius * sin(i * DoublePi / segment));
            circleZ[i] = z;
        }

        GLfloat AllCircleVertices[(segment + 2) * 3];

        for (int i = 0; i < vertices; i++) {
            AllCircleVertices[i * 3] = circleX[i];
            AllCircleVertices[(i * 3) + 1] = circleY[i];
            AllCircleVertices[(i * 3) + 2] = circleZ[i];
        }

        glEnableClientState(GL_VERTEX_ARRAY);

        glColor3f(r, g, b);

        glVertexPointer(3, GL_FLOAT, 0, AllCircleVertices);
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertices);

        glDisableClientState(GL_VERTEX_ARRAY);
    }

    void Next_step_Draw(GLfloat period, GLfloat time)
    {
        GLfloat w = (2.0f * M_PI) / period;
        GLfloat x = START_X + orbit * cos(w * time);
        GLfloat y = START_Y + orbit * sin(w * time);
        DrawPlanet(x, y);
    }

    void DrawOrbitMoon(GLfloat x, GLfloat y) {

        GLint vertices = segment + 2;
        GLfloat DoublePi = 2.0f * M_PI;

        GLfloat circleX[segment + 2];
        GLfloat circleY[segment + 2];
        GLfloat circleZ[segment + 2];

        for (int i = 0; i < vertices; i++) {
            circleX[i] = x + (orbit * cos(i * DoublePi / segment));
            circleY[i] = y + (orbit * sin(i * DoublePi / segment));
            circleZ[i] = z;
        }

        GLfloat AllCircleVertices[(segment + 2) * 3];

        for (int i = 0; i < vertices; i++) {
            AllCircleVertices[i * 3] = circleX[i];
            AllCircleVertices[(i * 3) + 1] = circleY[i];
            AllCircleVertices[(i * 3) + 2] = circleZ[i];
        }

        glEnableClientState(GL_VERTEX_ARRAY);

        glColor3f(1.0f, 1.0f, 1.0f);

        glVertexPointer(3, GL_FLOAT, 0, AllCircleVertices);
        glDrawArrays(GL_LINE_STRIP, 0, vertices);

        glDisableClientState(GL_VERTEX_ARRAY);
    }

    void DrawPlanetMoob(GLfloat x, GLfloat y) {

        GLint vertices = segment + 2;
        GLfloat DoublePi = 2.0f * M_PI;

        GLfloat circleX[segment + 2];
        GLfloat circleY[segment + 2];
        GLfloat circleZ[segment + 2];

        circleX[0] = x;
        circleY[0] = y;
        circleZ[0] = z;

        for (int i = 1; i < vertices; i++) {
            circleX[i] = x + (radius * cos(i * DoublePi / segment));
            circleY[i] = y + (radius * sin(i * DoublePi / segment));
            circleZ[i] = z;
        }

        GLfloat AllCircleVertices[(segment + 2) * 3];

        for (int i = 0; i < vertices; i++) {
            AllCircleVertices[i * 3] = circleX[i];
            AllCircleVertices[(i * 3) + 1] = circleY[i];
            AllCircleVertices[(i * 3) + 2] = circleZ[i];
        }

        glEnableClientState(GL_VERTEX_ARRAY);

        glColor3f(r, g, b);

        glVertexPointer(3, GL_FLOAT, 0, AllCircleVertices);
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertices);

        glDisableClientState(GL_VERTEX_ARRAY);
    }


};

Planet Sun(Sun_radius, 0, 1.0f, 0.8f, 0.0f);
Planet Mercury(Mercury_radius, 60, 1.0f, 0.0f, 0.0f);
Planet Venus(Venus_radius, 100, 0.0f, 0.0f, 1.0f);
Planet Earth(Earth_radius, 130, 0.0f, 1.0f, 0.0f);
Planet Mars(Mars_radius, 160, 1.0f, 0.5f, 0.0f);
Planet Jupiter(Jupiter_radius, 220, 1.0f, 0.7f, 0.2f);
Planet Saturn(Saturn_radius, 260, 1.0f, 0.0f, 0.2f);
Planet Neptune(Neptun_radius, 290, 0.0f, 0.8f, 1.0f);


int main() {

    glfwInit();

    GLFWwindow* window = glfwCreateWindow(1200, 1200, "Uklad sloneczny", NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" <<
            std::endl;
        glfwTerminate();
        return -1;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    //Load GLAD so it configures OpenGL
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, 1200, 1200, 0.0f, 0.0f, 1.0f); // essentially set coordinate system
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Sun.DrawPlanet(440, 880);
        Mercury.DrawOrbit();
        Mercury.DrawPlanet(500, 880);
        Venus.DrawOrbit();
        Venus.DrawPlanet(540, 880);
        Earth.DrawOrbit();
        Earth.DrawPlanet(570, 880);
        Mars.DrawOrbit();
        Mars.DrawPlanet(600, 880);
        Jupiter.DrawOrbit();
        Jupiter.DrawPlanet(660, 880);
        Saturn.DrawOrbit();
        Saturn.DrawPlanet(700, 880);
        Neptune.DrawOrbit();
        Neptune.DrawPlanet(730, 880);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}