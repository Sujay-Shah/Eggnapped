/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Moodie Ghaddar>
- End Header --------------------------------------------------------*/

#include <Stdafx.h>

LevelEditor::LevelEditor() :
	m_currentRoomType(""),
	m_pSelectedGO(nullptr),
	m_selectedGOname(""),
	m_indent(16),
	m_cameraMovSpeed(500.0f),
	m_roomSelectedItem(0),
	m_roomTemplateSelectedItem(0),
	m_difficulty(0),
	m_isFileNameInvalid(false),
	m_isLoadSuccess(true),
	m_isShopRoom(false),
	m_isBossRoom(false)
{
}

void LevelEditor::Initialize() {
	m_prefabStrings = TETRA_RESOURCES.GetPrefabStrings();
	for (unsigned int i = 0; i < m_prefabStrings.size(); ++i) {
		m_instanceCount.push_back(0);
	}

	RoomTemplatesInit();
	RoomInit();

	TETRA_EVENTS.Subscribe(EVENT_INPUT_MOVE, this);
}

void LevelEditor::RoomTemplatesInit() {
	std::string path = TETRA_GAME_CONFIG.RoomFilesDir() + "Templates/";
	for (auto &room : std::experimental::filesystem::directory_iterator(path)) {
		if (room.path().has_extension()) {
			std::string roomName = room.path().filename().string();
			roomName.pop_back();
			roomName.pop_back();
			roomName.pop_back();
			roomName.pop_back();
			roomName.pop_back();
			m_roomTemplatesStrings.push_back(roomName);
		}
	}
}

void LevelEditor::RoomInit() {
	std::string path = TETRA_GAME_CONFIG.RoomFilesDir();
	for (auto &room : std::experimental::filesystem::directory_iterator(path)) {
		if (room.path().has_extension()) {
			std::string roomName = room.path().filename().string();
			roomName.pop_back();
			roomName.pop_back();
			roomName.pop_back();
			roomName.pop_back();
			roomName.pop_back();
			m_roomStrings.push_back(roomName);
		}
	}
}

LevelEditor::~LevelEditor() {
	for (auto instance : m_instances) {
		delete instance.second;
	}

	m_instances.clear();
}


void LevelEditor::Update(float dt) {
	UpdateMenuBar();
	UpdatePrefabWindow();
	UpdateSceneWindow();
	UpdateInspectorWindow();

	if (!m_isPopUpOpen) {
		if (m_pCameraTransform)
			m_pCameraTransform->SetPosition(m_pCameraTransform->GetPosition() + m_cameraMoveDir*m_cameraMovSpeed*dt);

		if (TETRA_INPUT.IsKeyTriggered(SDL_SCANCODE_DELETE)) {
			DeleteInstance();
		}

		if (TETRA_INPUT.IsKeyTriggered(SDL_SCANCODE_ESCAPE) && m_pSelectedGO) {
			m_pSelectedGO = nullptr;
		}
	}

	if (m_pSelectedGO && m_pGizmoGO) {
		if (!m_pGizmoGO->m_isActive)
			m_pGizmoGO->SetActive(true);

		Transform* pSelectedGOTransform = m_pSelectedGO->GetComponent<Transform>(C_Transform);
		Transform* pGizmoGOTransform = m_pGizmoGO->GetComponent<Transform>(C_Transform);

		pGizmoGOTransform->SetPosition(pSelectedGOTransform->GetPosition());

		if (TETRA_INPUT.IsKeyTriggered(SDL_SCANCODE_F) && !m_isPopUpOpen) {
			Vector3D pos(pSelectedGOTransform->GetPosition().x, pSelectedGOTransform->GetPosition().y, m_pCameraTransform->GetPosition().z);
			m_pCameraTransform->SetPosition(pos);
		}
	}
	else if(m_pGizmoGO->m_isActive) {
		m_pGizmoGO->SetActive(false);
	}
}

