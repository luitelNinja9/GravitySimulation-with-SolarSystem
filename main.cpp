
//####Solar System and Gravity Simulation####//
//Step 0 : Include files and Definitions
#include <cmath>
#include<cstdlib>
#include <time.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include "Utils.h"
#include "Sphere.h"
#include<stack>
#include<iostream>
#include<vector>
#include "Stars.h"
#include "ImportedModel.h"
#include "Torus.h"
#include "Config.h"
#include "Gravity.h"





float all_velocity = 1.0f;

Torus myTorus_ring(0.5f, 0.145f, 48);

float zoomFeature = 1;
float zoomSensitivity = 0.1f;
float moveSensitivity = 0.1f;
float rotationSensitivity = 0.01f;
float delta = 0.00f;
glm::mat4 Rotation = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 1, 0));
glm::mat4 Rotation_drop = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0, 1, 0));

float dis = 0.0f;

//
std::vector<Star>stars;
std::vector<Planet>planets;


Star sun = Star(6, 0.3f, "8k_sun.jpg", glm::vec3(0.0f, 0.0f, 0.0f));
ImportedModel spaceShip("models/spaceShip.obj");
ImportedModel sat("models/sattelite.obj");
ImportedModel sat1("models/Satellite.obj");
//ImportedModel sat("Satellite.obj");

vector<Sattelite> dummy = { Sattelite(0,0,0,0,0) };
vector<Sattelite> moons = { Sattelite(2,3.0f,0.8f,0.7f,2.0f) };



const float fac = 2;

Planet mercury = Planet(3, 1.2f, 5.0f, 4.0f, 0.8f * all_velocity, dummy);
Planet venus = Planet(4.5, 1.3f, 6.7f, 6.0f, 0.7f * all_velocity, dummy);
Planet earth = Planet(5, 1.4f, 8.5f, 8.0f, 0.6f * all_velocity, moons, 1);
Planet mars = Planet(4, 1.5f, 10.2f, 10.0f, 0.5f * all_velocity, dummy);
Planet jupyter = Planet(10, 1.5f, 12.5f, 12.0f, 0.4f * all_velocity, dummy);
Planet saturn = Planet(8, 1.5f, 14.9f, 14.5f, 0.3f * all_velocity, dummy);
Planet uranus = Planet(7, 1.6f, 17.9f, 17.8f, 0.2f * all_velocity, dummy);
Planet neptune = Planet(6, 1.7f, 22.4f, 22.0f, 0.1f * all_velocity, dummy);

int screenSizeX, screenSizeY;
GLuint shadowTex, shadowBuffer;
glm::mat4 lightVmatrix;
glm::mat4 lightPmatrix;
glm::mat4 shadowMVP1;
glm::mat4 shadowMVP2;
glm::mat4 b;



GLuint planet_textures[8];
GLuint planet_textures_normal[8];


void installLights(glm::mat4 vMatrix);


#define numVAOs 1
#define numVBOs 21
//using namespace std;



//window
//int width, height;

//int addStar_;

double xpos, ypos;

//button
int normalView = 1;
int onHoverView = 2;



float cameraX, cameraY, cameraZ;
Sphere mySphere(200);

int renderingProgram, backgroundProgram;
//GLuint renderingProgramUI;


GLuint vao[numVAOs];
GLuint vbo[numVBOs];

//Variable used in display
GLuint mvLoc, projLoc, vLoc, sunTexture, moonTexture,earthTexture, earthNormalTexture, menuButtonTex, skyBackgroundTexture, spaceShipTexture,satelliteTexture,satelliteTexture1,saturnRingTexture;
GLuint planetTexture;

int width, height;
int button = 0;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat, tMat, rMat, oMat;
//L
glm::mat4 invTrMat;
glm::vec3 currentLightPos, lightPosV;

//L
//Location for shader uniform variable
GLuint globalAmbLoc, ambLoc, diffLoc, specLoc, posLoc, mAmbLoc, mDiffLoc, mSpecLoc, mShiLoc, buttonLoc,disLoc,Clickable_button_loc;
glm::vec3 initialLightLoc = glm::vec3(0.0f, 0.0f, 0.0f);
float lightPos[3];
//L
//sun light properties
float globalAmbient[4] = { 0.8f,0.8f,0.8f,1.0f };
float lightAmbient[4] = { 0.1f,0.1f,0.1f,1.0f };
float lightDiffuse[4] = { 0.6f,0.4f,0.4f,1.0f };
float lightSpecular[4] = { 0.6f,0.4f,0.4f,1.0f };

//Earth material Property

float previous, now, radius, dt;



