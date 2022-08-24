#include<cmath>
#include<vector>
#include<glm/glm.hpp>

#ifndef CUBE
#define CUBE

class Cube
{
private:

	std::vector<float>vertices;
	std::vector<float>texCoords;
	std::vector<float>texCoordsOrtho;

	//	std::vector<float>normals;

public:
	Cube();
	int getNumIndices();
	std::vector<float> getVertices();
	std::vector<float> getTexCoords();
	std::vector<float> getTexCoordsOrtho();


	//	std::vector<float> getNormals();
};
#endif // !SPHERE

