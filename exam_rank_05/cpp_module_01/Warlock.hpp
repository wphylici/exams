/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 00:17:00 by wphylici          #+#    #+#             */
/*   Updated: 2021/05/06 02:05:10 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>

class Warlock
{
	public:
		Warlock(std::string const &name, std::string const &title);
		~Warlock();

		std::string const &getName(void) const;
		std::string const &getTitle(void) const;
		void setTitle(std::string const &title);
		void introduce() const;

	private:
		Warlock();
		Warlock(Warlock const &warlock);
		Warlock &operator = (Warlock const &warlock);
		std::string _name;
		std::string _title;
};

#endif