#ifndef __u1Bar_H__
#define __u1Bar_H__

#include "u1UI_Element.h"
#include "e1Entity.h"


class u1Bar :public u1GUI
{
public:
	u1Bar() : u1GUI(BAR, 0, 0, nullptr, {0, 0, 0, 0}, false, false, false) {}
	u1Bar(const int &x, const int &y, int max_capacity, UIType type, u1GUI* parent, m1Module* callback);

	~u1Bar();
	void DecreaseBar(int quantity, UIType bar_type);
	//void RecoverBar(int quantity);

	int CalculateBar(int quantity);

public:

	u1Image* empty_bar = nullptr;
	u1Image* hp_bar = nullptr;

	u1Image* empty_mana_bar = nullptr;
	u1Image* mana_bar = nullptr;

	e1Entity* entity = nullptr;
	UIType bar_type;
	int max_capacity = 0;
	int current_quantity = 0;

	int max_width = 172;
	int current_width = 0;

};
#endif
