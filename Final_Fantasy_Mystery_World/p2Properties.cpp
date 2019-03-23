#include "p2Properties.h"
#include "p2Log.h"

Property::Property() {}

Property::Property(const char *value) : string_value(value) {}
Property::Property(const float &value) : value(value) {}
Property::Property(const bool value) : value(value) {}
Property::Property(const int &value) : value(value) {}

Property::~Property()
{
	name.clear();
}

void Property::SetName(const char * set_name)
{
	name.assign(set_name);
}

void Property::SetValue(const char * val)
{
	string_value.assign(val);
}

void Property::SetValue(const float & val)
{
	float_value = val;
}

void Property::SetValue(const bool val)
{
	bool_value = val;
}

void Property::SetValue(const int & val)
{
	int_value = val;
}

std::string Property::GetName() const
{
	return name;
}