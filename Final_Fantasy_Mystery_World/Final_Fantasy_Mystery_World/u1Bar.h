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
	int CalculateSkillBar(int quantity);
	void InnerDraw();

	void PrintBarNumbers(int addition = 0);

public:

	u1Image* empty_bar = nullptr;
	u1Image* filled_bar = nullptr;
	u1Image* aux_bar = nullptr;
	u1Label* bar_numbers_label = nullptr;
	e1Entity* entity = nullptr;
	UIType bar_type = UIType::NON;
	int max_capacity = 0;
	int current_quantity = 0;

	int max_width = 118;
	int max_height = 0; // vertical skill bar
	int current_width = 0;
	int current_height = 0; // verticla skill bar
	int targe_width = 0;
	int targe_height = 0; // vertical skill bar
	bool has_change = false;
	bool got_xp = false;

	int currentXP = 0; // current_quantity
	int lastLevelXP = 0;
	int nextLevelXP = 0;
	int xpBetweenLevels = 0;
	int xpSinceLevelUp = 0;
	float percentageOfXP = 0.f;
	int barWidth = 0;
	int aux_quantity = 0;
};
#endif
