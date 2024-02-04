#include <math.h>
#include "complex.h"

double Complex::magnitude() const {

    return sqrt(re*re + im*im);

}

double Complex::real() const{
    return re;
}

double Complex::imaginary() const{
    return im;
}

Complex Complex::conjugate() {
    return Complex(re, -im);
}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

bool operator==(const Complex& a, const Complex& b) {
    return a.real() == b.real() && a.imaginary() == b.imaginary();
}

Complex operator*(const Complex& a, const Complex& b) {
    return Complex(a.real() * b.real() - a.imaginary() * b.imaginary(), a.real() * b.imaginary() + a.imaginary() * b.real());
}

Complex operator+(const Complex& a, const Complex& b) {
    return Complex(a.real() + b.real(), a.imaginary() + b.imaginary());
}