#include "Health.h"

// Constructors
Health::Health()
{
	_maxHealth = 0;
	_currentHealth = 0;
}

Health::Health(int maxHealth)
{
	_maxHealth = maxHealth;
	_currentHealth = maxHealth;
}

// Operator Overloads

// For Health = Health + x
Health Health::operator+(int x)
{
	Health nh(_maxHealth);

	nh._currentHealth = _currentHealth + x;

	if (nh._currentHealth > nh._maxHealth) nh._currentHealth = nh._maxHealth;
	else if (nh._currentHealth < 0) nh._currentHealth = 0;

	return nh;
}

// For Health = Health - x
Health Health::operator-(int x)
{
	Health nh(_maxHealth);

	nh._currentHealth = _currentHealth - x;

	if (nh._currentHealth > nh._maxHealth) nh._currentHealth = nh._maxHealth;
	else if (nh._currentHealth < 0) nh._currentHealth = 0;

	return nh;
}

// For Health = x + Health
Health operator+(int x, Health h)
{
	Health nh(h._maxHealth);

	nh._currentHealth = h._currentHealth + x;

	if (nh._currentHealth > nh._maxHealth) nh._currentHealth = nh._maxHealth;
	else if (nh._currentHealth < 0) nh._currentHealth = 0;
	
	return nh;
}

// For Health = x - Health
Health operator-(int x, Health h)
{
	Health nh(h._maxHealth);

	nh._currentHealth = h._currentHealth - x;

	if (nh._currentHealth > nh._maxHealth) nh._currentHealth = nh._maxHealth;
	else if (nh._currentHealth < 0) nh._currentHealth = 0;

	return nh;
}

// For Health += x
Health Health::operator+=(int x)
{
	_currentHealth += x;

	if (_currentHealth > _maxHealth) _currentHealth = _maxHealth;
	else if (_currentHealth < 0) _currentHealth = 0;

	return *this;
}

// For Health += x
Health Health::operator-=(int x)
{
	_currentHealth -= x;

	if (_currentHealth > _maxHealth) _currentHealth = _maxHealth;
	else if (_currentHealth < 0) _currentHealth = 0;

	return *this;
}

// For Health == x
bool Health::operator==(int x)
{
	return (_currentHealth == x);
}