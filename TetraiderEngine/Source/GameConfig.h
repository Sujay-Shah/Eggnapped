/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Holden Profit>
- End Header --------------------------------------------------------*/

#pragma once

#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

class GameConfig
{
private:
	std::string m_texturesDir;
	std::string m_levelFilesDir;
	std::string m_prefabsDir;
	std::string m_sfxDir;
	std::string m_shadersDir;
	std::string m_roomFilesDir;
	std::string m_fontsDir;
	
	bool m_soundsMute;

	unsigned short m_roomWidth, m_roomHeight;	// Room dimensions in cells (ex. 12x8)
	unsigned short m_cellWidth, m_cellHeight;	// Cell dimensions in pixels (ex. 96x96)

	bool m_consoleEnabled;
	bool m_debugEnabled;
	bool m_postProcessingEnabled;

	Resolution m_resolutions[MAX_RESOLUTIONS];	// Array of supported resolutions, accepts a maximum of 4
	unsigned short m_currentResolution;			// Index into m_resolutions for currently used resolution
	unsigned short m_prevResolution;			// Saves the index into m_resolutions for toggling back and forth between full screen and windowed modes

	std::vector<unsigned int> m_seeds[4];		// Stores seeds for every given level 1-4
	bool m_shouldUseSeeds;						// Determines if stored seeds are used (true) or a random seed (false)


	void _ParseSeeds(const json& j, int index);
public:
	GameConfig();
	~GameConfig();
	GameConfig(const GameConfig &) = delete;
	void operator=(const GameConfig &) = delete;

	void LoadConfig(std::string);

	inline std::string TexturesDir() const { return m_texturesDir; }
	inline std::string LevelFilesDir() const { return m_levelFilesDir; }
	inline std::string PrefabsDir() const { return m_prefabsDir; }
	inline std::string SFXDir() const { return m_sfxDir; }
	inline std::string ShadersDir() const { return m_shadersDir; }
	inline std::string RoomFilesDir() const { return m_roomFilesDir; }
	inline std::string FontsDir() const { return m_fontsDir; }

	inline bool GetsoundsMute(){ return m_soundsMute; }
	inline unsigned short CellWidth() const { return m_cellWidth; }
	inline unsigned short CellHeight() const { return m_cellHeight; }
	inline unsigned short RoomWidth() const { return m_roomWidth; }
	inline unsigned short RoomHeight() const { return m_roomHeight; }
	inline unsigned short RoomWidthPixels() const { return m_cellWidth * m_roomWidth; }
	inline unsigned short RoomHeightPixels() const { return m_cellHeight * m_roomHeight; }

	inline bool IsConsoleEnabled() const { return m_consoleEnabled; }
	inline const Resolution& GetResolution() const { return m_resolutions[m_currentResolution]; }
	inline const Resolution& GetResolution(int i) const { return m_resolutions[i]; }
	void SelectResolution(unsigned short resolutionIndex);
	void SelectResolutionAndScreenMode(unsigned short resoutionIndex, bool isFullscreen);
	void NextResolution();
	void PrevResolution();
	inline unsigned short GetCurrentResolutionIndex() const { return m_currentResolution; }

	unsigned int GetSeed(int level);
};

#endif