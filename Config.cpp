#include<vector>
#include "Controls.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include "Sphere.h"
#include<vector>
#include "Stars.h"
#include "Gravity.h"
#include "Cube.h"



//#include "Config.h"




namespace GPB
{
	std::vector<Button> GPButton =
	{ Button(1800, 25, 1850, 75) ,
	Button(1800 - 60, 25, 1850 - 60, 75),
	Button(1800 - 120, 25, 1850 - 120, 75) };
	int count = 3;

};

namespace Control
{
	const float zoomSensitivity = 0.1f;
	const float moveSensitivity = 0.5f;
	float zoomFeature = 1.0f;
};

namespace Time
{
	float dT = 0.005f;
}
// 
// 
//using namespace std;
std::vector<Star_>stars_;
std::vector<Star_>stars_copy;
std::vector<Planet_>planets_;
std::vector<Planet_>planets_copy;
std::vector<Sattelite_>sattelites_;
std::vector<Sattelite_>sattelites_copy;




Star_ sun_ = Star_(3, 0.3f, "8k_sun.jpg", glm::vec3(0.0f, 0.0f, 0.0f));
//Star sun2 = Star(4, 0.4f, "8k_sun.jpg", glm::vec3(16.0f, 4.0f,4.0f),glm::vec3(0.0f));
//Star sun3 = Star(2, 0.3f, "8k_sun.jpg", glm::vec3(-16.0f, 4.0f,6.0f));




Cube myCube = Cube();

//window
//int width, height;


//double xpos, ypos;

//button




//float cameraX, cameraY, cameraZ;




//Variable used in display
//int normalView = 1;
//int onHoverView = 2;
//GLuint sunTexture, moonTexture, earthTexture, menuButtonTex;
//GLuint planetTexture;
//GLuint sunBTexture;
//GLuint ButtonTex[4] = { sunTexture, earthTexture,moonTexture , menuButtonTex };



//int width, height;
int Clickable_button = 1;
