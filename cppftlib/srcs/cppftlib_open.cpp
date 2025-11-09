/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cppftlib_open.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:00:45 by mstracke          #+#    #+#             */
/*   Updated: 2025/09/08 16:02:07 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cppftlib.hpp"

/**
 * @brief function to open an inputfile, check for access 
 * and sent it to a std::stringstream buffer 
 * 
 * consider: In C++98, open() can accept a const char* more reliably than std::string directly, 
 * so infile.c_str() is safer and more portable in older standards or use const char directly 
 * (instead of using const std::string& infile)
*/
bool	cppftlib::ft_open_inputfile(const char *path_infile, std::stringstream &buffer)
{
	//validate path of database
	std::ifstream		inputfile;
	//attempt to open infile-parameter
	inputfile.open(path_infile, std::fstream::in);
	//check if it was opened successful (fail also considers permission rights)
	if (!inputfile.is_open() || inputfile.fail())
	{
		return (false);
	}
	//read from inputfile to buffer
	buffer << inputfile.rdbuf();
	return (true);
}
