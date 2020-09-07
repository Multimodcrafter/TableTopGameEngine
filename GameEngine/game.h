#pragma once
#include <memory>
#include <vector>
#include <string>
#include "game_object.h"

class game abstract : public std::enable_shared_from_this<game>
{
public:
	virtual ~game() = default;
	void play();
	void change_state(std::shared_ptr<class state> new_state, int next_player = -1);
	template<typename T>
	const std::vector<std::shared_ptr<T>>& get_game_objects(std::shared_ptr<class player> from_player = nullptr);
	const std::vector<std::shared_ptr<player>>& get_players() const;
	int get_current_player() const;

protected:
	virtual std::vector<std::shared_ptr<class player>> get_initial_players() abstract;
	virtual std::shared_ptr<class state_factory> get_state_factory() abstract;
	virtual std::vector<std::string> get_states() abstract;
	virtual std::string get_start_state() abstract;
	virtual std::vector<std::shared_ptr<class game_object>> get_initial_game_objects() abstract;

private:
	void initialize();
	std::vector<std::shared_ptr<player>> players_;
	std::vector<std::shared_ptr<game_object>> game_objects_;
	std::shared_ptr<state_factory> state_factory_;
	std::shared_ptr<class state> current_state_;
	std::vector<std::string> states_;
	int current_player_index_ = 0;
	
};

template <typename T>
const std::vector<std::shared_ptr<T>>& game::get_game_objects(const std::shared_ptr<player> from_player)
{
	std::vector<std::shared_ptr<T>> result;
	for(auto object : game_objects_)
	{
		auto converted = std::dynamic_pointer_cast<T>(object);
		if(converted && (!from_player || object->belongs_to(from_player))) result.push_back(converted);
	}
	return result;
}
