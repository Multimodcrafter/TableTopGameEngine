#pragma once
#include <vector>
#include <memory>
#include <string>

class state abstract
{
public:
	virtual ~state() = default;
	virtual void initialize(const std::shared_ptr<class state_factory>& state_factory) abstract;
	virtual void pre_state_actions() abstract;
	virtual void post_state_actions() abstract;

	explicit state(std::weak_ptr<class game> game, std::string name, bool is_end_state);
	std::vector<std::shared_ptr<class action>> get_allowed_actions_for_player(std::shared_ptr<class player>& player);
	const std::string& get_name() const;
	bool is_end_state() const;

protected:
	std::shared_ptr<class game> get_game() const;
	void add_action(std::shared_ptr<class action> action);

private:
	const bool is_end_state_;
	const std::string name_;
	std::weak_ptr<class game> game_;
	std::vector<std::shared_ptr<class action>> actions_;
};
