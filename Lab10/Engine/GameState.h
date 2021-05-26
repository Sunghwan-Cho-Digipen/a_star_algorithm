/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameState.h
Purpose: Header file for Game States Interface
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/

#pragma once
#include <vector>
#include <string>

class GameState {
public:
	virtual void Load() = 0;
	virtual void Update(double dt) = 0;
	virtual void Draw() = 0;
	virtual void Unload() = 0;
	virtual std::string GetName() = 0;
private:
};

