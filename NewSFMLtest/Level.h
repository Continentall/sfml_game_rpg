#pragma once
#include "TinyXML/tinyxml2.h"
#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Object
{
public:
	Object(float x, float y, float width, float height) : rect(x, y, width, height){}

	int         GetPropertyInt(const std::string& name);
	float       GetPropertyFloat(const std::string& name);
	std::string GetPropertyString(const std::string& name);
	std::string name;
	std::string type;
	std::map<std::string, std::string> properties;
	sf::FloatRect rect;
};

class TileMap : public sf::Drawable
{
public:
	~TileMap();
	int widthOfmap;
	int heightOfmap;
	bool load(const std::string& tmx_file_path);

	Object               getObject(const std::string& name);
	std::vector<Object>  getObjectsByName(const std::string& name);
	std::vector<Object>  getObjectsByType(const std::string& type);
	std::vector<Object>& getAllObjects();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture* texture;
	std::vector<sf::VertexArray> tile_layers;
	std::vector<Object>          objects;
};