//Called from init
void setupVertices(void)
{
	std::vector<float>cubeVertices = myCube.getVertices();
	std::vector<float>cubeTexCoords = myCube.getTexCoordsOrtho();
	int cubeNumIndices = myCube.getNumIndices();



	//Uncomment For Adding sample Button
	float cubePositions[108] =
	{
		 -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
		 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		 -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f,
		 -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,
		 -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f,
		  1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, -1.0f
	};


	float cubeTextureCoord[72] = {
			 1.00f, 0.66f, 1.00f, 0.33f, 0.75f, 0.33f,
			 // back face lower right
			0.75f, 0.33f, 0.75f, 0.66f, 1.00f, 0.66f,
			// back face upper left
			0.75f, 0.33f, 0.50f, 0.33f, 0.75f, 0.66f,
			// right face lower right
			0.50f, 0.33f, 0.50f, 0.66f, 0.75f, 0.66f,
			// right face upper left
			0.50f, 0.33f, 0.25f, 0.33f, 0.50f, 0.66f,
			// front face lower right
			0.25f, 0.33f, 0.25f, 0.66f, 0.50f, 0.66f,
			// front face upper left
			0.25f, 0.33f, 0.00f, 0.33f, 0.25f, 0.66f,
			// left face lower right
			 0.00f, 0.33f, 0.00f, 0.66f, 0.25f, 0.66f,
			 // left face upper left
			 0.25f, 0.33f, 0.50f, 0.33f, 0.50f, 0.00f,
			 // bottom face upper right
			 0.50f, 0.00f, 0.25f, 0.00f, 0.25f, 0.33f,
			 // bottom face lower left
			0.25f, 1.00f, 0.50f, 1.00f, 0.50f, 0.66f,
			// top face upper right
			0.50f, 0.66f, 0.25f, 0.66f, 0.25f, 1.00f
	  // top face lower left
	};
	///*
		float menuButton[72] =
		{
			//0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
			//1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,
			0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,
			1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,

			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,


			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,
		};

		//*/

	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);



	
		std::vector<int> ind_ring = myTorus_ring.getIndices();
		std::vector<glm::vec3> vert_ring = myTorus_ring.getVertices();
		std::vector<glm::vec2> text_ring = myTorus_ring.getTexCoords();
		std::vector<glm::vec3> norm_ring = myTorus_ring.getNormals();
		std::vector<float> pvalues_ring;
		std::vector<float> tvalues_ring;
		std::vector<float> nvalues_ring;
		int numVertices = myTorus_ring.getNumVertices();
		for (int i = 0; i < numVertices; i++) {
			pvalues_ring.push_back(vert_ring[i].x);
			pvalues_ring.push_back(vert_ring[i].y);
			pvalues_ring.push_back(vert_ring[i].z);
			tvalues_ring.push_back(text_ring[i].s);
			tvalues_ring.push_back(text_ring[i].t);
			nvalues_ring.push_back(norm_ring[i].x);
			nvalues_ring.push_back(norm_ring[i].y);
			nvalues_ring.push_back(norm_ring[i].z);
		}

		// generate VBOs as before, plus one for indices
		glBindBuffer(GL_ARRAY_BUFFER, vbo[9]);
		// vertex positions
		glBufferData(GL_ARRAY_BUFFER, pvalues_ring.size() * 4, &pvalues_ring[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[10]);
		// texture coordinates
		glBufferData(GL_ARRAY_BUFFER, tvalues_ring.size() * 4, &tvalues_ring[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[11]);
		// normal vectors
		glBufferData(GL_ARRAY_BUFFER, nvalues_ring.size() * 4, &nvalues_ring[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[12]); // indices
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_ring.size() * 4, &ind_ring[0], GL_STATIC_DRAW);
	


	std::vector<int> ind = mySphere.getIndices();
	std::vector<glm::vec3> vert = mySphere.getVertices();
	std::vector<glm::vec2> tex = mySphere.getTexCoords();
	std::vector<glm::vec3> norm = mySphere.getNormals();
	std::vector<glm::vec3> tans = mySphere.getTangents();


	//SpaceShip
	std::vector<glm::vec3> vert1 = spaceShip.getVertices();
	std::vector<glm::vec2> tex1 = spaceShip.getTextureCoords();
	std::vector<glm::vec3> norm1 = spaceShip.getNormals();
	
	//Satellite
	std::vector<glm::vec3> vert2 = sat.getVertices();
	std::vector<glm::vec2> tex2 = sat.getTextureCoords();
	std::vector<glm::vec3> norm2 = sat.getNormals();

	std::vector<glm::vec3> vert3 = sat1.getVertices();
	std::vector<glm::vec2> tex3 = sat1.getTextureCoords();
	std::vector<glm::vec3> norm3 = sat1.getNormals();



	std::vector<float>pvalues;
	std::vector<float>tvalues;
	std::vector<float>nvalues;
	std::vector<float>tanvalues;

	//SpaceShip
	std::vector<float>pvalues2;
	std::vector<float>tvalues2;
	std::vector<float>nvalues2;

	//Sats
	std::vector<float>pvalues1;
	std::vector<float>tvalues1;
	std::vector<float>nvalues1;

	std::vector<float>pvalues3;
	std::vector<float>tvalues3;
	std::vector<float>nvalues3;

	int numIndices = mySphere.getNumIndices();
	int numIndices1 = spaceShip.getNumVertices();
	int numIndices2 = sat.getNumVertices();
	int numIndices3 = sat1.getNumVertices();

	for (int i = 0; i < numIndices; i++)
	{
		pvalues.push_back((vert[ind[i]]).x);
		pvalues.push_back((vert[ind[i]]).y);
		pvalues.push_back((vert[ind[i]]).z);

		tvalues.push_back((tex[ind[i]]).s);
		tvalues.push_back((tex[ind[i]]).t);

		nvalues.push_back((norm[ind[i]]).x);
		nvalues.push_back((norm[ind[i]]).y);
		nvalues.push_back((norm[ind[i]]).z);

		tanvalues.push_back((tans[ind[i]]).x);
		tanvalues.push_back((tans[ind[i]]).y);
		tanvalues.push_back((tans[ind[i]]).z);
	}

	for (int i = 0; i < numIndices1; i++)
	{
		pvalues1.push_back((vert1[i]).x);
		pvalues1.push_back((vert1[i]).y);
		pvalues1.push_back((vert1[i]).z);

		tvalues1.push_back((tex1[i]).s);
		tvalues1.push_back((tex1[i]).t);

		nvalues1.push_back((norm1[i]).x);
		nvalues1.push_back((norm1[i]).y);
		nvalues1.push_back((norm1[i]).z);
	}


		for (int i = 0; i < numIndices2; i++)
	{
		pvalues2.push_back((vert2[i]).x);
		pvalues2.push_back((vert2[i]).y);
		pvalues2.push_back((vert2[i]).z);

		tvalues2.push_back((tex2[i]).s);
		tvalues2.push_back((tex2[i]).t);

		nvalues2.push_back((norm2[i]).x);
		nvalues2.push_back((norm2[i]).y);
		nvalues2.push_back((norm2[i]).z);
	}
		
		for (int i = 0; i < numIndices3; i++)
	{
		pvalues3.push_back((vert3[i]).x);
		pvalues3.push_back((vert3[i]).y);
		pvalues3.push_back((vert3[i]).z);

		tvalues3.push_back((tex3[i]).s);
		tvalues3.push_back((tex3[i]).t);

		nvalues3.push_back((norm3[i]).x);
		nvalues3.push_back((norm3[i]).y);
		nvalues3.push_back((norm3[i]).z);
	}


	




	//Sphere vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, pvalues.size() * 4, &pvalues[0], GL_STATIC_DRAW);

	//tex Coordinates
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, tvalues.size() * 4, &tvalues[0], GL_STATIC_DRAW);

	//normal
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, nvalues.size() * 4, &nvalues[0], GL_STATIC_DRAW);


	//Uncomment for sample Button
	//cube
	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubePositions), cubePositions, GL_STATIC_DRAW);

	//cube Texture
	glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeTextureCoord), cubeTextureCoord, GL_STATIC_DRAW);


	//SpaceShip vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
	glBufferData(GL_ARRAY_BUFFER, pvalues1.size() * 4, &pvalues1[0], GL_STATIC_DRAW);

	//tex Coordinates
	glBindBuffer(GL_ARRAY_BUFFER, vbo[6]);
	glBufferData(GL_ARRAY_BUFFER, tvalues1.size() * 4, &tvalues1[0], GL_STATIC_DRAW);

	//normal
	glBindBuffer(GL_ARRAY_BUFFER, vbo[7]);
	glBufferData(GL_ARRAY_BUFFER, nvalues1.size() * 4, &nvalues1[0], GL_STATIC_DRAW);

	//Sat vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo[13]);
	glBufferData(GL_ARRAY_BUFFER, pvalues2.size() * 4, &pvalues2[0], GL_STATIC_DRAW);

	//tex Coordinates
	glBindBuffer(GL_ARRAY_BUFFER, vbo[14]);
	glBufferData(GL_ARRAY_BUFFER, tvalues2.size() * 4, &tvalues2[0], GL_STATIC_DRAW);

	//normal
	glBindBuffer(GL_ARRAY_BUFFER, vbo[15]);
	glBufferData(GL_ARRAY_BUFFER, nvalues2.size() * 4, &nvalues2[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[16]);
	glBufferData(GL_ARRAY_BUFFER, pvalues3.size() * 4, &pvalues3[0], GL_STATIC_DRAW);

	//tex Coordinates
	glBindBuffer(GL_ARRAY_BUFFER, vbo[17]);
	glBufferData(GL_ARRAY_BUFFER, tvalues3.size() * 4, &tvalues3[0], GL_STATIC_DRAW);

	//normal
	glBindBuffer(GL_ARRAY_BUFFER, vbo[18]);
	glBufferData(GL_ARRAY_BUFFER, nvalues3.size() * 4, &nvalues3[0], GL_STATIC_DRAW);

	//Sphere tangent
	glBindBuffer(GL_ARRAY_BUFFER, vbo[8]);
	glBufferData(GL_ARRAY_BUFFER, tanvalues.size() * 4, &tanvalues[0], GL_STATIC_DRAW);



	//Cube For Button
	glBindBuffer(GL_ARRAY_BUFFER, vbo[19]);
	glBufferData(GL_ARRAY_BUFFER, cubeVertices.size() * 4, &cubeVertices[0], GL_STATIC_DRAW);


	//glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(menuButton) , menuButton, GL_STATIC_DRAW);
	//cube Texture
	glBindBuffer(GL_ARRAY_BUFFER, vbo[20]);
	glBufferData(GL_ARRAY_BUFFER, cubeTexCoords.size() * 4, &cubeTexCoords[0], GL_STATIC_DRAW);
}

