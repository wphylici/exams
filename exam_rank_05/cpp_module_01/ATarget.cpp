#include "ATarget.hpp"

ATarget::ATarget(){}

ATarget::ATarget(std::string const &type)
{
	this->_type = type;
}

ATarget::ATarget(ATarget const &atarget)
{
	*this = atarget;
}

ATarget &ATarget::operator = (ATarget const &atarget)
{
	if (this == &atarget)
		return (*this);
	this->_type = atarget._type;
}

ATarget::~ATarget() {}

std::string const &ATarget::getType(void) const
{
	return (this->_type);
}

void ATarget::getHitBySpell(ASpell const &aspell) const
{
	std::cout << this->_type << " has been " << aspell.getEffects() << std::endl;
}