/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:26:53 by dde-giov          #+#    #+#             */
/*   Updated: 2024/10/01 11:58:57 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CONTACT_HPP
# define	CONTACT_HPP

#include <string>

class Contact {
private:
	std::string	frist_name;
	std::string	last_name;
	std::string	nickname;
	std::string	phone_number;
	std::string	darkest_secret;
public:
	Contact();
	~Contact();
	
	void	set_contact(std::string frist_name, std::string last_name,
		std::string nickname, std::string phone_number, std::string secret);

	std::string	get_frist_name();
	std::string	get_last_name();
	std::string	get_nickname();
	std::string	get_phone_number();
	std::string	get_darkest_secret();
};

#endif


