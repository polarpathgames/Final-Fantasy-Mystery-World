#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Collisions.h"
#include <math.h>
#include "j1EntityManager.h"
#include "Player.h"
#include "j1EntityManager.h"
#include <list>
#include "j1FadeToBlack.h"
#include "j1Pathfinding.h"
#include "j1Scene.h"
#include <string>
#include "p2Properties.h"
#include "Brofiler/Brofiler.h"

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.assign("map");
}

// Destructor
j1Map::~j1Map()
{}

bool j1Map::Start()
{
	quad = App->tex->Load("maps/cuadradito.png");
	return true;
}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.assign(config.child("folder").child_value());

	tutorial_map = config.child("maps").child("tutorial_map").text().as_string();
	shop_map = config.child("maps").child("shop_map").text().as_string();
	lobby_map = config.child("maps").child("lobby_map").text().as_string();
	home_map = config.child("maps").child("home_map").text().as_string();
	
	
	return ret;
}

void j1Map::Draw()
{
	BROFILER_CATEGORY("DrawMap", Profiler::Color::Pink);

	if(map_loaded == false)
		return;

	std::list<MapLayer*>::iterator item = data.layers.begin();
	
	for(; item != data.layers.end(); ++item)
	{
		MapLayer* layer = *item;

		if(layer->properties.GetValue("NoDraw") != 0 && !App->collision->debug)
			continue;

		for(int i = 0; i < data.width; ++i)
		{
			for(int j = 0; j < data.width; ++j)
			{
				iPoint tile_pos = MapToWorld(i, j);
				
					int tile_id = layer->Get(i, j);
					if (tile_id > 0)
					{
						TileSet* tileset = GetTilesetFromTileId(tile_id);
						if (App->render->IsOnCamera(tile_pos.x, tile_pos.y, tileset->tile_width, tileset->tile_height))
						{
							SDL_Rect r = tileset->GetTileRect(tile_id);

							App->render->Blit(tileset->texture, tile_pos.x, tile_pos.y, &r, true);
							
						}
				}
			}
		}
	}

	if (Grid) {
		for (int i = 0; i < data.width; ++i) {
			for (int j = 0; j < data.height; ++j) {

				App->render->Blit(quad, MapToWorld(i, j).x + 1, MapToWorld(i, j).y - 8, NULL, true);
			}
		}
	}
}

TileSet* j1Map::GetTilesetFromTileId(int id) const
{
	std::list<TileSet*>::const_iterator item = data.tilesets.begin();
	TileSet* set = *item;

	while(item != data.tilesets.end())
	{
		if(id < (*item)->firstgid)
		{
			/*std::list<TileSet*>::const_iterator item2 = item;
			--item2;
			set = *item2; //aixo ho estic fent malament segur IMPORTANT XD
			*/
			set = *prev(item);
			break;
		}
		set = *item;
		++item;
	}

	return set;
}

