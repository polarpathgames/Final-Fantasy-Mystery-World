#include "p2Properties.h"

Property::Property() {}

Property::~Property()
{
	name.clear();
}

void Property::SetName(const char * set_name)
{
	name.assign(set_name);
}

std::string Property::GetName() const
{
	return name;
}

PropertyString::PropertyString() {}

PropertyString::PropertyString(const char *value) : value(value) {}

PropertyString::~PropertyString() {}

void PropertyString::SetValue(const char * val)
{
	value.assign(val);
}

std::string PropertyString::GetValue() const
{
	return value;
}

PropertyFloat::PropertyFloat() {}

PropertyFloat::PropertyFloat(const float &value) : value(value) {}

PropertyFloat::~PropertyFloat() {}

void PropertyFloat::SetValue(const float & val)
{
	value = val;
}

float PropertyFloat::GetValue() const
{
	return value;
}

PropertyBool::PropertyBool() {}

PropertyBool::PropertyBool(const bool value) : value(value) {}

PropertyBool::~PropertyBool() {}

void PropertyBool::SetValue(const bool val)
{
	value = val;
}

bool PropertyBool::GetValue() const
{
	return value;
}

PropertyInt::PropertyInt() {}

PropertyInt::PropertyInt(const int &value) : value(value) {}

PropertyInt::~PropertyInt() {}

void PropertyInt::SetValue(const int & val)
{
	value = val;
}

int PropertyInt::GetValue() const
{
	return value;
}
