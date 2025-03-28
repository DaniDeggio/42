/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 22:37:49 by dde-giov          #+#    #+#             */
/*   Updated: 2025/03/28 00:44:22 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <iostream>

template <typename T>
class Array {
	private:
		T *_array;
		unsigned int _size;

	public:
		Array(){
			_array = new T[0];
			_size = 0;
		}

		Array(unsigned int n){
			_array = new T[n];
			_size = n;
		}

		Array(const Array &src){
			_array = new T[src._size];
			_size = src._size;
			for (unsigned int i = 0; i < _size; i++)
				_array[i] = src._array[i];
		}

		~Array(){
			delete[] _array;
		}

		Array &operator=(const Array &src){
			if (this == &src)
				return *this;
			delete[] _array;
			_array = new T[src._size];
			_size = src._size;
			for (unsigned int i = 0; i < _size; i++)
				_array[i] = src._array[i];
			return *this;
		}

		T &operator[](unsigned int n){
			if (n >= _size)
				throw std::exception();
			return _array[n];
		}

		unsigned int size() const{
			return _size;
	}
};

#endif