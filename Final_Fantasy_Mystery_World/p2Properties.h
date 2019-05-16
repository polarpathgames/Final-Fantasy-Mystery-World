#ifndef __P2PROPERTIES_H__
#define __P2PROPERTIES_H__

#include <string>
#include <list>

template<class TYPE>
class Property {
public:
	Property() { value = 0; }
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

	bool AddProperty(const char* name, TYPE value) {
		if (!FindNameValue(name)) {
			properties.push_back(DBG_NEW Property<TYPE>(name, value));
			return true;
		}
		SDL_Log("There is a property with name %s", name);
		return false;
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
	
	// * Return true if there is a property with that name
	bool FindNameValue(const char* prop_name) {
		for (std::list<Property<TYPE>*>::iterator item = properties.begin(); item != properties.end(); ++item) {
			if (strcmp((*item)->GetName(), prop_name) == 0) {
				return true;
			}
		}
		return false;
	}

};

#endif // !__PPROPERTIES_H__