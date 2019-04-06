#ifndef _J1DIALOGSYSTEM_H
#define _J1DIALOGSYSTEM_H

#include "j1Module.h"
#include <string>
#include <vector>
#include "j1App.h"
#include "p2Log.h"

class DialogOption
{
public:
	DialogOption() {};
	~DialogOption() {};
public:
	std::string text;
	int nextnode;
	int karma;
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
	int treeid, karma;
};

class j1DialogSystem : public j1Module
{
public:
	j1DialogSystem();
	~j1DialogSystem();
	bool Start();
	bool Update(float dt);
	bool CleanUp();

	void PerformDialogue(int tr_id);
	bool LoadDialogue(const char*);
	bool LoadTreeData(pugi::xml_node& trees, DialogTree* oak);
	bool LoadNodesDetails(pugi::xml_node& text_node, DialogNode* npc);
	void BlitDialog();
	bool CompareKarma();
	void CheckForKarma(DialogNode* karmaNode);
private:
	std::vector <DialogTree*> dialogTrees;
	DialogNode* currentNode;
	int input = 7;
	int treeid = 0;
	pugi::xml_document	tree_file;	
};

#endif