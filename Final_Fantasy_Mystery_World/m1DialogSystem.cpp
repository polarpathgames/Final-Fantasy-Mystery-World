#include "App.h"
#include "m1GUI.h"
#include "m1Fonts.h"
#include "m1DialogSystem.h"
#include "m1Window.h"
#include "m1Input.h"
#include "u1Label.h"
#include "u1Image.h"

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
	bool ret = true;

	for (int j = 0; j < dialogTrees.size(); j++)
	{
		for (int i = 0; i < dialogTrees[j]->dialogNodes.size(); i++)
			delete dialogTrees[j]->dialogNodes[i];

		dialogTrees[j]->dialogNodes.clear();
		delete dialogTrees[j];
	}
	dialogTrees.clear();

	return ret;
}

bool m1DialogSystem::PerformDialogue(int tr_id)
{
	bool ret = true;
	if (dialogTrees.empty())
		LOG("TreeEmpty");
	if (firstupdate)
	{
		currentNode = dialogTrees[tr_id]->dialogNodes[0];
		firstupdate = false;
	}
	if (currentNode->dialogOptions[0]->nextnode > dialogTrees[tr_id]->dialogNodes.size())
	{
		DeleteText();
		return ret;
	}
	if (CompareKarma() == true)
	{
		//Find the next node 
		if (input >= 0 && input < currentNode->dialogOptions.size()) //Only if the input is valid
		{
			for (int j = 0; j < dialogTrees[tr_id]->dialogNodes.size(); j++)
			{
				if (currentNode->dialogOptions[input]->nextnode == dialogTrees[tr_id]->dialogNodes[j]->id) //If the option id is the same as one of the nodes ids in the tree
				{
					CheckForKarma(currentNode);
					currentNode = dialogTrees[tr_id]->dialogNodes[j]; // we assign our node pointer to the next node in the tree				
					break;
				}
			}
		}
	}
	else if (CompareKarma() == false)
	{
		for (int i = 0; i < dialogTrees[tr_id]->dialogNodes.size(); i++)
		{
			// We search the mood of the bad response bad response = -1  / neutral = 0
			if (dialogTrees[tr_id]->karma == dialogTrees[tr_id]->dialogNodes[i]->karma)
			{
				currentNode = dialogTrees[tr_id]->dialogNodes[i]; //This node is the bad response from the npc
			}
		}
	}
	
	if (!waiting_input)
	{
		//Put the player's name in the lines of the npc dialog
		while (currentNode->text.find("PLAYERNAME") != std::string::npos)
		{
			currentNode->text.replace(currentNode->text.find("PLAYERNAME"), 10, "Ivan");
		}
		waiting_input = !waiting_input;
		BlitDialog(); // Print the dialog in the screen
	}
	
	return ret;
}

void m1DialogSystem::BlitDialog()
{
	dialog_panel = App->gui->AddImage(0, App->win->height - 199, {0, 3088,1023,199}, this, App->gui->screen, true, false, false, false);
	npc_text = App->gui->AddLabel(App->win->width * 0.5f, App->win->height-50, currentNode->text.c_str(), dialog_panel, BLACK, FontType::FF48,this, false);
	npc_text->SetPosRespectParent(LEFT_UP, 15);
	int space = 590;
	for (int i = 0; i < currentNode->dialogOptions.size(); i++)
	{
		u1Label* lb = new u1Label;
		lb = App->gui->AddLabel(0 + 15, space += 30, currentNode->dialogOptions[i]->text.c_str(), App->gui->screen, WHITE, FontType::FF48, this, false);
		player_text.push_back(lb);
	}
	

}

void m1DialogSystem::DeleteText()
{
	App->gui->DeleteUIElement(npc_text);
	npc_text = nullptr;
	for (int i = 0; i < player_text.size(); i++)
	{
		App->gui->DeleteUIElement(player_text[i]);
		player_text[i] = nullptr;
	}
	player_text.clear();
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

void m1DialogSystem::CheckForKarma(DialogNode* karmaNode)
{
	dialogTrees[treeid]->karma += karmaNode->dialogOptions[input]->karma;
}

bool m1DialogSystem::LoadDialogue(const char* file)
{
	bool ret = true;

	pugi::xml_parse_result result = tree_file.load_file(file);

	if (result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file, result.description());
		ret = false;
	}
	else
		LOG("XML was loaded succesfully!");

	if(ret)
		for (pugi::xml_node t = tree_file.child("dialogue").child("dialogtree"); t != NULL; t = t.next_sibling("dialogtree"))
		{
			DialogTree* tr = new DialogTree;
			tr->treeid = t.attribute("treeid").as_int();
			tr->karma = t.attribute("karma").as_int();
			LoadTreeData(t, tr);
			dialogTrees.push_back(tr);
		}

	return ret;
}

bool m1DialogSystem::LoadTreeData(pugi::xml_node& trees, DialogTree* oak)
{
	bool ret = true;

	//Filling the dialogue tree information
	for (pugi::xml_node n = trees.child("node");n != NULL; n = n.next_sibling("node"))
	{
		DialogNode* node = new DialogNode;
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
		DialogOption* option = new DialogOption;
		option->text.assign(op.attribute("line").as_string());
		option->nextnode = op.attribute("nextnode").as_int();
		option->karma = op.attribute("karma").as_int();
		npc->dialogOptions.push_back(option);
	}
	return ret;
}