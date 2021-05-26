/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.cpp
Purpose: Source file for Game State Manager
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/

#include "Engine.h"
#include "GameStateManager.h"


GameStateManager::GameStateManager() : currGameState(nullptr), nextGameState(nullptr), state(State::START) { }

void GameStateManager::AddGameState(GameState* gameState) {
	gameStates.push_back(gameState);
}

void GameStateManager::Update(double dt) {
	switch (state) {
	case State::START:
		nextGameState = gameStates[0];
		state = State::LOAD;
		break;
	case State::LOAD:
		currGameState = nextGameState;
		Engine::GetLogger().LogEvent("Load " + currGameState->GetName());
		currGameState->Load();
		Engine::GetLogger().LogEvent("Load Complete");
		state = State::RUNNING;
		break;
	case State::RUNNING:
		if (currGameState != nextGameState) {
			state = State::UNLOAD;
		} else {
			Engine::GetLogger().LogVerbose("Update " + currGameState->GetName());
			currGameState->Update(dt);
			currGameState->Draw();
		}
		break;
	case State::UNLOAD:
		Engine::GetLogger().LogEvent("Unload " + currGameState->GetName());
		currGameState->Unload();
		if (nextGameState == nullptr) {
			state = State::SHUTDOWN;
			break;
		}
		state = State::LOAD;
		break;
	case State::SHUTDOWN:
		state = State::EXIT;
		break;
	case State::EXIT:
		break;
	}
}

void GameStateManager::SetNextState(int initState) {
	nextGameState = gameStates[initState];
}

void GameStateManager::ReloadState() {
	state = State::UNLOAD;
}

void GameStateManager::Shutdown() {
	state = State::UNLOAD;
	nextGameState = nullptr;
}
