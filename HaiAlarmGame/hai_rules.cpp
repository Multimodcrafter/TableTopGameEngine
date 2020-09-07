#include "hai_rules.h"
#include "hai_alarm.h"
#include "card_stack.h"
#include "../GameEngine/parameter.h"
#include "console_player.h"
#include "card.h"

bool hai_rules::place_card_valid(const std::shared_ptr<game>& game, const std::shared_ptr<player>& player, std::vector<std::shared_ptr<parameter>>& parameters)
{
	const auto hai_game = std::dynamic_pointer_cast<hai_alarm>(game);
	if(hai_game->get_main_stack()->get_card_count() == 0) return false;
	return true;
}

bool hai_rules::turn_card_valid(const std::shared_ptr<game>& game, const std::shared_ptr<player>& player,
	std::vector<std::shared_ptr<parameter>>& parameters)
{
	const auto hai_game = std::dynamic_pointer_cast<hai_alarm>(game);
	const auto card_index = parameter::get_parameter_value(parameters,"card",-1);
	if(card_index == -1)
	{
		if(hai_game->player_has_covered_card(player->get_index(),false)) return true;
		return false;
	}
	if(!hai_game->get_player_deck(player->get_index())->get_card(card_index)->is_open) return true;
	return false;
}

bool hai_rules::win_with_turn_valid(const std::shared_ptr<game>& game, const std::shared_ptr<player>& player,
                                    std::vector<std::shared_ptr<parameter>>& parameters)
{
	const auto hai_game = std::dynamic_pointer_cast<hai_alarm>(game);
	const auto card_index = parameter::get_parameter_value(parameters,"card",-1);
	const auto player_dolphins_open = hai_game->get_player_deck_count(player->get_index(),false,true);
	const auto player_dolphins_covered = hai_game->get_player_deck_count(player->get_index(),false,false);
	const auto player_sharks_open = hai_game->get_player_deck_count(player->get_index(),true,true);
	const auto player_sharks_covered = hai_game->get_player_deck_count(player->get_index(),true,false);
	if(card_index == -1)
	{
		if(player_dolphins_open == 6 && player_dolphins_covered >= 1) return true;
		if(player_sharks_open >= 2 && player_sharks_covered >= 1)
		{
			for(auto i = 0u; i < hai_game->get_players().size(); ++i)
			{
				if(i == player->get_index()) continue;
				if(!hai_game->player_has_covered_card(i,true) && hai_game->get_player_deck_count(i,false,false) >= 5) return false;
				if(hai_game->get_player_deck_count(i,true,true) > player_sharks_open - 2) return false;
			}
			return true;
		}
		return false;
	}
	if(player_dolphins_open == 6 && !hai_game->get_player_deck(player->get_index())->get_card(card_index)->is_shark()) return true;
	if(player_sharks_open >= 2 && hai_game->get_player_deck(player->get_index())->get_card(card_index)->is_shark())
	{
		for(auto i = 0u; i < hai_game->get_players().size(); ++i)
		{
			if(i == player->get_index()) continue;
			if(!hai_game->player_has_covered_card(i,true) && hai_game->get_player_deck_count(i,false,false) >= 5) return false;
			if(hai_game->get_player_deck_count(i,true,true) > player_sharks_open - 2) return false;
		}
		return true;
	}
	return false;
}

bool hai_rules::dolphin_with_turn_valid(const std::shared_ptr<game>& game, const std::shared_ptr<player>& player,
	std::vector<std::shared_ptr<parameter>>& parameters)
{
	const auto hai_game = std::dynamic_pointer_cast<hai_alarm>(game);
	const auto card_index = parameter::get_parameter_value(parameters,"card",-1);
	const auto player_sharks_open = hai_game->get_player_deck_count(player->get_index(),true,true);
	const auto player_sharks_covered = hai_game->get_player_deck_count(player->get_index(),true,false);
	if(card_index == -1)
	{
		if(player_sharks_open >= 2 && player_sharks_covered >= 1)
		{
			auto possible = false;
			for(auto i = 0u; i < hai_game->get_players().size(); ++i)
			{
				if(i == player->get_index()) continue;
				if(!hai_game->player_has_covered_card(i,true) && hai_game->get_player_deck_count(i,false,false) >= 5) possible = true;
				if(hai_game->get_player_deck_count(i,true,true) > player_sharks_open - 2) return false;
			}
			return possible;
		}
		return false;
	}
	if(player_sharks_open >= 2 && hai_game->get_player_deck(player->get_index())->get_card(card_index)->is_shark())
	{
		auto possible = false;
		for(auto i = 0u; i < hai_game->get_players().size(); ++i)
		{
			if(i == player->get_index()) continue;
			if(!hai_game->player_has_covered_card(i,true) && hai_game->get_player_deck_count(i,false,false) >= 5) possible = true;
			if(hai_game->get_player_deck_count(i,true,true) > player_sharks_open - 2) return false;
		}
		return possible;
	}
	return false;
}

bool hai_rules::stay_dolphin_valid(const std::shared_ptr<game>& game, const std::shared_ptr<player>& player,
	std::vector<std::shared_ptr<parameter>>& parameters)
{
	const auto c_player = std::dynamic_pointer_cast<console_player>(player);
	if(!c_player->eligible_for_dolphin) return false;
	const auto hai_game = std::dynamic_pointer_cast<hai_alarm>(game);
	if(hai_game->get_player_deck_count(player->get_index(),false,true) == 5) return false;
	return hai_game->player_has_covered_card(player->get_index(),false);
}

