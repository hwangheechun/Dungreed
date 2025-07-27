#include "stdafx.h"
#include "MainScene.h"

MainScene::~MainScene()
{
}

HRESULT MainScene::Init()
{
	Player* player = new Player();
	player->SetMainScene(this);
	OBJECTMANAGER->AddObject(ObjectType::Player, player);

	CAMERA->ChangeTarget(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));
	CAMERA->SetCameraMode(CameraState::TARGET);

	Weapon* _weapon = new Weapon();
	OBJECTMANAGER->AddObject(ObjectType::Item, _weapon);

	Inventory* _inventory = new Inventory();
	OBJECTMANAGER->AddObject(ObjectType::UI, _inventory);

	UI* _ui = new UI();
	OBJECTMANAGER->AddObject(ObjectType::UI, _ui);

	/*Skeleton* skeleton = new Skeleton();
	OBJECTMANAGER->AddObject(ObjectType::Enemy, skeleton);*/

	for (int i = 0; i < 20; ++i) 
	{
		Bullet* bullet = new Bullet();

		OBJECTMANAGER->AddObject(ObjectType::Bullet, bullet);
	}

	//_maxX = 40;
	//_maxY = 40;

	//for (int i = 0; i <= _maxY; ++i)
	//{
	//	vTileOneLine v;
	//	for (int j = 0; j <= _maxX; ++j)
	//	{
	//		Tile* t = new Tile();
	//		t->SetTile(1, 0, 0);
	//		t->SetTileRc(j * TILE_SIZE, i * TILE_SIZE);		// 0, 0 -> 0, 0 / 0, 1 -> 48, 0 - left top 설정해 주는 함수

	//		v.emplace_back(t);
	//	}
	//	_tiles.emplace_back(v);
	//}

	IMAGEMANAGER->AddImage(L"tile null", L"Resources/tilenull.png");
	IMAGEMANAGER->AddFrameImage(L"terrain1", L"Resources/terrain1.png", 16, 18);
	IMAGEMANAGER->AddFrameImage(L"townTile", L"Resources/Map/TownTile.png", 10, 10);

	_imgTerrain = IMAGEMANAGER->FindImage(L"townTile");

	_ptMapSize.x = 50;
	_ptMapSize.y = 25;
	_rcMapView = RectMakePivot(Vector2(0, 0), Vector2((int)_ptMapSize.x * TILE_SIZE, (int)_ptMapSize.y * TILE_SIZE), Pivot::LeftTop);

	for (int i = 0; i < _ptMapSize.y; ++i)
	{
		vector<Tile*> v;
		for (int j = 0; j < _ptMapSize.x; ++j)
		{
			Tile* t = new Tile();
			t->SetTileRc(j * TILE_SIZE, i * TILE_SIZE);
			v.push_back(t);
		}
		_vTiles.push_back(v);
	}
	
	LoadMapFromFile(L"C:\\Users\\heech\\OneDrive\\Desktop\\Dungreed\\Resources\\Map\\MapData\\Test.map");

	return S_OK;
}

void MainScene::Release()
{
	OBJECTMANAGER->RemoveObject(ObjectType::Enemy, L"Skeleton");
}

void MainScene::Update()
{
	Scene::Update();
}

void MainScene::Render()
{
	Scene::Render();

	for (int i = 0; i < _vTiles.size(); ++i)
	{
		for (int j = 0; j < _vTiles[i].size(); ++j)
		{
			// FIXME : 실제 타일이 가지고 있는 Type의 타일 / 오브젝트로 출력 ... _vTiles[i][j]->GetTerrainImageNum();
			auto ptCenter = _vTiles[i][j]->GetRect().GetCenter();
			if (_vTiles[i][j]->GetTerrainX() == -1 || _vTiles[i][j]->GetTerrainY() == -1)
				IMAGEMANAGER->FindImage(L"tile null")->Render(CAMERA->GetRelativeVector2(Vector2(ptCenter.x, ptCenter.y) + Vector2(_rcMapView.left, _rcMapView.top)));
			else
				_imgTerrain->FrameRender(CAMERA->GetRelativeVector2(ptCenter + Vector2(_rcMapView.left, _rcMapView.top)), _vTiles[i][j]->GetTerrainX(), _vTiles[i][j]->GetTerrainY());

			/*if (_vTiles[i][j]->GetObjectX() >= 0 && _vTiles[i][j]->GetObjectX() >= 0)
				_imgObject->FrameRender(ptCenter + Vector2(_rcMapView.left, _rcMapView.top), _vTiles[i][j]->GetObjectX(), _vTiles[i][j]->GetObjectY());

			if (_eEditMode == EditMode::Type)
				_imgType->FrameRender(ptCenter + Vector2(_rcMapView.left, _rcMapView.top), _vTiles[i][j]->GetBlocked() ? 1 : 0, 0);*/
		}
	}

	_D2DRenderer->RenderText(500, 500, L"타일맵 위치" + to_wstring(_rcMapView.left), 15);
	_D2DRenderer->RenderText(700, 500, to_wstring(_rcMapView.top), 15);

	/*if(SCENEMANAGER->check())
		_D2DRenderer->RenderText(800, 500, L"메인씬이 있다니까?", 15);
	else
		_D2DRenderer->RenderText(800, 500, L"메인씬이 없다니까?", 15);*/

	_D2DRenderer->RenderText(CAMERA->GetRelativeVector2(_dungeonTestPos).x, CAMERA->GetRelativeVector2(_dungeonTestPos).y, L"던전 입구", 25);

	if (_backGround) 
	{
		Vector2 vImage{};
			vImage.x = _backGround->GetWidth();
			vImage.y = _backGround->GetHeight();
		_backGround->Render(vImage);
	}
}

