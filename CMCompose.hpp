/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CMCompose.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:37:01 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/05/16 16:23:39 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>

class	CMCompose
{
	private:
		std::string	_className;
		std::ofstream	&_hpp;
		std::ofstream	&_cpp;
		const bool	_gDebug;
		std::map<std::string, bool> _op;
	public:
		CMCompose(const std::string &className, std::ofstream &hpp, std::ofstream &cpp, const bool &gDebug);
		~CMCompose(void);
		CMCompose	&operator<<(const std::string &op);
		void		printOp(void) const;
		void		compose(void) const;
		void		closeFiles(void) const;
};
