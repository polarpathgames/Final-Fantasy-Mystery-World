#include "App.h"
#include "m1GUI.h"
#include "m1Fonts.h"
#include "e1StaticEntity.h"
#include "m1DialogSystem.h"
#include "m1Cutscene.h"
#include "m1Scene.h"
#include "m1Collisions.h"
#include "e1Player.h"
#include "m1Window.h"
#include "App.h"
#include "m1Input.h"
#include "m1Map.h"
#include "m1Render.h"
#include "u1Label.h"
#include "e1StaticEntity.h"
#include "u1Button.h"
#include "u1Image.h"
#include "m1EntityManager.h"
#include "m1MenuManager.h"
#include "Brofiler/Brofiler.h"
#include "m1FadeToBlack.h"

m1DialogSystem::m1DialogSystem()
{
	name.assign("dialogue");
}
m1DialogSystem::~m1DialogSystem()
{
}

bool m1DialogSystem::Start()
{
	bool ret = true;
	LoadDialogue("assets/xml/Dialog.xml");
	return ret;
}

bool m1DialogSystem::Update(float dt)
{
	bool ret = true;

	if (!end_dial) {
		if (strcmp(actual_text.data(), hole_text.data()) != 0) {
			text_speed += 50 * dt;
			if (text_speed >= 1.0F) {
				text_speed = 0.0F;
				actual_text.resize(actual_text.size() + 1, hole_text[actual_text.size()]);
 				npc_text->SetText(actual_text.data());
			}
		}
		if ((text_button.empty() && actual_text.size() == hole_text.size()) || ((App->input->GetKeyDown(SDL_SCANCODE_SPACE) || App->input->GetControllerButtonDown(SDL_CONTROLLER_BUTTON_A)) && text_button.empty() && actual_text.size() > 2)) {
			int space = 0;
			for (int i = 0; i < currentNode->dialogOptions.size(); i++)
			{
				u1Button* but = App->gui->AddButton(0, space += 30, { 0,0,30,50 }, { 0,0,30,50 }, { 0,0,30,50 }, this, npc_text, false, false, true, true);
				but->SetFocus(FocusType::CLASSIC_FOCUS);
				text_button.push_back(but);
				player_text.push_back(App->gui->AddLabel(0, 0, currentNode->dialogOptions[i]->text.c_str(), text_button[i], BLACK, FontType::FF48, this, false));
			}
			if (actual_text.size() != hole_text.size()) {
				actual_text.resize(hole_text.size());
				actual_text = hole_text;
				npc_text->SetText(actual_text.data());
			}
		}
	}
		
	if (end_dial)
		LOG("TRUEEEEEEEE");
	else LOG("FALSEEEEEE");
	return ret;
}

bool m1DialogSystem::CleanUp()
{
	BROFILER_CATEGORY("DialogSystem CleanUp", Profiler::Color::GreenYellow)
	bool ret = true;

	for (int j = 0; j < dialogTrees.size(); j++)
	{
		for (int i = 0; i < dialogTrees[j]->dialogNodes.size(); i++) {
			for (int k = 0; k < dialogTrees[j]->dialogNodes[i]->dialogOptions.size(); k++) {
				delete dialogTrees[j]->dialogNodes[i]->dialogOptions[k];
				dialogTrees[j]->dialogNodes[i]->dialogOptions[k] = nullptr;
			}
			dialogTrees[j]->dialogNodes[i]->dialogOptions.clear();

			delete dialogTrees[j]->dialogNodes[i];
			dialogTrees[j]->dialogNodes[i] = nullptr;
		}
		dialogTrees[j]->dialogNodes.clear();

		delete dialogTrees[j];
		dialogTrees[j] = nullptr;
	}
	dialogTrees.clear();

	return ret;
}

