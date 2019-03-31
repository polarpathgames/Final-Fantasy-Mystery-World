#include "Entity.h"
#include "j1App.h"
#include "j1EntityManager.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "p2Log.h"
#include "j1Textures.h"


Entity::Entity(const int& x, const int& y)
{
	position.x = x;
	position.y = y;
}

Entity::~Entity()
{
}

void Entity::Draw(SDL_Texture * tex, float dt)
{
	if (type != Entity::EntityType::SENSOR)
		App->render->Blit(tex, position.x, position.y, &(current_animation->GetCurrentFrame(dt)), true);
}

void Entity::SetPivot(const int & x, const int & y)
{
	pivot.create(x, y);
}

void Entity::LoadXML(std::string name_xml_file)
{
	config = App->LoadConfig(config_file, name_xml_file.data());
	switch (type) {
	case EntityType::PLAYER:
		node = config.child("player");
		break;
	default:
		LOG("Could not LoadXML");
		break;
	}
}

Animation Entity::LoadPushbacks(pugi::xml_node &config, std::string NameAnim) const
{
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

bool Entity::LoadEntityData(const char* file) {

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
	data.tileset.imagePath = _node.child("image").attribute("source").as_string();
	data.tileset.width = _node.child("image").attribute("width").as_uint();
	data.tileset.height = _node.child("image").attribute("height").as_uint();

	size.create(data.tileset.tilewidth, data.tileset.tileheight);

	//provisional ubication -----------------------------
	data.tileset.texture = App->tex->Load(data.tileset.imagePath.data());
	//----------------------------

	//count how many animations are in file
	_node = _node.child("tile");
	data.num_animations = 0;
	while (_node != NULL) {
		data.num_animations++;
		_node = _node.next_sibling("tile");
	}

	//reserve memory for all animations
	data.animations = new EntityAnim[data.num_animations];

	//count how many frames for each animation, assign memory for those frames and set id frame start
	_node = entity_file.child("tileset").child("tile");
	for (uint i = 0; i < data.num_animations; ++i) {
		data.animations[i].FrameCount(_node.child("animation").child("frame"));
		data.animations[i].frames = new SDL_Rect[data.animations[i].num_frames];
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
	//LoadProperties(entity_file.child("tileset").child("properties").child("property")); //Load properties, is a virtual function because every entity has its variables

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

	return ret;
}

void Entity::IdAnimToEnum() //Assign every id animation to enum animation
{
	for (uint i = 0; i < data.num_animations; ++i) {
		switch (data.animations[i].id) {
		case 1:
			data.animations[i].animType = AnimationState::IDLE_DOWN_LEFT;
			break;
		case 0:
			data.animations[i].animType = AnimationState::WALKING_DOWN_LEFT;
			break;
		case 3:
			data.animations[i].animType = AnimationState::WALKING_UP_LEFT;
			break;
		case 4:
			data.animations[i].animType = AnimationState::IDLE_UP_LEFT;
			break;
		case 6:
			data.animations[i].animType = AnimationState::WALKING_DOWN_RIGHT;
			break;
		case 7:
			data.animations[i].animType = AnimationState::IDLE_DOWN_RIGHT;
			break;
		case 9:
			data.animations[i].animType = AnimationState::WALKING_UP_RIGHT;
			break;
		case 10:
			data.animations[i].animType = AnimationState::IDLE_UP_RIGHT;
			break;
		case 12:
			data.animations[i].animType = AnimationState::WALKING_DOWN;
			break;
		case 13:
			data.animations[i].animType = AnimationState::IDLE_DOWN;
			break;
		case 15:
			data.animations[i].animType = AnimationState::WALKING_UP;
			break;
		case 16:
			data.animations[i].animType = AnimationState::IDLE_UP;
			break;
		case 18:
			data.animations[i].animType = AnimationState::WALKING_LEFT;
			break;
		case 19:
			data.animations[i].animType = AnimationState::IDLE_LEFT;
			break;
		case 21:
			data.animations[i].animType = AnimationState::WALKING_RIGHT;
			break;
		case 22:
			data.animations[i].animType = AnimationState::IDLE_RIGHT;
			break;
		case 24:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_LEFT;
			break;
		case 33:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_RIGHT;
			break;
		case 27:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_UP_LEFT;
			break;
		case 30:
			data.animations[i].animType = AnimationState::BASIC_ATTACK_DOWN_RIGHT;
			break;
		}

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

const Collider * Entity::GetCollider() const
{
	return coll;
}