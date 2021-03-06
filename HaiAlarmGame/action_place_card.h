﻿#pragma once
#include "../GameEngine/action.h"

class action_place_card final : public action
{
public:
	action_place_card(const std::shared_ptr<game>& game, const std::weak_ptr<state>& target_state)
		: action(game, target_state)
	{
	}

	void initialize() override;
protected:
	void perform(std::shared_ptr<player>& player, std::vector<std::shared_ptr<parameter>>& parameters) override;
	
};
