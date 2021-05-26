/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level.h
Purpose: Header file for Level
Project: CS230
Author: Kevin Wright
Creation date: 4/30/2020
-----------------------------------------------------------------*/

#pragma once
#include <vector>
#include <string>
#include "Level.h"

class WeightedLevel : public Level {
public:
	WeightedLevel() {
		levels.clear();
		levels = { "assets/WeightedLevel1.dat",
								 "assets/WeightedLevel2.dat",
								 "assets/WeightedLevel3.dat",
								 "assets/WeightedLevel4.dat",
								 "assets/WeightedLevel5.dat",
								 "assets/WeightedLevel6.dat",
								 "assets/WeightedLevel7.dat",
								 "assets/WeightedLevel8.dat" };
	}
protected:
};

