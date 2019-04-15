#ifndef _M1CUTSCENE_H__
#define _M1CUTSCENE_H__

#include "m1Module.h"
#include "e1Entity.h"
#include "p2PerfTimer.h"
#include "c1CutsceneAction.h"
#include <vector>
#include "c1CutsceneElement.h"
#include <map>


class m1CutScene : public m1Module {
public:

	m1CutScene();
	virtual ~m1CutScene() {};

	bool Awake(pugi::xml_node&);

	bool Start() { return true; };
	bool Update(float dt);
	bool CleanUp();

	//Cutscene Functions

	void PlayCutscene(std::string path);
	
	void ExecuteCutscene(float dt);
	void ClearCutscene();

	double GetTimer();
	void SetExecuting(bool executing);

private:
	bool LoadCutscene(std::string path);
private:
	p2PerfTimer cutscene_timer;
	bool is_executing = false;
	bool start = true;

public:
	pugi::xml_document cutscene_file;
	std::vector<c1CutsceneAction*> actions;
	std::map<std::string, c1CutsceneElement*> elements;

	std::vector<c1CutsceneAction*>::iterator item;

};





#endif // !_M1CUTSCENE_H__

