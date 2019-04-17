#include "e1Particles.h"
#include "App.h"
#include "m1Map.h"
#include "m1EntityManager.h"
#include "e1DynamicEntity.h"
#include "m1Render.h"
#include "e1Player.h"
#include "e1Archer.h"
#include "m1Scene.h"
#include "e1Enemy.h"
#include "e1Player.h"


e1Particles::e1Particles(const int & x, const int & y) : e1DynamicEntity(x, y)
{
	type = e1Entity::EntityType::PARTICLE;
	position = App->map->MapToWorld(position.x, position.y);
}

e1Particles::~e1Particles()
{
}

bool e1Particles::PreUpdate()
{
	return true;
}

bool e1Particles::Update(float dt)
{
	switch (particle_type)
	{
	case e1Particles::ParticleType::ARROW: {
		MoveArrow(dt);
		break; }
	case e1Particles::ParticleType::FIREBALL: {
		MoveFireBall(dt);
		break; }
	default:
		break;
	}

	return true;
}

bool e1Particles::CleanUp()
{
	return true;
}

void e1Particles::SetParticle(const ParticleType & particle_type, const Direction & dir)
{
	this->particle_type = particle_type;
	direction = dir;
	actual_tile = App->map->WorldToMap(position.x, position.y);
	switch (particle_type) {
	case ParticleType::ARROW:
		SetArrow();
		break;
	case ParticleType::FIREBALL:
		SetFireBall();
		break;
	default:
		break;
	}
	
}

void e1Particles::SetArrow()
{
	arrow_tile = actual_tile;
	velocity.x = 160;
	velocity.y = 80;
	switch (direction) {
	case Direction::DOWN_LEFT: // need fix
		position.y -= 10;
		GoDownLeft.PushBack({ 17,25,23,15 });
		SetPivot(10, 10);
		size.create(20, 20);
		current_animation = &GoDownLeft;
		max_arrow_distance.create(arrow_tile.x, arrow_tile.y + MAX_ARROW);
		break;
	case Direction::UP_RIGHT: // need fix
		position.x += 9;
		position.y -= 16;
		GoUpRight.PushBack({ 41,9,23,15 });
		SetPivot(10, 10);
		size.create(20, 20);
		current_animation = &GoUpRight;
		max_arrow_distance.create(arrow_tile.x, arrow_tile.y - MAX_ARROW);
		break;
	case Direction::UP_LEFT: // need fix
		//position.x += 13;
		position.y -= 16;
		GoUpLeft.PushBack({ 17,9,23,15 });
		SetPivot(10, 10);
		size.create(20, 20);
		current_animation = &GoUpLeft;
		max_arrow_distance.create(arrow_tile.x - MAX_ARROW, arrow_tile.y);
		break;
	case Direction::DOWN_RIGHT: // need fix
		position.x += 11;
		position.y -= 11;
		GoDownRight.PushBack({ 41,25,23,15 });
		SetPivot(10, 10);
		size.create(20, 20);
		current_animation = &GoDownRight;
		max_arrow_distance.create(arrow_tile.x + MAX_ARROW, arrow_tile.y);
		break;
	case Direction::DOWN:
		position.x += 13;
		position.y -= 5;
		GoDown.PushBack({ 8,8,8,27 });
		SetPivot(4, 21);
		size.create(20, 20);
		current_animation = &GoDown;
		max_arrow_distance.create(arrow_tile.x + MAX_ARROW, arrow_tile.y + MAX_ARROW);
		break;
	case Direction::UP:
		position.x += 13;
		position.y -= 15;
		GoUp.PushBack({ 0,8,8,27 });
		SetPivot(4, 7);
		size.create(20, 20);
		current_animation = &GoUp;
		max_arrow_distance.create(arrow_tile.x - MAX_ARROW, arrow_tile.y - MAX_ARROW);
		break;
	case Direction::LEFT:
		position.x -= 5;
		position.y -= 7;
		GoLeft.PushBack({ 28,0,28,7 });
		SetPivot(7, 4);
		size.create(20, 20);
		current_animation = &GoLeft;
		max_arrow_distance.create(arrow_tile.x - MAX_ARROW, arrow_tile.y + MAX_ARROW);
		break;
	case Direction::RIGHT:
		position.x += 10;
		position.y -= 7;
		GoRight.PushBack({ 0,0,28,7 });
		SetPivot(21, 4);
		size.create(20, 20);
		current_animation = &GoRight;
		max_arrow_distance.create(arrow_tile.x + MAX_ARROW, arrow_tile.y - MAX_ARROW);
		break;
	}
}

