#ifndef __P2PROPERTIES_H__
#define __P2PROPERTIES_H__

#include <string>
#include <list>

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
		value = 0;
	}

	void SetName(const char* _name) {
		name.assign(_name);
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

template<class TYPE>
struct Properties {

	std::list<Property<TYPE>*> properties;

	void CleanUp() {
		for (std::list<Property<TYPE>*>::iterator item = properties.begin(); item != properties.end(); ++item) {
			delete *item;
			*item = nullptr;
		}
		properties.clear();
	}

	TYPE GetValue(const char* identificator, TYPE default_value = 0) {
		TYPE ret = default_value;
		for (std::list<Property<TYPE>*>::iterator item = properties.begin(); item != properties.end(); ++item) {
			if (strcmp((*item)->GetName(),identificator) == 0) {
				ret = (*item)->GetValue();
			}
		}
		return ret;
	}
	
	bool FindNameValue(const char* prop_name) {
		bool ret = false;
		for (std::list<Property<TYPE>*>::iterator item = properties.begin(); item != properties.end(); ++item) {
			if (strcmp((*item)->GetName(), prop_name) == 0) {
				ret = true;
				break;
			}
		}
		return ret;
	}

};

#endif // !__PPROPERTIES_H__