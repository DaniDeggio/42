/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:26:36 by dde-giov          #+#    #+#             */
/*   Updated: 2024/10/01 11:59:31 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHONEBOOK_HPP
# define	 PHONEBOOK_HPP

#include "Contact.hpp"
#include <iomanip>
#include <iostream>
#include <string>

class PhoneBook{
private:
	Contact	Contacts[8];
public:
	PhoneBook();
	~PhoneBook();
	
    void	slide_contacts();
	void	add_contact(std::string frist_name, std::string last_name,
		std::string nickname, std::string phone_number, std::string secret);
	void	print_contact(int i);
	int		print_info(int i);
	int		check_contact(int i);
};

#endif
