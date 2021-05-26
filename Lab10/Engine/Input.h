/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input.h
Purpose: Header file for Input Module
Project: CS230
Author: Kevin Wright
Creation date: 3/19/2020
-----------------------------------------------------------------*/
#pragma once
#include "BasicDataTypes.h"
#include <vector>

class Input {
public:
	enum class ButtonType {
		None,	Enter,	Escape, Space, 	Left,	Up,		Right,	Down,
		A,		B,		C,		D,		E,		F,		G,		H,		I,		J,
		K,		L,		M,		N,		O,		P,		Q,		R,		S,		T,
		U,		V,		W,		X,		Y,		Z,		LeftMB, RightMB, MiddleMB,
		Count
	};
	class InputKey {
	public:
		InputKey(ButtonType button);
		bool IsKeyDown() const;
		bool IsKeyReleased() const;
	private:
		ButtonType button;
	};

	Input();
	bool IsKeyDown(ButtonType key) const;
	bool IsKeyUp(ButtonType key) const;
	bool IsKeyReleased(ButtonType key) const;
	void SetKeyDown(ButtonType key, bool value);
	void SetMousePos(Vector2DInt newMousePos);
	Vector2DInt GetMousePos();
	void Update();
private:
	Vector2DInt mousePos;
	std::vector<bool> keyDown;
	std::vector<bool> wasKeyDown;
};



