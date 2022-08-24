#include "Stars.h"
#include<iostream>

///*
using namespace std;



Star::Star(int scale_=1, float angularSpeed_=1.0f,const char* texString_="8k_sun.jpg", glm::vec3 position_ = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 velocity_)
{
	if (scale_ >= 1.0f && scale_ <= 10.0f)
	{
		Star::scale = float(scale_)/2.0f;
	}
	else
	{
		Star::scale=float(scale_);
	}
	Star:: textureString = texString_;
	Star::position = position_;
	Star::angularSpeed = angularSpeed_;
	Star::mass = pow(scale,3);
	Star::velocity = velocity_;
	Star::acceleration = glm::vec3(0.0f,0.0f,0.0f);

}


const char* Star::getTextureString()
{
	return textureString;
}

const float Star::getScale()
{
	return scale;
}

const float Star::getAngularSpeed()
{
	return angularSpeed;
}

glm::mat4 Star::translateMatrix()
{
	return glm::translate(glm::mat4(1.0f), Star::position);
}
glm::vec3 Star::positionVec()
{
	return Star::position;
}

glm::vec3 Star::velocityVec()
{
	return Star::velocity;
}

glm::vec3 Star::accelerationVec()
{
	return Star::acceleration;
}

glm::vec3 Star::scaleVec()
{
	return glm::vec3(scale,scale,scale);
}


Planet::Planet(int scale_, float angularSpeed_,float distance1_ , float distance2_ ,float revolution_, vector <Sattelite> sats_,int sattelite_)
{
	if (scale_ >= 1.0f && scale_ <= 10.0f)
	{
		Planet::scale = float(scale_)/2.0f;
	}
	else
	{
		Planet::scale=float(scale_);
	}

	
	Planet::scale = scale / 5.0f;

	Planet::angularSpeed = angularSpeed_;
	Planet::revolutionSpeed = revolution_;
	Planet::distance1 = distance1_;
	Planet::distance2 = distance2_;
	Planet::sattelite = sattelite_;
	sats = sats_;
}


const float Planet::getScale()
{
	return scale;
}

const float Planet::getAngularSpeed()
{
	return angularSpeed;
}

const float Planet::getRevolutionSpeed()
{
	return revolutionSpeed;
}


glm::vec3 Planet::scaleVec()
{
	return glm::vec3(scale,scale,scale);
}
const float Planet::getDistance1()
{
	return Planet::distance1;
}
const float Planet::getDistance2()
{
	return Planet::distance2;
}
const int Planet::withSattelite()
{
	return Planet::sattelite;
}


Sattelite::Sattelite(int scale_ = 1, float angularSpeed_ = 1.0f, float distance1_ = 0.0f, float distance2_ = 0.0f, float revolution_ = 0.1f)
{
	if (scale_ >= 1.0f && scale_ <= 10.0f)
	{
		scale = float(scale_) / 2.0f;
	}
	else
	{
		scale = float(scale_);
	}


	scale = scale / 10.0f;

	angularSpeed = angularSpeed_;
	revolutionSpeed = revolution_;
	distance1 = distance1_;
	distance2 = distance2_;
	
	
}


const float Sattelite::getScale()
{
	return scale;
}

const float Sattelite::getAngularSpeed()
{
	return angularSpeed;
}

const float Sattelite::getRevolutionSpeed()
{
	return revolutionSpeed;
}


glm::vec3 Sattelite::scaleVec()
{
	return glm::vec3(scale, scale, scale);
}
const float Sattelite::getDistance1()
{
	return Sattelite::distance1;
}
const float Sattelite::getDistance2()
{
	return Sattelite::distance2;
}
//*/



Star_::Star_(int scale_ = 1, float angularSpeed_ = 1.0f, const char* texString_ = "8k_sun.jpg", glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 velocity_ )
{
	if (scale_ >= 1.0f && scale_ <= 10.0f)
	{
		Star_::scale = float(scale_) / 2.0f;
	}
	else
	{
		Star_::scale = float(scale_);
	}
	Star_::textureString = texString_;
	Star_::position = position_;
	Star_::angularSpeed = angularSpeed_;
	Star_::mass = pow(scale, 3);
	Star_::velocity = velocity_;
	Star_::acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
}


const char* Star_::getTextureString()
{
	return textureString;
}

const float Star_::getScale()
{
	return scale;
}

const float Star_::getAngularSpeed()
{
	return angularSpeed;
}

glm::mat4 Star_::translateMatrix()
{
	return glm::translate(glm::mat4(1.0f), Star_::position);
}
glm::vec3 Star_::positionVec()
{
	return Star_::position;
}

glm::vec3 Star_::velocityVec()
{
	return Star_::velocity;
}

glm::vec3 Star_::accelerationVec()
{
	return Star_::acceleration;
}

glm::vec3 Star_::scaleVec()
{
	return glm::vec3(scale, scale, scale);
}



Sattelite_::Sattelite_(int scale_ = 1, float angularSpeed_ = 6.0f, const char* texString_ = "8k_moon.jpg", glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 velocity_)
{
	if (scale_ >= 1.0f && scale_ <= 10.0f)
	{
		scale = float(scale_) / 40.0f;
	}
	else
	{
		scale = float(scale_);
	}
	textureString = texString_;
	position = position_;
	angularSpeed = angularSpeed_;
	mass = 0.001 * pow(scale, 3);
	velocity = velocity_;
	acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
}


const char* Sattelite_::getTextureString()
{
	return textureString;
}

const float Sattelite_::getScale()
{
	return scale;
}

const float Sattelite_::getAngularSpeed()
{
	return angularSpeed;
}

glm::mat4 Sattelite_::translateMatrix()
{
	return glm::translate(glm::mat4(1.0f), position);
}
glm::vec3 Sattelite_::positionVec()
{
	return position;
}

glm::vec3 Sattelite_::velocityVec()
{
	return velocity;
}

glm::vec3 Sattelite_::accelerationVec()
{
	return Sattelite_::acceleration;
}

glm::vec3 Sattelite_::scaleVec()
{
	return glm::vec3(scale, scale, scale);
}



Planet_::Planet_(int scale_ = 1, float angularSpeed_ = 3.0f, const char* texString_ = "4k_earth_daymap.jpg", glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 velocity_)
{
	if (scale_ >= 1.0f && scale_ <= 10.0f)
	{
		scale = float(scale_) / 20.0f;
	}
	else
	{
		scale = float(scale_);
	}
	textureString = texString_;
	position = position_;
	angularSpeed = angularSpeed_;
	mass = 10.0f * pow(scale, 3);
	velocity = velocity_;
	acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
}


const char* Planet_::getTextureString()
{
	return textureString;
}

const float Planet_::getScale()
{
	return scale;
}

const float Planet_::getAngularSpeed()
{
	return angularSpeed;
}

glm::mat4 Planet_::translateMatrix()
{
	return glm::translate(glm::mat4(1.0f), position);
}
glm::vec3 Planet_::positionVec()
{
	return position;
}

glm::vec3 Planet_::velocityVec()
{
	return velocity;
}

glm::vec3 Planet_::accelerationVec()
{
	return acceleration;
}

glm::vec3 Planet_::scaleVec()
{
	return glm::vec3(scale, scale, scale);
}
