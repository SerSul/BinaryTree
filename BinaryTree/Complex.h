#pragma once
#include <iostream>

class Complex {
private:
    double real;
    double img;
public:
    //constructors
    Complex(const Complex& other): real(other.real), img(other.img) {}
    Complex(): real(0), img(0) {}
    Complex(double n_real, double n_img): real(n_real), img(n_img) {}
   
    //operators
    bool operator==(const Complex& other)const{
        if (this == &other) return true;
        return ((this->real == other.real) && (this->img == other.img));
    }

    bool operator!=(const Complex& other)const{
        return !(this == &other);
    }

    Complex operator+(const Complex& other) const {
        Complex result(*this);
        result.real += other.real;
        result.img += other.img;
        return result;
    }

    Complex operator-() const {
        Complex result;
        result.real = -(this->real);
        result.img = -(this->img);
        return result;
    }

    Complex operator-(const Complex& other) const {
        Complex result;
        result.real = this->real - other.real;
        result.img =  this->img - other.real;
        return result;
    }

    Complex operator*(const Complex& other) const  {
        Complex result;
        result.real = (this->real * other.real) - (this->img * other.img);
        result.img = (this->real * other.img) + (this->img * other.real);
        return result;
    }

    Complex operator/(const Complex& other) const  {
        Complex result;
        result.real = (this->real * other.real + this->img * other.img) / (other.real * other.real + other.img * other.img);
        result.img = (this->img * other.real - this->real * other.img) / (other.real * other.real + other.img * other.img);
        return result;
    }

    friend std::ostream& operator<< (std::ostream& out, const Complex& other) {
        out << other.real << " + " << other.img << "i;";
        return out;
    }

    friend std::istream& operator>> (std::istream& in, Complex& other) {
        std::cout << "\nre = ";
        in >> other.real;
        std::cout << "im = ";
        in >> other.img;
        return in;
    }
};
