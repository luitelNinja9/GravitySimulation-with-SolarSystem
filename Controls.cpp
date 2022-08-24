#include "Controls.h"
#include <GL/glew.h>



Button::Button(int x1, int y1, int x2, int y2, GLuint bT, int hv)
{

	xTopLeft = x1;
	yTopLeft = y1;
	xBottomRight = x2;
	yBottomRight = y2;
	onHover = hv;
	buttonTexture = bT;

}

glm::vec2 Button::getCentre()
{
	return glm::vec2(float(xTopLeft + xBottomRight) / 2.0f, float(yTopLeft + yBottomRight) / 2.0f);
}

glm::vec2 Button::getScale()
{
	return glm::vec2(float(xBottomRight - xTopLeft) / 2.0f, float(xTopLeft - xBottomRight) / 2.0f);
}

void Button::setHover()
{
	onHover = 2;
}

void Button::resetHover()
{
	onHover = 0;
}

int Button::getHover()
{
	return onHover;
}

GLuint Button::getBTexture()
{
	return buttonTexture;
}

void Button::setBTexture(GLuint gli)
{
	buttonTexture = gli;
}