#include "Fixed.hpp"

Fixed::Fixed(void): fx_value(0) {
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &fx) {
    std::cout << "Copy constructor called" << std::endl;
    *this = fx;
}

Fixed::Fixed(const int value): fx_value(value << this->fract) {
    std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float value): fx_value(roundf(value * (1 << this->fract))) {
    std::cout << "Float constructor called" << std::endl;
}

Fixed &Fixed::operator=(const Fixed &fx) {
    std::cout << "Assignation operator called" << std::endl;
    if (this != &fx) {
        this->fx_value = fx.fx_value;
    }
    return *this;
}

Fixed::~Fixed(void) {
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const {
    std::cout << "getRawBits member function called" << std::endl;
    return this->fx_value;
}

void Fixed::setRawBits(int const raw) {
    std::cout << "setRawBits member function called" << std::endl;
    this->fx_value = raw;
}

float Fixed::toFloat(void) const {
    return static_cast<float>(this->fx_value) / (1 << this->fract);
}

int Fixed::toInt(void) const {
    return this->fx_value >> this->fract;
}

Fixed Fixed::min(Fixed &n1, Fixed &n2) {
    return (n1 > n2) ? n2 : n1;
}

const Fixed Fixed::min(const Fixed &n1, const Fixed &n2) {
    return (n1 > n2) ? n2 : n1;
}

Fixed Fixed::max(Fixed &n1, Fixed &n2) {
    return (n1 > n2) ? n1 : n2;
}

const Fixed Fixed::max(const Fixed &n1, const Fixed &n2) {
    return (n1 > n2) ? n1 : n2;
}

bool Fixed::operator>(const Fixed &fx) const {
    return (this->fx_value > fx.fx_value);
}

bool Fixed::operator<(const Fixed &fx) const {
    return (this->fx_value < fx.fx_value);
}

bool Fixed::operator>=(const Fixed &fx) const {
    return (this->fx_value >= fx.fx_value);
}

bool Fixed::operator<=(const Fixed &fx) const {
    return (this->fx_value <= fx.fx_value);
}

bool Fixed::operator==(const Fixed &fx) const {
    return (this->fx_value == fx.fx_value);
}

bool Fixed::operator!=(const Fixed &fx) const {
    return (this->fx_value != fx.fx_value);
}

Fixed Fixed::operator+(const Fixed &fx) {
    return Fixed(this->toFloat() + fx.toFloat());
}

Fixed Fixed::operator-(const Fixed &fx) {
    return Fixed(this->toFloat() - fx.toFloat());
}

Fixed Fixed::operator*(const Fixed &fx) {
    return Fixed(this->toFloat() * fx.toFloat());
}

Fixed Fixed::operator/(const Fixed &fx) {
    if (fx.toFloat() == 0) {
        std::cerr << "Error: Division by zero" << std::endl;
        return Fixed(0); // Return zero or handle as you see fit.
    } else {
        return Fixed(this->toFloat() / fx.toFloat());
    }
}

Fixed &Fixed::operator++() {
    this->fx_value++;
    return *this;
}

Fixed &Fixed::operator--() {
    this->fx_value--;
    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed temp = *this;
    this->fx_value++;
    return temp;
}

Fixed Fixed::operator--(int) {
    Fixed temp = *this;
    this->fx_value--;
    return temp;
}

std::ostream &operator<<(std::ostream &out, const Fixed &fx) {
    out << fx.toFloat();
    return out;
}
