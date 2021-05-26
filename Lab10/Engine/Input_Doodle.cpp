/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input_Doodle.cpp
Purpose: Interface between doodle and our engine
Project: CS230
Author: Kevin Wright
Creation date: 3/17/2020
-----------------------------------------------------------------*/

#include "doodle/input.hpp"
#include "Input.h"
#include "Engine.h"

Input::ButtonType DoodleKeyToCS230Key(doodle::KeyboardButtons button) {
	if (button == doodle::KeyboardButtons::Enter) {
		return Input::ButtonType::Enter;
	} else if (button == doodle::KeyboardButtons::Escape) {
		return Input::ButtonType::Escape;
	} else if (button == doodle::KeyboardButtons::Space) {
		return Input::ButtonType::Space;
	} else if (button == doodle::KeyboardButtons::Left) {
		return Input::ButtonType::Left;
	} else if (button == doodle::KeyboardButtons::Right) {
		return Input::ButtonType::Right;
	} else if (button == doodle::KeyboardButtons::Up) {
		return Input::ButtonType::Up;
	} else if (button == doodle::KeyboardButtons::Down) {
		return Input::ButtonType::Down;
	} else if (button >= doodle::KeyboardButtons::A && button <= doodle::KeyboardButtons::Z) {
		int offset = static_cast<int>(button) - static_cast<int>(doodle::KeyboardButtons::A);
		return static_cast<Input::ButtonType>(static_cast<int>(Input::ButtonType::A) + offset);
	}
	return Input::ButtonType::None;
}


Input::ButtonType DoodleMouseToCS230Mouse(doodle::MouseButtons button) {
	if (button == doodle::MouseButtons::Left) {
		return Input::ButtonType::LeftMB;
	}
	if (button == doodle::MouseButtons::Middle) {
		return Input::ButtonType::MiddleMB;
	}
	if (button == doodle::MouseButtons::Right) {
		return Input::ButtonType::RightMB;
	}
	return Input::ButtonType::None;
}

void on_key_pressed(doodle::KeyboardButtons doodleButton) {
	Input::ButtonType button = DoodleKeyToCS230Key(doodleButton);
	if (button != Input::ButtonType::None) {
		Engine::GetLogger().LogEvent("on_key_pressed");
		Engine::GetInput().SetKeyDown(button, true);
	}
}

void on_key_released(doodle::KeyboardButtons doodleButton) {
	Input::ButtonType button = DoodleKeyToCS230Key(doodleButton);
	if (button != Input::ButtonType::None) {
		Engine::GetLogger().LogEvent("on_key_released");
		Engine::GetInput().SetKeyDown(button, false);
	}
}

void on_mouse_released(doodle::MouseButtons button) {
	Engine::GetInput().SetKeyDown(DoodleMouseToCS230Mouse(button), false);
}

void on_mouse_pressed(doodle::MouseButtons button) {
	Engine::GetInput().SetKeyDown(DoodleMouseToCS230Mouse(button), true);
}

void on_mouse_moved(int mouse_x, int mouse_y) {
	Engine::GetInput().SetMousePos({ mouse_x, mouse_y });
}