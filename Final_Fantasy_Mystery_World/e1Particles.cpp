#include "e1Particles.h"
#include "App.h"
#include "m1Map.h"
#include "m1EntityManager.h"
#include "m1Window.h"
#include "m1Input.h"
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
}

bool e1Particles::PreUpdate()
{
	if (particle_type == ParticleType::AMAZING_DRAGON_FIRE_BALL) {
		MoveAmazingFireBall(App->GetDeltaTime());
	}

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
	case e1Particles::ParticleType::THUNDERBOLT: {
		MoveIceStake(dt);
		break; }
	case e1Particles::ParticleType::AMAZING_DRAGON_FIRE_BALL: {
		iPoint pos = App->map->MapToWorld(actual_tile.x, actual_tile.y);
		SDL_Rect rect{ 2664,4659,120,90 };
		rect = { 2657,4660,64,40 };
		App->render->Blit((SDL_Texture*)App->gui->GetAtlas(), pos.x - 13, pos.y - 11, &rect, true);
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
	if (rotate_angle) {
		App->render->Blit(data.tileset.texture, position.x, position.y, &current_animation->GetCurrentFrame(dt), true, SDL_FLIP_NONE, 1.0f, nullptr, angle, size.x*0.5f, size.y*0.5f);
	}
	else {
		e1Entity::Draw(dt);
		if (App->debug && particle_type == ParticleType::AMAZING_DRAGON_FIRE_BALL) {
			std::vector<iPoint>::iterator item = amazing_fire_ball_attack_range.begin();
			for (; item != amazing_fire_ball_attack_range.end(); ++item) {
				iPoint pos = App->map->MapToWorld((*item).x, (*item).y);
				App->render->Blit(App->scene->player->ground, pos.x + 1, pos.y - 8, NULL, true);
			}
		}
	}
}

void e1Particles::SetParticle(const ParticleType & particle_type, const Direction & dir, const uint&turns)
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
	case ParticleType::THUNDERBOLT:
		name.assign("thunderbolt");
		SetThunderbolt();
		break;
	case ParticleType::AMAZING_DRAGON_FIRE_BALL:
		name.assign("amazing dragon fire ball");
		SetAmazingDragonFireBall(turns);
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
		anim.GoDownLeft.PushBack({ 17,25,23,15 });
		SetPivot(6, 12);
		current_animation = &anim.GoDownLeft;
		max_arrow_distance.create(arrow_tile.x, arrow_tile.y + MAX_ARROW);
		particle_offset.create(10, -10);
		break;
	case Direction::UP_RIGHT: // need fix
		position.x += 9;
		position.y -= 16;
		anim.GoUpRight.PushBack({ 41,9,23,15 });
		SetPivot(17, 4);
		particle_offset.create(-10, 10);
		current_animation = &anim.GoUpRight;
		max_arrow_distance.create(arrow_tile.x, arrow_tile.y - MAX_ARROW);
		break;
	case Direction::UP_LEFT: // need fix
		//position.x += 13;
		position.y -= 16;
		anim.GoUpLeft.PushBack({ 17,9,23,15 });
		SetPivot(5, 4);
		current_animation = &anim.GoUpLeft;
		particle_offset.create(10, 10);
		max_arrow_distance.create(arrow_tile.x - MAX_ARROW, arrow_tile.y);
		break;
	case Direction::DOWN_RIGHT: // need fix
		position.x += 11;
		position.y -= 11;
		anim.GoDownRight.PushBack({ 41,25,23,15 });
		SetPivot(18, 13);
		current_animation = &anim.GoDownRight;
		particle_offset.create(-10, -10);
		max_arrow_distance.create(arrow_tile.x + MAX_ARROW, arrow_tile.y);
		break;
	case Direction::DOWN:
		position.x += 13;
		position.y -= 5;
		anim.GoDown.PushBack({ 8,8,8,27 });
		SetPivot(4, 21);
		current_animation = &anim.GoDown;
		particle_offset.create(0, -5);
		max_arrow_distance.create(arrow_tile.x + MAX_ARROW, arrow_tile.y + MAX_ARROW);
		break;
	case Direction::UP:
		position.x += 13;
		position.y -= 15;
		anim.GoUp.PushBack({ 0,8,8,27 });
		SetPivot(4, 7);
		current_animation = &anim.GoUp;
		particle_offset.create(0, 5);
		max_arrow_distance.create(arrow_tile.x - MAX_ARROW, arrow_tile.y - MAX_ARROW);
		break;
	case Direction::LEFT:
		position.x -= 5;
		position.y -= 7;
		anim.GoLeft.PushBack({ 28,0,28,7 });
		SetPivot(7, 4);
		current_animation = &anim.GoLeft;
		particle_offset.create(5, 0);
		max_arrow_distance.create(arrow_tile.x - MAX_ARROW, arrow_tile.y + MAX_ARROW);
		break;
	case Direction::RIGHT:
		position.x += 10;
		position.y -= 7;
		anim.GoRight.PushBack({ 0,0,28,7 });
		SetPivot(21, 4);
		current_animation = &anim.GoRight;
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
	anim.GoDown.PushBack({ 71,0,22,28 });
	anim.GoDown.PushBack({ 93,0,22,28 });
	anim.GoDown.PushBack({ 115,0,22,28 });
	anim.GoDown.PushBack({ 137,0,22,28 });
	anim.GoDown.speed = 3.0f;
	current_animation = &anim.GoDown;
	particle_fire.push_back(App->particles->CreateFire(this, nullptr, { 0,0 }, { 0,2,2,0 }, { 20,10 }, { 20,4 }, { 60,-60 }, P_RANDOM, 65, 4, true, W_NON, { 11, 20 }));
	SetPivot(11, 2800);
	size.create(20, 20);

	shadow_fire_ball = new Animation();
	shadow_fire_ball->PushBack({ 1102,4719,96,48 });
	shadow_fire_ball->PushBack({ 1200,4719,96,48 });
	shadow_fire_ball->PushBack({ 1298,4719,96,48 });
	shadow_fire_ball->speed = 2;

	iPoint pos_shadow = App->map->MapToWorld(actual_tile.x, actual_tile.y);
	pos_shadow.x = (int)(App->render->camera.x) + (pos_shadow.x) * (int)App->win->GetScale();
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
	final_position = App->scene->player->GetPosition() + iPoint(0, -5);
	iPoint vector = final_position - initial_position;
	angle = RadToDeg(atan2(vector.y, vector.x));
	lerp_speed = 0.2f;

	rotate_angle = true;

	anim.IdleDown.PushBack({ 179,28,35,12 });
	current_animation = &anim.IdleDown;
	size.create(current_animation->GetCurrentFrame(0.f).w, current_animation->GetCurrentFrame(0.f).h);

	pivot.create(0, 50);
}

