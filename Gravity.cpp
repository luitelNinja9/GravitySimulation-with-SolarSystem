#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include "Stars.h"
#include<vector>
#include "Config.h"



///*
void calculateMotionParameters(std::vector<Star_>& stars, std::vector<Star_>& stars_copy)
{
	float radius, dt;
	//now = glfwGetTime();
	//dt = now - previous;
	dt = 0.025f;

	glm::vec3 acc_sum(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < stars.size(); ++i)
		//for (int i = stars.size()-1;i>=0;--i)
		//for (StarPtr = stars.begin(); StarPtr < stars.end(); StarPtr++)

	{
		glm::vec3 acc_sum(0.0f, 0.0f, 0.0f);
		//cout <<"\n<b>"<< i<<endl;
		//for (int j = stars.size() - 1; j >= 0; --j)
		for (int j = 0; j < stars_copy.size(); ++j)
		{
			//radius = glm::length(stars[i].position - stars[j].position);

			if (i != j)
			{
				//cout << j;
				radius = glm::length(stars_copy[j].position - stars[i].position);
				if ((radius - stars[i].getScale() - stars_copy[j].getScale()) < 0.2f)
				{
					//stars[i].velocity -= glm::dot(stars[i].velocity,stars[j].position-stars[i].position);
					stars[i].velocity = glm::vec3(0.0f, 0.0f, 0.0f);
					//stars[i].acceleration -= glm::dot(stars[i].acceleration, stars[j].position - stars[i].position);
					acc_sum = glm::vec3(0.0f, 0.0f, 0.0f);
					break;
				}
				else
				{
					acc_sum += ((stars_copy[j].position - stars[i].position) * float(stars_copy[j].mass / ((pow(radius, 3)) + 0.01f)));

				}
			}

		}

		stars[i].acceleration = acc_sum;
		//cout <<"\nAcceleration:" << stars[i].acceleration.x << "," << stars[i].acceleration.y << ","<<stars[i].acceleration.z;
		//stars[i].velocity += 5.0f* stars[i].acceleration * float(dt);
		stars[i].velocity = stars[i].velocity + 100.0f * stars[i].acceleration * float(dt);
		stars[i].position = stars[i].position + stars[i].velocity * float(dt);
		//stars[i].position += stars[i].velocity * float(dt);
		//cout << "\nPosition:" << stars[i].position.x << "," << stars[i].position.y << "," << stars[i].position.z << endl;



	}
	//previous = now;

}
void calculateMotionParameters(std::vector<Sattelite_>& stars, std::vector<Sattelite_>& stars_copy)
{
	float radius, dt;
	//now = glfwGetTime();
	//dt = now - previous;
	dt = 0.025f;

	glm::vec3 acc_sum(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < stars.size(); ++i)
		//for (int i = stars.size()-1;i>=0;--i)
		//for (StarPtr = stars.begin(); StarPtr < stars.end(); StarPtr++)

	{
		glm::vec3 acc_sum(0.0f, 0.0f, 0.0f);
		//cout <<"\n<b>"<< i<<endl;
		//for (int j = stars.size() - 1; j >= 0; --j)
		for (int j = 0; j < stars_copy.size(); ++j)
		{
			//radius = glm::length(stars[i].position - stars[j].position);

			if (i != j)
			{
				//cout << j;
				radius = glm::length(stars_copy[j].position - stars[i].position);
				if ((radius - stars[i].getScale() - stars_copy[j].getScale()) < 0.2f)
				{
					//stars[i].velocity -= glm::dot(stars[i].velocity,stars[j].position-stars[i].position);
					stars[i].velocity = glm::vec3(0.0f, 0.0f, 0.0f);
					//stars[i].acceleration -= glm::dot(stars[i].acceleration, stars[j].position - stars[i].position);
					acc_sum = glm::vec3(0.0f, 0.0f, 0.0f);
					break;
				}
				else
				{
					acc_sum += ((stars_copy[j].position - stars[i].position) * float(stars_copy[j].mass / ((pow(radius, 3)) + 0.01f)));

				}
			}

		}

		stars[i].acceleration = acc_sum;
		//cout <<"\nAcceleration:" << stars[i].acceleration.x << "," << stars[i].acceleration.y << ","<<stars[i].acceleration.z;
		//stars[i].velocity += 5.0f* stars[i].acceleration * float(dt);
		stars[i].velocity = stars[i].velocity + 100.0f * stars[i].acceleration * float(dt);
		stars[i].position = stars[i].position + stars[i].velocity * float(dt);
		//stars[i].position += stars[i].velocity * float(dt);
		//cout << "\nPosition:" << stars[i].position.x << "," << stars[i].position.y << "," << stars[i].position.z << endl;



	}
	//previous = now;

}
void calculateMotionParameters(std::vector<Planet_>& stars, std::vector<Planet_>& stars_copy)
{
	float radius, dt;
	//now = glfwGetTime();
	//dt = now - previous;
	dt = 0.025f;

	glm::vec3 acc_sum(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < stars.size(); ++i)
		//for (int i = stars.size()-1;i>=0;--i)
		//for (StarPtr = stars.begin(); StarPtr < stars.end(); StarPtr++)

	{
		glm::vec3 acc_sum(0.0f, 0.0f, 0.0f);
		//cout <<"\n<b>"<< i<<endl;
		//for (int j = stars.size() - 1; j >= 0; --j)
		for (int j = 0; j < stars_copy.size(); ++j)
		{
			//radius = glm::length(stars[i].position - stars[j].position);

			if (i != j)
			{
				//cout << j;
				radius = glm::length(stars_copy[j].position - stars[i].position);
				if ((radius - stars[i].getScale() - stars_copy[j].getScale()) < 0.2f)
				{
					//stars[i].velocity -= glm::dot(stars[i].velocity,stars[j].position-stars[i].position);
					stars[i].velocity = glm::vec3(0.0f, 0.0f, 0.0f);
					//stars[i].acceleration -= glm::dot(stars[i].acceleration, stars[j].position - stars[i].position);
					acc_sum = glm::vec3(0.0f, 0.0f, 0.0f);
					break;
				}
				else
				{
					acc_sum += ((stars_copy[j].position - stars[i].position) * float(stars_copy[j].mass / ((pow(radius, 3)) + 0.01f)));

				}
			}

		}

		stars[i].acceleration = acc_sum;
		//cout <<"\nAcceleration:" << stars[i].acceleration.x << "," << stars[i].acceleration.y << ","<<stars[i].acceleration.z;
		//stars[i].velocity += 5.0f* stars[i].acceleration * float(dt);
		stars[i].velocity = stars[i].velocity + 100.0f * stars[i].acceleration * float(dt);
		stars[i].position = stars[i].position + stars[i].velocity * float(dt);
		//stars[i].position += stars[i].velocity * float(dt);
		//cout << "\nPosition:" << stars[i].position.x << "," << stars[i].position.y << "," << stars[i].position.z << endl;



	}
	//previous = now;

}