bool hai_rules::win_dolphin_valid(const std::shared_ptr<game>& game, const std::shared_ptr<player>& player,
	std::vector<std::shared_ptr<parameter>>& parameters)
{
	const auto c_player = std::dynamic_pointer_cast<console_player>(player);
	if(!c_player->eligible_for_dolphin) return false;
	const auto hai_game = std::dynamic_pointer_cast<hai_alarm>(game);
	for(auto i = 0u; i < hai_game->get_players().size(); ++i)
	{
		if(i == player->get_index()) continue;
		if(!hai_game->player_has_covered_card(i,true) && hai_game->get_player_deck_count(i,false,false) >= 5) return false;
	}
	const auto card_index = parameter::get_parameter_value(parameters,"card",-1);
	if(card_index == -1) return true;
	if(hai_game->get_player_deck(player->get_index())->get_card(card_index)->is_shark()) return true;
	return hai_game->get_player_deck_count(player->get_index(),false,true) == 4;
}

bool hai_rules::foreign_turn_valid(const std::shared_ptr<game>& game, const std::shared_ptr<player>& player,
	std::vector<std::shared_ptr<parameter>>& parameters)
{
	const auto hai_game = std::dynamic_pointer_cast<hai_alarm>(game);
	if(hai_game->get_player_deck_count(player->get_index(),true,true) == 0) return false;
	const auto other_player = parameter::get_parameter_value(parameters,"player",-1);
	const auto card_index = parameter::get_parameter_value(parameters,"card",-1);
	if(other_player == -1 || card_index == -1)
	{
		for(const auto p : game->get_players())
		{
			if(p->get_index() == player->get_index()) continue;
			if(hai_game->player_has_covered_card(p->get_index(),false)) return true;
		}
		return false;
	}
	if(other_player == player->get_index()) return false;
	if(!hai_game->get_player_deck(other_player)->get_card(card_index)->is_open) return true;
	return false;
}

bool hai_rules::foreign_turn_win_valid(const std::shared_ptr<game>& game, const std::shared_ptr<player>& player,
	std::vector<std::shared_ptr<parameter>>& parameters)
{
	const auto hai_game = std::dynamic_pointer_cast<hai_alarm>(game);
	const auto other_player = parameter::get_parameter_value(parameters,"player",-1);
	const auto card_index = parameter::get_parameter_value(parameters,"card",-1);
	const auto dolphin_open_count = hai_game->get_player_deck_count(player->get_index(),false,true);
	const auto shark_open_count = hai_game->get_player_deck_count(player->get_index(),true,true);
	auto other_player_has_dolphin = false;
	auto other_player_has_shark = false;
	auto other_player_has_more_sharks = false;
	auto other_player_can_win_dolphin = false;
	for(const auto p : hai_game->get_players())
	{
		if(p->get_index() == player->get_index()) continue;
		if(hai_game->get_player_deck_count(p->get_index(),false,false) > 0) other_player_has_dolphin = true;
		if(hai_game->get_player_deck_count(p->get_index(),true,false) > 0) other_player_has_shark = true;
		if(hai_game->get_player_deck_count(p->get_index(),true,true) > shark_open_count - 2) other_player_has_more_sharks = true;
		if(!hai_game->player_has_covered_card(p->get_index(),true) && hai_game->get_player_deck_count(p->get_index(),false,false) >= 5) other_player_can_win_dolphin = true;
	}
	
	if(other_player == -1 || card_index == -1)
	{
		if(dolphin_open_count == 6 && other_player_has_dolphin) return true;
		if(shark_open_count >= 2 && other_player_has_shark && !other_player_has_more_sharks && !other_player_can_win_dolphin) return true;
		return false;
	}
	if(dolphin_open_count == 6 && !hai_game->get_player_deck(other_player)->get_card(card_index)->is_shark()) return true;
	if(other_player_has_more_sharks || other_player_can_win_dolphin) return false;
	if(shark_open_count >= 2 && hai_game->get_player_deck(other_player)->get_card(card_index)->is_shark()) return true;
	return false;
}

bool hai_rules::foreign_turn_dolphin_valid(const std::shared_ptr<game>& game, const std::shared_ptr<player>& player,
	std::vector<std::shared_ptr<parameter>>& parameters)
{
	const auto hai_game = std::dynamic_pointer_cast<hai_alarm>(game);
	const auto other_player = parameter::get_parameter_value(parameters,"player",-1);
	const auto card_index = parameter::get_parameter_value(parameters,"card",-1);
	const auto shark_open_count = hai_game->get_player_deck_count(player->get_index(),true,true);
	auto other_player_has_shark = false;
	auto other_player_has_more_sharks = false;
	auto other_player_can_win_dolphin = false;
	for(const auto p : hai_game->get_players())
	{
		if(p->get_index() == player->get_index()) continue;
		if(hai_game->get_player_deck_count(p->get_index(),true,false) > 0) other_player_has_shark = true;
		if(hai_game->get_player_deck_count(p->get_index(),true,true) > shark_open_count - 2) other_player_has_more_sharks = true;
		if(!hai_game->player_has_covered_card(p->get_index(),true) && hai_game->get_player_deck_count(p->get_index(),false,false) >= 5) other_player_can_win_dolphin = true;
	}
	
	if(other_player == -1 || card_index == -1)
	{
		if(shark_open_count >= 2 && other_player_has_shark && !other_player_has_more_sharks && other_player_can_win_dolphin) return true;
		return false;
	}
	if(other_player_has_more_sharks || !other_player_can_win_dolphin) return false;
	if(shark_open_count >= 2 && hai_game->get_player_deck(other_player)->get_card(card_index)->is_shark()) return true;
	return false;
}
