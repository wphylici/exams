/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wphylici <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 00:25:06 by wphylici          #+#    #+#             */
/*   Updated: 2021/05/06 02:10:18 by wphylici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Warlock.hpp"

Warlock::Warlock(std::string const &name, std::string const &title)
{
	this->_name = name;
	this->_title = title;

	std::cout << this->_name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock()
{
	std::cout << this->_name << ": My job here is done!" << std::endl;
}

std::string const &Warlock::getName(void) const
{
	return (this->_name);
}

std::string const &Warlock::getTitle(void) const
{
	return (this->_title);
}

void Warlock::setTitle(std::string const &title)
{
	this->_title = title;
}

void Warlock::introduce() const
{
	std::cout << this->_name << ": I am " << this->_name << ", " << this->_title << std::endl;
}