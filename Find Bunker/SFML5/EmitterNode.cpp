#include "EmitterNode.h"
#include "CommandQueue.h"
#include "Command.h"
#include "ParticleNode.h"


GEX::EmitterNode::EmitterNode(Particle::Type type)
	: SceneNode()
	, accummulatedTime_(sf::Time::Zero)
	, type_(type)
	, particleSystem_(nullptr)
{}

void GEX::EmitterNode::updateCurrent(sf::Time dt, CommandQueue & commands)
{
	if (particleSystem_) {
		emitParticle(dt);
	}
	else {
		auto finder = [this](ParticleNode& container, sf::Time)
		{
			if (container.getParticleType() == type_)		//
				particleSystem_ = &container;
		};

		Command command;
		command.category = Category::ParticleSystem;
		command.action = derivedAction<ParticleNode>(finder);

		commands.push(command);
	}
}

void GEX::EmitterNode::emitParticle(sf::Time dt)
{
	const float EMISSIONRATE = 30.f;
	const sf::Time interval = sf::seconds(1.f) / EMISSIONRATE;

	accummulatedTime_ += dt;

	while (accummulatedTime_ > interval) {
		accummulatedTime_ -= interval;
		particleSystem_->addParticle(getWorldPosition());
	}
}