void setupShadowBuffers(GLFWwindow* window) {
	glfwGetFramebufferSize(window, &width, &height);
	screenSizeX = width;
	screenSizeY = height;
	// create the custom frame buffer
	glGenFramebuffers(1, &shadowBuffer);
	// create the shadow texture and configure it to hold depth information.
	// these steps are similar to those in Program 5.2
	glGenTextures(1, &shadowTex);
	glBindTexture(GL_TEXTURE_2D, shadowTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32,
		screenSizeX, screenSizeY, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE,
		GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
}


//Step 4 : Init(Definition)  :: Application Specific initialization
//Buffers are created in init or at start of the program
//In OpenGL buffer is contained in Vertex Buffer Object(VBO)
//VAOs are vertex array objects helping to manipulate buffers in complex scenes
//OpenGL requires atleast one VAO to be created
//Create matrices that donot change in init:perspective matrix
void init(GLFWwindow* window)
{
	//Create thr program and save it in a global variable
	renderingProgram = createShaderProgram("shaders/vert_phong.glsl", "shaders/frag_phong.glsl");
	backgroundProgram = createShaderProgram("shaders/vertShaderBackground.glsl", "shaders/fragShaderBackground.glsl");

	//renderingProgramUI = createShaderProgram("shaders/vertShaderB.glsl", "shaders/fragShaderB.glsl");
	cameraX = 0.0f; cameraY = -0.5f; cameraZ = 8.0f;
	setupVertices();

	sunTexture = loadTexture("textures/8k_sun.jpg");
	moonTexture = loadTexture("textures/8k_moon.jpg");
	earthTexture = loadTexture("textures/2k_earth_daymap.jpg");
	earthNormalTexture = loadTexture("textures/8k_earth_normal_map.tif");

	planet_textures[0] = loadTexture("textures/2k_mercury.jpg");
	planet_textures[1] = loadTexture("textures/2k_venus_atmosphere.jpg");
	planet_textures[2] = loadTexture("textures/2k_earth_daymap.jpg");
	planet_textures[3] = loadTexture("textures/2k_mars.jpg");
	planet_textures[4] = loadTexture("textures/2k_jupiter.jpg");
	planet_textures[5] = loadTexture("textures/2k_saturn.jpg");
	planet_textures[6] = loadTexture("textures/2k_uranus.jpg");
	planet_textures[7] = loadTexture("textures/2k_neptune.jpg");

	planet_textures_normal[0] = loadTexture("textures/2k_mercury_normal.jpg");
	planet_textures_normal[1] = loadTexture("textures/2k_venus_atmosphere_normal.jpg");
	planet_textures_normal[2] = loadTexture("textures/2k_earth_daymap_normal.jpg");
	planet_textures_normal[3] = loadTexture("textures/2k_mars_normal.jpg");
	planet_textures_normal[4] = loadTexture("textures/2k_jupiter_normal.jpg");
	planet_textures_normal[5] = loadTexture("textures/2k_saturn_normal.jpg");
	planet_textures_normal[6] = loadTexture("textures/2k_uranus_normal.jpg");
	planet_textures_normal[7] = loadTexture("textures/2k_neptune_normal.jpg");

	//skyBackgroundTexture = loadCubeMap("textures/2k_stars_milky_way");
	skyBackgroundTexture = loadTexture("textures/8k_stars_milky_way.jpg");
	// folder containing the skybox textures
	//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	spaceShipTexture = loadTexture("textures/spstob_1.bmp");
	saturnRingTexture = loadTexture("textures/8k_saturn_ring_alpha.png");
	satelliteTexture1 = loadTexture("textures/satellite_Sat�lite_BaseColor.jpg");
	satelliteTexture = loadTexture("textures/sattelite.jpg");
	//satelliteTexture1 = loadTexture("textures/satellite_Sat�lite_BaseColor.jpg");



	//planetTexture = loadTexture("2k_earth_daymap.jpg");
	menuButtonTex = loadTexture("textures/2k_neptune_normal.jpg");


	GPB::GPButton[0].setBTexture(moonTexture);
	GPB::GPButton[1].setBTexture(earthTexture);
	GPB::GPButton[2].setBTexture(sunTexture);



	//Stars to draw
	stars.push_back(sun);

	//Planets to draw
	planets.push_back(mercury);
	planets.push_back(venus);
	planets.push_back(earth);
	planets.push_back(mars);
	planets.push_back(jupyter);
	planets.push_back(saturn);
	planets.push_back(uranus);
	planets.push_back(neptune);
	setupShadowBuffers(window);
	b = glm::mat4(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f);

}




void display(GLFWwindow* window, double currentTime)
{

	//Clear also the depth buffer , Place color in the color buffer, Clear the buffer and Place "clear color" in the buffer
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	//Send data from OpenGl application to uniform variable
//1.Acquire a reference to  uniform variable


	glUseProgram(backgroundProgram);
	mvLoc = glGetUniformLocation(backgroundProgram, "mv_matrix");
	projLoc = glGetUniformLocation(backgroundProgram, "proj_matrix");


	//
	vMat = Rotation * glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cameraX, cameraY, cameraZ));
	// build the MODEL-VIEW matrix
	mvMat = vMat * mMat;

	glfwGetFramebufferSize(window, &width, &height);
	aspect = float(width) / float(height);
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);//1.0472f = 60 degrees

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));


	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);



	// make the cube map the active texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, skyBackgroundTexture);
	// disable depth testing, and then draw the cube map
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);


	glDisable(GL_DEPTH_TEST);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glEnable(GL_DEPTH_TEST);



	glUseProgram(renderingProgram);

	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	GLuint nLoc = glGetUniformLocation(renderingProgram, "norm_matrix");


	oMat = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(oMat));

	for (int i = 0; i < GPB::count; ++i)
	{
		vMat = glm::translate(glm::mat4(1.0f), glm::vec3(GPB::GPButton[i].getCentre().x, 1080.0f - GPB::GPButton[i].getCentre().y, 0.0f));
		vMat *= glm::scale(glm::mat4(1.0f), glm::vec3(GPB::GPButton[i].getScale().x, GPB::GPButton[i].getScale().y, 1.0f));


		invTrMat = glm::transpose(glm::inverse(vMat));

		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(vMat));
		//L
		glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

		dis = 6.0f;
		buttonLoc = glGetUniformLocation(renderingProgram, "distance");
		glProgramUniform1f(renderingProgram, buttonLoc, dis);

		//Buttons
		glBindBuffer(GL_ARRAY_BUFFER, vbo[19]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[20]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		//Menu Button
		glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, menuButtonTex);
		glBindTexture(GL_TEXTURE_2D, GPB::GPButton[i].getBTexture());

		Clickable_button = GPB::GPButton[i].getHover();

		Clickable_button_loc = glGetUniformLocation(renderingProgram, "cbutton");
		glProgramUniform1i(renderingProgram, Clickable_button_loc, Clickable_button);


		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, planetTexture);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDrawArrays(GL_TRIANGLES, 0, myCube.getNumIndices());
	}



	Clickable_button = 0;
	//buttonLoc = glGetUniformLocation(renderingProgram, "button");
	glProgramUniform1i(renderingProgram, Clickable_button_loc, Clickable_button);





	stars_copy = stars_;
	planets_copy = planets_;
	sattelites_copy = sattelites_;
	calculateMotionParameters(stars_, stars_copy, planets_, planets_copy, sattelites_, sattelites_copy);
	calculateMotionParameters(planets_, planets_copy, stars_, stars_copy, sattelites_, sattelites_copy);
	calculateMotionParameters(sattelites_, sattelites_copy, stars_, stars_copy, planets_, planets_copy);
	
	//Build view,model and model-view matrix
	//vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));


	//L
	//Light Position
	vMat = Rotation * glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	currentLightPos = glm::vec3(initialLightLoc.x, initialLightLoc.y, initialLightLoc.z);
	installLights(vMat);

	
	buttonLoc = glGetUniformLocation(renderingProgram, "distance");
	glProgramUniform1f(renderingProgram, buttonLoc, dis);

	button = 1;
	disLoc = glGetUniformLocation(renderingProgram, "button");
	glProgramUniform1f(renderingProgram, disLoc, button);

	glfwGetFramebufferSize(window, &width, &height);
	aspect = float(width) / float(height);
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);//1.0472f = 60 degrees
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));




	for (int i = 0; i < stars_.size(); i++)
	{//The sun

		stars_[i].stackVariable.push(vMat);
		stars_[i].stackVariable.push(stars_[i].stackVariable.top());
		stars_[i].stackVariable.top() *= glm::translate(glm::mat4(1.0f), stars_[i].positionVec() * zoomFeature);
		stars_[i].stackVariable.push(stars_[i].stackVariable.top());
		stars_[i].stackVariable.top() *= glm::rotate(glm::mat4(1.0f), float(currentTime) * stars_[i].getAngularSpeed(), glm::vec3(0.0f, 1.0f, 0.0f));
		//mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(zoomFeature*2.0f, zoomFeature * 2.0f, zoomFeature * 2.0f));
		stars_[i].stackVariable.top() *= glm::scale(glm::mat4(1.0f), stars_[i].scaleVec() * zoomFeature);

		//L
		invTrMat = glm::transpose(glm::inverse(stars_[i].stackVariable.top()));
		glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(stars_[i].stackVariable.top()));

		dis = 4.3f;
		buttonLoc = glGetUniformLocation(renderingProgram, "distance");
		glProgramUniform1f(renderingProgram, buttonLoc, dis);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		//L
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);


		glBindBuffer(GL_ARRAY_BUFFER, vbo[8]);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(3);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sunTexture);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndices());
		//glBindTexture(GL_TEXTURE_2D, 0);
		stars_[i].stackVariable.pop();
		//}
	}

	for (int i = 0; i < sattelites_.size(); i++)
	{//The sun

		sattelites_[i].stackVariable.push(vMat);
		sattelites_[i].stackVariable.push(sattelites_[i].stackVariable.top());
		sattelites_[i].stackVariable.top() *= glm::translate(glm::mat4(1.0f), sattelites_[i].positionVec() * zoomFeature);
		sattelites_[i].stackVariable.push(sattelites_[i].stackVariable.top());
		sattelites_[i].stackVariable.top() *= glm::rotate(glm::mat4(1.0f), float(currentTime) * sattelites_[i].getAngularSpeed(), glm::vec3(0.0f, 1.0f, 0.0f));
		//mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(zoomFeature*2.0f, zoomFeature * 2.0f, zoomFeature * 2.0f));
		sattelites_[i].stackVariable.top() *= glm::scale(glm::mat4(1.0f), sattelites_[i].scaleVec() * zoomFeature);

		//L
		invTrMat = glm::transpose(glm::inverse(sattelites_[i].stackVariable.top()));
		glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

		dis = 4.3f;
		buttonLoc = glGetUniformLocation(renderingProgram, "distance");
		glProgramUniform1f(renderingProgram, buttonLoc, dis);

		//Uncomment to see the lower surface
		//mvStack.top() *= glm::rotate(glm::mat4(1.0f), -0.3f, glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(sattelites_[i].stackVariable.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		//L
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, moonTexture);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndices());
		//glBindTexture(GL_TEXTURE_2D, 0);
		sattelites_[i].stackVariable.pop();
		//}
	}

	for (int i = 0; i < planets_.size(); i++)
	{//The Earth

		planets_[i].stackVariable.push(vMat);
		planets_[i].stackVariable.push(planets_[i].stackVariable.top());
		planets_[i].stackVariable.top() *= glm::translate(glm::mat4(1.0f), planets_[i].positionVec() * zoomFeature);
		planets_[i].stackVariable.push(planets_[i].stackVariable.top());
		planets_[i].stackVariable.top() *= glm::rotate(glm::mat4(1.0f), float(currentTime) * planets_[i].getAngularSpeed(), glm::vec3(0.0f, 1.0f, 0.0f));
		//mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(zoomFeature*2.0f, zoomFeature * 2.0f, zoomFeature * 2.0f));
		planets_[i].stackVariable.top() *= glm::scale(glm::mat4(1.0f), planets_[i].scaleVec() * zoomFeature);

		//L
		invTrMat = glm::transpose(glm::inverse(planets_[i].stackVariable.top()));
		glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

		dis = 4.3f;
		buttonLoc = glGetUniformLocation(renderingProgram, "distance");
		glProgramUniform1f(renderingProgram, buttonLoc, dis);
		//Uncomment to see the lower surface
		//mvStack.top() *= glm::rotate(glm::mat4(1.0f), -0.3f, glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(planets_[i].stackVariable.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		//L
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, earthTexture);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndices());
		//glBindTexture(GL_TEXTURE_2D, 0);
		planets_[i].stackVariable.pop();
		//}
	}

	for (int i = 0; i < stars_.size(); ++i)
	{
		stars_[i].stackVariable.pop();
		stars_[i].stackVariable.pop();
	}



	button = normalView;
	glProgramUniform1i(renderingProgram, buttonLoc, button);


	// The solar System
	for (int i = 0; i < stars.size(); i++)
	{//The sun

		stars[i].stackVariable.push(vMat);
		stars[i].stackVariable.push(stars[i].stackVariable.top());
		stars[i].stackVariable.top() *= glm::translate(glm::mat4(1.0f), stars[i].positionVec() * zoomFeature);
		stars[i].stackVariable.push(stars[i].stackVariable.top());
		stars[i].stackVariable.top() *= glm::rotate(glm::mat4(1.0f), float(currentTime) * stars[i].getAngularSpeed(), glm::vec3(0.0f, 1.0f, 0.0f));
		//mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(zoomFeature*2.0f, zoomFeature * 2.0f, zoomFeature * 2.0f));
		stars[i].stackVariable.top() *= glm::scale(glm::mat4(1.0f), stars[i].scaleVec() * zoomFeature);

		//L
		invTrMat = glm::transpose(glm::inverse(stars[i].stackVariable.top()));
		glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

		dis = 4.3f;
		buttonLoc = glGetUniformLocation(renderingProgram, "distance");
		glProgramUniform1f(renderingProgram, buttonLoc, dis);
		//Uncomment to see the lower surface
		//mvStack.top() *= glm::rotate(glm::mat4(1.0f), -0.3f, glm::vec3(1.0f, 0.0f, 0.0f));


		glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(stars[i].stackVariable.top()));
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		//L
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[8]);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(3);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sunTexture);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndices());
		//glBindTexture(GL_TEXTURE_2D, 0);
		stars[i].stackVariable.pop();

		//}
	}



	//Planets
	float r = 0.9f;

	///*
	for (int i = 0; i < planets.size() + 1; ++i)
	{
		if (i == planets.size())
		{
			///*
			stars[0].stackVariable.push(stars[0].stackVariable.top());
			stars[0].stackVariable.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin(float(currentTime) * 0.2) * 2.0f * 15.0f * zoomFeature,
				0.0f, cos(float(currentTime) * 0.2) * 2.0f * 15.0f * zoomFeature));
			stars[0].stackVariable.push(stars[0].stackVariable.top());
			stars[0].stackVariable.top() *= glm::rotate(glm::mat4(1.0f), float(currentTime) * 0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
			stars[0].stackVariable.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(zoomFeature * 0.5, zoomFeature * 0.5, zoomFeature * 0.5));

			//L
			//invTrMat = glm::transpose(glm::inverse(stars[0].stackVariable.top()));

			glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(stars[0].stackVariable.top()));
			//L
			//glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

			dis = 15.0f;
			buttonLoc = glGetUniformLocation(renderingProgram, "distance");
			glProgramUniform1f(renderingProgram, buttonLoc, dis);


			glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, vbo[6]);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, spaceShipTexture);

			glEnable(GL_CULL_FACE);
			glFrontFace(GL_CCW);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);


			//*/
			
		}
		else
		{
			stars[0].stackVariable.push(stars[0].stackVariable.top());
			stars[0].stackVariable.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin(float(i)+float(currentTime) * planets[i].getRevolutionSpeed()) * 2.0f * planets[i].getDistance1() * zoomFeature,
				0.0f, cos(float(i)+float(currentTime) * planets[i].getRevolutionSpeed()) * 2.0f * planets[i].getDistance2() * zoomFeature));
			stars[0].stackVariable.push(stars[0].stackVariable.top());
			stars[0].stackVariable.top() *= glm::rotate(glm::mat4(1.0f), float(currentTime) * planets[i].getAngularSpeed(), glm::vec3(0.0f, 1.0f, 0.0f));
			stars[0].stackVariable.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(zoomFeature * planets[i].getScale(), zoomFeature * planets[i].getScale(), zoomFeature * planets[i].getScale()));

			//L
			invTrMat = glm::transpose(glm::inverse(stars[0].stackVariable.top()));

			glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(stars[0].stackVariable.top()));
			//L
			glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));


			dis = planets[i].getDistance1();
			buttonLoc = glGetUniformLocation(renderingProgram, "distance");
			glProgramUniform1f(renderingProgram, buttonLoc, dis);

			button = 1;
			disLoc = glGetUniformLocation(renderingProgram, "button");
			glProgramUniform1f(renderingProgram, disLoc, button);

			glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);

			//L
			glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(2);


			glBindBuffer(GL_ARRAY_BUFFER, vbo[8]);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(3);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, planet_textures[i]);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, planet_textures_normal[i]);


			glEnable(GL_CULL_FACE);
			glFrontFace(GL_CCW);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);

			glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndices());


			///*
			if (i == 5)
			{
				stars[0].stackVariable.pop();
				stars[0].stackVariable.push(stars[0].stackVariable.top());
				stars[0].stackVariable.top() *= glm::rotate(glm::mat4(1.0f), float(sin(0.3f*currentTime))*0.6f, glm::vec3(0.0f, 1.0f, 0.0f));
				stars[0].stackVariable.top() *= glm::rotate(glm::mat4(1.0f), float(sin(0.3f*currentTime))*0.6f, glm::vec3(0.0f, 0.0f, 1.0f));
				stars[0].stackVariable.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(zoomFeature * 3.0f, zoomFeature * 0.5f, zoomFeature *2.7f));


				invTrMat = glm::transpose(glm::inverse(stars[0].stackVariable.top()));
				glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

				button = 0;
				disLoc = glGetUniformLocation(renderingProgram, "button");
				glProgramUniform1f(renderingProgram, disLoc, button);

				dis = planets[i].getDistance1();
				buttonLoc = glGetUniformLocation(renderingProgram, "distance");
				glProgramUniform1f(renderingProgram, buttonLoc, dis);


				glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(stars[0].stackVariable.top()));
				//glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
				glBindBuffer(GL_ARRAY_BUFFER, vbo[9]);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, vbo[10]);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(1);

				glBindBuffer(GL_ARRAY_BUFFER, vbo[11]);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(2);


				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, saturnRingTexture);

				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LEQUAL);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[12]);
				glDrawElements(GL_TRIANGLES, myTorus_ring.getNumIndices(), GL_UNSIGNED_INT, 0);
			}

			//*/




			///*
			if (planets[i].withSattelite())
			{
				stars[0].stackVariable.pop();
				stars[0].stackVariable.push(stars[0].stackVariable.top());
				//stars[0].stackVariable.push(stars[0].stackVariable.top());
				//stars[0].stackVariable.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin(float(currentTime) * 2.0f) * 0.5f * zoomFeature, 0.5f * zoomFeature, cos(float(currentTime) * 2.0f) * 0.5f * zoomFeature));
				//stars[0].stackVariable.top() *= glm::rotate(glm::mat4(1.0f), float(currentTime) * 2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
				//stars[0].stackVariable.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(zoomFeature * 0.05f, zoomFeature * 0.05f, zoomFeature * 0.05f));

				stars[0].stackVariable.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin(float(currentTime) * planets[i].sats[0].getRevolutionSpeed()) * 2.0f * planets[i].sats[0].getDistance1() * zoomFeature,
					0.3f * zoomFeature, cos(float(currentTime) * planets[i].sats[0].getRevolutionSpeed()) * 2.0f * planets[i].sats[0].getDistance2() * zoomFeature));
				//stars[0].stackVariable.push(stars[0].stackVariable.top());
				stars[0].stackVariable.top() *= glm::rotate(glm::mat4(1.0f), float(currentTime) * planets[i].sats[0].getAngularSpeed(), glm::vec3(0.0f, 1.0f, 0.0f));
				stars[0].stackVariable.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(zoomFeature * planets[i].sats[0].getScale(), zoomFeature * planets[i].sats[0].getScale(), zoomFeature * planets[i].sats[0].getScale()));


				button = 1;
				disLoc = glGetUniformLocation(renderingProgram, "button");
				glProgramUniform1f(renderingProgram, disLoc, button);


				dis = planets[i].getDistance1();
				buttonLoc = glGetUniformLocation(renderingProgram, "distance");
				glProgramUniform1f(renderingProgram, buttonLoc, dis);

				invTrMat = glm::transpose(glm::inverse(stars[0].stackVariable.top()));
				glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

				glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(stars[0].stackVariable.top()));
				glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(1);



				//L
				glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(2);

				glBindBuffer(GL_ARRAY_BUFFER, vbo[8]);
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(3);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, moonTexture);

				glEnable(GL_CULL_FACE);
				glFrontFace(GL_CCW);
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LEQUAL);

				glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndices());

				stars[0].stackVariable.pop();
				stars[0].stackVariable.push(stars[0].stackVariable.top());
				stars[0].stackVariable.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin(float(currentTime) * 1.4f) * 2.0f * 0.4f * zoomFeature,
					0.25f * zoomFeature, cos(float(currentTime) * 1.4f) * 2.0f * 0.4f * zoomFeature));
				//stars[0].stackVariable.push(stars[0].stackVariable.top());
				stars[0].stackVariable.top() *= glm::rotate(glm::mat4(1.0f), float(currentTime) * 1.4f, glm::vec3(0.0f, 1.0f, 0.0f));
				stars[0].stackVariable.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(zoomFeature * 0.2, zoomFeature * 0.2, zoomFeature * 0.2));


				button = 0;
				disLoc = glGetUniformLocation(renderingProgram, "button");
				glProgramUniform1f(renderingProgram, disLoc, button);
				//L
				invTrMat = glm::transpose(glm::inverse(stars[0].stackVariable.top()));

				glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(stars[0].stackVariable.top()));
				//L
				glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));


				glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, vbo[6]);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(1);

				glBindBuffer(GL_ARRAY_BUFFER, vbo[7]);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(2);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, spaceShipTexture);

				glEnable(GL_CULL_FACE);
				glFrontFace(GL_CCW);
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LEQUAL);

				glDrawArrays(GL_TRIANGLES, 0, spaceShip.getNumVertices());
				//glBindTexture(GL_TEXTURE_2D, 0);

				stars[0].stackVariable.pop();
				stars[0].stackVariable.push(stars[0].stackVariable.top());
				//stars[0].stackVariable.push(stars[0].stackVariable.top());
				stars[0].stackVariable.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin(1.5f+float(currentTime) * 1.4f) * 2.0f * 0.4f * zoomFeature,
					0.25f * zoomFeature, cos(1.5f+float(currentTime) * 1.4f) * 2.0f * 0.4f * zoomFeature));
				//stars[0].stackVariable.push(stars[0].stackVariable.top());
				stars[0].stackVariable.top() *= glm::rotate(glm::mat4(1.0f), float(currentTime) * 1.4f, glm::vec3(0.0f, 1.0f, 0.0f));
				stars[0].stackVariable.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(zoomFeature * 0.0001, zoomFeature * 0.0001, zoomFeature * 0.0001));


				button = 0;
				disLoc = glGetUniformLocation(renderingProgram, "button");
				glProgramUniform1f(renderingProgram, disLoc, button);
				//L
				invTrMat = glm::transpose(glm::inverse(stars[0].stackVariable.top()));

				glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(stars[0].stackVariable.top()));
				//L
				glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));


				glBindBuffer(GL_ARRAY_BUFFER, vbo[13]);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, vbo[14]);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(1);

				glBindBuffer(GL_ARRAY_BUFFER, vbo[15]);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(2);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, satelliteTexture);

				glEnable(GL_CULL_FACE);
				glFrontFace(GL_CCW);
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LEQUAL);

				glDrawArrays(GL_TRIANGLES, 0, sat.getNumVertices());	
				
				stars[0].stackVariable.pop();
				//stars[0].stackVariable.push(stars[0].stackVariable.top());
				//stars[0].stackVariable.push(stars[0].stackVariable.top());
				stars[0].stackVariable.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin(3.0f+float(currentTime) * 1.4f) * 2.0f * 0.4f * zoomFeature,
					0.25f * zoomFeature, cos(3.0f+float(currentTime) * 1.4f) * 2.0f * 0.4f * zoomFeature));
				//stars[0].stackVariable.push(stars[0].stackVariable.top());
				stars[0].stackVariable.top() *= glm::rotate(glm::mat4(1.0f), float(currentTime) * 1.4f, glm::vec3(0.0f, 1.0f, 0.0f));
				stars[0].stackVariable.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(zoomFeature * 0.04, zoomFeature * 0.04, zoomFeature * 0.04));


				//L
				invTrMat = glm::transpose(glm::inverse(stars[0].stackVariable.top()));

				glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(stars[0].stackVariable.top()));
				//L
				glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));


				glBindBuffer(GL_ARRAY_BUFFER, vbo[16]);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, vbo[17]);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(1);

				glBindBuffer(GL_ARRAY_BUFFER, vbo[18]);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(2);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, satelliteTexture1);

				glEnable(GL_CULL_FACE);
				glFrontFace(GL_CCW);
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LEQUAL);

				glDrawArrays(GL_TRIANGLES, 0, sat1.getNumVertices());
				//glBindTexture(GL_TEXTURE_2D, 0);

			}
		}



		stars[0].stackVariable.pop();
		stars[0].stackVariable.pop();




	}


	for (int i = 1; i < stars.size(); ++i)
	{
		stars[i].stackVariable.pop();
		stars[i].stackVariable.pop();
	}



	Clickable_button = normalView;
	glProgramUniform1i(renderingProgram, Clickable_button_loc, Clickable_button);


}


