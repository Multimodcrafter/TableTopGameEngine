#include "console_player.h"
#include "action_place_card.h"
#include "action_turn_card.h"
#include "action_turn_foreign_card.h"
#include "../GameEngine/state.h"
#include <iostream>
#include <windows.h>
#include "../GameEngine/parameter.h"
#include "hai_alarm.h"
#include "card.h"
#include "card_stack.h"
#include "action_turn_dolphin.h"

void console_player::print_deck(const std::shared_ptr<card_stack>& stack, const bool with_indices, const bool covered)
{
	for(auto i = 0u; i < stack->get_card_count(); ++i)
	{
		const auto c = stack->get_card(i);
		const auto chr = c->is_open || !covered ? c->is_shark() ? 'S' : 'D' : 'C';
		std::cout << "|" << chr;
	}
	std::cout << "|" << std::endl;
	if(with_indices) {
		for(auto i = 0u; i < stack->get_card_count(); ++i)
		{
			std::cout << "|" << i + 1;
		}
		std::cout << "|" << std::endl;
	}
}

action_choice console_player::choose_action(std::vector<std::shared_ptr<action>>& available_actions)
{
	const auto game = std::dynamic_pointer_cast<hai_alarm>(get_game());
	clear_screen();
	std::cout << "It's player " << get_index() + 1 << "'s turn. Press enter when ready.";
	char _;
	std::cin.get(_);
	std::shared_ptr<action_place_card> place = nullptr;
	std::shared_ptr<action_turn_card> turn = nullptr;
	std::shared_ptr<action_turn_card> turn_dolphin = nullptr;
	std::shared_ptr<action_turn_card> turn_win = nullptr;
	std::shared_ptr<action_turn_dolphin> dolphin_turn = nullptr;
	std::shared_ptr<action_turn_dolphin> dolphin_win = nullptr;
	std::shared_ptr<action_turn_foreign_card> foreign = nullptr;
	std::shared_ptr<action_turn_foreign_card> foreign_dolphin = nullptr;
	std::shared_ptr<action_turn_foreign_card> foreign_win = nullptr;
	for(const auto& action : available_actions)
	{
		auto p = std::dynamic_pointer_cast<action_place_card>(action);
		auto t = std::dynamic_pointer_cast<action_turn_card>(action);
		auto tf = std::dynamic_pointer_cast<action_turn_foreign_card>(action);
		auto dt = std::dynamic_pointer_cast<action_turn_dolphin>(action);
		if(p) place = p;
		if(t) {
			auto t_name = t->get_target_state().lock()->get_name();
			if(t_name == "play") turn = t;
			else if(t_name == "dolphin") turn_dolphin = t;
			else if(t_name == "end") turn_win = t;
		}
		if(tf) {
			auto tf_name = tf->get_target_state().lock()->get_name();
			if(tf_name == "play") foreign = tf;
			else if(tf_name == "dolphin") foreign_dolphin = tf;
			else if(tf_name == "end") foreign_win = tf;
		}
		if(dt)
		{
			auto dt_name = dt->get_target_state().lock()->get_name();
			if(dt_name == "dolphin") dolphin_turn = dt;
			else if(dt_name == "end") dolphin_win = dt;
		}
	}
	std::cout << "The table looks like this: (C = covered, D = dolphin, S = shark)" << std::endl;

	for(auto i = 0u; i < game->get_players().size(); ++i)
	{
		std::cout << "Player " << i + 1;
		if(i == get_index()) std::cout << " (you)";
		std::cout << ":" << std::endl;
		print_deck(game->get_player_deck(i),false);
	}
	std::cout << "Your hand looks like this:" << std::endl;
	print_deck(game->get_player_hand(get_index()),true,false);

	std::cout << "Choose your action:" << std::endl;
	if(place) std::cout << "(1) place a card" << std::endl;
	if(turn || turn_dolphin || turn_win || dolphin_turn || dolphin_win) std::cout << "(2) turn one of your own cards" << std::endl;
	if(foreign || foreign_dolphin || foreign_win) std::cout << "(3) turn a card of another player" << std::endl;
	int choice;
	std::cin >> choice;
	while((choice != 1 || !place)
		&& (choice != 2 || !(turn || turn_dolphin || turn_win || dolphin_turn || dolphin_win))
		&& (choice != 3 || !(foreign || foreign_dolphin || foreign_win))
		)
	{
		std::cout << "Invalid choice. Choose one from the displayed numbers." << std::endl;
		std::cin >> choice;
	}

	action_choice result;

	switch (choice)
	{
	case 1:
	{
		std::cout << "Which card do you want to place down? (enter 1-3)" << std::endl;
		int card_choice;
		std::cin >> card_choice;
		while(card_choice < 1 || card_choice > 3)
		{
			std::cout << "invalid number. choose 1, 2 or 3" << std::endl;
			std::cin >> card_choice;
		}
		result.chosen_action = place;
		result.parameters = {std::make_shared<parameter>("card",card_choice - 1)};
		std::cout << "You placed a " << (game->get_player_hand(get_index())->get_card(card_choice-1)->is_shark() ? "shark" : "dolphin") << " card. press enter to continue";
		std::cin.get(_);
		std::cin.get(_);
		break;
	}
	case 2:
	{
		std::cout << "Which card do you want to turn? Your deck looks like this (C = covered, D = dolphin, S = shark)" << std::endl;
		auto stack = game->get_player_deck(get_index());
		print_deck(stack, true);
		unsigned int turn_choice;
		std::cin >> turn_choice;
		while(turn_choice < 1 || turn_choice > stack->get_card_count() || stack->get_card(turn_choice - 1)->is_open)
		{
			std::cout << "invalid choice. number must be between 1 and " << stack->get_card_count() << " and must correspond to a covered card." << std::endl;
			std::cin >> turn_choice;
		}
		result.parameters = {std::make_shared<parameter>("card",int(turn_choice - 1))};
		if(turn_win && turn_win->is_valid(game->get_players().at(game->get_current_player()),result.parameters)) result.chosen_action = turn_win;
		else if(dolphin_win && dolphin_win->is_valid(game->get_players().at(game->get_current_player()),result.parameters)) result.chosen_action = dolphin_win;
		else if(dolphin_turn && dolphin_turn->is_valid(game->get_players().at(game->get_current_player()),result.parameters)) result.chosen_action = dolphin_turn;
		else if(turn_dolphin && turn_dolphin->is_valid(game->get_players().at(game->get_current_player()),result.parameters)) result.chosen_action = turn_dolphin;
		else if(turn && turn->is_valid(game->get_players().at(game->get_current_player()),result.parameters)) result.chosen_action = turn;
		else std::cout << "You managed to enter some input, which the game wasn't expecting..." << std::endl;
		std::cout << "You opened a " << (game->get_player_deck(get_index())->get_card(turn_choice-1)->is_shark() ? "shark" : "dolphin") << " card. press enter to continue";
		std::cin.get(_);
		std::cin.get(_);
		break;
	}
	case 3:
	{
		std::cout << "From which other player do you want to turn a card? (you are nr. " << get_index() + 1 << ")" << std::endl;
		unsigned int foreign_choice;
		std::cin >> foreign_choice;
		while(foreign_choice < 1 || foreign_choice > game->get_players().size() || !game->player_has_covered_card(foreign_choice-1,false))
		{
			std::cout << "invalid choice. number out of range or player doesn't have a covered card.";
			std::cin >> foreign_choice;
		}
		std::cout << "This is the players deck (C = covered, D = dolphin, S = shark):" << std::endl;
		const auto foreign_stack = game->get_player_deck(foreign_choice-1);
		print_deck(foreign_stack,true);
		std::cout << "Which card would you like to turn?" << std::endl;
		unsigned int foreign_card;
		std::cin >> foreign_card;
		while(foreign_card < 1 || foreign_card > foreign_stack->get_card_count() || foreign_stack->get_card(foreign_card - 1)->is_open)
		{
			std::cout << "invalid choice. number must be between 1 and " << foreign_stack->get_card_count() << " and must correspond to a covered card." << std::endl;
			std::cin >> foreign_card;
		}
		result.parameters = {std::make_shared<parameter>("player",int(foreign_choice - 1)), std::make_shared<parameter>("card",int(foreign_card-1))};
		if(foreign_win && foreign_win->is_valid(game->get_players().at(game->get_current_player()),result.parameters)) result.chosen_action = foreign_win;
		else if(foreign_dolphin && foreign_dolphin->is_valid(game->get_players().at(game->get_current_player()),result.parameters)) result.chosen_action = foreign_dolphin;
		else if(foreign && foreign->is_valid(game->get_players().at(game->get_current_player()),result.parameters)) result.chosen_action = foreign;
		else std::cout << "You managed to enter some input the game wasn't expecting..." << std::endl;
		std::cout << "You opened a " << (foreign_stack->get_card(foreign_card-1)->is_shark() ? "shark" : "dolphin") << " card. press enter to continue.";
		std::cin.get(_);
		std::cin.get(_);
		break;
	}
	default:
		break;
	}
	
	return result;
}

void console_player::clear_screen(const char fill) {
	const COORD tl = {0,0};
    CONSOLE_SCREEN_BUFFER_INFO s;
	const auto console = GetStdHandle(STD_OUTPUT_HANDLE);   
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written;
	const DWORD cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}
