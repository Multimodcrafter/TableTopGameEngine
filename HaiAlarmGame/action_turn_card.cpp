#include "action_turn_card.h"
#include "hai_rules.h"
#include "state_end.h"
#include "../GameEngine/parameter.h"
#include "hai_alarm.h"
#include "../GameEngine/player.h"
#include "card_stack.h"
#include "card.h"
#include "console_player.h"

void action_turn_card::initialize()
{
	add_rule(&hai_rules::turn_card_valid);
	if(get_target_state().lock()->get_name() == "end") add_rule(&hai_rules::win_with_turn_valid);
	if(get_target_state().lock()->get_name() == "dolphin") add_rule(&hai_rules::dolphin_with_turn_valid);
	std::vector<std::shared_ptr<parameter>> params = {std::make_shared<parameter>("card",0)};
	set_parameters(params);
}

void action_turn_card::perform(std::shared_ptr<player>& player, std::vector<std::shared_ptr<parameter>>& parameters)
{
	const auto hai_game = std::dynamic_pointer_cast<hai_alarm>(get_game());
	const auto card_index = parameter::get_parameter_value(parameters,"card",-1);
	if(card_index != -1) {
		hai_game->get_player_deck(player->get_index())->get_card(card_index)->is_open = true;
		const auto c_player = std::dynamic_pointer_cast<console_player>(player);
		c_player->eligible_for_dolphin = false;
	}
	hai_game->change_state(get_target_state().lock());
}
