#pragma once
#include <vector>
#include <memory>
#include "player.h"

typedef bool (*rule)(const std::shared_ptr<class game>&,const std::shared_ptr<class player>&,std::vector<std::shared_ptr<class parameter>>&);

class action abstract
{
public:
	virtual ~action() = default;
	virtual void initialize() abstract;

	explicit action(std::weak_ptr<class game> game, std::weak_ptr<class state> target_state);
	void execute(std::shared_ptr<player>& player, std::vector<std::shared_ptr<class parameter>>& parameters);
	bool is_valid(const std::shared_ptr<player>& player, std::vector<std::shared_ptr<class parameter>>& parameters);
	std::vector<std::shared_ptr<class parameter>>& get_parameters();
	std::weak_ptr<class state> get_target_state() const;

protected:
	virtual void perform(std::shared_ptr<player>& player, std::vector<std::shared_ptr<class parameter>>& parameters) abstract;
	
	void add_rule(rule rule);
	void set_parameters(std::vector<std::shared_ptr<class parameter>>& parameters);
	std::shared_ptr<game> get_game() const;
	
private:
	std::weak_ptr<class state> target_state_;
	std::weak_ptr<class game> game_;
	std::vector<rule> rules_;
	std::vector<std::shared_ptr<class parameter>> parameters_;
};
