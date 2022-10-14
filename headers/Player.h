#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H
#include "Camera.h"

class Player
{
public:
	float health;
	int maxHealth;
	float pos[3];

	float speed;
	float jumpSpeed;
	float yVel;

	float sensitivity = 100.0f;
	bool isPaused = false;

	Player();
	void TakeDamage(float amount);
	void Heal(float amount);
	void Die();
};

#endif