bool m1DialogSystem::PerformDialogue(int tr_id)
{
	BROFILER_CATEGORY("DialogSystem PerformDialogue", Profiler::Color::GreenYellow)
	bool ret = true;
	treeid = tr_id;

	if (App->cutscene_manager->is_executing)
		return false;

	if (dialogTrees.empty())
		LOG("TreeEmpty");
	if (firstupdate)
	{
		if (CompareKarma() == true)
		{
			currentNode = dialogTrees[treeid]->dialogNodes[0];
		}
		else
		{
			for (int i = 0; i < dialogTrees[treeid]->dialogNodes.size(); i++)
			{
				// We search the mood of the bad response bad response = -1  / neutral = 0
				if (dialogTrees[treeid]->karma == dialogTrees[treeid]->dialogNodes[i]->karma)
				{
					currentNode = dialogTrees[treeid]->dialogNodes[i]; //This node is the bad response from the npc
					break;
				}
			}
		}
		firstupdate = false;
	}
		


	if (!waiting_input)
	{
		//Put the player's name in the lines of the npc dialog
		while (currentNode->text.find("PLAYERNAME") != std::string::npos)
		{
			currentNode->text.replace(currentNode->text.find("PLAYERNAME"), 10, App->globals.player_name);
		}
		waiting_input = !waiting_input;
		BlitDialog(); // Print the dialog in the screen
	}

	App->scene->player->BlockControls(true);
	end_dial = false;
	return ret;
}

void m1DialogSystem::BlitDialog()
{
	BROFILER_CATEGORY("DialogSystem BlitDialog", Profiler::Color::GreenYellow)

	dialog_panel = App->gui->AddImage(App->win->width*0.5f - 352, App->win->height - 199, {0, 3090,704,162}, this, App->gui->screen, true, false, false, false);
	char_face = App->gui->AddImage(8, 20, dialogTrees[treeid]->face, this, dialog_panel, true, false, false, false);
	actual_text = currentNode->text[0];
	hole_text = currentNode->text;
	npc_text = App->gui->AddLabel(App->win->width * 0.5f, App->win->height-50, currentNode->text.data(), dialog_panel, BLACK, FontType::FF48,this, false);
	npc_text->SetPosRespectParent(CENTERED_UP, 35);
	npc_text->SetText(actual_text.data());

}

void m1DialogSystem::DeleteText()
{
	BROFILER_CATEGORY("DialogSystem DeleteText", Profiler::Color::GreenYellow)
	App->gui->DeleteUIElement(npc_text);
	npc_text = nullptr;
	for (int i = 0; i < player_text.size(); i++)
	{
		App->gui->DeleteUIElement(player_text[i]);
		player_text[i] = nullptr;
	}
	player_text.clear();
	for (int j = 0; j < text_button.size(); j++)
	{
		App->gui->DeleteUIElement(text_button[j]);
		text_button[j] = nullptr;
	}
	text_button.clear();
	App->gui->DeleteUIElement(char_face);
	char_face = nullptr;
	App->gui->DeleteUIElement(dialog_panel);
	dialog_panel = nullptr;
	actual_text.clear();
	hole_text.clear();
}

bool m1DialogSystem::CompareKarma()
{
	bool ret = true;

	if (dialogTrees[treeid]->karma < 0)
		ret = false;

	return ret;
}

void m1DialogSystem::CheckForKarma(DialogOption* karmaNode)
{
	dialogTrees[treeid]->karma += karmaNode->karma;
}

bool m1DialogSystem::LoadDialogue(const char* file)
{
	BROFILER_CATEGORY("DialogSystem LoadDialogue", Profiler::Color::GreenYellow)
	bool ret = true;

	pugi::xml_parse_result result = tree_file.load_file(file);

	if (result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file, result.description());
		ret = false;
	}
	else {
		LOG("XML was loaded succesfully!");

		for (pugi::xml_node t = tree_file.child("dialogue").child("dialogtree"); t != NULL; t = t.next_sibling("dialogtree"))
		{
			DialogTree* tr = DBG_NEW DialogTree;
			tr->treeid = t.attribute("treeid").as_int();
			tr->karma = t.attribute("karma").as_int();
			tr->tag = t.attribute("tag").as_int();
			tr->face = { t.attribute("rect_x").as_int(),t.attribute("rect_y").as_int(), t.attribute("rect_w").as_int(), t.attribute("rect_h").as_int() };
			LoadTreeData(t, tr);
			dialogTrees.push_back(tr);
		}
	}

	tree_file.reset();

	return ret;
}

