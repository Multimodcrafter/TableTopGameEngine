#include "action.h"
#include "game.h"

action::action(const std::weak_ptr<game> game, const std::weak_ptr<state> target_state)
{
	game_ = game;
	target_state_ = target_state;
}

void action::execute(std::shared_ptr<player>& player, std::vector<std::shared_ptr<parameter>>& parameters)
{
	if(is_valid(player,parameters)) perform(player,parameters);
	game_.lock()->change_state(target_state_.lock());
}

bool action::is_valid(const std::shared_ptr<player>& player, std::vector<std::shared_ptr<parameter>>& parameters)
{
	for(auto rule : rules_)
	{
		if(!rule(game_.lock(), player,parameters)) return false;
	}
	return true;
}

std::vector<std::shared_ptr<parameter>>& action::get_parameters()
{
	return parameters_;
}

std::weak_ptr<state> action::get_target_state() const
{
	return target_state_;
}

void action::add_rule(const rule rule)
{
	rules_.push_back(rule);
}

void action::set_parameters(std::vector<std::shared_ptr<parameter>>& parameters)
{
	parameters_ = parameters;
}

std::shared_ptr<game> action::get_game() const
{
	return game_.lock();
}
