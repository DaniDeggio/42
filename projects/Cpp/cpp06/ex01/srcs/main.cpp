/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:54:02 by dde-giov          #+#    #+#             */
/*   Updated: 2025/03/27 04:34:39 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../class/Serializer.hpp"
#include "../class/Data.hpp"

int main() {
    Data myData;
    myData.n = 42;
    myData.s1 = "Roma Luiss";
	myData.s2 = "dde-giov";

    std::cout << "Original Data pointer: " << &myData << std::endl;
    std::cout << "n = " << myData.n << ", s1 = " << myData.s1 << ", s2 = " << myData.s2 << std::endl << std::endl;

    uintptr_t raw = Serializer::serialize(&myData);
    std::cout << "Serialized uintptr_t: " << raw << std::endl << std::endl;

    Data* ptr = Serializer::deserialize(raw);
    std::cout << "Deserialized Data pointer: " << ptr << std::endl;

    std::cout << "n = " << ptr->n << ", s1 = " << ptr->s1 << ", s2 = " << ptr->s2 << std::endl << std::endl;

    if (ptr == &myData)
        std::cout << "Same pointer!" << std::endl;
	else
		std::cout << "Different pointer!" << std::endl;
    return 0;
}
