#pragma once
#include <string>
#include <variant>
#include <memory>
#include <vector>

typedef std::variant<int,float,std::string,std::shared_ptr<class player>, std::shared_ptr<class game_object>> parameter_value;

class parameter final
{
public:
	parameter(std::string name, parameter_value value);
	[[nodiscard]] const std::string& get_name() const;
	[[nodiscard]] const parameter_value& get_value() const;
	template<typename T>
	static T get_parameter_value(std::vector<std::shared_ptr<parameter>>& parameters, std::string name, T default_value);

private:
	const std::string name_;
	const parameter_value value_;
	
};

template <typename T>
T parameter::get_parameter_value(std::vector<std::shared_ptr<parameter>>& parameters, const std::string name,
	T default_value)
{
	for(const auto& parameter : parameters)
	{
		if(parameter && parameter->get_name() == name && std::holds_alternative<T>(parameter->get_value())) return std::get<T>(parameter->get_value());
	}
	return default_value;
}
