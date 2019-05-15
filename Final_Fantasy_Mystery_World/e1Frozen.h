#ifndef __E1FROZEN_H__
#define __E1FROZEN_H__

#include "e1Enemy.h"

class e1BlueSlime;

class e1Frozen :public e1Enemy {

	enum class Phase {
		NORMAL, HARD
	};
public:
	e1Frozen(const int& x, const int& y);
	~e1Frozen();
	bool PreUpdate();
public:


	void IdAnimToEnum();

	void PrepareDistanceAttack();
	bool IsSpecialAttack1Finished();
	void AfetSpecialAttack1();
	void SummomBlueSlimes();

	void DoTeleport();

private:
	Phase phase = Phase::NORMAL;

	e1BlueSlime* slime_1 = nullptr;
	e1BlueSlime* slime_2 = nullptr;
};

#endif // !__E1FROZEN_H__
