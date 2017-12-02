/**
 * File: World.hpp
 */

#include "World.hpp"

World::World() {
	cube = new Cube("earth.bmp", "draw.bmp", "mandrill.bmp", "moon.bmp", "red.bmp");
	earth = new Sphere("earth.bmp", 201);
	earth->translate(2, 0, 0);
	earth->scale_change(-0.85);
	earth->rotate_mc(-1, 0, 0, 101.5); // make earth right side up
	moon = new Sphere("moon.bmp", 202);
	moon->scale_change(-0.95);
	moon->translate(2.5, 0, 0);
	sun = new Sphere("sun.bmp", 203);
	sun->scale_change(-0.5);
	sunLight = new PointLightSource();
	sunLight->translate(-2, -2, -2); //light sources start out at 2,2,2 by default, put it back at the origin
	myCamera = new Camera();
	lightSource = new PointLightSource();
	curve = NULL;
	totalRotation = 90;
	stepRotation = 1;
	bezCurveRes = 200;
	setWorldState(CP_SELECT);
}

World::~World() {
	delete cube;
	delete sun;
	delete earth;
	delete moon;
	controlPoints.clear();
	delete myCamera;
	delete lightSource;
	delete sunLight;
}

void World::draw_world() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat matAmb[] = { 0.2, .2, .2, 1.0 }; //ambient
	GLfloat matDif[] = { 0.8, .8, 0.8, 1.0 }; //diffuse
	GLfloat matSpec[] = { 0.0, 0.0, 0.0, 1.0 }; //specular
	GLfloat matEm[] = { 0, 0, 0, 1 }; //emission, make the axis always bright
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEm);

	if (ws != CP_SELECT && ws != BEZIER_CURVE_GEN) {
		myCamera->aspect = ((GLfloat) glutGet(GLUT_WINDOW_WIDTH))
				/ (glutGet(GLUT_WINDOW_HEIGHT) == 0 ? 0.01 : glutGet(GLUT_WINDOW_HEIGHT));
		myCamera->setProjectionMatrix();
	}
	if (ws == TEXTURED_CUBE) {
		lightSource->setGLLighting();
		lightSource->draw();
		cube->draw();

	} else if (ws == CP_SELECT || ws == BEZIER_CURVE_GEN) {
		// draw the axis to select on
		glColor3f(1, 1, 1);
		glPointSize(4);
		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex2i(0, -1);
		glVertex2i(0, 1);
		glVertex2i(-1, 0);
		glVertex2i(1, 0);
		glEnd();

		//now draw all the control points
		glColor3f(1, 0, 0);
		glBegin(GL_POINTS);
		for (unsigned i = 0; i < controlPoints.size(); i++) {
			glVertex2f(controlPoints[i]->x, controlPoints[i]->y);
		}
		glEnd();
		glPointSize(1);
		glLineWidth(1);
		if (ws == BEZIER_CURVE_GEN) { // also draw the curve
			curve->draw();
		}
	} else if (ws == ROT_SURFACE_GEN || ws == GL_SHADING || ws == GLSL_SHADING) {
		matEm[0] = 1, matEm[1] = 1, matEm[2] = 1;  //emission, make the axis always bright
		glMaterialfv(GL_FRONT, GL_EMISSION, matEm);
		// draw 3d axis
		glBegin(GL_LINES);
		glLineWidth(3);
		glColor3f(1, 1, 1);
		glVertex3f(-1, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(0, -1, 0);
		glVertex3f(0, 1, 0);
		glVertex3f(0, 0, -1);
		glVertex3f(0, 0, 1);
		glLineWidth(1);
		glEnd();
		if (ws == GLSL_SHADING) {
			//glDisable(GL_LIGHTING);
			glMateriali(GL_FRONT, GL_SHININESS, 100);
			lightSource->setGLLighting();
			lightSource->draw();
			matSpec[0] = .5, matSpec[1] = .5, matSpec[2] = .5;
		}
		if (ws == GL_SHADING) {

			lightSource->on = true;
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			lightSource->setGLLighting();
			lightSource->draw();

		} else {
			glDisable(GL_LIGHTING); // mesh with no lighting
		}

		matEm[0] = 0, matEm[1] = 0, matEm[2] = 0;
		matDif[0] = 0, matDif[1] = 0, matDif[2] = .8;
		matAmb[0] = 0, matAmb[1] = 0, matAmb[2] = .2;
		glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
		glMaterialfv(GL_FRONT, GL_EMISSION, matEm);
		curve->draw();

	} else if (ws == SOLAR_SYSTEM) {
		sunLight->setGLLighting();
		earth->draw();
		moon->draw();
		matEm[0] = .8, matEm[1] = 0.8, matEm[2]=.4;
		glMaterialfv(GL_FRONT, GL_EMISSION, matEm);
		sun->draw();

	}
	GLfloat v[4];
	glGetLightfv(GL_LIGHT0, GL_DIFFUSE, v);
	glFlush();
	glutSwapBuffers();
}

