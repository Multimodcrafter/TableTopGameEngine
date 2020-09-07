#include "action_place_card.h"
#include "../GameEngine/parameter.h"
#include "hai_alarm.h"
#include "console_player.h"
#include "hai_rules.h"

void action_place_card::initialize()
{
	std::vector<std::shared_ptr<parameter>> parameters = {std::make_shared<parameter>("card",0)};
	set_parameters(parameters);
	add_rule(&hai_rules::place_card_valid);
}

void action_place_card::perform(std::shared_ptr<player>& player, std::vector<std::shared_ptr<parameter>>& parameters)
{
	const auto card_index = parameter::get_parameter_value(parameters,"card",0);

	const auto game = std::dynamic_pointer_cast<hai_alarm>(get_game());
	const auto card = game->get_player_hand(player->get_index())->get_card(card_index);
	const auto new_card = game->get_main_stack()->pop_front_card();
	game->get_player_deck(player->get_index())->push_front_card(card);
	game->get_player_hand(player->get_index())->set_card(card_index,new_card);
}
