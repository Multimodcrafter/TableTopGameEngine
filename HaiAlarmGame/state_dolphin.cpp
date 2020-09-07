#include "state_dolphin.h"
#include <iostream>
#include "hai_alarm_state_factory.h"
#include "action_turn_dolphin.h"
#include "console_player.h"

void state_dolphin::initialize(const std::shared_ptr<state_factory>& state_factory)
{
	const auto turn = std::make_shared<action_turn_dolphin>(get_game(),state_factory->get_state("dolphin"));
	const auto turn_e = std::make_shared<action_turn_dolphin>(get_game(),state_factory->get_state("end"));
	add_action(turn);
	add_action(turn_e);
}

void state_dolphin::pre_state_actions()
{
	console_player::clear_screen();
	std::cout << "Everybody listen up, we have a Hai-Alarm but someone might safe us by using 'don't-panic'. Press enter to continue." << std::endl;
	char _;
	std::cin.get(_);
}

void state_dolphin::post_state_actions()
{
}
