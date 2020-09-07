#pragma once
#include "../GameEngine/game_object.h"

class card final : public game_object
{
public:
	explicit card(bool is_shark);
	bool belongs_to(std::shared_ptr<player> player) override;
	[[nodiscard]] bool is_shark() const;
	bool is_open = false;

private:
	const bool is_shark_;
};