void LevelEditor::UpdateMenuBar() {
	ImGui::BeginMainMenuBar();

	std::string menu_action = "";
	if (ImGui::BeginMenu("File")) {

		if (ImGui::MenuItem("New")) menu_action = "New";
		else if (ImGui::MenuItem("Save")) menu_action = "Save";
		else if (ImGui::MenuItem("Load")) menu_action = "Load";
		else if (ImGui::MenuItem("Exit to menu")) menu_action = "Exit";

		ImGui::EndMenu();
	}

	if (menu_action == "New") ImGui::OpenPopup("New");
	if (menu_action == "Save") {
		m_isFileNameInvalid = false;
		ImGui::OpenPopup("Save");
	}
	if (menu_action == "Load") ImGui::OpenPopup("Load");
	if (menu_action == "Exit") GoBackToMainMenu();


	if (ImGui::BeginPopup("New")) {
		m_isPopUpOpen = true;
		NewPopup();
		ImGui::EndPopup();
	}
	else if (ImGui::BeginPopup("Save")) {
		m_isPopUpOpen = true;
		SavePopup();
		ImGui::EndPopup();
	}
	else if (ImGui::BeginPopup("Load")) {
		m_isPopUpOpen = true;
		LoadPopup();
		ImGui::EndPopup();
	}
	else {
		m_isPopUpOpen = false;
	}

	ImGui::EndMainMenuBar();
}

void LevelEditor::UpdatePrefabWindow() {
	ImGui::Begin("Prefabs");

	for (unsigned int i = 0; i < m_prefabStrings.size(); ++i) {
		if (ImGui::Selectable(m_prefabStrings[i].c_str(), false, ImGuiSelectableFlags_AllowDoubleClick)) {
			if (ImGui::IsMouseDoubleClicked(0)) {
				m_pSelectedGO = CreateInstance(i);
				m_selectedGOname = m_instances[m_pSelectedGO]->name;
			}
		}
	}

	ImGui::End();
}

void LevelEditor::UpdateSceneWindow() {
	ImGui::Begin("Scene");

	for (auto instance : m_instances) {
		if (ImGui::Selectable(instance.second->name.c_str())) {
			m_pSelectedGO = instance.first;
			m_selectedGOname = instance.second->name;
		}
	}

	ImGui::End();
}

