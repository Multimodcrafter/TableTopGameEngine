#pragma once
#include <memory>
#include <vector>

class player;
class game;
class parameter;

class hai_rules
{
public:
	static bool place_card_valid(const std::shared_ptr<game>& game,const std::shared_ptr<player>& player, std::vector<std::shared_ptr<parameter>>& parameters);
	static bool turn_card_valid(const std::shared_ptr<game>& game,const std::shared_ptr<player>& player, std::vector<std::shared_ptr<parameter>>& parameters);
	static bool win_with_turn_valid(const std::shared_ptr<game>& game,const std::shared_ptr<player>& player, std::vector<std::shared_ptr<parameter>>& parameters);
	static bool dolphin_with_turn_valid(const std::shared_ptr<game>& game,const std::shared_ptr<player>& player, std::vector<std::shared_ptr<parameter>>& parameters);
	static bool stay_dolphin_valid(const std::shared_ptr<game>& game,const std::shared_ptr<player>& player, std::vector<std::shared_ptr<parameter>>& parameters);
	static bool win_dolphin_valid(const std::shared_ptr<game>& game,const std::shared_ptr<player>& player, std::vector<std::shared_ptr<parameter>>& parameters);
	static bool foreign_turn_valid(const std::shared_ptr<game>& game,const std::shared_ptr<player>& player, std::vector<std::shared_ptr<parameter>>& parameters);
	static bool foreign_turn_win_valid(const std::shared_ptr<game>& game,const std::shared_ptr<player>& player, std::vector<std::shared_ptr<parameter>>& parameters);
	static bool foreign_turn_dolphin_valid(const std::shared_ptr<game>& game,const std::shared_ptr<player>& player, std::vector<std::shared_ptr<parameter>>& parameters);
};
