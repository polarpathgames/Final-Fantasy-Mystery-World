#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include <list>
#include "p2Point.h"
#include "m1Module.h"
#include "p2Properties.h"
#include "SDL/include/SDL_rect.h"
#include <string>

struct SDL_Texture;

enum class Maps {

	LOBBY,
	TUTORIAL,
	SHOP,
	HOME,

	NONE
};

//-----------------------------------------------------------------
struct ObjectLayer {

	std::string name;
	std::string ent_type;

	uint tile_id = 0;
	int	coll_x = 0;
	int	coll_y = 0;
	int coll_width = 0;
	int coll_height = 0;
	Properties<int> properties;

	~ObjectLayer()
	{
		properties.CleanUp();
	}
};

// ----------------------------------------------------
struct MapLayer
{
	std::string						name;
	int								width = 0;
	int								height = 0;
	uint*							data = nullptr;
	Properties<int>					properties;

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		properties.CleanUp();

		RELEASE(data);
	}

	inline uint Get(int x, int y) const
	{
		return data[(y*width) + x];
	}
};

// ----------------------------------------------------
struct TileSet
{
	SDL_Rect GetTileRect(int id) const;

	std::string			name;
	int					firstgid = 0;
	int					margin = 0;
	int					spacing = 0;
	int					tile_width = 0;
	int					tile_height = 0;
	SDL_Texture*		texture = nullptr;
	int					tex_width = 0;
	int					tex_height = 0;
	int					num_tiles_width = 0;
	int					num_tiles_height = 0;
	int					offset_x = 0;
	int					offset_y = 0;
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};
// ----------------------------------------------------
struct MapData
{
	int							width = 0;
	int							height = 0;
	int							tile_width = 0;
	int							tile_height = 0;
	SDL_Color					background_color;
	MapTypes					type = MapTypes::MAPTYPE_UNKNOWN;
	std::list<TileSet*>			tilesets;
	std::list<MapLayer*>		layers;
	std::list<ObjectLayer*>		objects;
	Properties<int>				properties;
	std::list<iPoint>			no_walkables;
};

// ----------------------------------------------------
class m1Map : public m1Module
{
public:

	m1Map();

	// Destructor
	virtual ~m1Map();

	bool Start();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	iPoint MapToWorld(int x, int y) const;
	iPoint WorldToMap(int x, int y) const;
	iPoint TiledToWorld(int x, int y) const;
	bool CreateWalkabilityMap(int& width, int& height, uchar** buffer);

	bool ChangeMap(Maps type);

	bool IsWalkable(iPoint pos, bool need_convert = true);

private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadObject(pugi::xml_node& tileset_node, ObjectLayer* obj);
	bool LoadProperties(pugi::xml_node& node, Properties<int>* properties);

	TileSet* GetTilesetFromTileId(int id) const;

public:

	MapData		data;
	bool		grid = false;
	Maps		actual_map = Maps::NONE;
	Maps		last_map = Maps::NONE;

private:

	pugi::xml_document	map_file;
	std::string			folder;
	bool				map_loaded = false;
	SDL_Texture*		quad = nullptr;

	std::string tutorial_map;
	std::string lobby_map;
	std::string shop_map;
	std::string home_map;
	
};

#endif // __j1MAP_H__