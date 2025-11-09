/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:20:59 by mstracke          #+#    #+#             */
/*   Updated: 2025/11/09 15:15:25 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "../cppftlib/include/cppftlib.hpp"
#include "BitcoinExchange.hpp"
#include <iostream>
#include <sstream>      // std::stringstream, std::stringbuf
#include <fstream>	// std::ifstream, 
#include <string>	//std::erase
#include <map>
#include <utility> // std::make_pair()
#include <string>
// #include <cstdlib> // for atoi
#include <limits> //for INT_MIN / INT_MAX
#include <iomanip> //std::setprecision
// #include <cmath> //for std::nanf
	
/**
 * @brief check header of database-file / infile
 */
bool	BitcoinExchange::ft_header_check(const std::string &to_check, bool database)
{
	if ((database == false && !(to_check.substr(0, 13) ==  "date | value\n")))
	{
		std::cout << "wrong header / first line in input" << std::endl;
		return (false);
	}
	else if ((database == true && !(to_check.substr(0 , 19) == "date,exchange_rate\n")))
	{
		std::cout << "wrong header / first line in database" << std::endl;
		return (false);
	}
	//std::cout << "test: correct first line" << std::endl;
	return (true);
}

/**
 * @brief helper function for constructor that checks if the format of database file is correct
 * 
 * @param &buffer stream that has to be checked
 * @database if true, database has to be checked, if false, the input file has to be checked
 */
bool	BitcoinExchange::check_format(const std::stringstream &buffer)
{
	std::string	to_check = buffer.str();
	// int		pos = 0;
	std::size_t pos = 0;
	float		f = 0;

	//check for first line
	ft_header_check(to_check, true);
	//jump to next line
	pos = ft_jump_nl(to_check, pos);
	int i = 0;
	//size-check is necessary for cases in which the last char of string is "\n"
	while (pos != std::string::npos && to_check.size() > pos + 1)
	{
		pos++;
		//check if separator was set correct
		if (to_check[pos + 10] && to_check[pos + 10] != ',')
		{
			std::cout << "Error: incorrect separator line in database:" << to_check[pos + 10] << std::endl;
			return (false);
		}
		//validate date & float number
		if (!ft_validate_stringdate(to_check.substr(pos, 10))
				|| !cppftlib::ft_convert_to_float(f, to_check.substr(pos + 11, (ft_jump_nl(to_check, pos) - (pos + 11)))))
		{
			std::cout << "Error: date and / or float is false: " << i + 1 << ": " << to_check.substr(pos, 10) << ", " << to_check.substr(pos + 11, (ft_jump_nl(to_check, pos) - (pos + 11))) << std::endl;
			return (false);
		}
		// std::cout << "date and float is true: " << i + 1 << ": " << to_check.substr(pos, 10) << ", " << to_check.substr(pos + 11, (ft_jump_nl(to_check, pos) - (pos + 11))) << std::endl;
		pos = ft_jump_nl(to_check, pos);
		i++;
	}
	return (true);
}

/**
 * @brief the constructor reads from provided database.csv, 
 * does parsing of database-file, format:
 * date,price
 * YYY-MM-DD,float
 * stores the data into
 * std::map (private) and also finds the lowest date to store in this->start
 * 
 * think about integrating the path as a macro instead of sending it as a parameter
 */ 

BitcoinExchange::BitcoinExchange(std::string &path_database)
{
	std::stringstream	buffer;
	if (!cppftlib::ft_open_inputfile(path_database.c_str(), buffer))
	{
		std::cerr << "Database file error. Unable to construct class." << std::endl;
		throw BitcoinExchange::Exception_path();
	}
	if (check_format(buffer))
	{
		std::string		to_integrate = buffer.str();
		float 			f = 0;
		//jump to next line
		std::size_t		pos = ft_jump_nl(to_integrate, 0);
		//size-check is necessary for cases in which the last char of string is "\n"
		while (pos != std::string::npos && to_integrate.size() > pos + 1)
		{
			pos++;
			cppftlib::ft_convert_to_float(f, to_integrate.substr(pos + 11, (ft_jump_nl(to_integrate, pos) - (pos + 11))));
			//insert() won’t overwrite an existing key.
			// database.insert(std::make_pair(to_integrate.substr(pos, 10), f);
			//operator[] will overwrite if the key exists, otherwise it will insert the float as a new key of std::map
			this->_database[to_integrate.substr(pos, 10)] = f;
			pos = ft_jump_nl(to_integrate, pos);
		}
		std::map<std::string, float>::const_iterator it = this->_database.begin();
		this->start = ft_create_int_date(it->first);
		//search for lowest date
		for (; it != _database.end(); it++)
		{
			if (this->start > ft_create_int_date(it->first))
				this->start = ft_create_int_date(it->first);
		}
		// std::cout << "Default constructor was called." << std::endl; 
	}
	else
	{
		std::cerr << "Database format error. Unable to construct class." << std::endl;
		throw BitcoinExchange::Exception_data_format(); 
	}
} 

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) 
{ 
	this->_database = other._database;
	// std::cout << "Copy constructor was called." << std::endl;
}