void LevelEditor::UpdateInspectorWindow() {
	ImGui::Begin("Inspector");

	if (m_pSelectedGO) {
		ImGui::TextColored(ImVec4(1, 1, 0, 1), (m_selectedGOname).c_str());
		ImGui::Indent(m_indent);
		Transform* pTransform = m_pSelectedGO->GetComponent<Transform>(C_Transform);
		if (pTransform) {
			if (ImGui::CollapsingHeader("Transform")) {
				ImGui::Indent(m_indent);
				if (ImGui::CollapsingHeader("Position")) {
					int x = (int)(pTransform->GetPosition().x);
					int y = (int)(pTransform->GetPosition().y);
					ImGui::InputInt("x##1", &x, 8, 64);
					ImGui::InputInt("y##1", &y, 8, 64);
					pTransform->SetPosition(Vector3D((float)x, (float)y, 0));
				}
				if (ImGui::CollapsingHeader("Scale")) {
					int x = (int)(pTransform->GetScaleX());
					int y = (int)(pTransform->GetScaleY());
					ImGui::InputInt("x##2", &x, 8, 64);
					ImGui::InputInt("y##2", &y, 8, 64);
					pTransform->SetScale((float)x, (float)y);
				}
				if (ImGui::CollapsingHeader("Rotation")) {
					int z = (int)(pTransform->GetAngleZ());
					ImGui::InputInt("z##1", &z, 5, 15);
					if (z > 360) z = 0;
					pTransform->SetAngleZ((float)z);
				}
				ImGui::Indent(-m_indent);
			}
		}

		Body* pBody = m_pSelectedGO->GetComponent<Body>(C_Body);
		if (pBody) {
			if (ImGui::CollapsingHeader("Body")) {
				ImGui::Indent(m_indent);
				if (ImGui::CollapsingHeader("Shape")) {
					ImGui::Indent(m_indent);
					if (pBody->m_pShape->type == ShapeType::ST_AABB) {
						int width = (int)pBody->GetWidth();
						int height = (int)pBody->GetHeight();
						ImGui::InputInt("width##1", &width, 8, 64);
						ImGui::InputInt("height##1", &height, 8, 64);
						pBody->OverrideShapeData((float)width, (float)height);
					}
					else if (pBody->m_pShape->type == ShapeType::ST_Circle) {
						int radius = (int)pBody->GetRadius();
						ImGui::InputInt("radius##1", &radius, 8, 64);
						pBody->OverrideShapeData((float)radius);
					}
					ImGui::Indent(-m_indent);
				}
				if (ImGui::CollapsingHeader("Offset")) {
					ImGui::Indent(m_indent);
					int x = (int)(pBody->GetPositionOffset().x);
					int y = (int)(pBody->GetPositionOffset().y);
					ImGui::InputInt("x##3", &x, 8, 64);
					ImGui::InputInt("y##3", &y, 8, 64);
					pBody->SetOffset((float)x, (float)y);
					ImGui::Indent(-m_indent);
				}
				ImGui::Indent(-m_indent);
			}
		}

		Sprite* pSprite = m_pSelectedGO->GetComponent<Sprite>(C_Sprite);
		if (pSprite) {
			if (ImGui::CollapsingHeader("Sprite")) {
				ImGui::Indent(m_indent);
				float xTiling = pSprite->TileX();
				float yTiling = pSprite->TileY();
				bool isRepeat = pSprite->Repeats();
				ImGui::InputFloat("xTiling##4", &xTiling);
				ImGui::InputFloat("yTiling##4", &yTiling);
				ImGui::Checkbox("repeats", &isRepeat);
				pSprite->SetTileX(xTiling);
				pSprite->SetTileY(yTiling);
				pSprite->SetIsRepeat(isRepeat);
				ImGui::Indent(-m_indent);
			}
		}

		GateTriggerBox* pGateTriggerBox = m_pSelectedGO->GetComponent<GateTriggerBox>(C_GateTriggerBox);
		if (pGateTriggerBox) {
			if (ImGui::CollapsingHeader("GateTriggerBox")) {
				ImGui::Indent(m_indent);

				int numberOfGates = pGateTriggerBox->GetNumberOfGates();
				ImGui::InputInt("Gates", &numberOfGates, 1, 1);
				pGateTriggerBox->SetGatePosSize(numberOfGates);
				for (int i = 0; i < numberOfGates; ++i) {
					if (ImGui::CollapsingHeader(("GatePos##" + std::to_string(i)).c_str())) {
						int x = (int)pGateTriggerBox->GetGatePos(i).x;
						int y = (int)pGateTriggerBox->GetGatePos(i).y;
						ImGui::InputInt(("x##6" + std::to_string(i)).c_str(), &x, 8, 64);
						ImGui::InputInt(("y##6" + std::to_string(i)).c_str(), &y, 8, 64);
						pGateTriggerBox->SetGatePos(i, Vector3D((float)x, (float)y, 0));
						bool isHorizontal;
						isHorizontal = pGateTriggerBox->IsHorizontal(i);
						ImGui::Checkbox(("horizontal##6" + std::to_string(i)).c_str(), &isHorizontal);
						pGateTriggerBox->SetAlignment(i, isHorizontal);
					}
				}

				ImGui::Indent(-m_indent);
			}
		}

		PointLight* pPointLight = m_pSelectedGO->GetComponent<PointLight>(C_PointLight);
		if (pPointLight) {
			if (ImGui::CollapsingHeader("PointLight")) {
				ImGui::Indent(m_indent);
				int z = (int)pPointLight->GetOffset().z;
				Color _c = pPointLight->GetColor();
				Vector3D c = Vector3D((float)_c.r / 255, (float)_c.g / 255, (float)_c.b / 255);
				float fallOffA = pPointLight->LightA();
				float fallOffB = pPointLight->LightB();
				ImGui::SliderFloat("fallOffA##4", &fallOffA, -1, 0);
				ImGui::SliderFloat("fallOffB##4", &fallOffB, 0, 1);
				ImGui::InputInt("Z offset##4", &(int)z);
				if (ImGui::CollapsingHeader("Color")) {
					float r = c.x;
					float g = c.y;
					float b = c.z;
					ImGui::InputFloat("r##1", &r);
					ImGui::InputFloat("g##1", &g);
					ImGui::InputFloat("b##1", &b);
					pPointLight->SetColor(Vector3D(r, g, b));
				}

				pPointLight->SetOffset(Vector3D(0, 0, (float)z));
				pPointLight->SetFallOff(fallOffA, fallOffB);
			}
		}
	}

	ImGui::End();
}

