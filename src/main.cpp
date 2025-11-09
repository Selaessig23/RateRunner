/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:29:55 by mstracke          #+#    #+#             */
/*   Updated: 2025/11/09 15:24:17 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int	main (int argc, char *argv[])
{
// 	std::string	database = "cpp_09/data.csv";

	if (argc < 3)
	{
		std::cerr << "Error: could not open file. There is no infile." << std::endl;
		return (1);
	}
	else if (argc > 3)
	{
		std::cerr << "Error: There are too many arguments as input." << std::endl;
		return (1);
	}
	else
	{
		try {
			std::string	database = argv[1];
			BitcoinExchange	test(database);
			try {
			test.analyzer(argv[2]);
			} catch (const std::exception& e) {
				std::cout << "Exception caught: " << e.what() << std::endl;
			}
		} catch (const std::exception& e) {
			std::cout << "Exception caught: " << e.what() << std::endl;
		}

	}
	return (0);
}
