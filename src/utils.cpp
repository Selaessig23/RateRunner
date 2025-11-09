/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:38:32 by mstracke          #+#    #+#             */
/*   Updated: 2025/11/03 10:05:16 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/**
 * @brief function to create an int out of a std::string date (must be validated)
 * of format YYYY-MM-DD
 */
int	ft_create_int_date(std::string date)
{
	int	ret = 0;
	date.erase(4, 1);
	date.erase(6, 1);
	// std::cout << "test: " << date << std::endl;
	if (!cppftlib::ft_convert_to_int(ret, date))
		std::cerr << "Error in date conversion from std::string to int" << std::endl;
	return (ret);
}

/**
 * @brief helper function for ft_validate_year on the basis on Gregorian leap year rule
 * it checks if a year is a leapyear (==true) or not (==false)
 */
bool	ft_leapyear_check(int year)
{
	if (year % 400 == 0)
		return (true);
	else if (year % 4 == 0 && year % 100 != 0)
		return (true);
	else
		return (false);
}

/**
 * @brief function to validate the date of std::string data type according to the date format: Year-Month-Date
 * (2022-02-02)
 * 
 */
bool	ft_validate_stringdate(const std::string &date)
{
	//pre-check format:
	if (date[4] != '-' || date[7] != '-')
	{
		std::cout << "Error: There seems to be an error in date-format: " << date << std::endl;
		return (0);
	}
	int	year = 0; 
	int	month = 0;
	int	day = 0;
	
	if ((!cppftlib::ft_convert_to_int(year, date.substr(0,4).c_str()))
		|| (!cppftlib::ft_convert_to_int(month, date.substr(5,2).c_str()))
		|| (!cppftlib::ft_convert_to_int(day, date.substr(8,2).c_str())))
		return (false);
	if (year < 0)
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return (false);
	}
	if (month < 0 || month > 12)
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return (false);
	}
	int day_month_check[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	//consider leap year for february
	if (ft_leapyear_check(year))
		day_month_check[1] = 29;
	//check if day-month relation of date is valid
	if (day_month_check[month - 1] < day || day < 1)
	{
		std::cout << "Error: bad input (day does not exist in month) => " << date << std::endl;
		return (false);
	}
	return (true);
}

//helper function to jump to next line
std::size_t	ft_jump_nl(std::string &to_check, std::size_t pos)
{
	return (to_check.find('\n', pos));
}

