#include "hai_alarm.h"
#include "hai_alarm_state_factory.h"
#include "card_stack.h"
#include "card.h"
#include "console_player.h"
#include <iostream>

std::shared_ptr<card_stack> hai_alarm::get_player_hand(const int index) const
{
	return player_hands_.at(index);
}

std::shared_ptr<card_stack> hai_alarm::get_main_stack() const
{
	return main_stack_;
}

std::shared_ptr<card_stack> hai_alarm::get_player_deck(const int index) const
{
	return player_decks_.at(index);
}

bool hai_alarm::player_has_covered_card(const unsigned int player, const bool open) const
{
	if(player < 0 || player > get_players().size()) return false;
	for(auto i = 0u; i < player_decks_.at(player)->get_card_count(); ++i)
	{
		if(player_decks_.at(player)->get_card(i)->is_open == open) return true;
	}
	return false;
}

int hai_alarm::get_player_deck_count(const unsigned int player, const bool shark, const bool open)
{
	auto result = 0;
	if(player < 0 || player > get_players().size()) return 0;
	for(auto i = 0u; i < player_decks_.at(player)->get_card_count(); ++i)
	{
		const auto card = player_decks_.at(player)->get_card(i);
		if(card->is_shark() == shark && card->is_open == open) ++result;
	}
	return result;
}

std::vector<std::shared_ptr<player>> hai_alarm::get_initial_players()
{
	std::vector<std::shared_ptr<player>> result;
	std::cout << "How many players are participating?" << std::endl;
	int count;
	std::cin >> count;
	char _;
	std::cin.get(_);
	for(auto i = 0; i < count; ++i) 
	{
		result.push_back(std::make_shared<console_player>(shared_from_this()));
	}
	return result;
}

std::shared_ptr<state_factory> hai_alarm::get_state_factory()
{
	return std::make_shared<hai_alarm_state_factory>(shared_from_this());
}

std::vector<std::string> hai_alarm::get_states()
{
	std::vector<std::string> result = {"play","dolphin","end"};
	return result;
}

std::string hai_alarm::get_start_state()
{
	std::string result = "play";
	return result;
}

std::vector<std::shared_ptr<game_object>> hai_alarm::get_initial_game_objects()
{
	main_stack_ = std::make_shared<card_stack>(nullptr);
	player_hands_.clear();
	player_decks_.clear();
	for(auto player : get_players())
	{
		player_hands_.push_back(std::make_shared<card_stack>(player));
		player_decks_.push_back(std::make_shared<card_stack>(player));
	}
	
	std::vector<std::shared_ptr<game_object>> result;
	result.push_back(main_stack_);
	for(auto stack : player_hands_) result.push_back(stack);
	for(auto stack : player_decks_) result.push_back(stack);
	return result;
}