void installLights(glm::mat4 vMatrix)
{
	lightPosV = glm::vec3(vMatrix * glm::vec4(currentLightPos, 1.0));
	lightPos[0] = lightPosV.x;
	lightPos[1] = lightPosV.y;
	lightPos[2] = lightPosV.z;

	//get Location
	// get the locations of the light and material fields in the shader
	globalAmbLoc = glGetUniformLocation(renderingProgram, "globalAmbient");
	ambLoc = glGetUniformLocation(renderingProgram, "light.ambient");
	diffLoc = glGetUniformLocation(renderingProgram, "light.diffuse");
	specLoc = glGetUniformLocation(renderingProgram, "light.specular");
	posLoc = glGetUniformLocation(renderingProgram, "light.position");

	// set the uniform light and material values in the shader
	glProgramUniform4fv(renderingProgram, globalAmbLoc, 1, globalAmbient);
	glProgramUniform4fv(renderingProgram, ambLoc, 1, lightAmbient);
	glProgramUniform4fv(renderingProgram, diffLoc, 1, lightDiffuse);
	glProgramUniform4fv(renderingProgram, specLoc, 1, lightSpecular);
	glProgramUniform3fv(renderingProgram, posLoc, 1, lightPos);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (yoffset > 0)
	{
		zoomFeature += zoomSensitivity;
	}
	else if (yoffset < 0)
	{
		zoomFeature -= zoomSensitivity;
	}

}
int a = 0;
double time_;
void key_callback2(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_O && (action == GLFW_PRESS))
	{
		a = 1;
		glfwSetTime(time_);
	}
	if (key == GLFW_KEY_E && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		delta += rotationSensitivity;

		Rotation = (glm::rotate(glm::mat4(1.0f), delta, glm::vec3(0, 1, 0)));
		Rotation_drop = (glm::rotate(glm::mat4(1.0f), -delta, glm::vec3(0, 1, 0)));
	}
	if (key == GLFW_KEY_Z && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		delta += rotationSensitivity;

		Rotation = (glm::rotate(glm::mat4(1.0f), delta, glm::vec3(1, 0, 0)));

	}

	if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS)) cameraY += moveSensitivity;



	if (key == GLFW_KEY_Q && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		//cameraY -= moveSensitivity;
		delta -= rotationSensitivity;
		Rotation = (glm::rotate(glm::mat4(1.0f), delta, glm::vec3(0, 1, 0)));
		Rotation_drop = (glm::rotate(glm::mat4(1.0f), -delta, glm::vec3(0, 1, 0)));
	}

	if (key == GLFW_KEY_C && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		//cameraY -= moveSensitivity;
		delta -= rotationSensitivity;
		Rotation = (glm::rotate(glm::mat4(1.0f), delta, glm::vec3(1, 0, 0)));

	}

	if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS)) cameraY -= moveSensitivity;
	if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		cameraZ += moveSensitivity * sin(delta);
		cameraX += moveSensitivity * cos(delta);
	}
	if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		cameraZ -= moveSensitivity * sin(delta);
		cameraX -= moveSensitivity * cos(delta);
	}
	if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		cameraX += moveSensitivity * cos(delta - (3.1415 / 2));
		cameraZ += moveSensitivity * sin(delta - (3.1415 / 2));
	}
	if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		cameraX -= moveSensitivity * cos(delta - (3.1415 / 2));
		cameraZ -= moveSensitivity * sin(delta - (3.1415 / 2));
	}
	display(window,time_);
	glfwSwapBuffers(window);
	
}



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (key == GLFW_KEY_P && (action == GLFW_PRESS))
	{
		while (true)
		{
			//cout << "Hello";
			glfwPollEvents();
			glfwSetKeyCallback(window, key_callback2);
			if (a == 1)
			{
				break;
			}
			//break;
		}
		a = 0;
	}

	if (key == GLFW_KEY_E && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		delta += rotationSensitivity;

		Rotation = (glm::rotate(glm::mat4(1.0f), delta, glm::vec3(0, 1, 0)));
		Rotation_drop = (glm::rotate(glm::mat4(1.0f), -delta, glm::vec3(0, 1, 0)));
	}
		if (key == GLFW_KEY_Z && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		delta += rotationSensitivity;

		Rotation = (glm::rotate(glm::mat4(1.0f), delta, glm::vec3(1, 0, 0)));
		
	}

	if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS)) cameraY += 5.0f*moveSensitivity;
	if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS)) cameraX -= 5.0f*moveSensitivity;
	if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS)) cameraX += 5.0f*moveSensitivity;



	if (key == GLFW_KEY_Q && (action == GLFW_REPEAT || action == GLFW_PRESS)) 
	{
		//cameraY -= moveSensitivity;
		delta -= rotationSensitivity;
		Rotation = (glm::rotate(glm::mat4(1.0f), delta, glm::vec3(0, 1, 0)));
		Rotation_drop = (glm::rotate(glm::mat4(1.0f), -delta, glm::vec3(0, 1, 0)));
	}

	if (key == GLFW_KEY_C && (action == GLFW_REPEAT || action == GLFW_PRESS)) 
	{
		//cameraY -= moveSensitivity;
		delta -= rotationSensitivity;
		Rotation = (glm::rotate(glm::mat4(1.0f), delta, glm::vec3(1, 0, 0)));
		
	}

	if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS)) cameraY -= 5.0f*moveSensitivity;
	if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		cameraZ += 5.0f*moveSensitivity * sin(delta);
		cameraX += 5.0f*moveSensitivity * cos(delta);
	}
	if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		cameraZ -= 5.0f*moveSensitivity * sin(delta);
		cameraX -= 5.0f*moveSensitivity * cos(delta);
	}
	if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		cameraX += 5.0f* moveSensitivity * cos(delta - (3.1415 / 2));
		cameraZ += 5.0f * moveSensitivity * sin(delta - (3.1415 / 2));
	}
	if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS))
	{
		cameraX -= 5.0f * moveSensitivity * cos(delta - (3.1415 / 2));
		cameraZ -= 5.0f * moveSensitivity * sin(delta - (3.1415 / 2));
	}
}