//namespace Time
//{
//	float dT = 0.025;
//};

//Star motion due to star ,planets and sattelites

void calculateMotionParameters(std::vector<Star_>& stars, std::vector<Star_>& stars_copy,
	std::vector<Planet_>& planets, std::vector<Planet_>& planets_copy,
	std::vector<Sattelite_>& sattelites, std::vector<Sattelite_>& sattelites_copy)
{
	float radius, dt;
	//now = glfwGetTime();
	//dt = now - previous;
	dt = Time::dT;

	glm::vec3 acc_sum(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < stars.size(); ++i)
		//for (int i = stars.size()-1;i>=0;--i)
		//for (StarPtr = stars.begin(); StarPtr < stars.end(); StarPtr++)

	{
		glm::vec3 acc_sum(0.0f, 0.0f, 0.0f);
		//cout <<"\n<b>"<< i<<endl;
		//for (int j = stars.size() - 1; j >= 0; --j)
		for (int j = 0; j < stars_copy.size(); ++j)
		{
			//radius = glm::length(stars[i].position - stars[j].position);

			if (i != j)
			{
				//cout << j;
				radius = glm::length(stars_copy[j].position - stars[i].position);
				if ((radius - stars[i].getScale() - stars_copy[j].getScale()) < 0.2f)
				{
					//stars[i].velocity -= glm::dot(stars[i].velocity,stars[j].position-stars[i].position);
					stars[i].velocity = glm::vec3(0.0f, 0.0f, 0.0f);
					//stars[i].acceleration -= glm::dot(stars[i].acceleration, stars[j].position - stars[i].position);
					acc_sum = glm::vec3(0.0f, 0.0f, 0.0f);
					break;
				}
				else
				{
					acc_sum += ((stars_copy[j].position - stars[i].position) * float(stars_copy[j].mass / ((pow(radius, 3)) + 0.01f)));

				}
			}
		}
		//Planet	
		for (int j = 0; j < planets_copy.size(); ++j)
		{
			//radius = glm::length(stars[i].position - stars[j].position);


				//cout << j;
			radius = glm::length(planets_copy[j].position - stars[i].position);
			if ((radius - stars[i].getScale() - planets_copy[j].getScale()) < 0.2f)
			{
				//stars[i].velocity -= glm::dot(stars[i].velocity,stars[j].position-stars[i].position);
				stars[i].velocity = glm::vec3(0.0f, 0.0f, 0.0f);
				//stars[i].acceleration -= glm::dot(stars[i].acceleration, stars[j].position - stars[i].position);
				acc_sum = glm::vec3(0.0f, 0.0f, 0.0f);
				break;
			}
			else
			{
				acc_sum += ((planets_copy[j].position - stars[i].position) * float(planets_copy[j].mass / ((pow(radius, 3)) + 0.01f)));

			}

		}
		//Sattelite
		for (int j = 0; j < sattelites_copy.size(); ++j)
		{
			//radius = glm::length(stars[i].position - stars[j].position);

				//cout << j;
			radius = glm::length(sattelites_copy[j].position - stars[i].position);
			if ((radius - stars[i].getScale() - sattelites_copy[j].getScale()) < 0.2f)
			{
				//stars[i].velocity -= glm::dot(stars[i].velocity,stars[j].position-stars[i].position);
				stars[i].velocity = glm::vec3(0.0f, 0.0f, 0.0f);
				//stars[i].acceleration -= glm::dot(stars[i].acceleration, stars[j].position - stars[i].position);
				acc_sum = glm::vec3(0.0f, 0.0f, 0.0f);
				break;
			}
			else
			{
				acc_sum += ((sattelites_copy[j].position - stars[i].position) * float(sattelites_copy[j].mass / ((pow(radius, 3)) + 0.01f)));

			}


		}

		stars[i].acceleration = acc_sum;
		//cout <<"\nAcceleration:" << stars[i].acceleration.x << "," << stars[i].acceleration.y << ","<<stars[i].acceleration.z;
		//stars[i].velocity += 5.0f* stars[i].acceleration * float(dt);
		stars[i].velocity = stars[i].velocity + 120.0f * stars[i].acceleration * float(dt);
		stars[i].position = stars[i].position + 2.0f*stars[i].velocity * float(dt);
		//stars[i].position += stars[i].velocity * float(dt);
		//cout << "\nPosition:" << stars[i].position.x << "," << stars[i].position.y << "," << stars[i].position.z << endl;




	//previous = now;

	}
}

