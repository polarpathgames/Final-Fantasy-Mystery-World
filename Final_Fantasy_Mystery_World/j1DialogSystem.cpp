#include "j1App.h"
#include "j1UIManager.h"
#include "j1Fonts.h"
#include "j1DialogSystem.h"
#include "j1Input.h"
#include "GUI_Label.h"
#include "GUI_Button.h"

j1DialogSystem::j1DialogSystem()
{
}
j1DialogSystem::~j1DialogSystem()
{
}

bool j1DialogSystem::Start()
{
	bool ret = true;
	LoadDialogue("Dialog.xml");
	return ret;
}

bool j1DialogSystem::Update(float dt)
{
	bool ret = true;
		
	return ret;
}

bool j1DialogSystem::CleanUp()
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

void j1DialogSystem::PerformDialogue(int tr_id)
{
	if (dialogTrees.empty())
		LOG("TreeEmpty");

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

	//Put the player's name in the lines of the npc dialog


	while(currentNode->text.find("PLAYERNAME") != std::string::npos)
	{	
		currentNode->text.replace(currentNode->text.find("PLAYERNAME"), 10, "Ivan");
	}
	// Print the dialog in the screen
	BlitDialog();
}

void j1DialogSystem::BlitDialog()
{
	App->ui_manager->AddLabel(150, 180, currentNode->text.c_str(), App->ui_manager->screen, BLACK, FontType::FF48,this, false);
	int space = 200;
	for (int i = 0; i < currentNode->dialogOptions.size(); i++)
		App->ui_manager->AddLabel(150, space += 30, currentNode->dialogOptions[i]->text.c_str(), App->ui_manager->screen, GREEN, FontType::FF48, this, false);

}

bool j1DialogSystem::CompareKarma()
{
	bool ret = true;

	if (dialogTrees[treeid]->karma < 0)
		ret = false;

	return ret;
}

void j1DialogSystem::CheckForKarma(DialogNode* karmaNode)
{
	dialogTrees[treeid]->karma += karmaNode->dialogOptions[input]->karma;
}

bool j1DialogSystem::LoadDialogue(const char* file)
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

bool j1DialogSystem::LoadTreeData(pugi::xml_node& trees, DialogTree* oak)
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

bool j1DialogSystem::LoadNodesDetails(pugi::xml_node& text_node, DialogNode* npc)
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