//srand(time(0));


void addStar()
{
	//stars_.push_back(Star_(5.5, 0.1f, "8k_sun.jpg", glm::vec4(cameraX, cameraY + 0.5, cameraZ - 8.0,1.0f), (Rotation * glm::vec4(0.0f, 0.0f, -(rand()%13),1.0f))));
	glm::vec3 temp_vec = Rotation_drop * glm::vec4(0.0f, 0.5f, -8.0f, 1.0f);
	//stars_.push_back(Star_(5.5, 0.1f, "8k_sun.jpg", glm::vec4(cameraX, cameraY , cameraZ,1.0f), (-glm::rotate(glm::mat4(1.0f),(0.5f*3.14159f + 2*delta),glm::vec3(0.0,1.0,0.0))*Rotation * glm::vec4(0.0f, 0.0f, (-rand()%13),1.0f))));
	stars_.push_back(Star_(5.5, 0.1f, "8k_sun.jpg", glm::translate(glm::mat4(1.0f), temp_vec)*glm::vec4(cameraX,cameraY,cameraZ,1.0f), (Rotation_drop*glm::vec4(0.0f, 0.0f, (-rand()%13),1.0f))));
}
void addPlanet()
{
	glm::vec3 temp_vec = Rotation_drop * glm::vec4(0.0f, 0.5f, -8.0f, 1.0f);
	planets_.push_back(Planet_(6, 0.3f, "2k_earth_daymap.jpg", glm::translate(glm::mat4(1.0f), temp_vec) * glm::vec4(cameraX, cameraY, cameraZ, 1.0f), (Rotation_drop * glm::vec4(0.0f, 0.0f, (-rand() % 13), 1.0f))));
}
void addSattelite()
{
	glm::vec3 temp_vec = Rotation_drop * glm::vec4(0.0f, 0.5f, -8.0f, 1.0f);
	sattelites_.push_back(Sattelite_(4, 0.6f, "8k_moon.jpg", glm::translate(glm::mat4(1.0f), temp_vec) * glm::vec4(cameraX, cameraY, cameraZ, 1.0f), (Rotation_drop * glm::vec4(0.0f, 0.0f, (-rand() % 13), 1.0f))));
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	
	if ((xpos >= 1800 && xpos <= 1850) && (ypos >= 25 && ypos <= 75))
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) addSattelite();
	}
	//else GPB::GPButton[0].resetHover();
	if ((xpos >= (1760) && xpos <= (1790)) && (ypos >= 25 && ypos <= 75))
	{
		//button = onHoverView;
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) addPlanet();
	}
	//else GPB::GPButton[1].resetHover();
	if ((xpos >= (1680) && xpos <= (1730)) && (ypos >= 25 && ypos <= 75))
	{
		//button = onHoverView;
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) addStar();
	}
}