BitcoinExchange	BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		this->_database = other._database;
	}
	// std::cout << "Copy constructor was called." << std::endl;
	return (*this);
}

BitcoinExchange::~BitcoinExchange(){
	// std::cout << "Destructor was called." << std::endl;
}

/**
 * @brief function to calculate the exchange rate according to date and 
 * value (has to be multiplied)
 */
float	BitcoinExchange::ft_calc_exchange_rate(int date, float f)
{
	int	database_date = 0;
	for (std::map<std::string, float>::const_iterator it = this->_database.begin(); it != this->_database.end(); it++)
	{
		database_date = ft_create_int_date(it->first);
		//should consider exact matches and the closest lower date
		// std::cout << f << " * " << it->second << std::endl;
		if (date < database_date)
		{
			it--;
			return (f * it->second);
			// std::cout << (f * it->second);
			// break ;
		}
	}
	//for dates bigger than max date of database
	std::map<std::string, float>::const_iterator it = this->_database.begin();
	std::advance(it, _database.size() - 1);
	return (f * it->second);
}

/**
 * @brief function to analyze an input file
 * that should consist of dates and float-values in this format
 * date | value
 * 2011-01-03 | 3
 * [...]
 * this functions 
 * (1) checks if file is accessible
 * (2) loops through the table and checks if
 * (2a) date is valid
 * (2b) float-value is valid (0 < f < 1000)
 * (2c) display on the standard output the result of the value multiplied
 * by the exchange rate according to the date indicated in your database
 * (if no exact match: closest lower date)
 * 
 * @param infile the infile to analyze
 */
void	BitcoinExchange::analyzer(const char *infile)
{
	std::stringstream	buffer;
	// std::cout << "test analyzer" << std::endl;
	if (!cppftlib::ft_open_inputfile(infile, buffer))
	{
		std::cerr << "Input file error. " << std::endl;
		throw BitcoinExchange::Exception_path();
	}			
	std::string	to_check = buffer.str();
	//check header of table
	ft_header_check(to_check, false); //what to return if wrong?
	std::size_t	pos = ft_jump_nl(to_check, 0);
	//loop through the input file and analyze lines
	//size-check is necessary for cases in which the last char of string is "\n"
	while (pos != std::string::npos && to_check.size() > pos + 1)
	{
		pos++;
		int 	date = 0;
		float	f = 0;
		
		//validate date
		if (!ft_validate_stringdate(to_check.substr(pos, 10)))
		{
			// std::cout << "Error: bad input => " << to_check.substr(pos, 10) << std::endl;
		}
		//check if separator was set correct
		else if (to_check[pos + 10] && to_check[pos + 10] != ' ')
		{
			std::cout << "Error: There seems to be an error in date-format." << std::endl;
		}
		//check if day of date is set correctly
		else if ((to_check[pos + 11] && to_check[pos + 11] != '|') 
				|| (to_check[pos + 12] && to_check[pos + 12] != ' '))
		{
			std::cout << "Error: separator line was set incorrectly." << std::endl;
		}
		else 
		{
			date = ft_create_int_date(to_check.substr(pos, 10));
			if (date < start)
				std::cout << "Error: date lies before first date of bitcoin rate in database" << std::endl;
			else 
			{
				std::size_t end = ft_jump_nl(to_check, pos);
				if (end == std::string::npos)
					end = to_check.size() - (pos + 13);
				else
					end -= (pos + 13);
				// if (!ft_convert_to_float(f, to_check.substr(pos + 13, (ft_jump_nl(to_check, pos) - (pos + 13) + 1))))
				//check if float is correct
				if (!cppftlib::ft_convert_to_float(f, to_check.substr(pos + 13, end)))
					std::cout << "Error: not a float" << std::endl;
				else if (f > 1000)
					std::cout << "Error: too large a number." << std::endl;
				else if (f < 0)
					std::cout << "Error: not a positive number." << std::endl;
				else if (f != f) //by definition nanf is not equal to itself
				{
					std::cout << "Error: \"nanf\" was detected. Not supported by this program." << std::endl;
				}
				else
				{
					//print date, value and calculate exchange rate
					std::cout << to_check.substr(pos, 10) << " => " << f << " = " << cppftlib::ft_convert_float_to_string(ft_calc_exchange_rate(date, f)) << std::endl;
				}
			}
		}
		//jump to next line
		pos = ft_jump_nl(to_check, pos);
	}
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//test printing of database values
	// for (std::map<std::string, float>::const_iterator it = this->_database.begin(); it != _database.end(); it++)
	// {
		//std::cout << "first: " << it->first << std::fixed  << std::setprecision(2) << ", second: " << static_cast<float>(it->second) << std::endl;
	// }
	// std::cout << "size of database: " << this->_database.size() << std::endl;

}

char const	*BitcoinExchange::Exception_path::what(void) const throw()
{
		return ("Error opening file.");
}

char const	*BitcoinExchange::Exception_data_format::what(void) const throw()
{
	return ("Problems with format of file.");
}
