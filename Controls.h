#include<glm/glm.hpp>
#include <GL/glew.h>


#include <vector>

#ifndef CONTROLS
#define CONTROLS


class Button
{
private:
	int xTopLeft;
	int yTopLeft;
	int xBottomRight;
	int yBottomRight;
	int onHover;
	GLuint buttonTexture;
	//float scaleX;
	//float scaleY;
public:
	Button(int x1, int y1, int x2, int y2, GLuint bT = 0, int hv = 1);
	glm::vec2 getCentre();
	glm::vec2 getScale();
	void setHover();
	void resetHover();
	int getHover();
	GLuint getBTexture();
	void setBTexture(GLuint);
};



#endif