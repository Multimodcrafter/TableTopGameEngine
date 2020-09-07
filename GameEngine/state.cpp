#include "state.h"
#include "game.h"
#include "action.h"

state::state(const std::weak_ptr<game> game, const std::string name, const bool is_end_state) : is_end_state_(is_end_state), name_(name)
{
	game_ = game;
}

std::vector<std::shared_ptr<action>> state::get_allowed_actions_for_player(std::shared_ptr<player>& player)
{
	auto result = std::vector<std::shared_ptr<action>>();
	auto empty = std::vector<std::shared_ptr<parameter>>();
	for(auto a : actions_)
	{
		if(a->is_valid(player,empty)) result.push_back(a);
	}
	return result;
}

const std::string& state::get_name() const
{
	return name_;
}

bool state::is_end_state() const
{
	return is_end_state_;
}

std::shared_ptr<game> state::get_game() const
{
	return game_.lock();
}

void state::add_action(std::shared_ptr<action> action)
{
	actions_.push_back(action);
	action->initialize();
}
