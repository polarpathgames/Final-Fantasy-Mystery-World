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
	void UpdateBar(int quantity, UIType bar_type);

	int CalculateBar(int quantity);
	int CalculateExpBar(int xp);
	void InnerDraw();

	void PrintBarNumbers();

public:

	u1Image* empty_bar = nullptr;
	u1Image* filled_bar = nullptr;
	u1Image* aux_bar = nullptr;
	u1Label* bar_numbers_label = nullptr;
	e1Entity* entity = nullptr;
	UIType bar_type;
	int max_capacity = 0;
	int current_quantity = 0;

	int max_width = 172;
	int current_width = 0;
	int targe_width = 0;
	bool has_change = false;
	bool got_xp = false;

	int currentXP; // current_quantity
	int lastLevelXP;
	int nextLevelXP;
	int xpBetweenLevels;
	int xpSinceLevelUp;
	float percentageOfXP;
	int barWidth;

};
#endif
