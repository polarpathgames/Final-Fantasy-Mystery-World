#include "p2Properties.h"

Property::Property() {}
PropertyString::PropertyString() {}
PropertyFloat::PropertyFloat() {}
PropertyBool::PropertyBool() {}
PropertyInt::PropertyInt() {}

PropertyString::PropertyString(const char *value) : value(value) {}
PropertyFloat::PropertyFloat(const float &value) : value(value) {}
PropertyBool::PropertyBool(const bool value) : value(value) {}
PropertyInt::PropertyInt(const int &value) : value(value) {}

Property::~Property()
{
	name.clear();
}

PropertyString::~PropertyString() {}
PropertyFloat::~PropertyFloat() {}
PropertyBool::~PropertyBool() {}
PropertyInt::~PropertyInt() {}

void Property::SetName(const char * set_name)
{
	name.assign(set_name);
}

void PropertyString::SetValue(const char * val)
{
	value.assign(val);
}

void PropertyFloat::SetValue(const float & val)
{
	value = val;
}

void PropertyBool::SetValue(const bool val)
{
	value = val;
}

void PropertyInt::SetValue(const int & val)
{
	value = val;
}

std::string Property::GetName() const
{
	return name;
}

std::string PropertyString::GetValue() const
{
	return value;
}

float PropertyFloat::GetValue() const
{
	return value;
}

bool PropertyBool::GetValue() const
{
	return value;
}

int PropertyInt::GetValue() const
{
	return value;
}
