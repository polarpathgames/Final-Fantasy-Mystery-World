// ----------------------------------------------------
// m1Module.h
// Interface for all engine modules
// ----------------------------------------------------

#ifndef __Module_H__
#define __Module_H__

#include <string>
#include "PugiXml\src\pugixml.hpp"

class Application;
struct Collider;
class u1GUI;

enum class ColliderInfo;

class m1Module
{
private:
	bool enabled = true;

public:

	m1Module() : active(false)
	{}

	void Init()
	{
		active = true;
	}

	// Called before render is available
	virtual bool Awake(pugi::xml_node&)
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	virtual bool Load(pugi::xml_node&)
	{
		return true;
	}

	virtual bool Save(pugi::xml_node&) const
	{
		return true;
	}
	void Enable()
	{
			active = true;
			Start();
	}

	void Disable()
	{
			active = false;
			CleanUp();
	}

	// Callbacks ---
	virtual void OnCollision(Collider*, Collider*, ColliderInfo) {}
	virtual bool Interact(u1GUI* element) { return true; }

public:

	std::string	name;
	bool		active;

};

#endif // __m1Module_H__
