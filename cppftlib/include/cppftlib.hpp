/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cppftlib.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:03:55 by mstracke          #+#    #+#             */
/*   Updated: 2025/09/08 15:25:03 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CPPFTBIB_HPP
# define CPPFTBIB_HPP

#include <iostream>
#include <sstream>      // std::stringstream, std::stringbuf
#include <fstream>	// std::ifstream, 
#include <limits>	//for INT_MIN / INT_MAX

namespace cppftlib {
	bool		ft_open_inputfile(const char *path_infile, std::stringstream &buffer);
	bool		ft_convert_to_int(int &value, const std::string &to_convert);   
	bool		ft_convert_to_float(float &value, const std::string &to_convert);
	std::string 	ft_convert_float_to_string(float f);
} ;

# endif
