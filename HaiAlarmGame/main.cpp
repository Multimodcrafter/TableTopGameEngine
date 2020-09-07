#include "hai_alarm.h"
#include <iostream>
#include "state_play.h"

int main()
{
	auto alarm = std::make_shared<hai_alarm>();
	alarm->play();
	char _;
	std::cin >> _;
}
