#ifndef _P2RANDOM_H_
#define _P2RANDOM_H_

#include <random>
#include <iostream>
#include <time.h>

class Random {

public:

	Random() { srand(time(NULL)); }
	~Random(){}

	int Generate(int min, int max) {
		max += 1;
		int size = max - min;
		if (size > 0)
			return (rand() % size + min);
		else return 0;
	}

};

#endif // !_P2RANDOM_H_

