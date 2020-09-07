#include "state_end.h"
#include <iostream>
#include "hai_alarm.h"
#include "../GameEngine/player.h"
#include "console_player.h"

void state_end::initialize(const std::shared_ptr<state_factory>& state_factory)
{
}

void state_end::pre_state_actions()
{
	console_player::clear_screen();
	std::cout << "Game has ended, this is the resulting table:" << std::endl;
	const auto game = std::dynamic_pointer_cast<hai_alarm>(get_game());
	for(const auto player : game->get_players())
	{
		std::cout << "Player " << player->get_index() << ":\n";
		console_player::print_deck(game->get_player_deck(player->get_index()),false);
	}
}

void state_end::post_state_actions()
{
}
