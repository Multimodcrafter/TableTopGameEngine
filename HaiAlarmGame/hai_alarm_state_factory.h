#pragma once
#include "../GameEngine/state_factory.h"

class hai_alarm_state_factory final : public state_factory
{
public:
	explicit hai_alarm_state_factory(const std::shared_ptr<game> game)
		: state_factory(game)
	{
	}

protected:
	std::shared_ptr<state> create_state(const std::string& state_name) override;
	
};
