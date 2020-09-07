#pragma once
#include "../GameEngine/state.h"

class state_end final : public state
{
public:
	explicit state_end(const std::shared_ptr<game> game)
		: state(game, "end", true)
	{
	}

	void initialize(const std::shared_ptr<state_factory>& state_factory) override;
	void pre_state_actions() override;
	void post_state_actions() override;
};
