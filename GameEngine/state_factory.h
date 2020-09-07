#pragma once
#include <memory>
#include <string>
#include <map>

class state_factory abstract
{
public:
	virtual ~state_factory() = default;
	explicit state_factory(std::weak_ptr<class game> game);
	std::weak_ptr<class state> get_state(const std::string& state_name);

protected:
	virtual std::shared_ptr<class state> create_state(const std::string& state_name) abstract;

	std::shared_ptr<class game> get_game() const;
	
private:
	std::map<std::string,std::shared_ptr<class state>> instances_;
	std::weak_ptr<class game> game_;
};
