#include <iostream>
class Complex
{
private:
    double real;
    double imaginary;

public:
    Complex(double r, double i) : real(r), imaginary(i) {}

    Complex operator+(const Complex& other) const
    {
        return Complex(real + other.real, imaginary + other.imaginary);
    }

    double Getreal() const { return real; }
    double Getimaginary() const { return imaginary; }

    bool operator==(const Complex& other) const
    {
        return real == other.real && imaginary == other.imaginary;
    }
};

std::ostream& operator<<(std::ostream& os, const Complex& c)
{
    os << "(" << c.Getreal() << ", " << c.Getimaginary() << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Complex& c)
{
    char discard;
    double real, imaginary;
    if (is >> discard >> real >> discard >> imaginary >> discard)
    {
        c = Complex(real, imaginary);
    }
    return is;
}