void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	//if ((xpos >= 1605 && xpos <= 1880) && (ypos >= 26 && ypos <= 85))
	//	button = onHoverView;

	if ((xpos >= 1800 && xpos <= 1850) && (ypos >= 25 && ypos <= 75))
	{
		GPB::GPButton[0].setHover();
	}
	else GPB::GPButton[0].resetHover();
	if ((xpos >= (1760) && xpos <= (1790)) && (ypos >= 25 && ypos <= 75))
	{
		//button = onHoverView;
		GPB::GPButton[1].setHover();
	}
	else GPB::GPButton[1].resetHover();
	if ((xpos >= (1680) && xpos <= (1730)) && (ypos >= 25 && ypos <= 75))
	{
		//button = onHoverView;
		GPB::GPButton[2].setHover();
	}
	else GPB::GPButton[2].resetHover();

}

int main(void)
{
	//Step 1 : Init Graphics Library Framework
	if (!glfwInit()) { exit(EXIT_FAILURE); }

	//Step 2 : Instantiate GLFWwindow
	//1.window hint to specify version(major and minor) from function
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//2.create window object from Class and function
	
	//GLFWmonitor* monitor = glfwGetWindowMonitor(window);
	
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	//GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "SunEarthMoon!", NULL, NULL); //Last two parameters allow for Full screen and resource sharing
	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "SunEarthMoon", monitor, NULL);
	//3.make window context current from function
	glfwMakeContextCurrent(window);

	//Step 3 : Initialize openGL Extension Wrangler(GLEW)
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	//Vertical synchronization
	glfwSwapInterval(1);

	//Step 4 :  Init(Call)
	init(window);
	//float xscale, yscale;




	glfwGetWindowSize(window, &width, &height);
	//Step 5 : display(Call) - glfws
	//1.Loop for closing window
	while (!glfwWindowShouldClose(window)) {
		//Mouse Scroll Zoom Feature
		glfwSetScrollCallback(window, scroll_callback);
		//Key Input
		glfwSetKeyCallback(window, key_callback);
		//Onclick button


		//window
		glfwGetWindowSize(window, &width, &height);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwGetCursorPos(window, &xpos, &ypos);


		//glfwGetCursorPos(window, &xpos, &ypos);
		//if ((xpos >= 1605 && xpos <= 1880) && (ypos >= 25 && ypos <= 85))
		//{
		//	button = onHoverView;
		//}
		//cout<<xpos<<',' << ypos<<endl;
		//displayText();
		//2.Display window
		display(window, glfwGetTime());//glfwGetTime returns elapsed time since GLFW was initialized
		time_ = glfwGetTime();
	//3.Swap buffers ,Vertical synchronization :: Paints the screen
		glfwSwapBuffers(window);
		//4.Poll events, Handles events like key Press
		glfwPollEvents();
	}

	//Step 6 : Destroy the window and terminate
	//1.Distroy window
	glfwDestroyWindow(window);
	//2.Terminate
	glfwTerminate();
	exit(EXIT_SUCCESS);
}