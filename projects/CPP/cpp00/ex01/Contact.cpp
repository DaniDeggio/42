/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 18:30:42 by dde-giov          #+#    #+#             */
/*   Updated: 2024/06/12 05:17:39 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "Contact.hpp"

Contact::Contact(void){
    return ;
}

Contact::~Contact(void){
    return ;
}

void	Contact::set_contact(std::string frist_name, std::string last_name,
		std::string nickname, std::string phone_number, std::string secret){
    this->frist_name = frist_name;
    this->last_name = last_name;
    this->nickname = nickname;
    this->phone_number = phone_number;
    this->darkest_secret = secret;
}

std::string  Contact::get_frist_name(){
    return  (this->frist_name);
}

std::string  Contact::get_last_name(){
    return  (this->last_name);
}

std::string  Contact::get_nickname(){
    return  (this->nickname);
}

std::string  Contact::get_phone_number(){
    return  (this->phone_number);
}

std::string  Contact::get_darkest_secret(){
    return  (this->darkest_secret);
}
