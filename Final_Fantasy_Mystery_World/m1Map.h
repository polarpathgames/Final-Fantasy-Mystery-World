#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include <list>
#include "p2Point.h"
#include "m1Module.h"
#include "p2Properties.h"
#include "SDL/include/SDL_rect.h"
#include "p2Rooms.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include <string>

struct SDL_Texture;


enum class Maps {

	LOBBY,
	TUTORIAL,
	SHOP,
	HOME,
	QUEST2,
	FINAL_QUEST,
	DEBUG,

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

	// Load DBG_NEW map
	bool Load(const char* path);

	iPoint MapToWorld(int x, int y) const;
	iPoint MapToWorldCentered(int x, int y) const;
	iPoint WorldToMap(int x, int y) const;
	iPoint TiledToWorld(int x, int y) const;
	bool CreateWalkabilityMap(int& width, int& height, uchar** buffer);

	bool ChangeMap(Maps type);

	bool IsWalkable(iPoint pos, bool need_convert = true);
	void OnCollision(Collider* c1, Collider* c2);
private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadObject(pugi::xml_node& tileset_node, ObjectLayer* obj);
	bool LoadProperties(pugi::xml_node& node, Properties<int>* properties);

	TileSet* GetTilesetFromTileId(int id) const;

public:
	RoomManager * quest_rooms = nullptr;
	MapData		data;
	bool		grid = false;
	Maps		actual_map = Maps::NONE;
	Maps		last_map = Maps::NONE;

	uint		last_tiles_drawn = 0u;
	LobbyState lobby_state = LobbyState::NORMAL_LOBBY;
private:

	pugi::xml_document	map_file;
	std::string			folder;
	bool				map_loaded = false;
	SDL_Texture*		quad = nullptr;

	std::string lobby_map;
	std::string lobby_ice;
	std::string lobby_night;
	std::string shop_map;
	std::string home_map;

	std::string debug_map;

	Mix_Music* mus_shop = nullptr;
	Mix_Music* mus_lobby = nullptr;
	Mix_Music* mus_home = nullptr;
};

#endif // __j1MAP_H__