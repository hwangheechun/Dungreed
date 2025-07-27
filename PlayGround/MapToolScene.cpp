#include "stdafx.h"
#include "MapToolScene.h"
#include "Button.h"
#include <commdlg.h>

HRESULT MapToolScene::Init()
{
	IMAGEMANAGER->AddFrameImage(L"saveload", L"Resources/button_saveload.png", 2, 2);
	IMAGEMANAGER->AddImage(L"tile null", L"Resources/tilenull.png");

	IMAGEMANAGER->AddImage(L"terrain1 s", L"Resources/Map/TownTile.png");
	IMAGEMANAGER->AddFrameImage(L"terrain1", L"Resources/Map/TownTile.png",10, 10);
	/*IMAGEMANAGER->AddImage(L"object1 s", L"Resources/object1_s.png");
	IMAGEMANAGER->AddFrameImage(L"object1", L"Resources/object1.png", 16, 18);
	IMAGEMANAGER->AddImage(L"object4 s", L"Resources/object4_s.png");
	IMAGEMANAGER->AddFrameImage(L"object4", L"Resources/object4.png", 16, 18);
	IMAGEMANAGER->AddImage(L"enemy tile s", L"Resources/tile_enemy_s.png");
	IMAGEMANAGER->AddFrameImage(L"enemy tile", L"Resources/tile_enemy.png", 16, 18);*/
	IMAGEMANAGER->AddFrameImage(L"type tile", L"Resources/typetile.png", 1, 2);

	CAMERA->SetCameraMode(CameraState::NONE);
	CAMERA->SetPosition(Vector2(0, 0));

	Button* save = new Button(L"saveload", Vector2(WINSIZEX / 2 - 100, 66), 0, 0, 1, 0, bind(&MapToolScene::SaveMap, this));
	save->SetName(L"save button");
	save->SetActive(true);

	Button* load = new Button(L"saveload", Vector2(WINSIZEX / 2 + 100, 66), 0, 1, 1, 1, bind(&MapToolScene::LoadMap, this));
	load->SetName(L"load button");
	load->SetActive(true);

	OBJECTMANAGER->AddObject(ObjectType::UI, save);
	OBJECTMANAGER->AddObject(ObjectType::UI, load);

	_ptMapSize.x = 50;
	_ptMapSize.y = 25;

	_rcMapView = RectMakePivot(Vector2(10, 10), Vector2((int)_ptMapSize.x * TILE_SIZE, (int)_ptMapSize.y * TILE_SIZE), Pivot::LeftTop);
	_rcSampleView = RectMakePivot(Vector2(WINSIZEX - 600, 100), Vector2(512, 576), Pivot::LeftTop);

	_rcEditMode[0] = RectMakePivot(Vector2(_rcSampleView.left, _rcSampleView.bottom) + Vector2(0, 0), Vector2(50, 50), Pivot::LeftTop);
	_rcEditMode[1] = RectMakePivot(Vector2(_rcSampleView.left, _rcSampleView.bottom) + Vector2(70, 0), Vector2(50, 50), Pivot::LeftTop);
	_rcEditMode[2] = RectMakePivot(Vector2(_rcSampleView.left, _rcSampleView.bottom) + Vector2(140, 0), Vector2(50, 50), Pivot::LeftTop);
	_rcEditMode[3] = RectMakePivot(Vector2(_rcSampleView.left, _rcSampleView.bottom) + Vector2(210, 0), Vector2(50, 50), Pivot::LeftTop);

	_rcPenMode[0] = RectMakePivot(Vector2(_rcSampleView.left, _rcSampleView.bottom) + Vector2(0, 70), Vector2(50, 50), Pivot::LeftTop);
	_rcPenMode[1] = RectMakePivot(Vector2(_rcSampleView.left, _rcSampleView.bottom) + Vector2(70, 70), Vector2(50, 50), Pivot::LeftTop);

	_rcNonBlocked = RectMakePivot(Vector2(_rcSampleView.left, _rcSampleView.top) + Vector2(100, 100), Vector2(100, 50), Pivot::LeftTop);
	_rcBlocked = RectMakePivot(Vector2(_rcSampleView.left, _rcSampleView.top) + Vector2(100, 170), Vector2(100, 50), Pivot::LeftTop);

	_imgTerrainSample = IMAGEMANAGER->FindImage(L"terrain1 s");
	_imgTerrain = IMAGEMANAGER->FindImage(L"terrain1");
	/*_imgObjectSample = IMAGEMANAGER->FindImage(L"object1 s");
	_imgObject = IMAGEMANAGER->FindImage(L"object1");
	_imgEnemySample = IMAGEMANAGER->FindImage(L"enemy tile s");
	_imgEnemy = IMAGEMANAGER->FindImage(L"enemy tile");*/
	_imgType = IMAGEMANAGER->FindImage(L"type tile");

	_ptSampleStart.x = _ptSampleStart.y = -1;
	_ptDrawStart.x = _ptDrawStart.y = -1;

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

	for (int i = 0; i < SAMPLE_TILE_Y; ++i)
	{
		vector<Tile*> v;
		for (int j = 0; j < SAMPLE_TILE_X; ++j)
		{
			Tile* t = new Tile();
			t->SetTileRc(j * SAMPLE_TILE_SIZE, i * SAMPLE_TILE_SIZE);
			t->SetRect(RectMakePivot(Vector2(_rcSampleView.left + j * SAMPLE_TILE_SIZE,
				_rcSampleView.top + i * SAMPLE_TILE_SIZE), Vector2(SAMPLE_TILE_SIZE, SAMPLE_TILE_SIZE), Pivot::LeftTop));
			v.push_back(t);
		}
		_vSampleTiles.push_back(v);
	}

	//LoadMap();
	//LoadMapFromFile(L"C:\\Users\\heech\\OneDrive\\Desktop\\Dungreed\\Resources\\Map\\MapData\\1.map");

	return S_OK;
}

