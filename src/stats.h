#ifndef _stats_h
#define _stats_h

#define MAX_SKILL 100
#define MAX_ATTRIBUTE 35
#define NUM_SKILLS 21
#define NUM_ATTRIBUTES 5

#include <string>
#include <vector>
#include <list>

class Skill
{
public:
	Skill() : _number(0){}

	Skill(const unsigned int number, const std::string name, const std::string description) :
		_number(number), _name(name), _description(description) {}
	
	Skill(const Skill& other);

	inline unsigned int get() const
		{ return _number; }

	inline const std::string& getName() const
		{ return _name; }

	inline const std::string& getDescription() const
		{ return _description; }

	void set(const unsigned int n);

	void setName(const std::string &s);

	void setDescription(const std::string &s);

	Skill& operator = (const unsigned int &n)
		{ set(n); }

	Skill& operator ++ ()
		{ set(get()+1); }

private:
	unsigned int _number;
	std::string _name;
	std::string _description;
};

class Attribute
{
public:
	Attribute(){}
	Attribute(const unsigned int number, const std::string name, const std::string description) :
		_number(number), _name(name), _description(description) {}

	Attribute(const Attribute& other);

	inline unsigned int get() const
		{ return _number; }

	inline const std::string& getName() const
		{ return _name; }

	inline const std::string& getDescription() const
		{ return _description; }

	void set(const unsigned int n);

	void setName(const std::string &s);

	void setDescription(const std::string &s);

	Attribute& operator = (const unsigned int &n)
		{ set(n); }

	Attribute& operator ++ ()
		{ set(get()+1); }
private:
	unsigned int _number;
	std::string _name;
	std::string _description;
};

typedef std::vector<Skill> SkillVector;

typedef std::vector<Attribute> AttributeVector;

class Skills;

class SkillsObserver
{
public:
	virtual ~SkillsObserver(){}

	virtual void update(Skills* d) = 0;
protected:
	SkillsObserver(){}
};

typedef std::list<SkillsObserver*> SkillsObservers;

class Skills
{
public:
	Skills() : _data(NUM_SKILLS) {};

	void AddObserver(SkillsObserver* d);
	void DelObserver(SkillsObserver* d);
	void notify();

	Skill& operator [] (const unsigned int n)
	{
		if(n>=NUM_SKILLS) return _data[0];
		return _data[n];
	}

	inline void setFree(const unsigned int n)
	{ _free = n; }

	inline unsigned int getFree()
	{ return _free; }

private:
	SkillsObservers _observers;
	SkillVector _data;
	unsigned int _free;
};

class Attributes;

class AttributesObserver
{
public:
	virtual ~AttributesObserver(){}

	virtual void update(Attributes* d) = 0;
protected:
	AttributesObserver(){}
};

typedef std::list<AttributesObserver*> AttributesObservers;

class Attributes
{
public:
	Attributes() : _data(NUM_ATTRIBUTES) {}
	void AddObserver(AttributesObserver* d);
	void DelObserver(AttributesObserver* d);
	void notify();

	Attribute& operator [] (const unsigned int n)
	{
		if(n>=NUM_ATTRIBUTES) return _data[0];
		return _data[n];
	}

private:
	AttributesObservers _observers;
	AttributeVector _data;
};

#endif //#ifndef _stats_h
