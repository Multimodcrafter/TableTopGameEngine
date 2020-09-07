#pragma once
#include <vector>
#include <memory>

struct action_choice
{
	std::shared_ptr<class action> chosen_action;
	std::vector<std::shared_ptr<class parameter>> parameters;
};

class player abstract
{
public:
	virtual ~player() = default;
	virtual action_choice choose_action(std::vector<std::shared_ptr<class action>>& available_actions) abstract;

	explicit player(std::weak_ptr<class game> game);
	int get_index() const;
	void set_index(int index);
	
protected:
	std::shared_ptr<class game> get_game() const;

private:
	int index_ = 0;
	std::weak_ptr<class game> game_;
};
