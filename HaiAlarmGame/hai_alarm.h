#pragma once
#include "../GameEngine/game.h"

class hai_alarm final : public game
{
public:
	std::shared_ptr<class card_stack> get_player_hand(int index) const;
	std::shared_ptr<class card_stack> get_main_stack() const;
	std::shared_ptr<class card_stack> get_player_deck(int index) const;
	bool player_has_covered_card(unsigned int player, bool open) const;
	int get_player_deck_count(unsigned int player, bool shark, bool open);
	
protected:
	std::vector<std::shared_ptr<player>> get_initial_players() override;
	std::shared_ptr<state_factory> get_state_factory() override;
	std::vector<std::string> get_states() override;
	std::string get_start_state() override;
	std::vector<std::shared_ptr<game_object>> get_initial_game_objects() override;

private:
	std::shared_ptr<class card_stack> main_stack_;
	std::vector<std::shared_ptr<class card_stack>> player_hands_;
	std::vector<std::shared_ptr<class card_stack>> player_decks_;
};
