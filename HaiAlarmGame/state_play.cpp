#include "state_play.h"
#include "hai_alarm.h"
#include "card_stack.h"
#include "card.h"
#include "action_place_card.h"
#include "hai_alarm_state_factory.h"
#include "action_turn_card.h"
#include "action_turn_foreign_card.h"
#include <iostream>

void state_play::initialize(const std::shared_ptr<state_factory>& state_factory)
{
	const auto place = std::make_shared<action_place_card>(get_game(),state_factory->get_state("play"));
	const auto turn = std::make_shared<action_turn_card>(get_game(),state_factory->get_state("play"));
	const auto turn_d = std::make_shared<action_turn_card>(get_game(),state_factory->get_state("dolphin"));
	const auto turn_e = std::make_shared<action_turn_card>(get_game(),state_factory->get_state("end"));
	const auto foreign = std::make_shared<action_turn_foreign_card>(get_game(),state_factory->get_state("play"));
	const auto foreign_d = std::make_shared<action_turn_foreign_card>(get_game(),state_factory->get_state("dolphin"));
	const auto foreign_e = std::make_shared<action_turn_foreign_card>(get_game(),state_factory->get_state("end"));
	add_action(place);
	add_action(turn);
	add_action(turn_d);
	add_action(turn_e);
	add_action(foreign);
	add_action(foreign_d);
	add_action(foreign_e);
}

void state_play::pre_state_actions()
{
	const auto game = std::dynamic_pointer_cast<hai_alarm>(get_game());
	auto main = game->get_main_stack();
	main -> clear();
	for(auto i = 0; i < 32; ++i)
	{
		main->push_front_card(std::make_shared<card>(false));
		main->push_front_card(std::make_shared<card>(true));
	}
	main->shuffle();
	const int player_count = game->get_players().size();
	for(auto i = 0; i < player_count; ++i)
	{
		auto hand = game->get_player_hand(i);
		hand->push_front_card(main->pop_front_card());
		hand->push_front_card(main->pop_front_card());
		hand->push_front_card(main->pop_front_card());
	}
}

void state_play::post_state_actions()
{
}