void World::normalizeAll() {
	cube->normalize();
	sun->normalize();
	moon->normalize();
	earth->normalize();
	if (curve != NULL) {
		curve->normalize();
	}
}

void World::setWorldState(WorldState newState) {
	ws = newState;

	// Check if we need to be rendering in 3d or 2d
	if (ws == CP_SELECT || ws == BEZIER_CURVE_GEN) {
		initRenderingMode(2);
	} else {
		initRenderingMode(3);
	}
	int p;
	glGetIntegerv(GL_CURRENT_PROGRAM, &p);
	// check if we need to be using GLSL or not
	if (ws == GLSL_SHADING) {
		glUseProgram(program);
	} else if (p != 0) {
		glUseProgram(0);
	}

	if (ws == CP_SELECT) { //clear the cps and let the user make a new curve
		controlPoints.clear();
		if (curve != NULL){
			delete curve;
			curve = NULL;
		}
	} else if (ws == BEZIER_CURVE_GEN) {
		if (controlPoints.size() >= 2) {
			curve = new BezierCurve(controlPoints, bezCurveRes, totalRotation, stepRotation);
			curve->setDrawingMode(TWO_D);
		} else {
			::MessageBoxA(GetActiveWindow(), "You need to select at least 2 control points!", "Error", MB_OK);
			ws = CP_SELECT;
		}
	} else if (ws == ROT_SURFACE_GEN || ws == GL_SHADING || ws == GLSL_SHADING) {
		glDisable(GL_CULL_FACE);
		if (curve == NULL && controlPoints.size() >= 2) {
			curve = new BezierCurve(controlPoints, bezCurveRes, totalRotation, stepRotation);
		} else if (curve == NULL) {
			::MessageBoxA(GetActiveWindow(), "You need to select at least 2 control points!", "Error", MB_OK);
			ws = CP_SELECT;
		}
		if (ws == ROT_SURFACE_GEN) {
			curve->setDrawingMode(MESH);
		} else if (ws == GL_SHADING) {
			curve->setDrawingMode(GL_SHADE);
		} else if (ws == GLSL_SHADING) {
			curve->setDrawingMode(GLSL_SHADE);
		}
	} else if (ws == SOLAR_SYSTEM) {
		animateSolar();
	}
	glutPostRedisplay(); // calls the draw method
}

WorldState World::getWorldState() {
	return ws;
}
void animateSolarHelper(int pointerToWorld) {
	((World*) pointerToWorld)->animateSolar();
}
void World::animateSolar() {
	static DWORD start, end;
	start = GetTickCount();
	if (ws == SOLAR_SYSTEM) {
		sun->rotate_mc(0, -1, 0, 0.00000000005 * (end - start));
		earth->rotate_mc(.2, .7, 0, 3);
		earth->rotate_origin(0, -1, 0, 0.00000000005 * (end - start));
		moon->rotate_origin(0, -1, 0, 0.00000000005 * (end - start));
		moon->rotate_relative(earth->getMC().mat[0][3], earth->getMC().mat[1][3], earth->getMC().mat[2][3], 0, 1, 0,
				0.0000000003 * (end - start));
		glutPostRedisplay();
		glutTimerFunc(10, animateSolarHelper, (int) this);
	}
	end = GetTickCount();
	glutPostRedisplay();
}

void World::initRenderingMode(int dimensions) {
	if (dimensions == 2) {
		//Clear the matrix stack
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-1, 1, 1, -1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);
	} else if (dimensions == 3) {
		glClearColor(0.0, 0.0, 0.0, 1.0);  // Set display-window color to black
		myCamera->setDefaultCamera();
		myCamera->setProjectionMatrix();

		//init gl hidden surface removal
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		// initialise GL light and shading
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
}
void World::addControlPoint(GLfloat mouseX, GLfloat mouseY) {
	if (controlPoints.size() < 10) { // allowed to select at most 10 control points
		// mouse coordinates will be in frame buffer cs, we need to first convert them to world coordinates
		GLfloat winx = glutGet(GLUT_WINDOW_WIDTH);
		GLfloat winy = glutGet(GLUT_WINDOW_HEIGHT);
		mouseX /= winx / 2;
		mouseY /= winy / 2;
		mouseX -= 1;
		mouseY -= 1;
		controlPoints.push_back(new Point(mouseX, mouseY, 0));
	}
}
void World::setGLSLProgram(GLuint p) {
	program = p;
}
void World::clearCP(){
	controlPoints.clear();
}

void World::remakeCurve(){
	if (curve != NULL){
		delete curve;
		curve = NULL;
	}
	if (controlPoints.size() >= 2){
		setWorldState(ws); // will make a new curve depending on state and render appropriately
	}
}
