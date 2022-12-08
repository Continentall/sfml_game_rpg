#include "Level.h"

bool TileMap::load(const std::string& tmx_file_path)
{
	tinyxml2::XMLDocument document;
	if (document.LoadFile(tmx_file_path.c_str()) != tinyxml2::XML_SUCCESS)
	{
		std::cout << "Loading file " << tmx_file_path << " failed..." << std::endl;
		return false;
	}
	// получение данных тайлсета
	tinyxml2::XMLElement* root_element = document.FirstChildElement("map");
	const size_t tile_width = std::stoul(root_element->Attribute("tilewidth"));
	const size_t tile_height = std::stoul(root_element->Attribute("tileheight"));
	const size_t width = std::stoul(root_element->Attribute("width"));
	const size_t height = std::stoul(root_element->Attribute("height"));
	widthOfmap = width * tile_width;
	heightOfmap = height * tile_height;
	auto tileset = root_element->FirstChildElement("tileset");

	//Открытие файл tsx в пути source
	std::string sourceOfTsx = "maps/";
	sourceOfTsx += tileset->Attribute("source");
	tinyxml2::XMLDocument document2;
	if (document2.LoadFile(sourceOfTsx.c_str()) != tinyxml2::XML_SUCCESS)
	{
		std::cout << "Loading tsx file " << sourceOfTsx << " failed..." << std::endl;
		return false;
	}

	tinyxml2::XMLElement* tileset2 = document2.FirstChildElement("tileset");

	const size_t tile_count = std::stoul(tileset2->Attribute("tilecount"));
	const size_t columns = std::stoul(tileset2->Attribute("columns"));
	// получение путь до файла
	auto image = tileset2->FirstChildElement("image");
	std::string path = "maps/";
	path += image->Attribute("source");

	while (!isalpha(path.front())) // если редактор записал путь, например, так : "../textures/Tiles.png"
		path.erase(0, 1);          // то убираем все лишние символы в начале строки ( ../ ), чтобы мы могли его найти

	if (document.LoadFile(tmx_file_path.c_str()) != tinyxml2::XML_SUCCESS)
	{
		std::cout << "Loading file " << tmx_file_path << " failed..." << std::endl;
		return false;
	}


	texture = new sf::Texture();

	if (!texture->loadFromFile(path))
		return false;
	// создание сетки, индекс каждого тайла зависит от его координат в текстуре
	// Например, если ширина тайла 32 пикселей, координаты в текстуре : 
	// первого тайла (0, 0), второго (32, 0), третьего (64, 0) и так далее
	std::vector<sf::Vector2f> texture_grid;
	texture_grid.reserve(tile_count);
	size_t rows = tile_count / columns;
	for (size_t y = 0u; y < rows; ++y)
		for (size_t x = 0u; x < columns; ++x)
			texture_grid.emplace_back(sf::Vector2f((float)x * tile_width, (float)y * tile_height));
	// Обработка csv-массивов 
	for (auto layer = root_element->FirstChildElement("layer");
		layer != nullptr;
		layer = layer->NextSiblingElement("layer"))
	{
		// ширина и высота слоя в тайлах
		const size_t width = std::stoul(layer->Attribute("width"));
		const size_t height = std::stoul(layer->Attribute("height"));
		// перевод слоя в вектор целых чисел, где каждое число - номер тайла в тайлсете
		tinyxml2::XMLElement* data = layer->FirstChildElement("data");
		std::string dirty_string = data->GetText(), buffer;

		std::vector<size_t> csv_array;
		csv_array.reserve(dirty_string.size());

		for (auto& character : dirty_string)
		{
			if (isdigit(character))
				buffer += character;
			else
				if (!buffer.empty())
				{
					csv_array.push_back(std::stoi(buffer));
					buffer.clear();
				}
		}
		csv_array.shrink_to_fit();
		// создание массива вершин
		sf::VertexArray vertices;
		vertices.setPrimitiveType(sf::Quads);

		for (size_t y = 0u, index = 0u; y < height; ++y)
		{
			for (size_t x = 0u; x < width; ++x, ++index)
			{
				size_t tile_num = csv_array[index];
				// Если номер тайла больше нуля, то есть место не пусто - записываем тайл в массив вершин
				if (tile_num)
				{   // Проход по часовой стрелке
					sf::Vertex leftTop;     // Левый верхний угол тайла
					sf::Vertex rightTop;    // Верхний правый 
					sf::Vertex rightBottom; // Нижний правый 
					sf::Vertex leftBottom;  // Нижний левый
					// Устанавка тайла в позицию на карте
					leftTop.position = sf::Vector2f((float)x * tile_width, (float)y * tile_height);
					rightTop.position = sf::Vector2f(((float)x + 1) * tile_width, (float)y * tile_height);
					rightBottom.position = sf::Vector2f(((float)x + 1) * tile_width, (float)(y + 1) * tile_height);
					leftBottom.position = sf::Vector2f((float)x * tile_width, (float)(y + 1) * tile_height);
					// Определение его текстурных координат
					leftTop.texCoords = sf::Vector2f(texture_grid[tile_num - 1].x, texture_grid[tile_num - 1].y);
					rightTop.texCoords = sf::Vector2f(texture_grid[tile_num - 1].x + tile_width, texture_grid[tile_num - 1].y);
					rightBottom.texCoords = sf::Vector2f(texture_grid[tile_num - 1].x + tile_width, texture_grid[tile_num - 1].y + tile_height);
					leftBottom.texCoords = sf::Vector2f(texture_grid[tile_num - 1].x, texture_grid[tile_num - 1].y + tile_height);

					vertices.append(leftTop);
					vertices.append(rightTop);
					vertices.append(rightBottom);
					vertices.append(leftBottom);
				}
			}
		}
		tile_layers.push_back(std::move(vertices));
	}
	// Загрузка объектов, если есть
	for (auto object_group = root_element->FirstChildElement("objectgroup");
		object_group != nullptr;
		object_group = object_group->NextSiblingElement("objectgroup"))
	{// получение всех данные - тип, имя, позиция, и тд
		for (auto object = object_group->FirstChildElement("object");
			object != nullptr;
			object = object->NextSiblingElement("object"))
		{
			std::string object_name;
			if (object->Attribute("name"))
				object_name = object->Attribute("name");

			std::string object_type;
			if (object->Attribute("type"))
				object_type = object->Attribute("type");

			float x = std::stof(object->Attribute("x"));
			float y = std::stof(object->Attribute("y"));

			float width{}, height{};

			if (object->Attribute("width") && object->Attribute("height"))
			{
				width = std::stof(object->Attribute("width"));
				height = std::stof(object->Attribute("height"));
			}

			Object new_object(x, y, width, height);
			new_object.name = object_name;
			new_object.type = object_type;

			auto properties = object->FirstChildElement("properties");

			if (properties)
			{
				for (auto property = properties->FirstChildElement("property");
					property != nullptr;
					property = property->NextSiblingElement("property"))
				{
					std::string name, value;

					if (property->Attribute("name"))
						name = property->Attribute("name");

					if (property->Attribute("value"))
						value = property->Attribute("value");

					new_object.properties[name] = value;
				}
			}
			objects.emplace_back(std::move(new_object));
		}
	}
	return true;
}
// Получение только первого объекта с заданным именем
Object TileMap::getObject(const std::string& name)
{
	auto found = std::find_if(objects.begin(), objects.end(), [&](const Object& obj)
		{
			return obj.name == name;
		});

	return *found;
}
// Получение всех объектов с заданным именем
std::vector<Object> TileMap::getObjectsByName(const std::string& name)
{
	std::vector<Object> objects_by_name;

	std::copy_if(objects.begin(), objects.end(), std::back_inserter(objects_by_name), [&](const Object& obj)
		{
			return obj.name == name;
		});

	return objects_by_name;
}
// Получение всех объектов с заданным типом
std::vector<Object> TileMap::getObjectsByType(const std::string& type)
{
	std::vector<Object> objects_by_type;

	std::copy_if(objects.begin(), objects.end(), std::back_inserter(objects_by_type), [&](const Object& obj)
		{
			return obj.type == type;
		});

	return objects_by_type;
}
//Получение вообще всех объектов
std::vector<Object>& TileMap::getAllObjects()
{
	return objects;
}
// Отрисовка элемента карты
void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& layer : tile_layers)
		target.draw(layer, texture);
}

int Object::GetPropertyInt(const std::string& name)
{
	return std::stoi(properties[name]);
}

float Object::GetPropertyFloat(const std::string& name)
{
	return std::stof(properties[name]);
}

std::string Object::GetPropertyString(const std::string& name)
{
	return properties[name];
}
TileMap::~TileMap()
{
	if (texture)
		delete texture;
}