void e1Particles::SetThunderbolt()
{
	initial_position = GetPosition() - iPoint(0, 5);
	final_position = App->scene->player->GetPosition() + iPoint(0, -10);
	iPoint vector = final_position - initial_position;
	angle = RadToDeg(atan2(vector.y, vector.x));
	lerp_speed = 0.2f;

	fPoint v2 = vector.AproximateToFloat() * 0.7f;
	final_position = final_position - v2.AproximateToIntCast();


	rotate_angle = true;

	anim.IdleDown.PushBack({ 214,27,36,13 });
	current_animation = &anim.IdleDown;
	size.create(current_animation->GetCurrentFrame(0.f).w, current_animation->GetCurrentFrame(0.f).h);

	pivot.create(0, 50);
}

void e1Particles::SetAmazingDragonFireBall(const uint & turns)
{
	allow_turn = true;

	this->turns = turns;
	velocity.y = 160;
	position.y -= FIREBALL_ELEVATED_POS;
	position.x -= 7;

	amazing_fire_ball_attack_range.push_back(actual_tile + iPoint{ -1,-1 });
	amazing_fire_ball_attack_range.push_back(actual_tile + iPoint{ 1,1 });
	amazing_fire_ball_attack_range.push_back(actual_tile + iPoint{ -1,1 });
	amazing_fire_ball_attack_range.push_back(actual_tile + iPoint{ 1,-1 });
	amazing_fire_ball_attack_range.push_back(actual_tile);
	amazing_fire_ball_attack_range.push_back(actual_tile + iPoint{ 0,1 });
	amazing_fire_ball_attack_range.push_back(actual_tile + iPoint{ 0,-1 });
	amazing_fire_ball_attack_range.push_back(actual_tile + iPoint{ 1,0 });
	amazing_fire_ball_attack_range.push_back(actual_tile + iPoint{ -1,0 });

	anim.GoDown.PushBack({ 47,55,52,64 });
	anim.GoDown.PushBack({ 99,55,52,64 });
	anim.GoDown.PushBack({ 151,55,52,64 });
	anim.GoDown.PushBack({ 203,55,52,64 });
	anim.GoDown.speed = 3.0f;
	current_animation = &anim.GoDown;

	SetPivot(11, 2800);
	size.create(20, 20);
}

void e1Particles::MoveAmazingFireBall(float dt)
{
	if (turns == 0) {
		position.y += floor(velocity.y * dt);
		iPoint pos = App->map->WorldToMap(position.x, position.y + 50);
		if (pos == actual_tile + iPoint{ 1,1 }) {
			to_delete = true;
			turn_done = true;
			CollisionAmazingBall();
			App->render->CameraTremble(0.63F, 1.9F);
			App->input->ControllerVibration(0.5F, 200);
		}
	}
	else {
		--turns;
		turn_done = true;
	}


}

void e1Particles::CollisionAmazingBall()
{

	std::vector<iPoint>::iterator item = amazing_fire_ball_attack_range.begin();
	for (; item != amazing_fire_ball_attack_range.end(); ++item) {
		if ((*item) == App->scene->player->actual_tile) {
			App->scene->player->GetHitted(60);
			break;
		}
	}

}

void e1Particles::MoveIceStake(float dt)
{
	lerp_by += lerp_speed;
	position = lerp(initial_position, final_position, lerp_by).AproximateToIntFloor();

	if (lerp_by > 1.0F) {
		to_delete = true;
	}
}