//Sattelite motion due to star and Planet
void calculateMotionParameters(std::vector<Sattelite_>& stars, std::vector<Sattelite_>& stars_copy,
	std::vector<Star_>& planets, std::vector<Star_>& planets_copy,
	std::vector<Planet_>& sattelites, std::vector<Planet_>& sattelites_copy)
{
	float radius, dt;
	//now = glfwGetTime();
	//dt = now - previous;
	dt = Time::dT;

	glm::vec3 acc_sum(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < stars.size(); ++i)
		//for (int i = stars.size()-1;i>=0;--i)
		//for (StarPtr = stars.begin(); StarPtr < stars.end(); StarPtr++)

	{
		glm::vec3 acc_sum(0.0f, 0.0f, 0.0f);
		//cout <<"\n<b>"<< i<<endl;
		//for (int j = stars.size() - 1; j >= 0; --j)
		for (int j = 0; j < stars_copy.size(); ++j)
		{
			//radius = glm::length(stars[i].position - stars[j].position);

			if (i != j)
			{
				//cout << j;
				radius = glm::length(stars_copy[j].position - stars[i].position);
				if ((radius - stars[i].getScale() - stars_copy[j].getScale()) < 0.2f)
				{
					//stars[i].velocity -= glm::dot(stars[i].velocity,stars[j].position-stars[i].position);
					stars[i].velocity = glm::vec3(0.0f, 0.0f, 0.0f);
					//stars[i].acceleration -= glm::dot(stars[i].acceleration, stars[j].position - stars[i].position);
					acc_sum = glm::vec3(0.0f, 0.0f, 0.0f);
					break;
				}
				else
				{
					acc_sum += ((stars_copy[j].position - stars[i].position) * float(stars_copy[j].mass / ((pow(radius, 3)) + 0.01f)));

				}
			}

		}
		//Planet	
		for (int j = 0; j < planets_copy.size(); ++j)
		{
			//radius = glm::length(stars[i].position - stars[j].position);


				//cout << j;
			radius = glm::length(planets_copy[j].position - stars[i].position);
			if ((radius - stars[i].getScale() - planets_copy[j].getScale()) < 0.2f)
			{
				//stars[i].velocity -= glm::dot(stars[i].velocity,stars[j].position-stars[i].position);
				stars[i].velocity = glm::vec3(0.0f, 0.0f, 0.0f);
				//stars[i].acceleration -= glm::dot(stars[i].acceleration, stars[j].position - stars[i].position);
				acc_sum = glm::vec3(0.0f, 0.0f, 0.0f);
				break;
			}
			else
			{
				acc_sum += ((planets_copy[j].position - stars[i].position) * float(planets_copy[j].mass / ((pow(radius, 3)) + 0.01f)));

			}

		}
		//Sattelite
		for (int j = 0; j < sattelites_copy.size(); ++j)
		{
			//radius = glm::length(stars[i].position - stars[j].position);



				//cout << j;
			radius = glm::length(sattelites_copy[j].position - stars[i].position);
			if ((radius - stars[i].getScale() - sattelites_copy[j].getScale()) < 0.2f)
			{
				//stars[i].velocity -= glm::dot(stars[i].velocity,stars[j].position-stars[i].position);
				stars[i].velocity = glm::vec3(0.0f, 0.0f, 0.0f);
				//stars[i].acceleration -= glm::dot(stars[i].acceleration, stars[j].position - stars[i].position);
				acc_sum = glm::vec3(0.0f, 0.0f, 0.0f);
				break;
			}
			else
			{
				acc_sum += (20.0f / sattelites_copy.size()) * ((sattelites_copy[j].position - stars[i].position) * float(sattelites_copy[j].mass / ((pow(radius, 3)) + 0.01f)));

			}


		}

		stars[i].acceleration = acc_sum;
		//cout <<"\nAcceleration:" << stars[i].acceleration.x << "," << stars[i].acceleration.y << ","<<stars[i].acceleration.z;
		//stars[i].velocity += 5.0f* stars[i].acceleration * float(dt);
		stars[i].velocity = stars[i].velocity + 100.0f * stars[i].acceleration * float(dt);
		stars[i].position = stars[i].position + stars[i].velocity * float(dt);
		//stars[i].position += stars[i].velocity * float(dt);
		//cout << "\nPosition:" << stars[i].position.x << "," << stars[i].position.y << "," << stars[i].position.z << endl;




	//previous = now;

	}
}

