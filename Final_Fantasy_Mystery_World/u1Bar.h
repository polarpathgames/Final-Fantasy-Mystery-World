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
	/*void DecreaseBar(int quantity);
	void RecoverBar(int quantity);

	int CalculateBar(int quantity);
	int CurrentQuantity();*/

public:

	u1Image* full_bar = nullptr;

	e1Entity* entity = nullptr;
	UIType bar_type;
	int max_capacity;
	int current_capacity;


};
#endif