void LevelEditor::GoBackToMainMenu() {
	// This is hard coded.... Change later

	for (auto instance : m_instances) {
		delete instance.second;
	}

	m_instances.clear();
	TETRA_RENDERER.DisableWindowsCursor();
	TETRA_LEVELS.ChangeLevel(1);
}

void LevelEditor::NewPopup() {
	ImGui::TextColored(ImVec4(1,1,0,1),"Select Room Type: ");
	ImGui::ListBox("##RoomType", &m_roomTemplateSelectedItem, VectorOfStringGetter, static_cast<void*>(&m_roomTemplatesStrings), (int)m_roomTemplatesStrings.size());

	if (ImGui::Button("OK")) {
		if (m_instances.size() != 0) ClearScene();
		if (!LoadJsonFile(m_roomTemplatesStrings[m_roomTemplateSelectedItem], true)) {
			std::cout << "ERROR LOADING FILE" << std::endl;
			assert(0);
		}
		ImGui::CloseCurrentPopup();
	}

	ImGui::SameLine();

	if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();

	ImGui::TextColored(ImVec4(1, 0, 0, 1),"OK will clear any unsaved changes");
}

void LevelEditor::SavePopup() {
	if (m_instances.size() == 0) {
		ImGui::TextColored(ImVec4(1, 0, 0, 1), "SCENE IS EMPTY!");
		if (ImGui::Button("OK")) ImGui::CloseCurrentPopup();
	}
	else {
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "File name: ");
		ImGui::InputText("##FileName", m_fileName, IM_ARRAYSIZE(m_fileName));
		ImGui::InputInt("Difficulty", &m_difficulty, 1, 2);
		ImGui::Checkbox("isBossRoom", &m_isBossRoom);
		ImGui::Checkbox("isShopRoom", &m_isShopRoom);
		if (ImGui::Button("Save")) {
			if (ValidateFileName()) {
				std::string fileName;
				SetFileName(fileName);
				SaveJsonFile(fileName);
				ImGui::CloseCurrentPopup();
			}
			else
				m_isFileNameInvalid = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();
		if (m_isFileNameInvalid) 
			ImGui::TextColored(ImVec4(1, 0, 0, 1), "INVALID FILE NAME");
	}
}

void LevelEditor::LoadPopup() {
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Select File to Load: ");
	ImGui::ListBox("##RoomType", &m_roomSelectedItem, VectorOfStringGetter, static_cast<void*>(&m_roomStrings), (int)m_roomStrings.size());

	if (ImGui::Button("Load")) {
		if (m_instances.size() != 0) ClearScene();
		if (!LoadJsonFile(m_roomStrings[m_roomSelectedItem], false)) {
			std::cout << "ERROR LOADING FILE" << std::endl;
			assert(0);
		}
		ImGui::CloseCurrentPopup();
	}

	ImGui::SameLine();

	if (ImGui::Button("Cancel")) ImGui::CloseCurrentPopup();
	ImGui::TextColored(ImVec4(1, 0, 0, 1), "Loading will clear any unsaved changes");
}

bool LevelEditor::ValidateFileName() {
	int count = 0;
	for (int i = 0; i < fileNameSize; ++i) {
		if (m_fileName[i] != '\0')
			++count;
		else
			break;
	}

	if (count == 0 || count >= fileNameSize - 1)
		return false;
	else
		return true;
}

void LevelEditor::SetFileName(std::string& name) {
	name = m_fileName;
}

void LevelEditor::ClearScene() {
	for (auto instance : m_instances) {
		instance.first->Destroy();
		--m_instanceCount[instance.second->index];
		delete instance.second;
	}

	m_instances.clear();
}

