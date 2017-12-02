#include "Cube.hpp"

void Cube::setVerticesNormalsAndColors() {
	vertex[0][0] = -1, vertex[0][1] = -1, vertex[0][2] = -1;
	vertex[1][0] = -1, vertex[1][1] = 1, vertex[1][2] = -1;
	vertex[2][0] = 1, vertex[2][1] = -1, vertex[2][2] = -1;
	vertex[3][0] = 1, vertex[3][1] = 1, vertex[3][2] = -1;
	vertex[4][0] = -1, vertex[4][1] = -1, vertex[4][2] = 1;
	vertex[5][0] = -1, vertex[5][1] = 1, vertex[5][2] = 1;
	vertex[6][0] = 1, vertex[6][1] = -1, vertex[6][2] = 1;
	vertex[7][0] = 1, vertex[7][1] = 1, vertex[7][2] = 1;

	//which vertices are included in which faces
	face[0][0] = 0, face[0][1] = 1, face[0][2] = 3, face[0][3] = 2;
	face[1][0] = 3, face[1][1] = 7, face[1][2] = 6, face[1][3] = 2;
	face[2][0] = 7, face[2][1] = 5, face[2][2] = 4, face[2][3] = 6;
	face[3][0] = 4, face[3][1] = 5, face[3][2] = 1, face[3][3] = 0;
	face[4][0] = 5, face[4][1] = 7, face[4][2] = 3, face[4][3] = 1;
	face[5][0] = 6, face[5][1] = 4, face[5][2] = 0, face[5][3] = 2;

	//the face colour setting
	faceColor[0][0] = 1.0, faceColor[0][1] = 0.0, faceColor[0][2] = 0.0; // red
	faceColor[1][0] = 0.0, faceColor[1][1] = 1.0, faceColor[1][2] = 0.0; // green
	faceColor[2][0] = 0.0, faceColor[2][1] = 0.0, faceColor[2][2] = 1.0; // blue
	faceColor[3][0] = 1.0, faceColor[3][1] = 1.0, faceColor[3][2] = 0.0; // yellow
	faceColor[4][0] = 1.0, faceColor[4][1] = 0.0, faceColor[4][2] = 1.0; // purple
	faceColor[5][0] = 0.0, faceColor[5][1] = 1.0, faceColor[5][2] = 1.0; // cyan

	// face normal settings
	cube_face_norm_mc[0][0] = 0.0, cube_face_norm_mc[0][1] = 0.0, cube_face_norm_mc[0][2] = -1.0;
	cube_face_norm_mc[1][0] = 1.0, cube_face_norm_mc[1][1] = 0.0, cube_face_norm_mc[1][2] = 0.0;
	cube_face_norm_mc[2][0] = 0.0, cube_face_norm_mc[2][1] = 0.0, cube_face_norm_mc[2][2] = 1.0;
	cube_face_norm_mc[3][0] = -1.0, cube_face_norm_mc[3][1] = 0.0, cube_face_norm_mc[3][2] = 0.0;
	cube_face_norm_mc[4][0] = 0.0, cube_face_norm_mc[4][1] = 1.0, cube_face_norm_mc[4][2] = 0.0;
	cube_face_norm_mc[5][0] = 0.0, cube_face_norm_mc[5][1] = -1.0, cube_face_norm_mc[5][2] = 0.0;
}

Cube::Cube() {
	setVerticesNormalsAndColors();
	useTextures = false;
}
Cube::Cube(std::string texture2, std::string texture3, std::string texture4, std::string texture5,
		std::string texture6) {
	useTextures = true;
	setVerticesNormalsAndColors();
	// now need to load the textures
	textures[0].makeCheckerboard();
	textures[0].setTexture(101);

	textures[1].readBMPFile(texture2);
	textures[1].setTexture(102);

	textures[2].readBMPFile(texture3);
	textures[2].setTexture(103);

	textures[3].readBMPFile(texture4);
	textures[3].setTexture(104);

	textures[4].readBMPFile(texture5);
	textures[4].setTexture(105);

	textures[5].readBMPFile(texture6);
	textures[5].setTexture(106);
}

void Cube::draw_face(int i) {
	if (useTextures) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 100 + i + 1);
		glBegin(GL_QUADS);
		glNormal3fv(&cube_face_norm_mc[i][0]);
		glTexCoord2f(0, 0);
		glVertex3fv(&vertex[face[i][0]][0]);
		glTexCoord2f(1, 0);
		glVertex3fv(&vertex[face[i][1]][0]);
		glTexCoord2f(1, 1);
		glVertex3fv(&vertex[face[i][2]][0]);
		glTexCoord2f(0, 1);
		glVertex3fv(&vertex[face[i][3]][0]);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	} else {
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glNormal3fv(&cube_face_norm_mc[i][0]);
		glVertex3fv(&vertex[face[i][0]][0]);
		glVertex3fv(&vertex[face[i][1]][0]);
		glVertex3fv(&vertex[face[i][2]][0]);
		glVertex3fv(&vertex[face[i][3]][0]);
		glEnd();
	}

}

void Cube::drawNormal(int f) {
	//draw the normal for the current face in the center of the face
	GLfloat center[] = { 0, 0, 0 };
	for (int i = 0; i < 4; i++) {
		center[0] += vertex[face[f][i]][0];
		center[1] += vertex[face[f][i]][1];
		center[2] += vertex[face[f][i]][2];
	}
	center[0] /= 4;
	center[1] /= 4;
	center[2] /= 4;
	glBegin(GL_LINES);
	glVertex3fv(center);
	glVertex3f(center[0] + cube_face_norm_mc[f][0], center[1] + cube_face_norm_mc[f][1],
			center[2] + cube_face_norm_mc[f][2]);
	glEnd();
}

void Cube::draw() {
	glPushMatrix();
	this->ctm_multiply();
	glScalef(s, s, s);
	for (int i = 0; i < 6; i++) {
		draw_face(i);
		//drawNormal(i);
	}
	glPopMatrix();
}

