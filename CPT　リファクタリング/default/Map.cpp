#include "Map.h"
#include "Player.h"


Map::Map()
{
	modelHandle_stage = MV1LoadModel("data/model/stage.mqo");	//ステージ用のデカいボックス
	modelHandle_frame = MV1LoadModel("data/model/frame.mqo");	//枠
	modelHandle_tower = MV1LoadModel("data/model/tower.x");	//タワー
}


Map::~Map()
{
	// モデルのアンロード.
	MV1DeleteModel(modelHandle_stage);
	MV1DeleteModel(modelHandle_frame);
	MV1DeleteModel(modelHandle_tower);
}

void Map::Update()
{

}

void Map::Draw()
{
	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle_stage, VGet(0, 0, 0));
	MV1SetPosition(modelHandle_frame, VGet(0, 0, 0));
	MV1SetPosition(modelHandle_tower, VGet(0, 0, 0));
	// ３Ｄモデルの描画
	//MV1DrawModel(modelHandle_stage);
	MV1DrawModel(modelHandle_frame);
	MV1DrawModel(modelHandle_tower);
}