/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cppftlib_convert_s2i.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:08:07 by mstracke          #+#    #+#             */
/*   Updated: 2025/09/08 15:15:16 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cppftlib.hpp"

//solution that checks for valid numbers which is a bit more efficient and ignores leading / trailing whitespaces compared to the stringstream-approach
/* bool	check_number(const std::string &to_convert)
{
	const char* cstr = to_transform.c_str();
	char* endptr = NULL;
	double	to_test= std::strtod(cstr, &endptr);
	//endptr will be set by strtod to point to the first character after the parsed number.
	//should I change this to also accept values with ending "f"?
	if (endptr == cstr || *endptr != '\0')
	{
		if (*endptr != 'f' 
			|| (*endptr == 'f' && *(endptr + 1) != '\0'))
		{
			std::cerr << "Invalid numeric string: " << to_transform << std::endl;
			return (false);  // Conversion failed
		}
	}
}
*/


/**
 * @brief function to convert an std::string to int, considering MAX_INT and MIN_INT
 *
 * @param value a reference to the int value that should be used for converted value
 * @param to_convert the string that has to be converted to int
 *
 * @return returns true if succesful, false if converions failed
 */
bool	cppftlib::ft_convert_to_int(int &value, const std::string &to_convert)
{
	if 	((to_convert == "-inff") | (to_convert == "+inff") 
			| (to_convert == "nanf") | (to_convert == "-inf")
		       	| (to_convert == "+inf") | (to_convert == "nan"))
		return (false);
	std::stringstream	ss(to_convert); //cpp-function, but does not check INT_MAX or INT_MIN, does not throw exceptions
	double				maxInt = std::numeric_limits<int>::max(); //cpp-style of using INT_MAX, <limits>-lib required
	double				minInt = std::numeric_limits<int>::min(); //cpp-style of using INT_MIN, <limits>-lib required
	long				to_test;
	char				c;
	// ss >> to_test;
	//!(iss >> to_test) → failed to parse an integer at all
	//(iss >> c) → there’s still extra data left over (not just whitespace)
	if (!(ss >> to_test) || (ss >> c))
	{
		std::cerr << "Invalid integer: $" << to_convert << "$" << std::endl;
	}
	// ss >> to_test;
	if (to_test > maxInt || to_test < minInt)
	{
		std::cout << "max, min? " << to_test << std::endl;
		return (false);
	}
	else
	{
		value = to_test;
		return (true);
	}
}
