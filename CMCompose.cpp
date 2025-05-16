/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CMCompose.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:23:29 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/05/16 16:23:31 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CMCompose.hpp"

CMCompose::CMCompose(const std::string &className, std::ofstream &hpp, std::ofstream &cpp, const bool &gDebug) : _className(className), _hpp(hpp), _cpp(cpp), _gDebug(gDebug)
{
	const char *opsArray[] = {"op+", "op-", "op*", "op/", "op%", "op++", "op--", "++op", "--op",
		"op==", "op!=", "op>", "op<", "op>=", "op<=", "op&&", "op||", "op!",
		"op&", "op|", "op^", "op~", "op<<", "op>>", "op.", "op->", "op?", "op:", "op,", "op()", "op[]",
		"op+=", "op-=", "op*=", "op/=", "op%=", "op&=", "op|=", "op^=", "op<<=", "op>>=",
		"opnew", "opdelete", "opnew[]", "opdelete[]"};

	for (size_t i = 0; i < sizeof(opsArray) / sizeof(opsArray[0]); ++i)
		_op[opsArray[i]] = 0;
}

CMCompose::~CMCompose(void)
{
	std::cout << "\e[32;1m[" << _className << "] Complete !\e[0m\n";
}

CMCompose	&CMCompose::operator<<(const std::string &op)
{
	if (_op.find(op) != _op.end())
		_op[op] = 1;
	else
		std::cout << "\e[31;1m[" << op << "] Invalid operator.\e[0m\n";
	return (*this);
}

void	CMCompose::printOp(void) const
{
	std::string	op;

	for (std::map<std::string, bool>::const_iterator it = _op.begin(); it != _op.end(); ++it)
	{
		const std::string	&id = it->first;
		bool			added = it->second;

		if (!added)
			continue ;
		if (id == "++op" || id == "--op")
			op = id.substr(0, 2);
		else
			op = id.substr(2);
		if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%"
			|| op == "&" || op == "|" || op == "^" || op == "<<" || op == ">>")
		{
			_hpp << "\t\t" << _className << "\toperator" << op << "(const " << _className << " &rhs) const;\n";
			_cpp << "\n" << _className << "\t" << _className << "::operator" << op
				<< "(const " << _className << " &rhs) const\n{\n\t\n}\n";
		}
		else if (op == "+=" || op == "-=" || op == "*=" || op == "/=" || op == "%="
			|| op == "&=" || op == "|=" || op == "^=" || op == "<<=" || op == ">>=")
		{
			_hpp << "\t\t" << _className << "\t&operator" << op << "(const " << _className << " &rhs);\n";
			_cpp << "\n" << _className << "\t&" << _className << "::operator" << op
				<< "(const " << _className << " &rhs)\n{\n\treturn (*this);\n}\n";
		}
		else if (op == "==" || op == "!=" || op == "<" || op == "<=" || op == ">" || op == ">=" || op == "&&" || op == "||")
		{
			_hpp << "\t\tbool\toperator" << op << "(const " << _className << " &rhs) const;\n";
			_cpp << "\nbool\t" << _className << "::operator" << op
				<< "(const " << _className << " &rhs) const\n{\n\t\n}\n";
		}
		else if	 (op == "!")
		{
			_hpp << "\t\tbool\toperator!(void) const;\n";
			_cpp << "\nbool\t" << _className << "::operator!(void) const\n{\n\t\n}\n";
		}
		else if (op == "~")
		{
			_hpp << "\t\t" << _className << "\toperator~(void) const;\n";
			_cpp << "\n" << _className << "\t" << _className << "::operator~(void) const\n{\n\t\n}\n";
		}
		else if (op == "++" || op == "--") {
			if (id == "++op" || id == "--op")
			{
				_hpp << "\t\t" << _className << "\t&operator" << op << "(void);\n";
				_cpp << "\n" << _className << "\t&" << _className << "::operator" << op
					<< "(void)\n{\n\treturn (*this);\n}\n";
			}
			else
			{
				_hpp << "\t\t" << _className << "\toperator" << op << "(int);\n";
				_cpp << "\n" << _className << "\t" << _className << "::operator" << op
					<< "(int)\n{\n\t" << _className << "\ttmp\n\n\treturn (tmp);\n}\n";
			}
		}
		else if (op == "[]")
		{
			_hpp << "\t\tint\t\t&operator[](int i);\n";
			_cpp << "\nint\t\t&" << _className << "::operator[](int i)\n{\n\t\n}\n";
		}
		else if (op == "()")
		{
			_hpp << "\t\tvoid\toperator()(void) const;\n";
			_cpp << "\nvoid\t" << _className << "::operator()(void) const\n{\n\t\n}\n";
		}
		else if (op == "->")
		{
			_hpp << "\t\t" << _className << "\t*operator->(void);\n";
			_cpp << "\n" << _className << "\t*" << _className << "::operator->(void)\n{\n\t\n}\n";
		}
		else if (op == "new")
		{
			_hpp << "\t\tvoid\t*operator new(std::size_t size);\n";
			_cpp << "\nvoid\t*" << _className << "::operator new(std::size_t size)\n{\n\treturn (::operator new(size));\n}\n";
		}
		else if (op == "delete")
		{
			_hpp << "\t\tvoid\toperator delete(void *ptr);\n";
			_cpp << "\nvoid\t" << _className << "::operator delete(void *ptr)\n{\n\t::operator delete(ptr);\n}\n";
		}
		else if (op == "new[]")
		{
			_hpp << "\t\tvoid\t*operator new[](std::size_t size);\n";
			_cpp << "\nvoid\t*" << _className << "::operator new[](std::size_t size)\n{\n\treturn (::operator new[](size));\n}\n";
		}
		else if (op == "delete[]")
		{
			_hpp << "\t\tvoid\toperator delete[](void *ptr);\n";
			_cpp << "\nvoid\t" << _className << "::operator delete[](void *ptr)\n{\n\t::operator delete[](ptr);\n}\n";
		}
	}
}

void	CMCompose::compose(void) const
{
	_hpp << "#pragma once\n\nclass\t" << _className << "\n{\n\tpublic:\n\t\t"
		<< _className << "(void);\n\t\t" << _className << "(const " << _className << " &cpy);\n\t\t"
		<< _className << "\t&operator=(const " << _className << " &cpy);\n\t\t~"
		<< _className << "(void);\n";
	_cpp << "#include \"" << _className << ".hpp\"\n\n"
		<< _className << "::" << _className << "(void)\n{\n\t";
	if (_gDebug)
		_cpp << "std::cout << \"" << _className << " default constructor called\\n\";\n}\n\n";
	else
		_cpp << "\n}\n\n";
	_cpp << _className << "::" << _className << "(const " << _className << " &cpy)\n{\n\t";
	if (_gDebug)
		_cpp << "std::cout << \"" << _className << " copy constructor called\\n\";\n}\n\n";
	else
		_cpp << "\n}\n\n";
	_cpp << _className << "\t&" << _className << "::operator=(const " << _className << " &cpy)\n{\n\t";
	if (_gDebug)
		_cpp << "std::cout << \"" << _className << " copy assignment operator called\\n\";\n";
	_cpp << "return (*this);\n}\n\n" << _className << "::~" << _className << "(void)\n{\n\t";
	if (_gDebug)
		_cpp << "std::cout << \"" << _className << " destructor called\\n\";\n}\n";
	else
		_cpp << "\n}\n";
	CMCompose::printOp();
	_hpp << "};\n";
	CMCompose::closeFiles();
}

void	CMCompose::closeFiles(void) const
{
	_hpp.close();
	_cpp.close();
}