//Planet motion due to star and sattelites
void calculateMotionParameters(std::vector<Planet_>& stars, std::vector<Planet_>& stars_copy,
	std::vector<Star_>& planets, std::vector<Star_>& planets_copy,
	std::vector<Sattelite_>& sattelites, std::vector<Sattelite_>& sattelites_copy)
{
	float radius, dt;
	//now = glfwGetTime();
	//dt = now - previous;
	dt = Time::dT;

	glm::vec3 acc_sum(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < stars.size(); ++i)
		//for (int i = stars.size()-1;i>=0;--i)
		//for (StarPtr = stars.begin(); StarPtr < stars.end(); StarPtr++)

	{
		glm::vec3 acc_sum(0.0f, 0.0f, 0.0f);
		//cout <<"\n<b>"<< i<<endl;
		//for (int j = stars.size() - 1; j >= 0; --j)
		for (int j = 0; j < stars_copy.size(); ++j)
		{
			//radius = glm::length(stars[i].position - stars[j].position);

			if (i != j)
			{
				//cout << j;
				radius = glm::length(stars_copy[j].position - stars[i].position);
				if ((radius - stars[i].getScale() - stars_copy[j].getScale()) < 0.2f)
				{
					//stars[i].velocity -= glm::dot(stars[i].velocity,stars[j].position-stars[i].position);
					stars[i].velocity = glm::vec3(0.0f, 0.0f, 0.0f);
					//stars[i].acceleration -= glm::dot(stars[i].acceleration, stars[j].position - stars[i].position);
					acc_sum = glm::vec3(0.0f, 0.0f, 0.0f);
					break;
				}
				else
				{
					acc_sum += ((stars_copy[j].position - stars[i].position) * float(stars_copy[j].mass / ((pow(radius, 3)) + 0.01f)));

				}
			}
		}
		//Planet	
		for (int j = 0; j < planets_copy.size(); ++j)
		{
			//radius = glm::length(stars[i].position - stars[j].position);


				//cout << j;
			radius = glm::length(planets_copy[j].position - stars[i].position);
			if ((radius - stars[i].getScale() - planets_copy[j].getScale()) < 0.2f)
			{
				//stars[i].velocity -= glm::dot(stars[i].velocity,stars[j].position-stars[i].position);
				stars[i].velocity = glm::vec3(0.0f, 0.0f, 0.0f);
				//stars[i].acceleration -= glm::dot(stars[i].acceleration, stars[j].position - stars[i].position);
				acc_sum = glm::vec3(0.0f, 0.0f, 0.0f);
				break;
			}
			else
			{
				acc_sum += ((planets_copy[j].position - stars[i].position) * float(planets_copy[j].mass / ((pow(radius, 3)) + 0.01f)));

			}

		}
		//Sattelite
		for (int j = 0; j < sattelites_copy.size(); ++j)
		{
			//radius = glm::length(stars[i].position - stars[j].position);


				//cout << j;
			radius = glm::length(sattelites_copy[j].position - stars[i].position);
			if ((radius - stars[i].getScale() - sattelites_copy[j].getScale()) < 0.2f)
			{
				//stars[i].velocity -= glm::dot(stars[i].velocity,stars[j].position-stars[i].position);
				stars[i].velocity = glm::vec3(0.0f, 0.0f, 0.0f);
				//stars[i].acceleration -= glm::dot(stars[i].acceleration, stars[j].position - stars[i].position);
				acc_sum = glm::vec3(0.0f, 0.0f, 0.0f);
				break;
			}
			else
			{
				acc_sum += ((sattelites_copy[j].position - stars[i].position) * float(sattelites_copy[j].mass / ((pow(radius, 3)) + 0.01f)));

			}


		}

		stars[i].acceleration = acc_sum;
		//cout <<"\nAcceleration:" << stars[i].acceleration.x << "," << stars[i].acceleration.y << ","<<stars[i].acceleration.z;
		//stars[i].velocity += 5.0f* stars[i].acceleration * float(dt);
		stars[i].velocity = stars[i].velocity + 120.0f * stars[i].acceleration * float(dt);
		stars[i].position = stars[i].position + 2.0f*stars[i].velocity * float(dt);
		//stars[i].position += stars[i].velocity * float(dt);
		//cout << "\nPosition:" << stars[i].position.x << "," << stars[i].position.y << "," << stars[i].position.z << endl;




	//previous = now;

	}
}
//*/
