#pragma once
#include "../GameEngine/state.h"

class state_play final : public state
{
public:

	explicit state_play(const std::shared_ptr<game> game)
		: state(game, "play", false)
	{
	}

	void initialize(const std::shared_ptr<state_factory>& state_factory) override;
	void pre_state_actions() override;
	void post_state_actions() override;
};
