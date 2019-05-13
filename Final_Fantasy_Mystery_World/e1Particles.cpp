#include "e1Particles.h"
#include "App.h"
#include "m1Map.h"
#include "m1EntityManager.h"
#include "m1Window.h"
#include "m1GUI.h"
#include "e1DynamicEntity.h"
#include "m1Render.h"
#include "e1Rock.h"
#include "e1Player.h"
#include "e1Archer.h"
#include "m1Scene.h"
#include "e1Enemy.h"
#include "m1ParticleManager.h"
#include "e1Player.h"
#include "p2Math.h"
#include "Brofiler/Brofiler.h"
#include "m1Textures.h"


e1Particles::e1Particles(const int & x, const int & y) : e1DynamicEntity(x, y)
{
	type = e1Entity::EntityType::PARTICLE;
	position = App->map->MapToWorld(position.x, position.y);
	data.tileset.imagePath.assign("assets/sprites/Particles.png");
	data.tileset.texture = App->tex->Load(data.tileset.imagePath.data());

	allow_turn = false;
}

e1Particles::~e1Particles()
{
	for (std::list<p1Follow*>::iterator item = particle_follow.begin(); item != particle_follow.end(); ++item) {
		App->particles->DeleteFollow_p(*item);
	}
	for (std::list<p1Fire*>::iterator item = particle_fire.begin(); item != particle_fire.end(); ++item) {
		App->particles->DeleteFire_p(*item);
	}
}

bool e1Particles::PreUpdate()
{
	return true;
}

bool e1Particles::Update(float dt)
{
	BROFILER_CATEGORY("Update Particles Entoty", Profiler::Color::Yellow);

	switch (particle_type)
	{
	case e1Particles::ParticleType::ARROW: {
		MoveArrow(dt);
		break; }
	case e1Particles::ParticleType::FIREBALL: {
		MoveFireBall(dt);
		break; }
	case e1Particles::ParticleType::ICE_STAKE: {
		MoveIceStake(dt);
		break; }
	default:
		break;
	}
	iPoint pos = App->map->MapToWorld(fireball_tile_objective.x, fireball_tile_objective.y);

	if (App->debug)
		App->render->Blit(App->scene->player->ground, pos.x + 1, pos.y - 8, NULL, true);
	return true;
}

bool e1Particles::CleanUp()
{
	return true;
}

void e1Particles::Draw(float dt)
{
	if (particle_type == ParticleType::ICE_STAKE) {
		App->render->Blit(data.tileset.texture, position.x, position.y, &current_animation->GetCurrentFrame(dt), true, SDL_FLIP_NONE, 1.0f, nullptr, angle, size.x*0.5f, size.y*0.5f);
	}
	else {
		e1Entity::Draw(dt);
	}
}

