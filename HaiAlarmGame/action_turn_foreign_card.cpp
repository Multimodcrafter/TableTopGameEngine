#include "action_turn_foreign_card.h"
#include "hai_rules.h"
#include "../GameEngine/parameter.h"
#include "hai_alarm.h"
#include "card_stack.h"
#include "card.h"
#include "../GameEngine/state.h"
#include "console_player.h"

void action_turn_foreign_card::initialize()
{
	add_rule(&hai_rules::foreign_turn_valid);
	if(get_target_state().lock()->get_name() == "end") add_rule(&hai_rules::foreign_turn_win_valid);
	if(get_target_state().lock()->get_name() == "dolphin") add_rule(&hai_rules::foreign_turn_dolphin_valid);
	std::vector<std::shared_ptr<parameter>> params = {std::make_shared<parameter>("card",0),std::make_shared<parameter>("player",0)};
	set_parameters(params);
}

void action_turn_foreign_card::perform(std::shared_ptr<player>& player, std::vector<std::shared_ptr<parameter>>& parameters)
{
	const auto other_player = parameter::get_parameter_value(parameters,"player",-1);
	const auto card_index = parameter::get_parameter_value(parameters,"card",-1);
	if(other_player == -1 || card_index == -1) return;
	const auto hai_game = std::dynamic_pointer_cast<hai_alarm>(get_game());
	const auto foreign_card = hai_game ->get_player_deck(other_player)->get_card(card_index);
	foreign_card->is_open = true;
	if(foreign_card->is_shark())
	{
		const auto new_card = hai_game->get_main_stack()->pop_front_card();
		hai_game->get_player_deck(player->get_index())->push_front_card(foreign_card);
		hai_game->get_player_deck(other_player)->set_card(card_index,new_card);
	}
	else
	{
		unsigned int shark_card = -1;
		const auto deck = hai_game->get_player_deck(player->get_index());
		for(auto i = 0u; i < deck->get_card_count(); ++i)
		{
			if(deck->get_card(i)->is_shark())
			{
				shark_card = i;
				break;
			}
		}
		const auto s_card = deck->get_card(shark_card);
		hai_game->get_player_deck(other_player)->set_card(card_index,s_card);
		deck->set_card(shark_card,foreign_card);
		const auto c_player = std::dynamic_pointer_cast<console_player>(hai_game->get_players().at(other_player));
		c_player->eligible_for_dolphin = false;
	}
}
