#pragma once
#include "../GameEngine/player.h"
#include "card_stack.h"

class console_player final : public player
{
public:
	explicit console_player(const std::weak_ptr<game>& game)
		: player(game)
	{
	}

	static void print_deck(const std::shared_ptr<card_stack>& stack, bool with_indices, bool covered = true);
	action_choice choose_action(std::vector<std::shared_ptr<action>>& available_actions) override;
	static void clear_screen(char fill = ' ');
	bool eligible_for_dolphin = true;
};
