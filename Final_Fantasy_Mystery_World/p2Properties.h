#ifndef __P2PROPERTIES_H__
#define __P2PROPERTIES_H__

#include <string>

class Property {
public:
	Property();
	~Property();

public:
	std::string name;
};

class PropertyString :public Property {
public:
	PropertyString();
	~PropertyString();

public:
	std::string value;
};

class PropertyFloat :public Property {
public:
	PropertyFloat();
	~PropertyFloat();

public:
	float value = 0.0F;
};

class PropertyBool :public Property {
public:
	PropertyBool();
	~PropertyBool();

public:
	bool value = true;
};

class PropertyInt :public Property {
public:
	PropertyInt();
	~PropertyInt();

public:
	int value = 0;
};

#endif // !__PPROPERTIES_H__