bool m1DialogSystem::LoadTreeData(pugi::xml_node& trees, DialogTree* oak)
{
	BROFILER_CATEGORY("DialogSystem LoadTreeData", Profiler::Color::GreenYellow)

	bool ret = true;

	//Filling the dialogue tree information
	for (pugi::xml_node n = trees.child("node");n != NULL; n = n.next_sibling("node"))
	{
		DialogNode* node = DBG_NEW DialogNode;
		node->text.assign(n.attribute("line").as_string());
		node->id = n.attribute("id").as_int();
		node->karma = n.attribute("karma").as_int();
		LoadNodesDetails(n, node);
		oak->dialogNodes.push_back(node);
		
	}
	return ret;
}

bool m1DialogSystem::LoadNodesDetails(pugi::xml_node& text_node, DialogNode* npc)
{
	bool ret = true;
	for (pugi::xml_node op = text_node.child("option"); op != NULL; op = op.next_sibling("option"))
	{
		DialogOption* option = DBG_NEW DialogOption;
		option->text.assign(op.attribute("line").as_string());
		option->nextnode = op.attribute("nextnode").as_int();
		option->karma = op.attribute("karma").as_int();
		option->tag = op.attribute("tag").as_int();
		npc->dialogOptions.push_back(option);
	}
	return ret;
}

bool m1DialogSystem::Load(pugi::xml_node& node)
{
	bool ret = true;

	CleanUp();
	for (pugi::xml_node t = node.child("dialogtree"); t != NULL; t = t.next_sibling("dialogtree"))
	{
		DialogTree* tr = DBG_NEW DialogTree;
		tr->treeid = t.attribute("treeid").as_int();
		tr->karma = t.attribute("karma").as_int();
		tr->tag = t.attribute("tag").as_int();
		tr->face = { t.attribute("rect_x").as_int(),t.attribute("rect_y").as_int(), t.attribute("rect_w").as_int(), t.attribute("rect_h").as_int() };
		LoadTreeData(t, tr);
		dialogTrees.push_back(tr);
	}
	return ret;
}

bool m1DialogSystem::Save(pugi::xml_node& node) const
{
	 std::vector<DialogTree*>::const_iterator item = dialogTrees.cbegin();
	 int trees = 0;
	for (; item != dialogTrees.cend(); ++item)
	{
		pugi::xml_node t = node.append_child("dialogtree");
		t.append_attribute("treeid") = (int)dialogTrees[trees]->treeid;
		t.append_attribute("karma") = (int)dialogTrees[trees]->karma;
		t.append_attribute("tag") = (int)dialogTrees[trees]->tag;
		t.append_attribute("rect_x") = (int)dialogTrees[trees]->face.x;
		t.append_attribute("rect_y") = (int)dialogTrees[trees]->face.y;
		t.append_attribute("rect_w") = (int)dialogTrees[trees]->face.w;
		t.append_attribute("rect_h") = (int)dialogTrees[trees]->face.h;
		std::vector<DialogNode*>::const_iterator item2 = dialogTrees[trees]->dialogNodes.cbegin();
		int nodes = 0;
		for (; item2 != dialogTrees[trees]->dialogNodes.cend(); ++item2)
		{
			pugi::xml_node n = t.append_child("node");
			n.append_attribute("line") = dialogTrees[trees]->dialogNodes[nodes]->text.data();
			n.append_attribute("id") = (int)dialogTrees[trees]->dialogNodes[nodes]->id;
			n.append_attribute("karma") = (int)dialogTrees[trees]->dialogNodes[nodes]->karma;
			std::vector<DialogOption*>::const_iterator item3 = dialogTrees[trees]->dialogNodes[nodes]->dialogOptions.cbegin();
			int options = 0;
			for (; item3 != dialogTrees[trees]->dialogNodes[nodes]->dialogOptions.cend(); ++item3)
			{
				pugi::xml_node o = n.append_child("option");
				o.append_attribute("line") = dialogTrees[trees]->dialogNodes[nodes]->dialogOptions[options]->text.data();
				o.append_attribute("nextnode") = (int)dialogTrees[trees]->dialogNodes[nodes]->dialogOptions[options]->nextnode;
				o.append_attribute("karma") = (int)dialogTrees[trees]->dialogNodes[nodes]->dialogOptions[options]->karma;
				o.append_attribute("tag") = (int)dialogTrees[trees]->dialogNodes[nodes]->dialogOptions[options]->tag;
				options++;
			}
			nodes++;
		}
		trees++;
	}
	return true;
}

