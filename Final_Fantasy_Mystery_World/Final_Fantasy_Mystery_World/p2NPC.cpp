#include "p2NPC.h"
#include "App.h"
#include "p2Log.h"

bool LoadNPC(const char * name)
{
	bool ret = true;

	static pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("assets/xml/p2NPC.xml");

	if (result == NULL)
	{
		LOG("Could not load map xml file p2NPC.xml. pugi error: %s", result.description());
		ret = false;
	}

	if (ret) {
		pugi::xml_node node = doc.child("data");
		for (node = node.child("npc"); node; node = node.next_sibling()) {
			if (strcmp(node.attribute("name").as_string(), name) == 0)
				break;
		}

		if (!node) {
			LOG("Node %s not found", name);
			ret = false;
		}
		else {

		}


		doc.reset();
	}

	return ret;
}
