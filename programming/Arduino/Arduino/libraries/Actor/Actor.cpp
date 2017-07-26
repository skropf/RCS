#include "Actor.h"

void Actor::setId(int id)
{
	this->id =id;
}
int Actor::getId()
{
	return this->id;
}

void Actor::setName(char* name)
{
	this->name =name;
}
char* Actor::getName()
{
	return this->name;
}