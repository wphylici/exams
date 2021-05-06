#include "ASpell.hpp"

ASpell::ASpell(){}

ASpell::ASpell(std::string const &name, std::string const &effects)
{
	this->_name = name;
	this->_effects = effects;

}

ASpell::ASpell(ASpell const &aspell)
{
	*this = aspell;
}

ASpell &ASpell::operator = (ASpell const &aspell)
{
	if (this == &aspell)
		return (*this);
	this->_name = aspell._name;
	this->_effects = aspell._effects;
}

ASpell::~ASpell() {}

std::string const &ASpell::getName(void) const
{
	return (this->_name);
}

std::string const &ASpell::getEffects(void) const
{
	return (this->_effects);
}

void ASpell::launch(ATarget const &atarget) const
{
	atarget.getHitBySpell(*this);
}