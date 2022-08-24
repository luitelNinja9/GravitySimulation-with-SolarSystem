

#include<vector>
#include "Stars.h"

#ifndef GRAVITY
#define GRAVITY
///*
void calculateMotionParameters(std::vector<Star_>& stars, std::vector<Star_>& stars_copy);
void calculateMotionParameters(std::vector<Sattelite_>& stars, std::vector<Sattelite_>& stars_copy);
void calculateMotionParameters(std::vector<Planet_>& stars, std::vector<Planet_>& stars_copy);

void calculateMotionParameters(std::vector<Star_>& stars, std::vector<Star_>& stars_copy,
	std::vector<Planet_>& planets, std::vector<Planet_>& planets_copy,
	std::vector<Sattelite_>& sattelites, std::vector<Sattelite_>& sattelites_copy);

void calculateMotionParameters(std::vector<Planet_>& stars, std::vector<Planet_>& stars_copy,
	std::vector<Star_>& planets, std::vector<Star_>& planets_copy,
	std::vector<Sattelite_>& sattelites, std::vector<Sattelite_>& sattelites_copy);

void calculateMotionParameters(std::vector<Sattelite_>& stars, std::vector<Sattelite_>& stars_copy,
	std::vector<Star_>& planets, std::vector<Star_>& planets_copy,
	std::vector<Planet_>& sattelites, std::vector<Planet_>& sattelites_copy);

//*/
#endif 
