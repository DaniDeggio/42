/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 05:21:30 by dde-giov          #+#    #+#             */
/*   Updated: 2024/10/01 12:14:37 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phone.hpp"

void question(int n){
 if (n == 0)
		std::cout << "Type the Frist Name:" << std::endl;
if (n == 1)
		std::cout << "Type the Last Name:" << std::endl;
if (n == 2)
		std::cout << "Type the NickName:" << std::endl;
if (n == 3)
		std::cout << "Type the Phonenumber:" << std::endl;
if (n == 4)
		std::cout << "Type the Darkest Secret:" << std::endl;
}

int check_answare(std::string answare, int n){
	answare.erase(0, answare.find_first_not_of(" \t\v\f\r"));
		while (isspace(answare[answare.length() - 1]))
            answare.erase(answare.find_last_not_of(" \t\v\r\f") + 1, answare[answare.length() - 1]);
	if (answare.empty())
		return (1);
	if (n == 3){
		if (atoi(answare.c_str()) == 0)
			return (1);
	}
	return (0);
}

void	add_newcontact(PhoneBook &phonebook, std::string answare, int n){
	static	std::string frist_name;
	static	std::string last_name;
    static	std::string nickname;
	static	std::string phone_number;
	static	std::string secret;
	
	if (n == 0)
		frist_name = answare;
	if (n == 1)
		last_name = answare;
	if (n == 2)
		nickname = answare;
	if (n == 3)
		phone_number = answare;
	if (n == 4)
	{
		secret = answare;
		phonebook.add_contact(frist_name, last_name, nickname, phone_number, secret);
	}
}
