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
#include "../Engine/GameState.h"
#include "../Engine/Input.h"

class Texture;
class Sprite;
class Board;
class Cell;

class Level : public GameState {
public:
	Level();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "Level"; }

protected:
	virtual bool Visit() = 0;
	virtual void MakeBoard(std::string levelData) = 0;
	virtual Board* GetBoard() = 0;
	virtual void PlayerSelected(Vector2DInt cellLocation) = 0;

	int currLevel;

	std::vector<std::string> levels = { "assets/Level1.dat",
							 "assets/Level2.dat",
							 "assets/Level3.dat",
							 "assets/Level4.dat",
							 "assets/Level5.dat",
							 "assets/Level6.dat",
							 "assets/Level7.dat",
							 "assets/Level8.dat" };
private:
	enum class State {
		PickStart,
		Filling,
		Filling_Step,
		Done,
	};
	enum class Modes {
		Play,
		Step,
	};

	State state;
	Modes mode;

	Input::InputKey quitKey;
	Input::InputKey reloadKey;
	
	Vector2DInt modePos;
	Vector2DInt resetPos;
	Vector2DInt startingSpotPos;
	Vector2DInt nextLevelPos;
	Vector2DInt stepPos;

	Sprite* modeText;
	Texture* resetText;
	Texture* startingSpotText;
	Texture* nextLevelText;
	Texture* stepText;
};