iPoint j1Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	if(data.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x * data.tile_width;
		ret.y = y * data.tile_height;
	}
	else if(data.type == MAPTYPE_ISOMETRIC)
	{
		ret.x = (x - y) * (data.tile_width * 0.5f);
		ret.y = (x + y) * (data.tile_height * 0.5f);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

iPoint j1Map::WorldToMap(int x, int y) const
{
	iPoint ret(0,0);

	if(data.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / data.tile_width;
		ret.y = y / data.tile_height;
	}
	else if(data.type == MAPTYPE_ISOMETRIC)
	{
		
		float half_width = data.tile_width * 0.5f;
		float half_height = data.tile_height * 0.5f;
		ret.x = int( (x / half_width + y / half_height) / 2);
		ret.y = int( (y / half_height - (x / half_width)) / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

iPoint j1Map::TiledToWorld(int x, int y) const
{
	iPoint ret = { 0,0 };


	ret.x = x / (data.tile_width*0.5f);
	ret.y = y / data.tile_height;

	ret = MapToWorld(ret.x, ret.y);

	return ret;
}

SDL_Rect TileSet::GetTileRect(int id) const
{
	int relative_id = id - firstgid;
	SDL_Rect rect;
	rect.w = tile_width;
	rect.h = tile_height;
	rect.x = margin + ((rect.w + spacing) * (relative_id % num_tiles_width));
	rect.y = margin + ((rect.h + spacing) * (relative_id / num_tiles_width));
	return rect;
}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// Remove all tilesets
	std::list<TileSet*>::iterator item;
	item = data.tilesets.begin();

	while(item != data.tilesets.end())
	{
		App->tex->UnLoad((*item)->texture);
		RELEASE(*item);
		++item;
	}
	data.tilesets.clear();

	// Remove all layers
	std::list<MapLayer*>::iterator item2;
	item2 = data.layers.begin();

	while(item2 != data.layers.end())
	{
		RELEASE(*item2);
		++item2;
	}
	data.layers.clear();

	std::list<ObjectLayer*>::iterator item3;
	item3 = data.objects.begin();

	while (item3 != data.objects.end())
	{
		RELEASE(*item3);
		++item3;
	}
	data.objects.clear();

	data.properties.CleanUp();

	data.no_walkables.clear();

	App->collision->CleanUp();
	// Clean up the pugui tree
	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	std::string tmp = folder.data();
	tmp += file_name;
	pugi::xml_parse_result result = map_file.load_file(tmp.data());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	// Load general info ----------------------------------------------
	if(ret == true)
	{
		ret = LoadMap();
	}

	
	// Load all tilesets info ----------------------------------------------
	pugi::xml_node tileset;
	for(tileset = map_file.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();

		if(ret == true)
		{
			ret = LoadTilesetDetails(tileset, set);
		}

		if(ret == true)
		{
			ret = LoadTilesetImage(tileset, set);
		}

		data.tilesets.push_back(set);
	}

	// Load layer info ----------------------------------------------
	pugi::xml_node layer;
	for(layer = map_file.child("map").child("layer"); layer && ret; layer = layer.next_sibling("layer"))
	{
		MapLayer* lay = new MapLayer();

		ret = LoadLayer(layer, lay);

		if(ret == true)
			data.layers.push_back(lay);
	}

	// Load objects info --------------------------------------------
	pugi::xml_node objectGroup;
	pugi::xml_node object;

	for (objectGroup = map_file.child("map").child("objectgroup"); objectGroup && ret; objectGroup = objectGroup.next_sibling("objectgroup"))
	{
		for (object = objectGroup.child("object"); object; object = object.next_sibling("object")) {

			ObjectLayer* obj = new ObjectLayer();

			if (ret == true && object != NULL)
				ret = LoadObject(object, obj);

			data.objects.push_back(obj);
		}
	}

	//Load Map Properties -------------------------------------------------------
	LoadProperties(map_file.child("map").child("properties"), &data.properties);

	if(ret == true)
	{
		LOG("Successfully parsed map XML file: %s", file_name);
		LOG("width: %d height: %d", data.width, data.height);
		LOG("tile_width: %d tile_height: %d", data.tile_width, data.tile_height);

		std::list<TileSet*>::iterator item = data.tilesets.begin();
		while(item != data.tilesets.end())
		{
			TileSet* s = *item;
			LOG("Tileset ----");
			LOG("name: %s firstgid: %d", s->name.data(), s->firstgid);
			LOG("tile width: %d tile height: %d", s->tile_width, s->tile_height);
			LOG("spacing: %d margin: %d", s->spacing, s->margin);
			++item;
		}

		std::list<MapLayer*>::iterator item_layer = data.layers.begin();
		while(item_layer != data.layers.end())
		{
			MapLayer* l = *item_layer;
			LOG("Layer ----");
			LOG("name: %s", l->name.data());
			LOG("tile width: %d tile height: %d", l->width, l->height);
			++item_layer;
		}
	}

	map_loaded = ret;

	return ret;
}

// Load map general properties
bool j1Map::LoadMap()
{
	bool ret = true;
	pugi::xml_node map = map_file.child("map");

	if(map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		data.width = map.attribute("width").as_int();
		data.height = map.attribute("height").as_int();
		data.tile_width = map.attribute("tilewidth").as_int();
		data.tile_height = map.attribute("tileheight").as_int();
		std::string bg_color(map.attribute("backgroundcolor").as_string());
		
		data.background_color.r = 0;
		data.background_color.g = 0;
		data.background_color.b = 0;
		data.background_color.a = 0;

		if(bg_color.size() > 0)
		{
			std::string red, green, blue;
			red = bg_color.substr(1, 2);
			green = bg_color.substr(3, 4);
			blue = bg_color.substr(5, 6);

			int v = 0;

			sscanf_s(red.data(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.r = v;

			sscanf_s(green.data(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.g = v;

			sscanf_s(blue.data(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.b = v;
		}

		std::string orientation(map.attribute("orientation").as_string());

		if(orientation == "orthogonal")
		{
			data.type = MAPTYPE_ORTHOGONAL;
		}
		else if(orientation == "isometric")
		{
			data.type = MAPTYPE_ISOMETRIC;
		}
		else if(orientation == "staggered")
		{
			data.type = MAPTYPE_STAGGERED;
		}
		else
		{
			data.type = MAPTYPE_UNKNOWN;
		}

	}

	return ret;
}

bool j1Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	set->name.assign(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tile_width = tileset_node.attribute("tilewidth").as_int();
	set->tile_height = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	pugi::xml_node offset = tileset_node.child("tileoffset");

	if(offset != NULL)
	{
		set->offset_x = offset.attribute("x").as_int();
		set->offset_y = offset.attribute("y").as_int();
	}
	else
	{
		set->offset_x = 0;
		set->offset_y = 0;
	}

	return ret;
}

bool j1Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if(image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		set->texture = App->tex->Load(PATH(folder.data(), image.attribute("source").as_string()));
		int w, h;
		SDL_QueryTexture(set->texture, NULL, NULL, &w, &h);
		set->tex_width = image.attribute("width").as_int();

		if(set->tex_width <= 0)
		{
			set->tex_width = w;
		}

		set->tex_height = image.attribute("height").as_int();

		if(set->tex_height <= 0)
		{
			set->tex_height = h;
		}

		set->num_tiles_width = set->tex_width / set->tile_width;
		set->num_tiles_height = set->tex_height / set->tile_height;
	}

	return ret;
}

bool j1Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_int();
	layer->height = node.attribute("height").as_int();
	LoadProperties(node.child("properties"), &layer->properties);
	pugi::xml_node layer_data = node.child("data");

	if(layer_data == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'layer/data' tag.");
		ret = false;
		RELEASE(layer);
	}
	else
	{
		layer->data = new uint[layer->width*layer->height];
		memset(layer->data, 0, layer->width*layer->height);

		int i = 0;
		for(pugi::xml_node tile = layer_data.child("tile"); tile; tile = tile.next_sibling("tile"))
		{
			layer->data[i++] = tile.attribute("gid").as_int(0);
		}
	}

	return ret;
}

bool j1Map::LoadObject(pugi::xml_node & object_node, ObjectLayer * obj)
{
	bool ret = true;
	if (object_node.empty())	ret = false;

	//Load Collider / Entity data
	obj->name = object_node.attribute("name").as_string();
	obj->ent_type = object_node.attribute("type").as_string();
	obj->tile_id = object_node.attribute("id").as_uint();
	obj->coll_x = object_node.attribute("x").as_int();
	obj->coll_y = object_node.attribute("y").as_int();
	obj->coll_height = object_node.attribute("height").as_uint();
	obj->coll_width = object_node.attribute("width").as_uint();
	
	//Load Collider type from ObjectGroup
	pugi::xml_node objGroup = object_node.parent();
	std::string type(objGroup.child("properties").child("property").attribute("value").as_string());


	pugi::xml_node prop = object_node.child("properties");
	if (prop)
		LoadProperties(prop, &obj->properties);


	return ret;
}

// Load a group of properties from a node and fill a list with it
bool j1Map::LoadProperties(pugi::xml_node& node, Properties<int>* properties)
{
	bool ret = false;

	if(node != nullptr)
	{
		pugi::xml_node prop;

		for(prop = node.child("property"); prop; prop = prop.next_sibling("property"))
		{
			Property<int>* p = new Property<int>();

			p->SetName(prop.attribute("name").as_string());
			p->SetValue(prop.attribute("value").as_int());

			properties->properties.push_back(p);
		}
	}

	return ret;
}

bool j1Map::CreateWalkabilityMap(int& width, int& height, uchar** buffer)
{
	bool ret = false;
	std::list<MapLayer*>::const_iterator item;
	item = data.layers.begin();

	for(item = data.layers.begin(); item != data.layers.end(); ++item)
	{
		MapLayer* layer = *item;

		if(layer->properties.GetValue("Navigation", 0) == 0)
			continue;

		uchar* map = new uchar[layer->width*layer->height];
		memset(map, 1, layer->width*layer->height);

		for(int y = 0; y < data.height; ++y)
		{
			for(int x = 0; x < data.width; ++x)
			{
				int i = (y*layer->width) + x;
				iPoint tile_pos = MapToWorld(x, y);
				int tile_id = layer->Get(x, y);
				TileSet* tileset = (tile_id > 0) ? GetTilesetFromTileId(tile_id) : NULL;
				
				if(tileset != NULL)
				{
					//tile_pos.x -= 1;
					iPoint pos = WorldToMap(tile_pos.x + data.tile_width/2, tile_pos.y-data.tile_height/2);
					data.no_walkables.push_back(pos);
					map[i] = (tile_id - tileset->firstgid) > 0 ? 0 : 1;
					/*TileType* ts = tileset->GetTileType(tile_id);
					if(ts != NULL)
					{
						map[i] = ts->properties.Get("walkable", 1);
					}*/
				}
			}
		}

		*buffer = map;
		width = data.width;
		height = data.height;
		ret = true;

		break;
	}

	return ret;
}

bool j1Map::ChangeMap(Maps type)
{
	last_map = actual_map;
	App->entity_manager->DeleteEntitiesNoPlayer();
	CleanUp();
	switch(type) {
	case Maps::LOBBY:
		Load(lobby_map.data());
		actual_map = Maps::LOBBY;
		break;
	case Maps::TUTORIAL:
		Load(tutorial_map.data());
		actual_map = Maps::TUTORIAL;
		break;
	case Maps::SHOP:
		Load(shop_map.data());
		actual_map = Maps::SHOP;
		break;
	case Maps::HOME:
		Load(home_map.data());
		actual_map = Maps::HOME;
		break;
	default:
		LOG("Could not load the map");
		break;
	}
	int w, h;
	uchar* data = NULL;
	if (CreateWalkabilityMap(w, h, &data))
		App->pathfinding->SetMap(w, h, data);
	App->scene->CreateEntities();

	return true;
}

bool j1Map::IsWalkable(iPoint pos, bool need_convert)
{
	bool ret = true;

	std::list<iPoint>::const_iterator item = data.no_walkables.begin();
	if (need_convert)
		pos = WorldToMap(pos.x + 1, pos.y - 8);

	for (; item != data.no_walkables.end(); ++item) {
		if ((*item) == pos) {
			ret = false;
			break;
		}
	}

	return ret;
}