bool m1DialogSystem::Interact(u1GUI* interaction)
{
	bool ret = true;

	for (int i = 0; i < text_button.size(); i++)
	{
		if (interaction == text_button[i])
		{
			if (currentNode->dialogOptions[i]->nextnode < dialogTrees[treeid]->dialogNodes.size())
			{
				dialogTrees[treeid]->karma += currentNode->dialogOptions[i]->karma;
				currentNode = dialogTrees[treeid]->dialogNodes[currentNode->dialogOptions[i]->nextnode];
 				waiting_input = false;
				DeleteText();
				return false;
			}
		    else
		    {
			   dialogTrees[treeid]->karma += currentNode->dialogOptions[i]->karma;
			   dialogTrees[treeid]->tag += currentNode->dialogOptions[i]->tag;
			   DeleteText();
			   std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
			   std::vector<e1Entity*>::iterator item = entities.begin();
			   switch (dialogTrees[treeid]->tag)
			   {
			   case 1: // SHOP
				   App->menu_manager->CreateShopMenu();
				   App->scene->SetMenuState(StatesMenu::SHOP_MENU);
				   App->globals.shop_gone = true;
				   break;
			   case -2: //FOUNTAIN MANA
				   App->scene->player->AugmentMana(100);
				   App->scene->player->BlockControls(false);
				   for (; item != entities.end(); ++item) {
					   if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::STATIC) {
						   e1StaticEntity* stat = (e1StaticEntity*)(*item);
						   if (stat->static_type == e1StaticEntity::Type::QUEST_FOUNTAIN) {
							   delete stat->idle;
							   stat->idle = nullptr;
							   stat->idle = new Animation();
							   stat->idle->PushBack({ 1141, 5,50,43 });
							   stat->frame = stat->idle->frames[0];
							   stat->current_animation = stat->idle;
							   stat->position = { stat->position.x + 7, stat->position.y + 5 };
							   break;
						   }
					   }
				   }
				   App->menu_manager->EnableHUD(true);
				   App->map->quest_rooms->actual_room->fountain_drunk = true;
				   break;
			   case 2: //FOUNTAIN LIVES
				   App->scene->player->AugmentLives(250);
				   App->scene->player->BlockControls(false);
				   for (; item != entities.end(); ++item) {
					   if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::STATIC) {
						   e1StaticEntity* stat = (e1StaticEntity*)(*item);
						   if (stat->static_type == e1StaticEntity::Type::QUEST_FOUNTAIN) {
							   delete stat->idle;
							   stat->idle = nullptr;
							   stat->idle = new Animation();
							   stat->idle->PushBack({  1141, 5,50,43  });
							   stat->frame = stat->idle->frames[0];
							   stat->current_animation = stat->idle;
							   stat->position = { stat->position.x + 7, stat->position.y + 5 };
							   break;
						   }
					   }
				   }
				   App->map->quest_rooms->actual_room->fountain_drunk = true;
				   App->menu_manager->EnableHUD(true);
				   break;
			   case 3: //Fountain drunk
				   App->menu_manager->EnableHUD(true);
				   App->scene->player->BlockControls(false);
				   break;
			   case 33: { // take flash
				   App->globals.ability2_gained = true;
				   App->scene->player->BlockControls(true);
				   App->menu_manager->CreateHelpAbilityMenu(AbilityType::FLASH);
				  // App->menu_manager->ShowHUD(false);
				   App->scene->SetMenuState(StatesMenu::FIRSTABILITY_MENU);
				   std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
				   std::vector<e1Entity*>::iterator item = entities.begin();
				   for (; item != entities.end(); ++item) {
					   if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::STATIC && static_cast<e1StaticEntity*>(*item)->static_type == e1StaticEntity::Type::FLASH_INFO) {
						   (*item)->to_delete = true;
						   break;
					   }
				   }
				   break; }
			   case 900:
				   App->menu_manager->EnableHUD(true);
				   App->scene->player->BlockControls(false);
				   break;
			   case -3://SAVE FUNCTION
			   {
				   //Save function
				   Animation * anim = new Animation();
				   anim->PushBack({ 1130,4482,50,49 });
				   anim->PushBack({ 1210,4483,50,49 });
				   anim->PushBack({ 1280,4482,50,49 });
				   anim->PushBack({ 1353,4482,50,49 });
				   anim->PushBack({ 1425,4482,50,49 });
				   anim->PushBack({ 1497,4483,50,49 });
				   anim->PushBack({ 1570,4482,50,49 });
				   anim->PushBack({ 1130,4539,50,49 });
				   anim->PushBack({ 1210,4539,50,49 });
				   anim->PushBack({ 1282,4539,50,49 });
				   anim->PushBack({ 1355,4539,50,49 });
				   anim->PushBack({ 1426,4539,50,49 });
				   anim->PushBack({ 1496,4539,50,49 });
				   anim->PushBack({ 1569,4539,50,49 });
				   anim->loop = true;
				   anim->speed = 14;
				   App->gui->AddImage(900, 650, { 0,0,0,0 }, nullptr, App->gui->screen, true, false, false, false, anim);
				   App->scene->player->BlockControls(false);
				   App->SaveGame("save_game.xml");
				   for (; item != entities.end(); ++item) {
					   if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::STATIC && static_cast<e1StaticEntity*>(*item)->static_type == e1StaticEntity::Type::FEATHER) {
						   static_cast<e1StaticEntity*>(*item)->interacting_state = e1StaticEntity::InteractingStates::NONE;
						   if (static_cast<e1StaticEntity*>(*item)->button_interact != nullptr) {
							   static_cast<e1StaticEntity*>(*item)->button_interact->to_delete = true;
						   }
						   break;
					   }
				   }
				   break;
			   }
			   case 4: //Checking if player has gone to the shop
				   App->cutscene_manager->PlayCutscene("assets/xml/CutsceneHomeSleep.xml");
				   App->map->lobby_state = LobbyState::ICE_LOBBY;
				   App->globals.CutSceneHomeToSleepQuest2 = true;
				   //App->scene->player->BlockControls(false);
				   break;
			   case 5: //Portal Dialog Quest 2
				   App->map->lobby_state = LobbyState::NORMAL_LOBBY;
				   App->fade_to_black->FadeToBlack(Maps::LOBBY);
				   App->globals.ice_queen_killed = true;
				   for (; item != entities.end(); ++item) {
					   if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::STATIC && static_cast<e1StaticEntity*>(*item)->static_type == e1StaticEntity::Type::PORTAL) {
						   static_cast<e1StaticEntity*>(*item)->interacting_state = e1StaticEntity::InteractingStates::NONE;
						   if (static_cast<e1StaticEntity*>(*item)->button_interact != nullptr) {
							   static_cast<e1StaticEntity*>(*item)->button_interact->to_delete = true;
						   }
						   break;
					   }
				   }
				   break;
			   case 6: //Quest 3 beginning
			   {
				   App->cutscene_manager->PlayCutscene("assets/xml/CutsceneHomeSleep2.xml");
				   App->globals.sleep2 = true;
				   App->map->lobby_state = LobbyState::NIGHT_LOBBY;
				   break;
			   }				  
			   case 7: //Quest 3 Portal				   
				   App->fade_to_black->FadeToBlack(Maps::FINAL_QUEST, 2.0F);
				   break;
			   case 30: //old statue tutorial diagonal
				   App->menu_manager->CreateHelpDiagonalMenu();
				   App->scene->SetMenuState(StatesMenu::HELP_DIAGONAL_MENU);
				   break;
			   case 60: //old statue tutorial ATTACK
				   App->menu_manager->CreateHelpAttackMenu();
				   App->scene->SetMenuState(StatesMenu::HELP_ATTACK_MENU);
				   break;
			   case 90: //old statue tutorial ATTACK
				   App->menu_manager->CreateHelpAbilityMenu(AbilityType::ABILITY1);
				   App->scene->SetMenuState(StatesMenu::HELP_ABILITY_MENU);
				   break;
			   case 43: // go to quest 2 in lobby ice
				   App->fade_to_black->FadeToBlack(Maps::QUEST2, 2.0F);
				   break;
			   case 190: //old statue tutorial ATTACK
				   App->menu_manager->CreateHelpAbilityMenu(AbilityType::FLASH);
				   App->scene->SetMenuState(StatesMenu::HELP_ABILITY_MENU);
				   break;
			   default:
				   App->scene->player->BlockControls(false);
				   break;
			   }
			   dialogTrees[treeid]->tag = 0;
			   waiting_input = false;
			   firstupdate = true;
			   end_dial = true;
			   return false;
		    }
		}
		
	}
	
	return ret;
}