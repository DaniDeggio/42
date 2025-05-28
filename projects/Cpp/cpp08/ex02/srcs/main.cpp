/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 23:38:13 by dde-giov          #+#    #+#             */
/*   Updated: 2025/04/01 07:14:12 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include "../include/Array.hpp"

#define MAX_VAL 750
int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
		std::cout << "trying negative index" << std::endl;
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
		std::cout << "trying out of range index" << std::endl;
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;//

	
	// Test: deep copy
	std::cout << std::endl << "Testing deep copy" << std::endl;
	{
		Array<int> tmp = numbers;
		Array<int> test(tmp);

		numbers[0] = 999999;
		if (tmp[0] == numbers[0])
			std::cerr << "Deep copy failed!" << std::endl;
		tmp[0] = numbers[0];
		if (test[0] == numbers[0])
			std::cerr << "Deep copy failed!" << std::endl;
	}

	// Test: Array string
	std::cout << std::endl << "Testing Array<std::string>" << std::endl;
	Array<std::string> strArr(3);
	strArr[0] = "42";
	strArr[1] = "Roma";
	strArr[2] = "dde-giov";
	for (unsigned int i = 0; i < strArr.size(); ++i)
		std::cout << "strArr[" << i << "] = " << strArr[i] << std::endl;

	// Test: empty array
	std::cout << std::endl << "Testing empty array" << std::endl;
	Array<float> emptyArr;
	std::cout << "emptyArr.size() = " << emptyArr.size() << std::endl;
	try {
		emptyArr[0] = 3.14f;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
