#pragma once
class Health
{
private:
	int _currentHealth;
	int _maxHealth;

public:
	Health(int maxHealth);

	// Operator overloads
	Health operator+(int);
	Health operator-(int);
	friend Health operator+(int, Health);
	friend Health operator-(int, Health);
	Health operator+=(int);
	Health operator-=(int);
};

