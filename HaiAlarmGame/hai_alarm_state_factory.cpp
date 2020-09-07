#include "hai_alarm_state_factory.h"
#include "state_play.h"
#include "state_dolphin.h"
#include "state_end.h"

std::shared_ptr<state> hai_alarm_state_factory::create_state(const std::string& state_name)
{
	if(state_name == "play") return std::make_shared<state_play>(get_game());
	if(state_name == "dolphin") return std::make_shared<state_dolphin>(get_game());
	if(state_name == "end") return std::make_shared<state_end>(get_game());
	return nullptr;
}
