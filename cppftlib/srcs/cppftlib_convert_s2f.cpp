/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cppftlib_convert_s2f.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:12:15 by mstracke          #+#    #+#             */
/*   Updated: 2025/09/08 15:15:01 by mstracke         ###   ########.fr       */
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
 * @brief function to convert the string to float
 * it considers pseudo-literals -inff | +inff | nanf
 * it checks for max-min values before conversion 
 * it ignores leading/trailing spaces
 * 
 * @param value a reference to the int value that should be used for converted value
 * @param to_convert the string that has to be converted to int
 *
 * @return returns true if succesful, false if converions failed
 */
// A valid value must be either a float or a positive integer, between 0 and 1000.
bool	cppftlib::ft_convert_to_float(float &value, const std::string &to_convert)
{
	//to handle pseudo-literals
	if (to_convert == "-inff")
		value = -1.0f / 0.0f; 
	else if (to_convert == "+inff")
		value = 1.0f / 0.0f;
	else if (to_convert == "nanf")
	{
		value = 0.0f / 0.0f;
		// return (false);
	}
	else
	{
		std::stringstream		ss(to_convert);
		double				to_test;
		char 				c;
		double				max = std::numeric_limits<float>::max(); //cpp-style of using FLOAT_MAX, <limits>-lib required
		double				min = -std::numeric_limits<float>::max(); //cpp-style of using FLOAT_MIN, <limits>-lib required
		// Try to read a double
		if (!(ss >> to_test))
		{
// 			std::cerr << "Invalid float: $" << to_convert << "$" << std::endl;
			return false; // no double at the start
		}
		// Check for leftover junk (ignoring whitespace), think about how to accept "f"
		if (ss >> c && ((c == 'f' && (ss >> c)) || c != 'f'))
		{
// 			std::cerr << "Invalid float: $" << to_convert << "$" << std::endl;
			return false; // extra characters after the number
		}
		// ss >> to_test;
		if (to_test > max || to_test < min)
		{
// 			std::cout << "max, min? " << to_test << std::endl;
			return (false);
		}
		value = to_test;
	}
	return (true);
}

