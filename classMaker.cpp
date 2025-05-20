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

static void	printHelp(void)
{
	std::cout << "Usage:\n\t- class -d <format1> <format2> <format3>... # Fills all classes with debug messages (Constructors and Destructor)\n\t- "
		<< "class <format1> <format2> <format3>... # Basic class making\nFormats:\n\t- ClassName # Creates a class\n\t- \"ClassName ; <operator1> <operator2>...\""
		<< " # Creates a class with operators\n\t- \"ClassName : ParentClass1, ParentClass2, ...\" # Creates a class with inheritance /!\\ NOT IMPLEMENTED YET /!\\\n\t-"
		<< " \"ClassName : ParentClass, ... ; <operator> ...\" # Creates a class with both inheritance and operators"
		<< " /!\\ NOT IMPLEMENTED YET /!\\\nOperators:\n\t- op+ op- op/ op* op% op++ ++op op-- --op # Arithmetic and Increment/Decrement operators\n\t- op== op!= op> op< op>= op<="
		<< " # Comparison operators\n\t- op&& op|| op! # Logical operatos\n\t- op& op| op^ op~ op<< op>> # Bitwise operators\n\t- op&= op|= op^= op<<= op>>="
		<< " # Bitwise compound assignment operators\n\t- op+= op-= op/= op*= op%= # Compound assignment operators\n\t- op. op-> op? op: op, op() op[] # Miscellaneous operators"
		<< "\n\t- opnew opdelete opnew[] opdelete[] # Memory management operators\nExtra Information:\n\t- The setup is public only (no protected, no private...)\n\t-"
		<< " The program is case sensitive (\"Class:Parent,ParentTheSecond ; op++op--\" will create a class named \"Class:Parent,ParentTheSecond\" with no operator)\n";
}

static void	parseCompose(CMCompose &constructor, std::string &rules)
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
	if (argc == 1)
		printHelp();
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