void MapToolScene::Release()
{
}

void MapToolScene::Update()
{
	//마우스 위치 맞추기
	_ptDrawStart.x = (_ptMouse.x - _rcMapView.left) / TILE_SIZE;
	_ptDrawStart.y = (_ptMouse.y - _rcMapView.top) / TILE_SIZE;

	if (_ptDrawStart.x < 0) _ptDrawStart.x = 0;
	else if (_ptDrawStart.x >= MAX_TILE_X) _ptDrawStart.x = MAX_TILE_X - 1;
	else if (_ptDrawStart.x >= _ptMapSize.x)
		_ptDrawStart.x = _ptMapSize.x - 1;

	if (_ptDrawStart.y < 0) _ptDrawStart.y = 0;
	else if (_ptDrawStart.y >= MAX_TILE_Y) _ptDrawStart.y = MAX_TILE_Y - 1;
	else if (_ptDrawStart.y >= _ptMapSize.y)
		_ptDrawStart.y = _ptMapSize.y - 1;

	if (RECT rc = _rcSampleView.GetRect(); PtInRect(&rc, _ptMouse))
	{
		if (_eEditMode != EditMode::Type) {
			for (int i = 0; i < SAMPLE_TILE_Y; ++i)
			{
				for (int j = 0; j < SAMPLE_TILE_X; ++j)
				{
					RECT rc2 = _vSampleTiles[i][j]->GetRect().GetRect();
					if (PtInRect(&rc2, _ptMouse))
					{
						if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
						{
							_ptSampleStart.x = j;
							_ptSampleStart.y = i;
						}
					}
				}
			}
		}
		else {
			if (RECT rc = _rcNonBlocked.GetRect(); PtInRect(&rc, _ptMouse)) {
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					_ePenMode = PenMode::Plus;
				}
			}
			else if (RECT rc = _rcBlocked.GetRect(); PtInRect(&rc, _ptMouse)) {
				if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
				{
					_ePenMode = PenMode::Minus;
				}
			}
		}

		if (_ptSampleStart.x != -1 && _ptSampleStart.y != -1)	
		{
			_ePenMode = PenMode::Plus;
			_rcSampleSelect = RectMakePivot(_vSampleTiles[_ptSampleStart.y][_ptSampleStart.x]->GetRect().GetCenter(),
				Vector2(SAMPLE_TILE_SIZE, SAMPLE_TILE_SIZE), Pivot::Center);
		}
	}
	else if (RECT rc = _rcMapView.GetRect(); PtInRect(&rc, _ptMouse)) {
		if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
		{
			do {
				if (_ptDrawStart.x == -1 || _ptDrawStart.y == -1)
					break;

				if (_ePenMode == PenMode::Plus) {
					switch (_eEditMode)
					{
					case EditMode::Terrain:
						_vTiles[_ptDrawStart.y][_ptDrawStart.x]->SetTerrainImageNum(_nTerrainNum);
						_vTiles[_ptDrawStart.y][_ptDrawStart.x]->SetTerrainX(_ptSampleStart.x);
						_vTiles[_ptDrawStart.y][_ptDrawStart.x]->SetTerrainY(_ptSampleStart.y);
						break;
					case EditMode::Object:
						_vTiles[_ptDrawStart.y][_ptDrawStart.x]->SetObjectImageNum(_nTerrainNum);
						_vTiles[_ptDrawStart.y][_ptDrawStart.x]->SetObjectX(_ptSampleStart.x);
						_vTiles[_ptDrawStart.y][_ptDrawStart.x]->SetObjectY(_ptSampleStart.y);
						break;
					case EditMode::Enemy:
						MapTool_EnemyInfo enemy;
						enemy.tileX = _ptDrawStart.x;
						enemy.tileY = _ptDrawStart.y;
						enemy.frameX = _ptSampleStart.x;
						enemy.frameY = _ptSampleStart.y;
						enemy.enemyType = _ptSampleStart.x;
						_vEnemies.push_back(enemy);
						break;
					case EditMode::Type:
						_vTiles[_ptDrawStart.y][_ptDrawStart.x]->SetBlocked(false);
						break;
					case EditMode::End:
						break;
					default:
						break;
					}
				}
				else {
					switch (_eEditMode)
					{
					case EditMode::Terrain:
						_vTiles[_ptDrawStart.y][_ptDrawStart.x]->SetTerrainImageNum(0);
						_vTiles[_ptDrawStart.y][_ptDrawStart.x]->SetTerrainX(-1);
						_vTiles[_ptDrawStart.y][_ptDrawStart.x]->SetTerrainY(-1);
						break;
					case EditMode::Object:
						_vTiles[_ptDrawStart.y][_ptDrawStart.x]->SetObjectImageNum(0);
						_vTiles[_ptDrawStart.y][_ptDrawStart.x]->SetObjectX(-1);
						_vTiles[_ptDrawStart.y][_ptDrawStart.x]->SetObjectY(-1);
						break;
					case EditMode::Enemy:
						break;
					case EditMode::Type:
						_vTiles[_ptDrawStart.y][_ptDrawStart.x]->SetBlocked(true);
						break;
					case EditMode::End:
						break;
					default:
						break;
					}
				}
			} while (false);
		}
	}

	if (RECT rc = _rcPenMode[0].GetRect();  PtInRect(&rc, _ptMouse)) {
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			_ePenMode = PenMode::Plus;
		}
	}

	if (RECT rc = _rcPenMode[1].GetRect(); PtInRect(&rc, _ptMouse)) {
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			_ePenMode = PenMode::Minus;
			_ptSampleStart.x = -1;
			_ptSampleStart.y = -1;
			_rcSampleSelect = FloatRect();
		}
	}

	if (RECT rc = _rcEditMode[0].GetRect();  PtInRect(&rc, _ptMouse)) {
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			_eEditMode = EditMode::Terrain;

			_ptSampleStart.x = -1;
			_ptSampleStart.y = -1;
			_rcSampleSelect = FloatRect();
		}
	}

	if (RECT rc = _rcEditMode[1].GetRect();  PtInRect(&rc, _ptMouse)) {
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			_eEditMode = EditMode::Object;

			_ptSampleStart.x = -1;
			_ptSampleStart.y = -1;
			_rcSampleSelect = FloatRect();
		}
	}

	if (RECT rc = _rcEditMode[2].GetRect();  PtInRect(&rc, _ptMouse)) {
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			_eEditMode = EditMode::Enemy;

			_ptSampleStart.x = -1;
			_ptSampleStart.y = -1;
			_rcSampleSelect = FloatRect();
		}
	}

	if (RECT rc = _rcEditMode[3].GetRect();  PtInRect(&rc, _ptMouse)) {
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			_eEditMode = EditMode::Type;

			_ptSampleStart.x = -1;
			_ptSampleStart.y = -1;
			_rcSampleSelect = FloatRect();
		}
	}

	//if (KEYMANAGER->IsStayKeyDown(0x41))	//A_좌로 이동
	//{
	//	CAMERA->Move(Vector2(-1, 0));
	//}
	//else if (KEYMANAGER->IsStayKeyDown(0x44))	//D_우로 이동
	//{
	//	CAMERA->Move(Vector2(1, 0));
	//}
}

