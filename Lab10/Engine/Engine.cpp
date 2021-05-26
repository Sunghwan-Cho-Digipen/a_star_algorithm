/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.cpp
Purpose: source file for Engine Module
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/
#include <chrono>

#include "Logger.h"
#include "Engine.h"

Engine::Engine() : frameCount(0),
#ifdef _DEBUG				
							logger(Logger::Severity::Debug, true)
#else 						
							logger(Logger::Severity::Event, false)
#endif
{}

Engine::~Engine() {
}

void Engine::Init(std::string windowName) {
	logger.LogEvent("Engine Init");
	window.Init(windowName);
	lastTick = std::chrono::system_clock::now();
	fpsCalcTime = lastTick;
}

void Engine::Shutdown() {
	logger.LogEvent("Engine Shutdown");
}

void Engine::Update() {
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	double dt = std::chrono::duration<double>(now - lastTick).count();

	if (dt >= 1 / Engine::Target_FPS) {
		logger.LogVerbose("Engine Update");
		lastTick = now;

		if (++frameCount >= Engine::FPS_IntervalFrameCount) {
			double actualTime = std::chrono::duration<double>((now - fpsCalcTime)).count();
			logger.LogVerbose("FPS:  " + std::to_string(frameCount / actualTime));
			frameCount = 0;
			fpsCalcTime = now;
		}
		gameStateManager.Update(dt);
		input.Update();
		window.Update();
	}
}

bool Engine::HasGameEnded() {
	return gameStateManager.HasGameEnded();
}

void Engine::AddSpriteFont(std::string fileName) {
	fonts.push_back(SpriteFont(fileName));
}

void Engine::DrawText(int fontIndex, Vector2DInt pos, std::string text, SpriteFont::Justified justified, Color color) {
	fonts[fontIndex].DrawText(pos, text, justified, color);
}