void e1Particles::SetParticle(const ParticleType & particle_type, const Direction & dir)
{
	BROFILER_CATEGORY("SetParticle Entity", Profiler::Color::Yellow);

	this->particle_type = particle_type;
	direction = dir;
	actual_tile = App->map->WorldToMap(position.x, position.y);
	switch (particle_type) {
	case ParticleType::ARROW:
		name.assign("arrow");
		SetArrow();
		break;
	case ParticleType::FIREBALL:
		name.assign("fireball");
		SetFireBall();
		break;
	case ParticleType::ICE_STAKE:
		name.assign("ice stake");
		SetIceStake();
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
	size.create(20, 20);
	arrow_time = SDL_GetTicks();
	iPoint particle_offset = { 0,0 };

	switch (direction) {
	case Direction::DOWN_LEFT: // need fix
		position.y -= 10;
		GoDownLeft.PushBack({ 17,25,23,15 });
		SetPivot(6, 12);
		current_animation = &GoDownLeft;
		max_arrow_distance.create(arrow_tile.x, arrow_tile.y + MAX_ARROW);
		particle_offset.create(10, -10);
		break;
	case Direction::UP_RIGHT: // need fix
		position.x += 9;
		position.y -= 16;
		GoUpRight.PushBack({ 41,9,23,15 });
		SetPivot(17, 4);
		particle_offset.create(-10, 10);
		current_animation = &GoUpRight;
		max_arrow_distance.create(arrow_tile.x, arrow_tile.y - MAX_ARROW);
		break;
	case Direction::UP_LEFT: // need fix
		//position.x += 13;
		position.y -= 16;
		GoUpLeft.PushBack({ 17,9,23,15 });
		SetPivot(5, 4);
		current_animation = &GoUpLeft;
		particle_offset.create(10, 10);
		max_arrow_distance.create(arrow_tile.x - MAX_ARROW, arrow_tile.y);
		break;
	case Direction::DOWN_RIGHT: // need fix
		position.x += 11;
		position.y -= 11;
		GoDownRight.PushBack({ 41,25,23,15 });
		SetPivot(18, 13);
		current_animation = &GoDownRight;
		particle_offset.create(-10, -10);
		max_arrow_distance.create(arrow_tile.x + MAX_ARROW, arrow_tile.y);
		break;
	case Direction::DOWN:
		position.x += 13;
		position.y -= 5;
		GoDown.PushBack({ 8,8,8,27 });
		SetPivot(4, 21);
		current_animation = &GoDown;
		particle_offset.create(0, -5);
		max_arrow_distance.create(arrow_tile.x + MAX_ARROW, arrow_tile.y + MAX_ARROW);
		break;
	case Direction::UP:
		position.x += 13;
		position.y -= 15;
		GoUp.PushBack({ 0,8,8,27 });
		SetPivot(4, 7);
		current_animation = &GoUp;
		particle_offset.create(0, 5);
		max_arrow_distance.create(arrow_tile.x - MAX_ARROW, arrow_tile.y - MAX_ARROW);
		break;
	case Direction::LEFT:
		position.x -= 5;
		position.y -= 7;
		GoLeft.PushBack({ 28,0,28,7 });
		SetPivot(7, 4);
		current_animation = &GoLeft;
		particle_offset.create(5, 0);
		max_arrow_distance.create(arrow_tile.x - MAX_ARROW, arrow_tile.y + MAX_ARROW);
		break;
	case Direction::RIGHT:
		position.x += 10;
		position.y -= 7;
		GoRight.PushBack({ 0,0,28,7 });
		SetPivot(21, 4);
		current_animation = &GoRight;
		particle_offset.create(-5, 0);
		max_arrow_distance.create(arrow_tile.x + MAX_ARROW, arrow_tile.y - MAX_ARROW);
		break;
	}

	particle_follow.push_back(App->particles->CreateFollow(this, nullptr, { 8,0,2,2 }, { 12,2 }, { 20,10 }, 5, 60, true, false, particle_offset));
	particle_follow.push_back(App->particles->CreateFollow(this, nullptr, { 8,0,2,2 }, { 12,2 }, { 20,10 }, 5, 60, true, false));
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
			LookForRocks();
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
			LookForRocks();
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
			LookForRocks();
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
			LookForRocks();
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
			LookForRocks();
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
			LookForRocks();
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
			LookForRocks();
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
			LookForRocks();
			to_delete = true;
		}
		break; }
	default:
		break;
	}

}

void e1Particles::LookForEnemyCollision()
{
	BROFILER_CATEGORY("LookForEnemyCollsion", Profiler::Color::Yellow);

	std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
	std::vector<e1Entity*>::iterator item = entities.begin();

	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::ENEMY) {
			iPoint origin = arrow_tile;
			iPoint destination = (*item)->actual_tile;
			e1Enemy* enemy = (e1Enemy*)(*item);
			if (origin == destination && enemy->arrow_time != arrow_time) {
				enemy->arrow_time = arrow_time;
				enemy->GetHitted(App->scene->player->stats.attack_power_ability_1);
			}
		}
	}

}

void e1Particles::LookForRocks()
{
	BROFILER_CATEGORY("LookForRocks", Profiler::Color::Yellow);

	std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
	std::vector<e1Entity*>::iterator item = entities.begin();

	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::STATIC) {
			e1StaticEntity* ent = (e1StaticEntity*)(*item);
			if (ent->static_type == e1StaticEntity::Type::BREAKABLE_ROCK) {
				iPoint origin = arrow_tile;
				iPoint destination = (*item)->actual_tile;
				if (origin == destination) {
					e1Rock* rock = (e1Rock*)(*item);
					rock->GetHitted();
				}
			}
		}
	}
}

