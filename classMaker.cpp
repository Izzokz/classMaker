/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classMaker.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:18:40 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/05/16 16:22:56 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CMCompose.hpp"

bool	gDebug = 0;

void	parseCompose(CMCompose &constructor, std::string &rules)
{
	size_t			semi = rules.find(';');

	if (semi == std::string::npos)
		return ;
	std::string		ops = rules.substr(semi + 1);
	std::istringstream	iss(ops);
	std::string 		op;
	while (iss >> op)
		constructor << op;
}

int	main(int argc, char *argv[])
{
	if (argc > 1 && (std::string)*(argv + 1) == "-d")
	{
		gDebug = 1;
		argc--;
		argv++;
	}
	while (--argc)
	{
		++argv;
		std::string	className = std::string(*argv).substr(0, std::string(*argv).find(' '));
		std::ofstream	hpp((className + ".hpp").c_str());
		if (!hpp.is_open())
		{
			std::cout << "\e[31;1m[Fatal Error] Can't open " << className + ".hpp\e[0m\n";
			continue ;
		}
		std::ofstream	cpp((className + ".cpp").c_str());
		if (!cpp.is_open())
		{
			std::cout << "\e[31;1m[Fatal Error] Can't open " << className + ".cpp\e[0m\n";
			hpp.close();
			continue ;
		}
		CMCompose	constructor(className, hpp, cpp, gDebug);
		std::string	rules = *argv;
		parseCompose(constructor, rules);
		constructor.compose();
	}
}
