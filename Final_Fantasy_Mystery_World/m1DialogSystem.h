#ifndef _J1DIALOGSYSTEM_H
#define _J1DIALOGSYSTEM_H

#include "m1Module.h"
#include <string>
#include <vector>
#include "App.h"
#include "p2Log.h"

class u1Label;
class u1Image;
class u1Button;

class DialogOption
{
public:
	DialogOption() {};
	~DialogOption() {};
public:
	std::string text;
	int nextnode;
	int karma;
	int tag;
};

class DialogNode
{
public:
	DialogNode() {};
	~DialogNode() {};
public:
	std::string text;
	std::vector <DialogOption*> dialogOptions;
	int id, karma;
};
class DialogTree
{
public:
	DialogTree() {};
	~DialogTree() {};

public:
	std::vector <DialogNode*> dialogNodes;
	int treeid, karma, tag;
	SDL_Rect face;
};

class m1DialogSystem : public m1Module
{
public:
	m1DialogSystem();
	~m1DialogSystem();
	bool Start();
	bool Update(float dt);
	bool CleanUp();
	bool Interact(u1GUI* element);
	bool Save(pugi::xml_node&) const;
	bool Load(pugi::xml_node&);
	void DeleteText();
	bool PerformDialogue(int tr_id);
	bool LoadDialogue(const char*);
	bool LoadTreeData(pugi::xml_node& trees, DialogTree* oak);
	bool LoadNodesDetails(pugi::xml_node& text_node, DialogNode* npc);
	void BlitDialog();
	bool CompareKarma();
	void CheckForKarma(DialogOption* karmaNode);
public:
	bool firstupdate = true, waiting_input = false, end_dial = true, black = false;
	std::vector <DialogTree*> dialogTrees;

private:
	
	DialogNode* currentNode = nullptr;
	
	int treeid = 0;
	pugi::xml_document	tree_file;	
	
	u1Label* npc_text = nullptr;
	std::vector <u1Label*> player_text;
	std::vector <u1Button*> text_button;

	u1Image* dialog_panel = nullptr;
	u1Image* char_face = nullptr;
};

#endif