/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cppftlib_convert_f2s.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:00:42 by mstracke          #+#    #+#             */
/*   Updated: 2025/11/03 10:02:02 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cppftlib.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

/**
 * @brief function to convert string to float while considering 
 * the shortest decimal 
 * (remove all unnecessary '0' && if whole number delete '.' as well
 * value should be without a scientific notation
 */
std::string cppftlib::ft_convert_float_to_string(float f)
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << f;  
	std::string s = oss.str();
	//  Remove trailing zeros and decimal if unnecessary
	if(s.find('.') != std::string::npos)
	{
		while (!s.empty() 
			&& s[s.size() - 1] == '0') 
			s.erase(s.size() - 1, 1);
		if (!s.empty() 
			&& s[s.size() - 1] == '.') 
			s.erase(s.size() - 1, 1);
	}
	return s;
}
