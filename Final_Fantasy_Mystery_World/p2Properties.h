#ifndef __P2PROPERTIES_H__
#define __P2PROPERTIES_H__

#include <string>

class Property {
	Property();
	~Property();

public:
	std::string name;
};

class PropertyString :public Property {

public:
	std::string value;
};

class PropertyFloat :public Property {

public:
	float value;
};

class PropertyBool :public Property {

public:
	bool value;
};

class PropertyInt :public Property {

public:
	int value;
};

#endif // !__PPROPERTIES_H__
