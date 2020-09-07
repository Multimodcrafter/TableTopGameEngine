#pragma once
#include "../GameEngine/game_object.h"
#include <vector>

class card_stack final : public game_object
{
public:
	explicit card_stack(std::shared_ptr<player> owner);
	bool belongs_to(std::shared_ptr<player> player) override;
	void shuffle();
	std::shared_ptr<class card> pop_front_card();
	void push_front_card(const std::shared_ptr<card>& card);
	std::shared_ptr<class card> get_card(int index);
	std::shared_ptr<class card> pop_card(int index);
	void set_card(unsigned int index, const std::shared_ptr<card>& card);
	unsigned int get_card_count() const;
	void clear();

private:
	const std::shared_ptr<player> owner_{};
	std::vector<std::shared_ptr<class card>> cards_;
};
