#pragma once
class GameObject
{
public:
	GameObject(void);
	~GameObject(void);

	virtual int getEntityType() = 0;
};