void MapToolScene::Render()
{
	

	for (int i = 0; i < _vTiles.size(); ++i)
	{
		for (int j = 0; j < _vTiles[i].size(); ++j)
		{
			// FIXME : 실제 타일이 가지고 있는 Type의 타일 / 오브젝트로 출력 ... _vTiles[i][j]->GetTerrainImageNum();
			auto ptCenter = _vTiles[i][j]->GetRect().GetCenter();
			if (_vTiles[i][j]->GetTerrainX() == -1 || _vTiles[i][j]->GetTerrainY() == -1)
				IMAGEMANAGER->FindImage(L"tile null")->Render(Vector2(ptCenter.x, ptCenter.y) + Vector2(_rcMapView.left, _rcMapView.top));
			else
				_imgTerrain->FrameRender(ptCenter + Vector2(_rcMapView.left, _rcMapView.top), _vTiles[i][j]->GetTerrainX(), _vTiles[i][j]->GetTerrainY());

			/*if (_vTiles[i][j]->GetObjectX() >= 0 && _vTiles[i][j]->GetObjectX() >= 0)
				_imgObject->FrameRender(ptCenter + Vector2(_rcMapView.left, _rcMapView.top), _vTiles[i][j]->GetObjectX(), _vTiles[i][j]->GetObjectY());*/

			if (_eEditMode == EditMode::Type)
				_imgType->FrameRender(ptCenter + Vector2(_rcMapView.left, _rcMapView.top), _vTiles[i][j]->GetBlocked() ? 1 : 0, 0);
		}
	}

	{
		Image* imgRender = nullptr;
		switch (_eEditMode)
		{
		case EditMode::Terrain:
			imgRender = _imgTerrainSample;
			break;
		case EditMode::Object:
			imgRender = _imgObjectSample;
			break;
		case EditMode::Enemy:
			imgRender = _imgEnemySample;
			break;
		case EditMode::Type:
			D2DRenderer::GetInstance()->DrawRectangle(_rcNonBlocked, D2DRenderer::DefaultBrush::Green, 2.0f);
			D2DRenderer::GetInstance()->DrawRectangle(_rcBlocked, D2DRenderer::DefaultBrush::Red, 2.0f);
			break;
		case EditMode::End:
			break;
		default:
			break;
		}

		if (imgRender)
			imgRender->Render(Vector2(imgRender->GetWidth() / 2 + _rcSampleView.left, imgRender->GetHeight() / 2 + _rcSampleView.top));
	}

	/*_D2DRenderer->RenderText(50, 500, L"카메라:" + to_wstring((int)CAMERA->GetrcTop().x), 15);
	_D2DRenderer->RenderText(50, 550, L"카메라:" + to_wstring((int)CAMERA->GetrcTop().y), 15);
	_D2DRenderer->RenderText(50, 600, L"카메라:" + to_wstring((int)CAMERA->GetrcBottom().x), 15);
	_D2DRenderer->RenderText(50, 650, L"카메라:" + to_wstring((int)CAMERA->GetrcBottom().y), 15);
	_D2DRenderer->RenderText(50, 675, L"카메라 중앙:" + to_wstring((int)CAMERA->GetPosition().x), 15);
	_D2DRenderer->RenderText(250, 675, to_wstring((int)CAMERA->GetPosition().y), 15);*/

	for (int i = 0; i < _vEnemies.size(); ++i) {
		_imgEnemy->FrameRender(Vector2(
			_vTiles[_vEnemies[i].tileY][_vEnemies[i].tileX]->GetRect().GetCenter()) + Vector2(_rcMapView.left, _rcMapView.top),
			_vEnemies[i].frameX, _vEnemies[i].frameY);
	}

	D2DRenderer::GetInstance()->DrawRectangle(_rcSampleSelect, D2DRenderer::DefaultBrush::Green, 2.0f);
	D2DRenderer::GetInstance()->DrawRectangle(_rcSampleView, D2DRenderer::DefaultBrush::Green, 2.0f);
	D2DRenderer::GetInstance()->DrawRectangle(_rcMapView, D2DRenderer::DefaultBrush::Green, 2.0f);

	D2DRenderer::GetInstance()->DrawRectangle(_rcEditMode[0], D2DRenderer::DefaultBrush::Black, 2.0f);
	D2DRenderer::GetInstance()->DrawRectangle(_rcEditMode[1], D2DRenderer::DefaultBrush::Black, 2.0f);
	D2DRenderer::GetInstance()->DrawRectangle(_rcEditMode[2], D2DRenderer::DefaultBrush::Black, 2.0f);
	D2DRenderer::GetInstance()->DrawRectangle(_rcEditMode[3], D2DRenderer::DefaultBrush::Black, 2.0f);

	D2DRenderer::GetInstance()->DrawRectangle(_rcPenMode[0], D2DRenderer::DefaultBrush::Blue, 2.0f);
	D2DRenderer::GetInstance()->DrawRectangle(_rcPenMode[1], D2DRenderer::DefaultBrush::Red, 2.0f);

	if (_ePenMode == PenMode::Plus && _ptSampleStart.x != -1 && _ptSampleStart.y != -1 && _ptDrawStart.x != -1 && _ptDrawStart.y != -1) {
		auto rc = _vTiles[_ptDrawStart.y][_ptDrawStart.x]->GetRect();
		Image* imgRender = nullptr;

		switch (_eEditMode)
		{
		case EditMode::Terrain:
			imgRender = _imgTerrain;
			break;
		case EditMode::Object:
			imgRender = _imgObject;
			break;
		case EditMode::Enemy:
			imgRender = _imgEnemy;
			break;
		case EditMode::Type:
			break;
		case EditMode::End:
			break;
		default:
			break;
		}
		if (imgRender) {
			imgRender->SetAlpha(0.7f);
			imgRender->FrameRender(rc.GetCenter() + Vector2(_rcMapView.left, _rcMapView.top), _ptSampleStart.x, _ptSampleStart.y);
		}
	}
}

