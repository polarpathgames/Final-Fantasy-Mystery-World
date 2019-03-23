#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include <list>
#include "p2Point.h"
#include "j1Module.h"
#include "p2Properties.h"
#include <string>

enum class Maps {

	LOBBY,
	TUTORIAL,

	NONE
};

//-----------------------------------------------------------------
struct ObjectLayer {

	std::string name;
	std::string ent_type;

	uint tile_id;
	int	coll_x;
	int	coll_y;
	int coll_width = 0;
	int coll_height = 0;

};

// ----------------------------------------------------
struct MapLayer
{
	std::string						name;
	int								width;
	int								height;
	uint*							data;
	std::list<Property<int>*>		properties;

	auto GetProperty(const char*);

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		for (std::list<Property<int>*>::iterator item = properties.begin(); item != properties.end(); item++) {
			delete *item;
			*item = nullptr;
		}
		properties.clear();

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
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;
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
	int							width;
	int							height;
	int							tile_width;
	int							tile_height;
	SDL_Color					background_color;
	MapTypes					type;
	std::list<TileSet*>			tilesets;
	std::list<MapLayer*>		layers;
	std::list<ObjectLayer*>		objects;
	std::list<Property*>		properties;
};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

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
	bool CreateWalkabilityMap(int& width, int& height, uchar** buffer) const;

	bool ChangeMap(Maps type);

private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadObject(pugi::xml_node& tileset_node, ObjectLayer* obj);
	bool LoadProperties(pugi::xml_node& node, Properties& properties);

	TileSet* GetTilesetFromTileId(int id) const;

public:

	MapData data;
	bool	Grid = true;

private:

	pugi::xml_document	map_file;
	std::string			folder;
	bool				map_loaded;
	SDL_Texture*		quad;

	std::string tutorial_map;
	std::string lobby_map;

	
};

#endif // __j1MAP_H__