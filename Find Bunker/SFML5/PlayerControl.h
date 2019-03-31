//
// Doxy comments go here

#pragma once
#include <map>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include "Command.h"
#include "Category.h"


namespace GEX {

	// forward declartion
	class CommandQueue;

	enum class Action {
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		RotateRight,
		RotateLeft,
		Fire,
		LaunchMissile,
		RR,
		RL,
		Attack,
		Jump
	};

	enum class MissionStatus {
		MissionRunning,
		MissionSuccess,
		MissionFailure
	};


	class PlayerControl
	{
	public:
						PlayerControl();

		//9.24 you should know difference between functions of two voids
		void			handleEvent(const sf::Event& event, CommandQueue& commands);
		void			handleRealtimeInput(CommandQueue& commands);

		//10.22
		void			setMissionStatus(MissionStatus status);
		MissionStatus	getMissionStatus() const;

	private:

		void			initializeAction();
		//9.24
		static bool		isRealTimeAction(Action action);
	
	private:
		std::map<sf::Keyboard::Key, Action>		keyBindings_;
		std::map<Action, Command>				actionBindings_;
		//10.22
		MissionStatus							currentMissionStatus_;
	
	};

}