void LevelEditor::DeleteInstance() {
	if (!m_pSelectedGO) return;

	m_pSelectedGO->Destroy();
	std::unordered_map<GameObject*, ObjectInstance*>::iterator it = m_instances.find(m_pSelectedGO);
	--m_instanceCount[it->second->index];
	delete (it->second);
	m_instances.erase(it);
	m_pSelectedGO = nullptr;
}

bool VectorOfStringGetter(void* data, int n, const char** out_text)
{
	std::vector<std::string>* v = static_cast<std::vector<std::string>*>(data);
	*out_text = (*v)[n].c_str();
	return true;
}

void LevelEditor::HandleEvent(Event* pEvent) {
	if (pEvent->Type() == EVENT_OnLevelInitialized) {
		GameObject* pGO = TETRA_GAME_OBJECTS.GetPrimaryCamera();
		if(pGO)
			m_pCameraTransform = pGO->GetComponent<Transform>(C_Transform);

		if (TETRA_LEVELS.GetCurrentLevel() == 0) {
			m_pGizmoGO = TETRA_GAME_OBJECTS.CreateGameObject(m_gizmoObject);
			m_pGizmoGO->SetActive(false);
		}
	}
	else if (pEvent->Type() == EVENT_INPUT_MOVE) {
		InputAxisData* pData = pEvent->Data<InputAxisData>();
		m_cameraMoveDir = pData->m_dir;
	}
}

bool LevelEditor::LoadJsonFile(std::string room, bool isTemplate) {
	if (isTemplate) {
		room = "Templates/" + room;
		ClearFileName();
	}
	else {
		ClearFileName();
		for (unsigned int i = 0; i < room.size(); ++i) {
			m_fileName[i] = room[i];
		}
	}

	std::string path = TETRA_GAME_CONFIG.RoomFilesDir() + room + ".json";
	json j = OpenJsonFile(path);
	if (j == 0) return false;

	int gameObjectSize = j["GAME_OBJECTS"].size();
	for (int i = 0; i < gameObjectSize; i++) {
		int prefabNumber = -1;
		for (unsigned int k = 0; k < m_prefabStrings.size(); ++k) {
			if (j["GAME_OBJECTS"][i]["prefab"] == m_prefabStrings[k]) {
				prefabNumber = k;
			}
		}

		if (prefabNumber >= 0) {
			GameObject* pGO = CreateInstance(prefabNumber);
			if (pGO) {
				pGO->OverrideComponents(j["GAME_OBJECTS"][i]);
			}
		}
	}

	m_currentRoomType = ValueExists(j, "ROOM_CONNECTION_TYPE") ? ParseString(j, "ROOM_CONNECTION_TYPE") : "";
	m_difficulty = ValueExists(j, "DIFFICULTY") ? ParseInt(j, "DIFFICULTY") : 0;
	m_isBossRoom = ValueExists(j, "BOSS_ROOM") ? ParseBool(j, "BOSS_ROOM") : false;
	m_isShopRoom = ValueExists(j, "SHOP_ROOM") ? ParseBool(j, "SHOP_ROOM") : false;
	m_pSelectedGO = nullptr;
	return true;
}

void LevelEditor::ClearFileName() {
	for (int i = 0; i < fileNameSize; ++i) {
		m_fileName[i] = '\0';
	}
}