void e1Particles::SetFireBall()
{
	velocity.y = 160;
	position.y -= FIREBALL_ELEVATED_POS;
	position.x += 5;
	//actual_tile -= {1, 1};
	fireball_tile_objective = actual_tile;
	GoDown.PushBack({ 71,0,22,28 });
	GoDown.PushBack({ 93,0,22,28 });
	GoDown.PushBack({ 115,0,22,28 });
	GoDown.PushBack({ 137,0,22,28 });
	GoDown.speed = 3.0f;
	current_animation = &GoDown;
	particle_fire.push_back(App->particles->CreateFire(this, nullptr, { 0,0 }, { 0,2,2,0 }, { 20,10 }, { 20,4 }, { 60,-60 }, P_RANDOM, 65, 4, true, W_NON, { 11, 20 }));
	SetPivot(11, 2800);
	size.create(20, 20);

	shadow_fire_ball = new Animation();
	shadow_fire_ball->PushBack({ 1114,4756,14,10 });
	shadow_fire_ball->PushBack({ 1140,4756,14,10 });
	shadow_fire_ball->PushBack({ 1182,4756,14,10 });
	shadow_fire_ball->speed = 2;

	iPoint pos_shadow = App->map->MapToWorld(actual_tile.x, actual_tile.y);
	pos_shadow.x = (int)(App->render->camera.x) + (pos_shadow.x + 20) * (int)App->win->GetScale();
	pos_shadow.y = (int)(App->render->camera.y) + pos_shadow.y * (int)App->win->GetScale();
	App->gui->AddImage(pos_shadow.x, pos_shadow.y, { 0,0,0,0 }, nullptr, App->gui->screen, true, false, false, false, shadow_fire_ball);
}

void e1Particles::MoveFireBall(float dt)
{
	iPoint pos = App->map->WorldToMap(position.x, position.y + 20);

	if (pos == fireball_tile_objective) {
		FireBallExplosionCollision();
		to_delete = true;
	}

	position.y += floor(velocity.y * dt);
	

}

void e1Particles::FireBallExplosionCollision()
{
	BROFILER_CATEGORY("FireBallExplosionCollision", Profiler::Color::Yellow);

	std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
	std::vector<e1Entity*>::iterator item = entities.begin();

	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::ENEMY) {
			iPoint origin = fireball_tile_objective;
			iPoint destination = (*item)->actual_tile;
			e1Enemy* enemy = (e1Enemy*)(*item);
			if (origin == destination)
				enemy->GetHitted(App->scene->player->stats.attack_power_ability_1);
		}
		else if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::STATIC) {
			e1StaticEntity* ent = (e1StaticEntity*)(*item);
			if (ent->static_type == e1StaticEntity::Type::BREAKABLE_ROCK) {
				iPoint origin = fireball_tile_objective;
				iPoint destination = (*item)->actual_tile;
				if (origin == destination) {
					e1Rock* rock = (e1Rock*)(*item);
					rock->GetHitted();
				}
			}
		}
	}


}

void e1Particles::SetIceStake()
{
	initial_position = GetPosition() - iPoint(0, 15);
	iPoint vector = App->scene->player->GetPosition() + iPoint(0, -5) - initial_position;
	angle = RadToDeg(atan2(vector.y, vector.x));

	IdleDown.PushBack({ 179,28,35,12 });
	current_animation = &IdleDown;
	size.create(current_animation->GetCurrentFrame(0.f).w, current_animation->GetCurrentFrame(0.f).h);

	CreateParticleFollow(this, nullptr, { 0,0,10,10 });
	
}

void e1Particles::MoveIceStake(float dt)
{
	lerp_by += lerp_speed;
	position = lerp(initial_position, App->scene->player->GetPosition() + iPoint(0, -5), lerp_by).AproximateToIntFloor();

	if (lerp_by > 1.0F) {
		to_delete = true;
	}
}
