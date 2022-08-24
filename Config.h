#include "Controls.h"
#include "Cube.h"
#include "Sphere.h"
#include "Stars.h"

//Gravity Party Buttons
namespace GPB
{
	extern std::vector<Button> GPButton;
	extern int count;

};


namespace Time
{
	extern float dT;
};

extern std::vector<Star_>stars_;
extern std::vector<Star_>stars_copy;
extern std::vector<Planet_>planets_;
extern std::vector<Planet_>planets_copy;
extern std::vector<Sattelite_>sattelites_;
extern std::vector<Sattelite_>sattelites_copy;




extern Star_ sun_;
//Star sun2 = Star(4, 0.4f, "8k_sun.jpg", glm::vec3(16.0f, 4.0f,4.0f),glm::vec3(0.0f));
//Star sun3 = Star(2, 0.3f, "8k_sun.jpg", glm::vec3(-16.0f, 4.0f,6.0f));




extern Cube myCube;



//window
//int width, height;


//extern double xpos, ypos;

//button
//extern int normalView;
//extern int onHoverView;

//extern GLuint Clickable_button_loc;
//Variable used in display
//extern GLuint  sunTexture, moonTexture, earthTexture, menuButtonTex;
//extern GLuint planetTexture;
//extern GLuint sunBTexture;
//extern GLuint ButtonTex[4];



extern int Clickable_button;


//L

