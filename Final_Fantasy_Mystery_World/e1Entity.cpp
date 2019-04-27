#include "e1Entity.h"
#include "App.h"
#include "m1EntityManager.h"
#include "m1Render.h"
#include "m1Scene.h"
#include "m1Map.h"
#include "p2Log.h"
#include "m1Textures.h"
#include "m1Collisions.h"
#include "Brofiler/Brofiler.h"


e1Entity::e1Entity(const int& x, const int& y)
{
	position.x = x;
	position.y = y;
}

e1Entity::~e1Entity()
{
	if (coll != nullptr) {
		App->collision->DeleteCollider(coll);
	}
	general_properties.CleanUp();
}

void e1Entity::Draw(float dt)
{
	if (drawable)
		App->render->Blit(data.tileset.texture, position.x, position.y, &(current_animation->GetCurrentFrame(dt)), true);
}

void e1Entity::SetPivot(const int & x, const int & y)
{
	pivot.create(x, y);
}

iPoint e1Entity::GetPosition() const
{
	return position + pivot;
}

Animation e1Entity::LoadPushbacks(pugi::xml_node &config, std::string NameAnim) const
{
	BROFILER_CATEGORY("LoadPushbacks Entity", Profiler::Color::Yellow);

	std::string XML_NAME_ANIM;
	SDL_Rect rect;
	Animation anim;
	XML_NAME_ANIM = "Animations";

	for (pugi::xml_node frames = config.child(XML_NAME_ANIM.data()).child(NameAnim.data()).child("frame"); frames; frames = frames.next_sibling("frame")) {
		rect.x = frames.attribute("x").as_int();
		rect.y = frames.attribute("y").as_int();
		rect.w = frames.attribute("w").as_int();
		rect.h = frames.attribute("h").as_int();
		anim.PushBack({ rect.x,rect.y,rect.w,rect.h });
	}
	anim.speed = config.child(XML_NAME_ANIM.data()).child(NameAnim.data()).attribute("speed").as_float();
	anim.loop = config.child(XML_NAME_ANIM.data()).child(NameAnim.data()).attribute("loop").as_bool();

	return anim;
}

bool e1Entity::LoadEntityData(const char* file) {

	BROFILER_CATEGORY("LoadEntityData", Profiler::Color::Yellow);

	bool ret = true;

	pugi::xml_parse_result result = entity_file.load_file(file);

	if (result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file, result.description());
		ret = false;
	}

	//fill tileset info
	pugi::xml_node _node = entity_file.child("tileset");

	data.tileset.name.assign(_node.attribute("name").as_string());
	data.tileset.tilewidth = _node.attribute("tilewidth").as_uint();
	data.tileset.tileheight = _node.attribute("tileheight").as_uint();
	data.tileset.spacing = _node.attribute("spacing").as_uint();
	data.tileset.margin = _node.attribute("margin").as_uint();
	data.tileset.tilecount = _node.attribute("tilecount").as_uint();
	data.tileset.columns = _node.attribute("columns").as_uint();
	data.tileset.imagePath = std::string("assets/") + _node.child("image").attribute("source").as_string();
	data.tileset.width = _node.child("image").attribute("width").as_uint();
	data.tileset.height = _node.child("image").attribute("height").as_uint();

	size.create(data.tileset.tilewidth, data.tileset.tileheight);

	data.tileset.texture = App->tex->Load(data.tileset.imagePath.data());

	//count how many animations are in file
	_node = _node.child("tile");
	data.num_animations = 0;
	while (_node != NULL) {
		data.num_animations++;
		_node = _node.next_sibling("tile");
	}

	//reserve memory for all animations
	data.animations = DBG_NEW EntityAnim[data.num_animations];

	//count how many frames for each animation, assign memory for those frames and set id frame start
	_node = entity_file.child("tileset").child("tile");
	for (uint i = 0; i < data.num_animations; ++i) {
		data.animations[i].FrameCount(_node.child("animation").child("frame"));
		data.animations[i].frames = DBG_NEW SDL_Rect[data.animations[i].num_frames];
		data.animations[i].id = _node.attribute("id").as_uint();
		data.animations[i].speed = _node.child("properties").child("property").attribute("value").as_int(1);
		_node = _node.next_sibling("tile");
	}

	//fill frame array with current information
	_node = entity_file.child("tileset").child("tile");
	pugi::xml_node node_frame;
	for (uint i = 0; i < data.num_animations; ++i) {
		node_frame = _node.child("animation").child("frame");
		for (uint j = 0; j < data.animations[i].num_frames; ++j) {
			data.animations[i].frames[j] = data.tileset.GetTileRect(node_frame.attribute("tileid").as_uint());
			node_frame = node_frame.next_sibling("frame");
		}
		_node = _node.next_sibling("tile");
	}
	//LOG all animation information
	for (uint i = 0; i < data.num_animations; ++i) {
		LOG("Animation %i--------", data.animations[i].id);
		for (uint j = 0; j < data.animations[i].num_frames; ++j) {
			LOG("frame %i x: %i y: %i w: %i h: %i",
				j, data.animations[i].frames[j].x, data.animations[i].frames[j].y,
				data.animations[i].frames[j].w, data.animations[i].frames[j].h);
		}
	}

	//Load data
	LoadProperties(entity_file.child("tileset").child("properties").child("property")); //Load properties

	//LoadCollider(entity_file.child("tileset").child("tile").child("objectgroup").child("object")); //Load collider

	//Convert id animations to enum
	IdAnimToEnum();

	PushBack();

	//deleting entity animation data already loaded in its corresponding animation variables
	for (uint i = 0; i < data.num_animations; ++i) {		//this block of code delete animation data loaded of xml,
		if (data.animations[i].frames != nullptr) {			//is in PushBack() because when load all animation in its
			delete[] data.animations[i].frames;				//corresponding variables, that data is useless
			data.animations[i].frames = nullptr;
		}
	}
	if (data.animations != nullptr) {
		delete[] data.animations;
		data.animations = nullptr;
	}

	entity_file.reset();

	return ret;
}

void e1Entity::LoadProperties(pugi::xml_node &property)
{
	for (; property != NULL; property = property.next_sibling()) {
		Property<int>* prop = DBG_NEW Property<int>(property.attribute("name").as_string(), property.attribute("value").as_int());
		general_properties.properties.push_back(prop);
	}
}

//Functions to help loading data in xml-------------------------------------
//Get the rect info of an id of tileset
SDL_Rect TileSetEntity::GetTileRect(int id) const {
	SDL_Rect rect;
	rect.w = tilewidth;
	rect.h = tileheight;
	rect.x = margin + ((rect.w + spacing) * (id % columns));
	rect.y = margin + ((rect.h + spacing) * (id / columns));
	return rect;
}

//Return how many frames are in one animation
uint EntityAnim::FrameCount(pugi::xml_node& n) {
	num_frames = 0;
	pugi::xml_node node = n;
	for (; node != NULL; node = node.next_sibling("frame")) {
		num_frames++;
	}

	return num_frames;
}

const Collider * e1Entity::GetCollider() const
{
	return coll;
}