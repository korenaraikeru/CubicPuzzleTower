#pragma once
#include "DxLib.h"

class Cube;

class Scaf
{
public:
	Scaf();
	~Scaf();

	void Init();
	void Update(const Cube& cube);
	void Draw();

	const VECTOR& GetPos() const { return pos; }

private:
	int modelHandle;
	VECTOR pos;
};