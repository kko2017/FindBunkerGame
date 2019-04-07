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

		void			handleEvent(const sf::Event& event, CommandQueue& commands);
		void			handleRealtimeInput(CommandQueue& commands);

		void			setMissionStatus(MissionStatus status);
		MissionStatus	getMissionStatus() const;

	private:
		void			initializeAction();
		static bool		isRealTimeAction(Action action);
	
	private:
		std::map<sf::Keyboard::Key, Action>		keyBindings_;
		std::map<Action, Command>				actionBindings_;
		MissionStatus							currentMissionStatus_;
	};

}