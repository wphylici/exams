#ifndef ASPELL_HPP
# define ASPELL_HPP

# include "ATarget.hpp"

# include <iostream>

class ATarget;

class ASpell
{
	public:
		ASpell();
		ASpell(std::string const &name, std::string const &effects);
		ASpell(ASpell const &aspell);
		ASpell &operator = (ASpell const &aspell);
		virtual ~ASpell();

		std::string const &getName(void) const;
		std::string const &getEffects(void) const;
		void launch(ATarget const &atarget) const;

		virtual ASpell *clone(void) const = 0;

	private:
		std::string _name;
		std::string _effects;
};

#endif