void MainScene::LoadMapFromFile(const std::wstring& mapFileName)
{
	//// 기존 타일 제거
	//for (int i = 0; i < _vTiles.size(); ++i)
	//{
	//	for (int j = 0; j < _vTiles[i].size(); ++j)
	//	{
	//		if (_vTiles[i][j] != nullptr)
	//			_vTiles[i][j]->Release();
	//		SAFE_DELETE(_vTiles[i][j]);
	//	}
	//	_vTiles[i].clear();
	//}
	//_vTiles.clear();

	// 맵 파일 열기
	HANDLE file = CreateFile(mapFileName.c_str(), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//if (file == INVALID_HANDLE_VALUE) return;
	if (file == INVALID_HANDLE_VALUE)
	{
		DWORD error = GetLastError();  // 실패 이유 코드 가져오기

		wchar_t message[512];
		wsprintf(message, L"CreateFile 실패\n파일명: %s\n에러 코드: %d", mapFileName.c_str(), error);
		MessageBox(NULL, message, L"파일 열기 실패", MB_OK);
		return;
	}

	DWORD read = 0;

	ReadFile(file, &_ptMapSize.x, sizeof(int), &read, NULL);
	ReadFile(file, &_ptMapSize.y, sizeof(int), &read, NULL);

	for (int i = 0; i < _ptMapSize.y; ++i)
	{
		std::vector<Tile*> v;
		for (int j = 0; j < _ptMapSize.x; ++j)
		{
			Tile* t = new Tile();

			int terX, terY, terN;
			int objX, objY, objN;

			ReadFile(file, &terX, sizeof(int), &read, NULL);
			ReadFile(file, &terY, sizeof(int), &read, NULL);
			ReadFile(file, &terN, sizeof(int), &read, NULL);
			ReadFile(file, &objX, sizeof(int), &read, NULL);
			ReadFile(file, &objY, sizeof(int), &read, NULL);
			ReadFile(file, &objN, sizeof(int), &read, NULL);

			t->SetTiles(terX, terY, terN, objX, objY, objN);
			t->SetTileRc(j * TILE_SIZE, i * TILE_SIZE);
			v.push_back(t);
		}
		_vTiles.push_back(v);
	}

	CloseHandle(file);

	// 맵 파일명에서 이름 추출
	size_t lastSlash = mapFileName.find_last_of(L"\\/");
	std::wstring name = (lastSlash != std::wstring::npos)
		? mapFileName.substr(lastSlash + 1)
		: mapFileName;

	// ../Enemy/ + mapFileName로 적 파일 열기
	std::wstring enemyFilePath = L"../Enemy/" + name;

	file = CreateFile(enemyFilePath.c_str(), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
		return;

	int maxNum = 0;
	ReadFile(file, &maxNum, sizeof(int), &read, NULL);

	/*_vEnemies.clear();

	for (int i = 0; i < maxNum; ++i)
	{
		int tileX, tileY, frameX, frameY, enemyType;

		ReadFile(file, &tileX, sizeof(int), &read, NULL);
		ReadFile(file, &tileY, sizeof(int), &read, NULL);
		ReadFile(file, &frameX, sizeof(int), &read, NULL);
		ReadFile(file, &frameY, sizeof(int), &read, NULL);
		ReadFile(file, &enemyType, sizeof(int), &read, NULL);

		MapTool_EnemyInfo enemy = { tileX, tileY, frameX, frameY, enemyType };
		_vEnemies.push_back(enemy);
	}*/

	CloseHandle(file);
}

Tile* MainScene::GetTile(int x, int y)
{
	if (y < 0 || y >= _vTiles.size()) return nullptr;
	if (x < 0 || x >= _vTiles[y].size()) return nullptr;
	return _vTiles[y][x];
}
