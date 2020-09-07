#include "card_stack.h"
#include <random>
#include <chrono>

card_stack::card_stack(const std::shared_ptr<player> owner) : owner_(owner)
{
}

bool card_stack::belongs_to(const std::shared_ptr<player> player)
{
	return owner_ == player;
}

void card_stack::shuffle()
{
	auto rng = std::default_random_engine(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
	std::shuffle(std::begin(cards_), std::end(cards_), rng);
}

std::shared_ptr<card> card_stack::pop_front_card()
{
	auto result = cards_.back();
	cards_.pop_back();
	return result;
}

void card_stack::push_front_card(const std::shared_ptr<card>& card)
{
	cards_.push_back(card);
}

std::shared_ptr<card> card_stack::get_card(const int index)
{
	return cards_.at(index);
}

std::shared_ptr<card> card_stack::pop_card(const int index)
{
	auto result = cards_.at(index);
	cards_.erase(cards_.begin() + index);
	return result;
}

void card_stack::set_card(const unsigned int index, const std::shared_ptr<card>& card)
{
	if(index < cards_.size()) cards_[index] = card;
}

unsigned card_stack::get_card_count() const
{
	return cards_.size();
}

void card_stack::clear()
{
	cards_.clear();
}
