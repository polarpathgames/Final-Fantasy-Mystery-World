#ifndef __P2PROPERTIES_H__
#define __P2PROPERTIES_H__

#include <string>


class Property {
	enum class Type {
		STRING,
		INT,
		FLOAT,
		BOOL,

		NONE
	};

public:
	Property();
	Property(const char * value);
	Property(const float & value);
	Property(const bool value);
	Property(const int & value);
	~Property();

	void SetName(const char* name);

	void SetValue(const char* value);
	void SetValue(const bool value);
	void SetValue(const int &value);
	void SetValue(const float &value);

	std::string GetName() const;
	int GetValue() const;
	float GetValue(Type) const;
	bool GetValue(Type) const;
	const char* GetValue(Type) const;

private:
	std::string name;
	Type type = Type::NONE;

	int int_value = 0;
	float float_value = 0.0F;
	bool bool_value = false;
	std::string string_value;
};
#endif // !__PPROPERTIES_H__