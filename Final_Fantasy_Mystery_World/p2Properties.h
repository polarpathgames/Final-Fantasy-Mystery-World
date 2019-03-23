#ifndef __P2PROPERTIES_H__
#define __P2PROPERTIES_H__

#include <string>

class Property {
public:
	Property();
	~Property();

	void SetName(const char* name);
	std::string GetName() const;

public:
	std::string name;
};

class PropertyString :public Property {
public:
	PropertyString();
	PropertyString(const char*);
	~PropertyString();

	void SetValue(const char* value);
	std::string GetValue() const;

private:
	std::string value;
};

class PropertyFloat :public Property {
public:
	PropertyFloat();
	PropertyFloat(const float&);
	~PropertyFloat();

	void SetValue(const float &value);
	float GetValue() const;

private:
	float value = 0.0F;
};

class PropertyBool :public Property {
public:
	PropertyBool();
	PropertyBool(const bool);
	~PropertyBool();

	void SetValue(const bool value);
	bool GetValue() const;

private:
	bool value = true;
};

class PropertyInt :public Property {
public:
	PropertyInt();
	PropertyInt(const int&);
	~PropertyInt();

	void SetValue(const int &value);
	int GetValue() const;

private:
	int value = 0;
};

#endif // !__PPROPERTIES_H__
