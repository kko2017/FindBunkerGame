//
//

#pragma once
#include "TextureManager.h"
#include "StateIdentifier.h"
#include "CommandQueue.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>


namespace GEX {
	// forward declarations
	class PlayerControl;
	class StateStack;

	class State
	{
	public:
		typedef std::unique_ptr<State> Ptr;
		struct Context {

			Context(sf::RenderWindow& window, TextureManager& textures, PlayerControl& player);

			sf::RenderWindow*	window;
			TextureManager*		textures;
			PlayerControl*		player;
		};

	public:
							State(StateStack& stack, Context context);
		virtual				~State();

		virtual void		draw() = 0;
		virtual bool		update(sf::Time) = 0;   // = 0 means abstarct.
		virtual bool		handleEvent(const sf::Event&) = 0;


	protected:
		void				requestStackPush(StateID stateID);
		void				requestStackPop();
		void				requestStackClear();

		Context				getContext() const;

	private:
		StateStack*			stack_;
		Context				context_;

	};

}

