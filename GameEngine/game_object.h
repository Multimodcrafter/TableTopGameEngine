#pragma once
#include <memory>

class game_object abstract
{
public:
	virtual ~game_object() = default;
	virtual bool belongs_to(std::shared_ptr<class player> player) abstract;
	
};
