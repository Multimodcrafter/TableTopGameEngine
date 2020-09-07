#include "player.h"

player::player(const std::weak_ptr<game> game)
{
	game_ = game;
}

int player::get_index() const
{
	return index_;
}

void player::set_index(const int index)
{
	index_ = index;
}

std::shared_ptr<game> player::get_game() const
{
	return game_.lock();
}
