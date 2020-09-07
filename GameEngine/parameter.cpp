#include "parameter.h"

#include <utility>

parameter::parameter(std::string name, parameter_value value) : name_(std::move(name)), value_(std::move(value))
{
	
}

const std::string& parameter::get_name() const
{
	return name_;
}

const parameter_value& parameter::get_value() const
{
	return value_;
}
