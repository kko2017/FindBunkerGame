#include "Projectile.h"
#include "DataTables.h"
#include "Utility.h"
#include "Category.h"
#include "EmitterNode.h"
#include <cassert>

namespace {
	const std::map<GEX::Projectile::Type, GEX::ProjectileData> TABLE = GEX::initializeProjectileData();
}	// anonymous namespace for static blah.

GEX::Projectile::Projectile(Type type, const TextureManager & textures)
	: Entity(1)
	, type_(type)
	, sprite_(textures.get(TABLE.at(type).texture), TABLE.at(type).textureRect)
{
	centerOrigin(sprite_);
	
	if (isGuided()) {
		std::unique_ptr<EmitterNode> smoke(new EmitterNode(Particle::Type::Smoke));
		smoke->setPosition(0.f, Projectile::getBoundingBox().height / 2.f);
		attachChild(std::move(smoke));

		std::unique_ptr<EmitterNode> fire(new EmitterNode(Particle::Type::Propellant));
		fire->setPosition(0.f, Projectile::getBoundingBox().height / 2.f);
		attachChild(std::move(fire));
	}
}

unsigned int GEX::Projectile::getCategory() const
{
	if (type_ == Type::EnemyBullet)
		return Category::EnemyProjectile;
	else
		return Category::AlliedProjectile;
}

float GEX::Projectile::getMaxSpeed() const
{
	return TABLE.at(type_).speed;
}

int GEX::Projectile::getDamage() const
{
	return TABLE.at(type_).damage;
}
//10.17
bool GEX::Projectile::isGuided() const
{
	return (type_ == Type::Missile);
}

void GEX::Projectile::guidedTowards(sf::Vector2f position)
{
	assert(isGuided());
	targetDirection_ = unitVector(position - getWorldPosition());
}

//10.18
sf::FloatRect GEX::Projectile::getBoundingBox() const
{
	return getWorldTransform().transformRect(sprite_.getGlobalBounds());

}

void GEX::Projectile::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	if (isGuided()) {
		const float APPROACH_RATE = 400.f;
		
		auto newVelocity = unitVector(APPROACH_RATE * dt.asSeconds()
										* targetDirection_ + getVelocity());
		
		newVelocity *= getMaxSpeed();
		setVelocity(newVelocity);

		auto angle = std::atan2(newVelocity.y, newVelocity.x); 
		setRotation(toDegree(angle) + 90.f);
	}

	Entity::updateCurrent(dt, commands);
}

void GEX::Projectile::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}
