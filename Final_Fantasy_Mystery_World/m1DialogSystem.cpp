#include "App.h"
#include "m1GUI.h"
#include "m1Fonts.h"
#include "e1StaticEntity.h"
#include "m1DialogSystem.h"
#include "m1Scene.h"
#include "e1Player.h"
#include "m1Window.h"
#include "App.h"
#include "m1Input.h"
#include "u1Label.h"
#include "u1Button.h"
#include "u1Image.h"
#include "Brofiler/Brofiler.h"

m1DialogSystem::m1DialogSystem()
{
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

	return ret;
}

void m1DialogSystem::BlitDialog()
{
	BROFILER_CATEGORY("DialogSystem BlitDialog", Profiler::Color::GreenYellow)

	dialog_panel = App->gui->AddImage(App->win->width*0.5f - 352, App->win->height - 199, {0, 3090,704,162}, this, App->gui->screen, true, false, false, false);
	char_face = App->gui->AddImage(8, 20, dialogTrees[treeid]->face, this, dialog_panel, true, false, false, false);
	npc_text = App->gui->AddLabel(App->win->width * 0.5f, App->win->height-50, currentNode->text.c_str(), dialog_panel, BLACK, FontType::FF48,this, false);
	npc_text->SetPosRespectParent(CENTERED_UP, 35);
	int space = 0;
	for (int i = 0; i < currentNode->dialogOptions.size(); i++)
	{
		text_button.push_back(App->gui->AddButton(0, space += 30, { 0,0,30,50 }, { 0,0,30,50 }, { 0,0,30,50 }, this, npc_text, false, false, true, true));
		player_text.push_back(App->gui->AddLabel(0, 0, currentNode->dialogOptions[i]->text.c_str(), text_button[i], BLACK, FontType::FF48, this, false));
	}
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
			   switch (dialogTrees[treeid]->tag)
			   {
			   case 1: // SHOP
				   App->scene->CreateShopMenu();
				   App->scene->SetMenuState(StatesMenu::SHOP_MENU);
				   break;
			   case -2: //FOUNTAIN MANA
				   App->scene->player->AugmentMana(100);
				   App->scene->player->BlockControls(false);
				   break;
			   case 2: //FOUNTAIN LIVES
				   App->scene->player->AugmentLives(250);
				   App->scene->player->BlockControls(false);
				   break;
			   case -3://SAVE FUNCTION
				   //Save function
				   App->scene->player->BlockControls(false);
				   break;
			   case 30: //old statue tutorial diagonal
				   App->scene->CreateHelpDiagonalMenu();
				   App->scene->SetMenuState(StatesMenu::HELP_DIAGONAL_MENU);
				   break;
			   case 60: //old statue tutorial ATTACK
				   App->scene->CreateHelpAttackMenu();
				   App->scene->SetMenuState(StatesMenu::HELP_ATTACK_MENU);
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