#include "PlayerControl.h"
#include "Actor.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Category.h"

namespace GEX {

	struct ActorMover 
	{
		ActorMover(float vx, float vy)
			: velocity(vx, vy)
		{}

		void operator() (Actor& actor, sf::Time dt) const {

			actor.accelerate(velocity);

		}
		sf::Vector2f velocity;
		
	};

	PlayerControl::PlayerControl()
		//10.22
		: currentMissionStatus_(MissionStatus::MissionRunning)
	{
		// set up bindings
		keyBindings_[sf::Keyboard::Left] = Action::MoveLeft;
		keyBindings_[sf::Keyboard::Right] = Action::MoveRight;
		keyBindings_[sf::Keyboard::Up] = Action::MoveUp;
		keyBindings_[sf::Keyboard::Down] = Action::MoveDown;

		//10.31
		keyBindings_[sf::Keyboard::Space] = Action::Attack;
		keyBindings_[sf::Keyboard::M] = Action::LaunchMissile;

		//9.26
		keyBindings_[sf::Keyboard::K] = Action::RotateLeft;
		keyBindings_[sf::Keyboard::L] = Action::RotateRight;

		// set up action bindings
		initializeAction();

		//for (auto& pair : actionBindings_) {
		//	pair.second.category = Category::PlayerAircraft;
		//}

	}
	 
	//9.24
	void PlayerControl::handleEvent(const sf::Event & event, CommandQueue & commands)
	{
		if (event.type == sf::Event::KeyPressed) {
			auto found = keyBindings_.find(event.key.code);
			if (found != keyBindings_.end()) {
				commands.push(actionBindings_[found->second]);
			}
		}
	}

	//9.24
	void PlayerControl::handleRealtimeInput(CommandQueue & commands)
	{
		// traverse all assigned keys, look up action, generate command
		for (auto pair : keyBindings_) {
			if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second)) {
				commands.push(actionBindings_[pair.second]);
			}
		}
	}

	//10.22
	void PlayerControl::setMissionStatus(MissionStatus status)
	{
		currentMissionStatus_ = status;
	}

	MissionStatus PlayerControl::getMissionStatus() const
	{
		return currentMissionStatus_;
	}

	//9.24
	bool PlayerControl::isRealTimeAction(Action action) {
		switch (action) 
		{
		case Action::MoveLeft:
		case Action::MoveRight:
		case Action::MoveUp:
		case Action::MoveDown:
		case Action::RR:
		case Action::RL:
		case Action::Attack:
			return true;
			break;
		default:
			return false;
			break;
		}
	}

	void PlayerControl::initializeAction()
	{
		const float playerSpeed = 200.f;

		actionBindings_[Action::MoveLeft].action = derivedAction<Actor>(ActorMover(-playerSpeed, 0.f));
		actionBindings_[Action::MoveRight].action = derivedAction<Actor>(ActorMover(+playerSpeed, 0.f));
		actionBindings_[Action::MoveUp].action = derivedAction<Actor>(ActorMover(0.f, -playerSpeed));
		actionBindings_[Action::MoveDown].action = derivedAction<Actor>(ActorMover(0.f, +playerSpeed));

		//9.26
		for (auto& pair : actionBindings_) {
			pair.second.category = Category::Hero;
		}		
	}

}