void LevelEditor::SaveJsonFile(std::string fileName) {
	ofstream file;
	file.open((TETRA_GAME_CONFIG.RoomFilesDir() + fileName + ".json"));
	if (!file.is_open()) {
		printf("Something went wrong while opening file\n");
		return;
	}

	file << "{" << endl;
	file << "	\"ROOM_CONNECTION_TYPE\": " << "\"" << m_currentRoomType << "\"," << endl;
	file << "	\"DIFFICULTY\": " << m_difficulty << "," << endl;
	file << "	\"BOSS_ROOM\": ";
	if (m_isBossRoom)
		file << "true," << endl;
	else 
		file << "false," << endl;

	file << "	\"SHOP_ROOM\": ";
	if (m_isShopRoom)
		file << "true," << endl;
	else
		file << "false," << endl;

	file << "	\"GAME_OBJECTS\": [" << endl;

	std::unordered_map<GameObject*, ObjectInstance*>::iterator it = m_instances.begin();
	while(it != m_instances.end()) {
		file << "		{" << endl;
		
		file << "			\"prefab\": " << "\"" << m_prefabStrings[it->second->index] << "\"," << endl;
		Transform* pTransform = it->first->GetComponent<Transform>(C_Transform);
		Body* pBody = it->first->GetComponent<Body>(C_Body);
		Sprite* pSprite = it->first->GetComponent<Sprite>(C_Sprite);
		GateTriggerBox* pTriggerBox = it->first->GetComponent<GateTriggerBox>(C_GateTriggerBox);
		if (pTransform) {
			file << "			\"position\": {" << endl;
			file << "				\"x\": " << std::to_string(pTransform->GetPosition().x) << "," << endl;
			file << "				\"y\": " << std::to_string(pTransform->GetPosition().y) << endl;
			file << "			}," << endl;
			file << "			\"scale\": {" << endl;
			file << "				\"x\": " << std::to_string(pTransform->GetScaleX()) << "," << endl;
			file << "				\"y\": " << std::to_string(pTransform->GetScaleY()) << endl;
			file << "			}," << endl;
			file << "			\"rotation\": {" << endl;
			file << "				\"z\": " << std::to_string(pTransform->GetAngleZ()) << endl;
			file << "			}";
		}

		if (pBody) {
			file << "," << endl;
			file << "			\"shape\": {" << endl;
			if (pBody->m_pShape->type == ShapeType::ST_AABB) {
				file << "				\"width\": " << std::to_string(pBody->GetWidth()) << "," << endl;
				file << "				\"height\": " << std::to_string(pBody->GetHeight()) << "," << endl;
			}
			else if (pBody->m_pShape->type == ShapeType::ST_Circle) {
				file << "				\"radius\": " << std::to_string(pBody->GetRadius()) << "," << endl;
			}

			file << "				\"offset\": {" << endl;
			file << "					\"x\": " << std::to_string(pBody->GetPositionOffset().x) << "," << endl;
			file << "					\"y\": " << std::to_string(pBody->GetPositionOffset().y) << endl;
			file << "				}" << endl;
			file << "			}";
		}

		if (pSprite) {
			file << "," << endl;
			file << "			\"tiling\": {" << endl;
			file << "				\"x\": " << std::to_string(pSprite->TileX()) << "," << endl;
			file << "				\"y\": " << std::to_string(pSprite->TileY()) << endl;
			file << "			}," << endl;
			file << "			\"repeats\": ";
			if (pSprite->Repeats())
				file << "true";
			else
				file << "false";
		}

		if (pTriggerBox) {
			file << "," << endl;
			file << "			\"gatePositions\": [" << endl;
			for (int i = 0; i < pTriggerBox->GetNumberOfGates(); ++i) {
				file << "				{" << endl;
				file << "					\"position\": {" << endl;
				file << "						\"x\": " << std::to_string(pTriggerBox->GetGatePos(i).x) << "," << endl;
				file << "						\"y\": " << std::to_string(pTriggerBox->GetGatePos(i).y) << endl;
				file << "					}," << endl;
				file << "					\"isHorizontal\": ";
				if (pTriggerBox->IsHorizontal(i))
					file << "true" << endl;
				else
					file << "false" << endl;
				if(i + 1 == pTriggerBox->GetNumberOfGates())
					file << "				}" << endl;
				else
					file << "				}," << endl;
			}
			file << "			]";
		}

		if(std::next(it) != m_instances.end()) file << "		}," << endl;
		else file << "		}" << endl;

		++it;
	}

	file << "	]" << endl;
	file << "}" << endl;

	file.close();
	m_roomStrings.push_back(fileName);
}

GameObject* LevelEditor::CreateInstance(int prefabNumber) {
	++m_instanceCount[prefabNumber];
	std::string instanceString = m_prefabStrings[prefabNumber] + "_" + std::to_string(m_instanceCount[prefabNumber]);
	GameObject* pGO = TETRA_GAME_OBJECTS.CreateGameObject(m_prefabStrings[prefabNumber]);
	ObjectInstance* pInstance = new ObjectInstance(prefabNumber, instanceString);
	m_instances[pGO] = pInstance;
	return pGO;
}