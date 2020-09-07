#include "card.h"

card::card(const bool is_shark) : is_shark_(is_shark)
{
}

bool card::belongs_to(std::shared_ptr<player> player)
{
	return false;
}

bool card::is_shark() const
{
	return is_shark_;
}
