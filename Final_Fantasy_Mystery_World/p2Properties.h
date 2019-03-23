#ifndef __P2PROPERTIES_H__
#define __P2PROPERTIES_H__

#include <string>

template<class TYPE>
class Property {
public:
	Property() {}
	Property(const char * _name, const TYPE val) {
		name.assign(_name);
		value = val;
	}
	~Property() {
		name.clear();
	}

	void SetName(const char* _name) {
		name.assing(_name);
	}
	void SetValue(const TYPE val) {
		value = val;
	}

	const char* GetName() const {
		return name.data();
	}
	TYPE GetValue() const {
		return value;
	}

private:
	std::string name;
	TYPE value;
};

struct Properties {

	std::list<Property<int>*> properties;

	int Get

};

#endif // !__PPROPERTIES_H__