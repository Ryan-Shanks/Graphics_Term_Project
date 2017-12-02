#ifndef CCUBE_H
#define CCUBE_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"
#include "RGBpixmap.h"

class Cube: public Shape {
protected:
	GLfloat vertex[8][3];
	GLint face[6][4];
	GLfloat faceColor[6][3];   // RGB color for each face
	GLfloat cube_face_norm_mc[6][3];  // normal for each face in MC
	void drawNormal(int f);
	void setVerticesNormalsAndColors();
	RGBpixmap textures[6];
	bool useTextures;
public:
	Cube();
	Cube(std::string texture2,std::string texture3,std::string texture4,std::string texture5,std::string texture6);
	void draw_face(int);
	void draw();
};

#endif
