/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:04:57 by mstracke          #+#    #+#             */
/*   Updated: 2025/11/03 10:05:03 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>

int		ft_create_int_date(std::string date);
bool		ft_validate_stringdate(const std::string &date);
bool		ft_leapyear_check(int year);
std::size_t	ft_jump_nl(std::string &to_check, std::size_t pos);

# endif
