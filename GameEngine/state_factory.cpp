#include "state_factory.h"
#include "state.h"

state_factory::state_factory(const std::weak_ptr<game> game)
{
	game_ = game;
}

std::weak_ptr<state> state_factory::get_state(const std::string& state_name)
{
	if(instances_.find(state_name) != instances_.end()) return instances_[state_name];
	instances_[state_name] = create_state(state_name);
	return instances_[state_name];
}

std::shared_ptr<game> state_factory::get_game() const
{
	return game_.lock();
}
