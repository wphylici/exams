#ifndef ATARGET_HPP
# define ATARGET_HPP

# include "ASpell.hpp"

# include <iostream>

class ASpell;

class ATarget
{
	public:
		ATarget();
		ATarget(std::string const &type);
		ATarget(ATarget const &atarget);
		ATarget &operator = (ATarget const &atarget);
		virtual ~ATarget();

		std::string const &getType(void) const;
		void getHitBySpell(ASpell const &aspell) const;

		virtual ATarget *clone(void) const = 0;

	private:
		std::string _type;
};

#endif