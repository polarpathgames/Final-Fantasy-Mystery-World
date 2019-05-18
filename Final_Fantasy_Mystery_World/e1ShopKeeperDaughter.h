#ifndef __e1ShopKeeperDaughter_H__
#define __e1ShopKeeperDaughter_H__

#include "e1NPC.h"

class e1ShopKeeperDaughter : public e1NPC
{
public:
	e1ShopKeeperDaughter(const int &x, const int &y);

	virtual ~e1ShopKeeperDaughter();

	bool PreUpdate();

	bool Update(float dt);
	void IdAnimToEnum();

private:
	u1Image* button_interact = nullptr;
};
#endif 
