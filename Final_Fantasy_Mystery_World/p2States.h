#ifndef __P2STATES_H__
#define __P2STATES_H__

enum class States {
	SNOWSTORM,

	NONE
};

class State {
public:
	State(const States & state) :state(state) {}

	int GetDamage() {
		return 0;
	}

private:
	States state;

};

#endif // !__P2STATES_H__