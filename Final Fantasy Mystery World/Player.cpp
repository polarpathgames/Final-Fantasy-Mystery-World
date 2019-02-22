#include "Player.h"
#include "j1Input.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "EntityManager.h"
#include "j1Map.h"
#include <string>

Player::Player()
{
	name_file_xml.assign("player_config.xml");

	

	config = App->LoadConfig(config_file,name_file_xml.data());
	node = config.child("player");

	
	GoLeft = LoadPushbacks(node, "GoLeft");
	IdleLeft = LoadPushbacks(node, "IdleLeft");
	position.x = 100;
	position.y = 200;
	current_animation = &IdleLeft;

}

Player::~Player()
{
}

bool Player::Update(float dt)
{

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		current_animation = &GoLeft;
		position.x -= 200 * dt;
		position.y += 130 * dt;
	}
	else current_animation = &IdleLeft;

	return true;
}

bool Player::PreUpdate()
{
	return true;
}

bool Player::PostUpdate()
{
	return true;
}

bool Player::Load(pugi::xml_node &)
{
	return true;
}

bool Player::Save(pugi::xml_node &) const
{
	return true;
}

bool Player::CleanUp()
{
	return true;
}
