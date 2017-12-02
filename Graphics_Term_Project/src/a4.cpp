/**
 *	CP411 Assignment 4, adapted from assignment 3 and originally from A2 template from Dr. Fan
 */
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "InitShader.hpp"

#include "World.hpp"
#include "Camera.hpp"
#include "MenuHandler.hpp"
#include "Sphere.hpp"

void display(void) {
	myWorld->draw_world();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

void mouseAction(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (myWorld->getWorldState() == CP_SELECT) {
			// when clicked, need to capture a point instead
			myWorld->addControlPoint(x, y);
		} else {
			moving = true;
			xBegin = x;
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		moving = 0;
		myWorld->normalizeAll();
	}
}

void mouseMotion(GLint x, GLint y) {
	GLfloat rx, ry, rz, theta;
	if (moving) {
		//model rotations
		theta = (xBegin - x > 0) ? 1 : -1;
		if (coordinate == MODEL && myWorld->getWorldState() == TEXTURED_CUBE) {
			if (type == ROTX || type == ROTY || type == ROTZ) {
				int vert = type - 1;
				// no model transformations on the point source
				rx = myWorld->cube->getMC().mat[0][vert];
				ry = myWorld->cube->getMC().mat[1][vert];
				rz = myWorld->cube->getMC().mat[2][vert];
				myWorld->cube->rotate_mc(rx, ry, rz, theta * 0.5);
			} else if (type == SCALE) {
				myWorld->cube->scale_change(theta * 0.02);
			}

		} else if (coordinate == WORLD && myWorld->getWorldState() == TEXTURED_CUBE) {
			if (type == ROTX || type == ROTY || type == ROTZ) {
				// unit vector for axis of rotation
				rx = type == ROTX;
				ry = type == ROTY;
				rz = type == ROTZ;
				myWorld->cube->rotate_origin(rx, ry, rz, theta * 0.5);
			} else if (type == TX) {
				myWorld->cube->translate(theta * 0.02, 0, 0);
			} else if (type == TY) {
				myWorld->cube->translate(0, theta * 0.02, 0);
			} else if (type == TZ) {
				myWorld->cube->translate(0, 0, theta * 0.02);
			}
		} else if (coordinate == VIEW) {
			if (type == TX) {
				myWorld->myCamera->translate(theta * 0.05, 0, 0);
			} else if (type == TY) {
				myWorld->myCamera->translate(0, theta * 0.05, 0);
			} else if (type == TZ) {
				myWorld->myCamera->translate(0, 0, theta * 0.05);

			} else if (type == ROTX || type == ROTY || type == ROTZ) {
				myWorld->myCamera->rotate(type == ROTX, type == ROTY, type == ROTZ, theta * 0.5);

			} else if (type == CLIP_NEAR) {
				myWorld->myCamera->setViewVolume(myWorld->myCamera->viewAngle, myWorld->myCamera->aspect,
						myWorld->myCamera->nearDist + theta * 0.05, myWorld->myCamera->farDist);
			} else if (type == CLIP_FAR) {
				myWorld->myCamera->setViewVolume(myWorld->myCamera->viewAngle, myWorld->myCamera->aspect,
						myWorld->myCamera->nearDist, myWorld->myCamera->farDist + theta * 0.05);

			} else if (type == VIEW_ANGLE) {
				myWorld->myCamera->setViewVolume(myWorld->myCamera->viewAngle + 0.5 * theta, myWorld->myCamera->aspect,
						myWorld->myCamera->nearDist, myWorld->myCamera->farDist);
			} else if (type == ROTX_UP || type == ROTY_UP || type == ROTZ_UP) {
				myWorld->myCamera->rotateViewUp(type == ROTX_UP, type == ROTY_UP, type == ROTZ_UP, theta * 0.5);
			}
		} else if (coordinate == LIGHT) {
			if (lightOperation == L_ROTX || lightOperation == L_ROTY || lightOperation == L_ROTZ) {
				// unit vector for axis of rotation
				rx = lightOperation == L_ROTX;
				ry = lightOperation == L_ROTY;
				rz = lightOperation == L_ROTZ;
				myWorld->lightSource->rotate_origin(rx, ry, rz, theta * 0.5);
			} else if (lightOperation == L_TX) {
				myWorld->lightSource->translate(theta * 0.02, 0, 0);
			} else if (lightOperation == L_TY) {
				myWorld->lightSource->translate(0, theta * 0.02, 0);
			} else if (lightOperation == L_TZ) {
				myWorld->lightSource->translate(0, 0, theta * 0.02);
			}
			if (lightOperation == L_POINT_INTENSITY) {
				myWorld->lightSource->increment(theta * -0.05, 0, 0);
			} else if (lightOperation == L_POINT_REFLECTION) {
				myWorld->lightSource->increment(0, theta * -0.05, 0);
			} else if (lightOperation == L_AMBIENT_REFLECTION) {
				myWorld->lightSource->increment(0, 0, theta * -0.05);
			}
		}

		glutPostRedisplay();
	}

}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("A4 Ryan Shanks)");
	int i;
	glGetIntegerv(GL_MODELVIEW_STACK_DEPTH, &i);
	myWorld = new World();
	createMenu();

	glewInit();
	GLuint SLProgramObject = InitShader("src/vertexshader.txt", "src/fragmentshader.txt");
	glUseProgram(0); // dont use the shader yet
	myWorld->setGLSLProgram(SLProgramObject);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glutDisplayFunc(display);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseAction);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();



	delete myWorld;
	return 0;
}
