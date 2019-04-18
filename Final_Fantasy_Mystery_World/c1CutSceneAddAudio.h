#ifndef __C1CUTSCENEADDAUDIO_H__
#define __C1CUTSCENEADDAUDIO_H__

#include "c1CutSceneAction.h"
#include "c1CutSceneEntity.h"
#include "p2Log.h"

class c1CutSceneAddAudio : public c1CutsceneAction
{
public:
	c1CutSceneAddAudio(uint start, uint duration, std::string name, std::string path);
	~c1CutSceneAddAudio();
	void Execute(float dt);
protected:
	std::string names;
	std::string paths;
};





#endif

