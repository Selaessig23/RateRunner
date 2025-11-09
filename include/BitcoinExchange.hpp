/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:22:03 by mstracke          #+#    #+#             */
/*   Updated: 2025/11/09 15:14:22 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include "../cppftlib/include/cppftlib.hpp"
#include <iostream>
#include <sstream>      // std::stringstream, std::stringbuf
#include <fstream>	// std::ifstream 
#include <string>	//std::erase
#include <map>
#include <utility> // std::make_pair()
#include <string>
// #include <cstdlib> // for atoi
#include <limits> //for INT_MIN / INT_MAX
#include <iomanip> //std::setprecision
// #include <cmath> //for std::nanf
	

/**
 * @brief class to 
 * store prices from a csv in format 
 * date,price
 * YYY-MM-DD,float
 * does parsing of database,
 * reads from infile, does parsing of infile
 * and displays on the standard output the result of the value (provided by infile) 
 * multiplied by the exchange rate according to the date indicated in your database.
 */
class	BitcoinExchange{

	private:
		std::map<std::string, float>	_database;
		int				start;

		//member functions that help checing format and calculating exchange rate
		float				ft_calc_exchange_rate(int date, float f);
		bool				ft_header_check(const std::string &to_check, bool database);
		bool				check_format(const std::stringstream &buffer);

	public:
		BitcoinExchange(std::string &path_database);
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange	operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		void	analyzer(const char *infile);

		class	Exception_path : public std::exception{
			public:
				virtual char const	*what(void) const throw();
		} ;
				
		class	Exception_data_format : public std::exception{
			public:
				virtual char const	*what(void) const throw();
		} ;
		
};

//helper functions, maybe for some of them it makes sense to place them within the class to reach attributes of the class
//utils.hpp
// bool		ft_leapyear_check(int year);
// bool		ft_validate_stringdate(const std::string &date);
// std::size_t	ft_jump_nl(std::string &to_check, std::size_t pos);
// int		ft_create_int_date(std::string date);

//functions form my cpp_libft
// bool	ft_open_inputfile(const char *path_infile, std::stringstream &buffer);
// bool	ft_convert_to_int(int &value, const std::string &to_transform);
// bool	ft_convert_to_float(float &value, const std::string &to_convert);
// std::string 	ft_convert_float_to_string(float f);
# endif
