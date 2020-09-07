#include "game.h"
#include "player.h"
#include "state_factory.h"
#include "state.h"
#include "action.h"

void game::play()
{
	initialize();
	while(!current_state_->is_end_state())
	{
		auto current_player = players_.at(current_player_index_);
		auto actions = current_state_->get_allowed_actions_for_player(current_player);
		if(!actions.empty()) {
			auto chosen_action = current_player->choose_action(actions);
			while(!chosen_action.chosen_action->is_valid(current_player,chosen_action.parameters))
			{
				chosen_action = current_player->choose_action(actions);
			}
			chosen_action.chosen_action->execute(current_player,chosen_action.parameters);
		}
		current_player_index_ = (current_player_index_ + 1) % players_.size();
	}
}

void game::change_state(const std::shared_ptr<state> new_state, const int next_player)
{
	if(new_state != current_state_) {
		current_state_->post_state_actions();
		current_state_ = new_state;
		current_state_->pre_state_actions();
	}
	if(next_player != -1)
	{
		current_player_index_ = next_player - 1;
	}
}

const std::vector<std::shared_ptr<player>>& game::get_players() const
{
	return players_;
}

int game::get_current_player() const
{
	return current_player_index_;
}

void game::initialize()
{
	players_ = get_initial_players();
	for(auto i = 0u; i < players_.size(); ++i)
	{
		players_.at(i)->set_index(i);
	}
	state_factory_ = get_state_factory();
	states_ = get_states();
	game_objects_ = get_initial_game_objects();
	current_state_ = state_factory_->get_state(get_start_state()).lock();
	for(auto state : states_)
	{
		state_factory_->get_state(state).lock()->initialize(state_factory_);
	}
	current_state_->pre_state_actions();
}
