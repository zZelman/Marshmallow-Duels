#ifndef CPOWERUP_HOLDER_H_
#define CPOWERUP_HOLDER_H_

#include "include_sfml.h"
#include "CTexture.h"
#include "ARenderable.h"
#include "AUpdate.h"
#include "DPhysics.h"
#include "CPlayer.h"

/**
 * A floating PowerUp, ones that the player does not have yet.
 *
 * Acts like a container for the power of the power up, and thus
 * uses a has-a relationship.
 */
class CPowerUp_holder: public ARenderable, public AUpdate, public DPhysics
{
public:
	CPowerUp_holder(CTexture* pTexture, const sf::Vector2<int>& currSub,
	                const sf::Vector2<int>& spawnPos, const sf::Vector2<int>& spawnSpeeds);
	virtual ~CPowerUp_holder();

	/**
	 * Collision between this PowerUp and the given CPlayer has occurred,
	 * therefore this gives responsibility of the power to the player.
	 */
	void givePower(CPlayer* pPlayer);

	/**
	 * Function to update object state each update cycle
	 */
	void update();

	void stepNormally();
};

#endif /* CPOWERUP_HOLDER_H_ */
