#include "p2Properties.h"

Property::Property() {}

Property::~Property()
{
	name.clear();
}

std::string Property::GetName() const
{
	return name;
}

PropertyString::PropertyString()
{
}

PropertyString::PropertyString(const char *value) : value(value)
{
}

PropertyString::~PropertyString()
{
}

std::string PropertyString::GetValue() const
{
	return value;
}

PropertyFloat::PropertyFloat()
{
}

PropertyFloat::PropertyFloat(const float &value) : value(value)
{
}

PropertyFloat::~PropertyFloat()
{
}

float PropertyFloat::GetValue() const
{
	return value;
}

PropertyBool::PropertyBool()
{
}

PropertyBool::PropertyBool(const bool value) : value(value)
{
}

PropertyBool::~PropertyBool()
{
}

bool PropertyBool::GetValue() const
{
	return value;
}

PropertyInt::PropertyInt()
{
}

PropertyInt::PropertyInt(const int &value) : value(value)
{
}

PropertyInt::~PropertyInt()
{
}

int PropertyInt::GetValue() const
{
	return value;
}