void e1Particles::MoveArrow(float dt)
{
	actual_tile = App->map->WorldToMap(position.x, position.y);

	switch (direction)
	{
	case Direction::UP: {
		actual_tile.x += 1;
		actual_tile.y += 1;
		if (arrow_tile.x - 1 == actual_tile.x && arrow_tile.y - 1 == actual_tile.y) {
			arrow_tile = actual_tile;
		}
		if (App->map->IsWalkable(arrow_tile, false) && arrow_tile != max_arrow_distance) {
			LookForEnemyCollision();
			position.y -= floor(velocity.y * dt * 2);
		}
		else {
			to_delete = true;
		}
		break; }
	case Direction::DOWN: {
		actual_tile.x += 1;
		actual_tile.y += 1;
		if (arrow_tile.x + 1 == actual_tile.x && arrow_tile.y + 1 == actual_tile.y) {
			arrow_tile = actual_tile;
		}
		if (App->map->IsWalkable(arrow_tile, false) && arrow_tile != max_arrow_distance) {
			LookForEnemyCollision();
			position.y += floor(velocity.y * dt * 2);
		}
		else {
			to_delete = true;
		}
		break; }
	case Direction::RIGHT: {
		actual_tile.x += 1;
		if (arrow_tile.x + 1 == actual_tile.x && arrow_tile.y - 1 == actual_tile.y) {
			arrow_tile = actual_tile;
		}
		if (App->map->IsWalkable(arrow_tile, false) && arrow_tile != max_arrow_distance) {
			LookForEnemyCollision();
			position.x += floor(velocity.x * dt);
		}
		else {
			to_delete = true;
		}

		break; }
	case Direction::LEFT: {
		//actual_tile.x += 1;
		actual_tile.y += 1;
		if (arrow_tile.x - 1 == actual_tile.x && arrow_tile.y + 1 == actual_tile.y) {
			arrow_tile = actual_tile;
		}
		if (App->map->IsWalkable(arrow_tile, false) && arrow_tile != max_arrow_distance) {
			LookForEnemyCollision();
			position.x -= floor(velocity.x * dt);
		}
		else {
			to_delete = true;
		}
		
		break; }
	case Direction::UP_LEFT: {
		actual_tile.y += 1;
		if (arrow_tile.x - 1 == actual_tile.x && arrow_tile.y == actual_tile.y) {
			arrow_tile = actual_tile;
		}
		if (App->map->IsWalkable(arrow_tile, false) && arrow_tile != max_arrow_distance) {
			LookForEnemyCollision();
			position.x -= floor(velocity.x * dt);
			position.y -= floor(velocity.y * dt);
		}
		else {
			to_delete = true;
		}
		break; }
	case Direction::DOWN_LEFT: {
		actual_tile.x += 1;
		actual_tile.y += 2;
		if (arrow_tile.x == actual_tile.x && arrow_tile.y + 1 == actual_tile.y) {
			arrow_tile = actual_tile;
		}
		if (App->map->IsWalkable(arrow_tile, false) && arrow_tile != max_arrow_distance) {
			LookForEnemyCollision();
			position.x -= floor(velocity.x * dt);
			position.y += floor(velocity.y * dt);
		}
		else {
			to_delete = true;
		}
		break; }
	case Direction::UP_RIGHT: {
		actual_tile.x += 1;
		actual_tile.y += 1;
		if (arrow_tile.x == actual_tile.x && arrow_tile.y - 1 == actual_tile.y) {
			arrow_tile = actual_tile;
		}
		if (App->map->IsWalkable(arrow_tile, false) && arrow_tile != max_arrow_distance) {
			LookForEnemyCollision();
			position.x += floor(velocity.x * dt);
			position.y -= floor(velocity.y * dt);
		}
		else {
			to_delete = true;
		}
		break; }
	case Direction::DOWN_RIGHT: {
		actual_tile.y += 2;
		actual_tile.x += 2;
		if (arrow_tile.x + 1 == actual_tile.x && arrow_tile.y == actual_tile.y) {
			arrow_tile = actual_tile;
		}
		if (App->map->IsWalkable(arrow_tile, false) && arrow_tile != max_arrow_distance) {
			LookForEnemyCollision();
			position.x += floor(velocity.x * dt);
			position.y += floor(velocity.y * dt);
		}
		else {
			to_delete = true;
		}
		break; }
	default:
		break;
	}

}

void e1Particles::LookForEnemyCollision()
{
	bool ret = false;
	std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
	std::vector<e1Entity*>::iterator item = entities.begin();

	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::ENEMY) {
			iPoint origin = arrow_tile;
			iPoint destination = (*item)->actual_tile;
			e1Enemy* enemy = (e1Enemy*)(*item);
			if (origin == destination)
				enemy->GetHitted(App->scene->player->stats.attack_power);
		}
	}
}

void e1Particles::SetFireBall()
{
	velocity.y = 160;
	position.y -= FIREBALL_ELEVATED_POS;
	position.x += 5;
	actual_tile -= {1, 1};
	fireball_tile_objective = actual_tile;
	GoDown.PushBack({ 71,0,22,28 });
	GoDown.PushBack({ 93,0,22,28 });
	GoDown.PushBack({ 115,0,22,28 });
	GoDown.PushBack({ 137,0,22,28 });
	GoDown.speed = 3.0f;
	current_animation = &GoDown;

	SetPivot(11, 2800);
	size.create(20, 20);
}

void e1Particles::MoveFireBall(float dt)
{
	iPoint pos = App->map->WorldToMap(position.x, position.y + 3);

	if (pos == fireball_tile_objective) {
		to_delete = true;
	}

	position.y += floor(velocity.y * dt);
	

}
