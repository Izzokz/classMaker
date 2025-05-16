/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classMaker.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:18:40 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/05/15 15:18:41 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>

bool	gDebug = 0;

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
		std::ofstream	hpp(((std::string)*argv + ".hpp").c_str());
		if (!hpp.is_open())
		{
			std::cout << "\e[31;1m[Fatal Error] Can't open " << (std::string)*argv + ".hpp\e[0m\n";
			return (2);
		}
		std::ofstream	cpp(((std::string)*argv + ".cpp").c_str());
		if (!cpp.is_open())
		{
			std::cout << "\e[31;1m[Fatal Error] Can't open " << (std::string)*argv + ".cpp\e[0m\n";
			hpp.close();
			return (2);
		}
		hpp << "#pragma once\n\nclass\t" << *argv << "\n{\n\tpublic:\n\t\t"
			<< *argv << "(void);\n\t\t" << *argv << "(const " << *argv << " &cpy);\n\t\t"
			<< *argv << "\t&operator=(const " << *argv << " &cpy);\n\t\t~"
			<< *argv << "(void);\n}\n";
		hpp.close();
		cpp << "#include \"" << *argv << ".hpp\"\n\n"
			<< *argv << "::" << *argv << "(void)\n{\n\t";
		if (gDebug)
			cpp << "std::cout << \"" << *argv << " default constructor called\\n\";\n}\n\n";
		else
			cpp << "\n}\n\n";
		cpp << *argv << "::" << *argv << "(const " << *argv << " &cpy)\n{\n\t";
		if (gDebug)
			cpp << "std::cout << \"" << *argv << " copy constructor called\\n\";\n}\n\n";
		else
			cpp << "\n}\n\n";
		cpp << *argv << "\t&" << *argv << "::operator=(const " << *argv << " &cpy)\n{\n\t";
		if (gDebug)
			cpp << "std::cout << \"" << *argv << " copy assignment operator called\\n\";\n}\n\n";
		else
			cpp << "\n}\n\n";
		cpp << *argv << "::~" << *argv << "(void)\n{\n\t";
		if (gDebug)
			cpp << "std::cout << \"" << *argv << " destructor called\\n\";\n}\n";
		else
			cpp << "\n}\n";
	}
}
