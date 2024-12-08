/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phone.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:01:16 by dde-giov          #+#    #+#             */
/*   Updated: 2024/06/17 02:15:32 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONE_HPP
# define PHONE_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include "PhoneBook.hpp"

void    question(int n);
int     check_answare(std::string answare, int n);
void	add_newcontact(PhoneBook &phonebook, std::string answare, int n);

#endif