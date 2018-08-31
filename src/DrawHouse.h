//
// Created by erick on 8/22/18.
//

#ifndef LAB01_DRAWHOUSE_H
#define LAB01_DRAWHOUSE_H

#include <GL/glew.h>
#include <Mesh.h>
#include <math.h>
#include "DrawCircle.h"

void get_roof_mesh(){
	Mesh roof;
	
	Vertex vertices[] = {
		Vertex(glm::vec3(-5.0f,5.0f,-4.0f));
		Vertex(glm::vec3(-6.0f,2.5f,-5.0f));
		Vertex(glm::vec3(6.0f,2.5f,-5.0f));
		Vertex(glm::vec3(5.0f,5.0f,-4.0f));
		Vertex(glm::vec3(5.0f,5.0f,4.0f));
		Vertex(glm::vec3(6.0f, 2.5f, -5.0f));
		Vertex(glm::vec3(-2.0f,5.0f,));
		Vertex(glm::vec3(-2.0f,7.0f));
		Vertex(glm::vec3(-4.0f,7.0f));
	};

       
}

void get_main_body_mesh(){

    //Color
    glColor3f(0.988, 0.956, 0.611);

    //Non-looping line
    glBegin(GL_QUADS);
        glVertex2f(-5.0f,2.5f);
        glVertex2f(-5.0f,-4.0f);
        glVertex2f(5.0f,-4.0f);
        glVertex2f(5.0f,2.5f);
    glEnd();

    //Draw to screen
    glFlush();
}

void DrawDoor(){

    //Color
    glColor3f(1.0, 0.4, 1.0);

    glBegin(GL_QUADS);
        glVertex2f(1.5f,1.0f);
        glVertex2f(1.5f,-4.0f);
        glVertex2f(3.5f,-4.0f);
        glVertex2f(3.5f,1.0f);
    glEnd();

    //Doornob
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(4.0f);
    glBegin(GL_POINTS);
        glVertex2f(2.9f,-2.0f);
    glEnd();

    //Draw to screen
    glFlush();
}

void DrawWindow(){

    //Color
    glColor3f(1.0, 0.4, 0.6);

    //Non-looping line
    glBegin(GL_QUADS);
        glVertex2f(-3.5f,1.5f);
        glVertex2f(-3.5f,-1.5f);
        glVertex2f(-1.5f,-1.5f);
        glVertex2f(-1.5f,1.5f);
    glEnd();

    //Window frame
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(4.0f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-2.5f,1.5f);
        glVertex2f(-2.5f,-1.5f);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(4.0f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-3.5f,0.0f);
        glVertex2f(-1.5f,0.0f);
    glEnd();


    //Draw to screen
    glFlush();
}

void DrawSun(){
    //Color
    glColor3f(0.937, 0.870, 0.164);

    //line width
    glLineWidth(2000.0f);

    //Non-looping line
    glBegin(GL_POLYGON);
    glMaterialfv(GL_EMISSION,)
    for (int i=0; i < 360; i++) {
        float theta = i * 3.1415926f/180.0f; //get the current angle

        float x = 3 * cosf(theta);//calculate the x component
        float y = 3 * sinf(theta);//calculate the y component

        glVertex2f(x + -10.0f, y + 10.0f);//output vertex
    }
    glEnd();

    //Color
//    glColor3f(1.0, 0.4, 0.6);

    //Non-looping line
//    glBegin(GL_LINE_STRIP);
//    for (int i=0; i < 10; i++) {
//        float theta = i * 3.1415926f/180.0f; //get the current angle
//
//        float x = 10 * cosf(theta);//calculate the x component
//        float y = 10 * sinf(theta);//calculate the y component
//
//        glVertex2f(x + -10.0f, y + 10.0f);//output vertex
//    }
//    glEnd();


    //Draw to screen
    glFlush();
}


#endif //LAB01_DRAWHOUSE_H
