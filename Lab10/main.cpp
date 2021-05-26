/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: main.cpp
Purpose: Source file for Main
Project: CS230
Author: Kevin Wright
Creation date: 3/17/2020
-----------------------------------------------------------------*/

#include <exception>    // std::exception

#include "Engine/Engine.h"
#include "Game/Splash.h"
#include "Game/AStar.h"
#include "Game/Screens.h"


int main(void) {
	Engine& engine = Engine::Instance();

	try {
		engine.Init("AStar");

		engine.GetGameStateManager().AddGameState(new Splash());
		engine.GetGameStateManager().AddGameState(new AStar());
		engine.AddSpriteFont("assets/Numbers.png");
		engine.AddSpriteFont("assets/Numbers2.png");

		while (engine.HasGameEnded() == false) {
			engine.Update();
		}
		engine.Shutdown();
		return 0;
	} catch (std::exception & e) {
		Engine::GetLogger().LogError(e.what());
		return -1;
	}
}