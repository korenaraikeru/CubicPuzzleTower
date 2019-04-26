#include "Scaffold.h"
#include "Inputkey.h"
#include "Cube.h"
#include "Sound.h"

Scaf::Scaf()
{
	modelHandle = MV1LoadModel("data/model/scaffold.mqo");
}

Scaf::~Scaf()
{
	MV1DeleteModel(modelHandle);
}

void Scaf::Init()
{
	pos = VGet(0.0f, -150.0f, 0.0f);
}

void Scaf::Update(const Cube& cube)
{
	if (pos.y != 0)
		playSound(SE_SCAF);
	else if (pos.y == 0)
	{
		stopSound(SE_SCAF);
		resetSound(SE_SCAF);
	}

	if (cube.clear_flag)
	{
		pos.y += 2.f;
	}
	else
	{
		if (pos.y != 0)
		{
			pos.y += 2.f;
		}
		if (pos.y > 0)
		{
			pos.y = 0.f;
		}
	}
	MV1SetPosition(modelHandle, pos);
}

void Scaf::Draw()
{
	MV1DrawModel(modelHandle);
}