void MapToolScene::SaveMap()
{
	ShowCursor(true);
	OPENFILENAME ofn = { 0 };
	wchar_t filePathSize[1028] = L"";

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePathSize;
	ofn.nMaxFile = sizeof(filePathSize);
	ofn.nFilterIndex = true;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrDefExt = L"map";
	ofn.lpstrFilter = (L"타일맵 파일(*.map)");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetSaveFileName(&ofn) == FALSE) return;

	HANDLE file;
	DWORD write;

	file = CreateFile(filePathSize, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// 맵 사이즈부터 저장
	WriteFile(file, &_ptMapSize.x, sizeof(int), &write, NULL);
	WriteFile(file, &_ptMapSize.y, sizeof(int), &write, NULL);

	for (int i = 0; i < _ptMapSize.y; ++i)
	{
		for (int j = 0; j < _ptMapSize.x; ++j)
		{
			int terX = _vTiles[i][j]->GetTerrainX();
			int terY = _vTiles[i][j]->GetTerrainY();
			int terN = _vTiles[i][j]->GetTerrainImageNum();
			int objX = _vTiles[i][j]->GetObjectX();
			int objY = _vTiles[i][j]->GetObjectY();
			int objN = _vTiles[i][j]->GetObjectImageNum();
			bool isBlocked = _vTiles[i][j]->_blocked; // Blocked 정보 추출

			WriteFile(file, &terX, sizeof(int), &write, NULL);
			WriteFile(file, &terY, sizeof(int), &write, NULL);
			WriteFile(file, &terN, sizeof(int), &write, NULL);
			WriteFile(file, &objX, sizeof(int), &write, NULL);
			WriteFile(file, &objY, sizeof(int), &write, NULL);
			WriteFile(file, &objN, sizeof(int), &write, NULL);
			WriteFile(file, &isBlocked, sizeof(bool), &write, NULL); // ← 이 한 줄 추가
		}
	}

	wchar_t temp[1028];
	wcsncpy_s(temp, wcslen(ofn.lpstrFile) + 1, ofn.lpstrFile, wcslen(ofn.lpstrFile));
	wchar_t* context = NULL;
	wchar_t* token = wcstok_s(temp, L"\\", &context);
	while (wcslen(context))
	{
		token = wcstok_s(NULL, L"\\", &context);
	}

	CloseHandle(file);

	wstring name = token;

	// enemy 저장
	wstring s = L"../enemy/";
	s += name;

	file = CreateFile(s.c_str(), GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	int size = _vEnemies.size();
	WriteFile(file, &size, sizeof(int), &write, NULL);

	for (int i = 0; i < _vEnemies.size(); ++i)
	{
		int tileX = _vEnemies[i].tileX;
		int tileY = _vEnemies[i].tileY;
		int frameX = _vEnemies[i].frameX;
		int frameY = _vEnemies[i].frameY;
		int enemyType = _vEnemies[i].enemyType;

		WriteFile(file, &tileX, sizeof(int), &write, NULL);
		WriteFile(file, &tileY, sizeof(int), &write, NULL);
		WriteFile(file, &frameX, sizeof(int), &write, NULL);
		WriteFile(file, &frameY, sizeof(int), &write, NULL);
		WriteFile(file, &enemyType, sizeof(int), &write, NULL);
	}

	CloseHandle(file);
	ShowCursor(false);
}

void MapToolScene::LoadMap()
{
	OPENFILENAME ofn = { 0 };
	wchar_t filePathSize[1028] = L"";
	wchar_t* context = NULL;

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePathSize;
	ofn.nMaxFile = sizeof(filePathSize);
	ofn.nFilterIndex = true;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFilter = (L"타일맵 파일(*.map)");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == FALSE) return;

	for (int i = 0; i < _vTiles.size(); ++i)
	{
		for (int j = 0; j < _vTiles[i].size(); ++j)
		{
			if (_vTiles[i][j] != nullptr)
				_vTiles[i][j]->Release();
			SAFE_DELETE(_vTiles[i][j]);
		}
		_vTiles[i].clear();
	}
	_vTiles.clear();

	HANDLE file;
	DWORD read;

	file = CreateFile(filePathSize, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, &_ptMapSize.x, sizeof(int), &read, NULL);
	ReadFile(file, &_ptMapSize.y, sizeof(int), &read, NULL);

	for (int i = 0; i < _ptMapSize.y; ++i)
	{
		vector<Tile*> v;
		for (int j = 0; j < _ptMapSize.x; ++j)
		{
			Tile* t = new Tile();

			int terX;
			int terY;
			int terN;
			int objX;
			int objY;
			int objN;

			ReadFile(file, &terX, sizeof(int), &read, NULL);
			ReadFile(file, &terY, sizeof(int), &read, NULL);
			ReadFile(file, &terN, sizeof(int), &read, NULL);
			ReadFile(file, &objX, sizeof(int), &read, NULL);
			ReadFile(file, &objY, sizeof(int), &read, NULL);
			ReadFile(file, &objN, sizeof(int), &read, NULL);

			//새로 추가한 내용(7.19)
			bool isBlocked;
			ReadFile(file, &isBlocked, sizeof(bool), &read, NULL);
			t->SetBlocked(isBlocked); // 타일에 반영

			t->SetTiles(terX, terY, terN, objX, objY, objN);
			t->SetTileRc(j * TILE_SIZE, i * TILE_SIZE);
			v.push_back(t);
		}
		_vTiles.push_back(v);
	}

	wchar_t temp[1028];
	wcsncpy_s(temp, wcslen(ofn.lpstrFile) + 1, ofn.lpstrFile, wcslen(ofn.lpstrFile));

	context = NULL;
	wchar_t* token = wcstok_s(temp, L"\\", &context);
	while (wcslen(context))
	{
		token = wcstok_s(NULL, L"\\", &context);
	}

	CloseHandle(file);

	wstring name = token;

	char str2[500];

	wstring s = L"../Enemy/";
	s += name;

	file = CreateFile(s.c_str(), GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (file == INVALID_HANDLE_VALUE)
		return;

	int maxNum = 0;
	ReadFile(file, &maxNum, sizeof(int), &read, NULL);

	_vEnemies.clear();

	for (int i = 0; i < maxNum; ++i)
	{
		int tileX;
		int tileY;
		int frameX;
		int frameY;
		int enemyType;

		ReadFile(file, &tileX, sizeof(int), &read, NULL);
		ReadFile(file, &tileY, sizeof(int), &read, NULL);
		ReadFile(file, &frameX, sizeof(int), &read, NULL);
		ReadFile(file, &frameY, sizeof(int), &read, NULL);
		ReadFile(file, &enemyType, sizeof(int), &read, NULL);

		MapTool_EnemyInfo enemy = { tileX, tileY, frameX, frameY, enemyType };
		_vEnemies.push_back(enemy);
	}

	CloseHandle(file);
}

void MapToolScene::LoadMapFromFile(const std::wstring& mapFileName)
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
	if (file == INVALID_HANDLE_VALUE)	//파일 열기 실패 시 체크 (7.20 추가)
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

			//새로 추가한 내용(7.19)
			bool isBlocked;
			ReadFile(file, &isBlocked, sizeof(bool), &read, NULL);
			t->SetBlocked(isBlocked);  // 또는 t->_blocked = isBlocked;

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
