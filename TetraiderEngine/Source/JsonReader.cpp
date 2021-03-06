/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Author: <Holden Profit>
- End Header --------------------------------------------------------*/

#include <Stdafx.h>

namespace JsonReader {
	std::vector<Point> ParsePoints(const json & j, const String & first)
	{
		std::vector<Point> points;
		if (j.find(first) != j.end()) {
			int size = j[first].size();
			for (int i = 0; i < size; ++i) {
				Point p;
				p.x = j[first][i]["x"];
				p.y = j[first][i]["y"];
				points.push_back(p);
			}
		}
		return points;
	}

	std::vector<Point> ParsePoints(const json & j, const String & first, const String & second)
	{
		std::vector<Point> points;
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				int size = j[first][second].size();
				for (int i = 0; i < size; ++i) {
					Point p;
					p.x = j[first][second][i]["x"];
					p.y = j[first][second][i]["y"];
					points.push_back(p);
				}
			}
		}
		return points;
	}

	float ParseFloat(const json& j, const String& first)
	{
		if (j.find(first) != j.end())
				return j[first];

		return 0.0f;
	}

	float ParseFloat(const json& j, const String& first, const String& second)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end())
				return j[first][second];
		}
		return 0.0f;
	}

	float ParseFloat(const json& j, const String& first, const String& second, const String& third)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				if (j[first][second].find(third) != j[first][second].end())
					return j[first][second][third];
			}
		}
		return 0.0f;
	}

	double ParseDouble(const json& j, const String& first)
	{
		if (j.find(first) != j.end()) return j[first];
		return 0.0;
	}

	double ParseDouble(const json& j, const String& first, const String& second)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end())
				return j[first][second];
		}
		return 0.0;
	}

	double ParseDouble(const json& j, const String& first, const String& second, const String& third)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				if (j[first][second].find(third) != j[first][second].end())
					return j[first][second][third];
			}
		}
		return 0.0;
	}

	int ParseInt(const json& j, const String& first)
	{
		if (j.find(first) != j.end())
			return j[first];
		return 0;
	}

	int ParseInt(const json& j, const String& first, const String& second)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end())
				return j[first][second];
		}
		return 0;
	}

	int ParseInt(const json& j, const String& first, const String& second, const String& third)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				if (j[first][second].find(third) != j[first][second].end())
					return j[first][second][third];
			}
		}
		return 0;
	}

	String ParseString(const json& j, const String& first)
	{
		if (j.find(first) != j.end())
			return j[first];
		return "";
	}

	String ParseString(const json& j, const String& first, const String& second)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end())
				return j[first][second];
		}
		return "";
	}

	String ParseString(const json& j, const String& first, const String& second, const String& third)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				if (j[first][second].find(third) != j[first][second].end())
					return j[first][second][third];
			}
		}
		return "";
	}

	bool ParseBool(const json& j, const String& first)
	{
		if (j.find(first) != j.end())
			return j[first];
		return false;
	}

	bool ParseBool(const json& j, const String& first, const String& second)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end())
				return j[first][second];
		}
		return false;
	}

	bool ParseBool(const json& j, const String& first, const String& second, const String& third)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				if (j[first][second].find(third) != j[first][second].end())
					return j[first][second][third];
			}
		}
		return false;
	}

	std::vector<String> ParseStringList(const json& j, const String& first)
	{
		if (j.find(first) != j.end())
			return j[first];
		return std::vector<String>();
	}

	std::vector<String> ParseStringList(const json& j, const String& first, const String& second)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end())
				return j[first][second];
		}
		return std::vector<String>();
	}

	std::vector<String> ParseStringList(const json& j, const String& first, const String& second, const String& third)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				if (j[first][second].find(third) != j[first][second].end())
					return j[first][second][third];
			}
		}
		return std::vector<String>();
	}

	Vector2D ParseVector2D(const json& j, const String& first)
	{
		if (j.find(first) != j.end()) {
			return Vector2D(
				ParseFloat(j[first], "x"),
				ParseFloat(j[first], "y"),
				ParseFloat(j[first], "w")
			);
		}
		return Vector2D();
	}

	Vector2D ParseVector2D(const json& j, const String& first, const String& second)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				return Vector2D(
					ParseFloat(j[first][second], "x"),
					ParseFloat(j[first][second], "y"),
					ParseFloat(j[first][second], "w")
				);
			}
		}
		return Vector2D();
	}

	Vector3D ParseVector3D(const json& j, const String& first)
	{
		if (j.find(first) != j.end()) {
			return Vector3D(
				ParseFloat(j[first], "x"),
				ParseFloat(j[first], "y"),
				ParseFloat(j[first], "z"),
				ParseFloat(j[first], "w")
			);
		}
		return Vector3D();
	}

	Vector3D ParseVector3D(const json& j, const String& first, const String& second)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				return Vector3D(
					ParseFloat(j[first][second], "x"),
					ParseFloat(j[first][second], "y"),
					ParseFloat(j[first][second], "z"),
					ParseFloat(j[first][second], "w")
				);
			}
		}
		return Vector3D();
	}

	Vector3D ParseColor(const json& j, const String& first)
	{
		if (j.find(first) != j.end()) {
			return Vector3D(
				ValueExists(j, first) ? j[first]["r"] : 1.0f,
				ValueExists(j, first) ? j[first]["g"] : 1.0f,
				ValueExists(j, first) ? j[first]["b"] : 1.0f,
				ValueExists(j, first) ? j[first]["a"] : 1.0f
			);
		}
		return Vector3D(1, 1, 1, 1);
	}

	Vector3D ParseColor(const json& j, const String& first, const String& second)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				return Vector3D(
					ValueExists(j, first, second) ? j[first][second]["r"] : 1.0f,
					ValueExists(j, first, second) ? j[first][second]["g"] : 1.0f,
					ValueExists(j, first, second) ? j[first][second]["b"] : 1.0f,
					ValueExists(j, first, second) ? j[first][second]["a"] : 1.0f
				);
			}
		}
		return Vector3D(1, 1, 1, 1);
	}

	bool ValueExists(const json& j, const String& first)
	{
		return j.find(first) != j.end();
	}

	bool ValueExists(const json& j, const String& first, const String& second)
	{
		if (j.find(first) != j.end()) {
			return j[first].find(second) != j[first].end();
		}
		return false;
	}

	bool ValueExists(const json& j, const String& first, const String& second, const String& third)
	{
		if (j.find(first) != j.end()) {
			if (j[first].find(second) != j[first].end()) {
				if (j[first][second].find(third) != j[first][second].end())
					return true;
			}
		}
		return false;
	}

	json OpenJsonFile(const String& fileName)
	{
		try {
			std::ifstream i(fileName);
			json j;
			i >> j;
			i.close();
			return j;
		}
		catch (json::parse_error &e) {
			std::cerr << e.what() << " in" + fileName << std::endl;
			return 0;
		}
	}

	bool KeyIs(json::iterator it, const String& key)
	{
		return it.key().compare(key) == 0;
	}

	void SerializeInterpolationItem(InterpolationItem & i, const json & j, const String & first)
	{
		i.points = ParsePoints(j, first, "points");
		i.amplitude = ParseFloat(j, first, "amplitude");
	}

}

