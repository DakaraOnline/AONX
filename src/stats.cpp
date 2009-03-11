
#include "stats.h"


void Skill::set(const unsigned int n)
{
	if(n<=MAX_SKILL)
		_number = n;
}

void Skill::setName(const std::string &s)
{
	_name = s;
}

void Skill::setDescription(const std::string &s)
{
	_description = s;
}

Skill::Skill(const Skill& other)
{
	set(other.get());
	setName(other.getName());
	setDescription(other.getDescription());
}



void Attribute::set(const unsigned int n)
{
	if(n<=MAX_ATTRIBUTE)
		_number = n;
}

void Attribute::setName(const std::string &s)
{
	_name = s;
}

void Attribute::setDescription(const std::string &s)
{
	_description = s;
}

Attribute::Attribute(const Attribute& other)
{
	set(other.get());
	setName(other.getName());
	setDescription(other.getDescription());
}

void Skills::AddObserver(SkillsObserver* d)
{
	_observers.push_back(d);
	d->update(this);
}

void Skills::DelObserver(SkillsObserver* d)
{
	SkillsObservers::iterator it;
	for(it = _observers.begin();
		(*it)!=d;
		it++);
	_observers.erase(it);
}

void Skills::notify()
{
	for(SkillsObservers::iterator it = _observers.begin();
		it != _observers.end();
		it++)
	{
		(*it)->update(this);
	}
}


void Attributes::AddObserver(AttributesObserver* d)
{
	_observers.push_back(d);
	d->update(this);
}

void Attributes::DelObserver(AttributesObserver* d)
{
	AttributesObservers::iterator it;
	for(it = _observers.begin();
		(*it)!=d;
		it++);
	_observers.erase(it);
}

void Attributes::notify()
{
	for(AttributesObservers::iterator it = _observers.begin();
		it != _observers.end();
		it++)
	{
		(*it)->update(this);
	}
}
