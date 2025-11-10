#include <iostream>
using namespace std;

class Complex {
private:
    float real;
    float imag;

public:
    // a) Default Constructor (creates 0 + 0i)
    Complex() {
        real = 0;
        imag = 0;
    }

    // Parameterized Constructor
    Complex(float r, float i) {
        real = r;
        imag = i;
    }

    // b) Overload '+' operator to add two complex numbers
    Complex operator+(const Complex &c) {
        Complex temp;
        temp.real = real + c.real;
        temp.imag = imag + c.imag;
        return temp;
    }

    // c) Overload '*' operator to multiply two complex numbers
    Complex operator*(const Complex &c) {
        Complex temp;
        temp.real = (real * c.real) - (imag * c.imag);
        temp.imag = (real * c.imag) + (imag * c.real);
        return temp;
    }

    // d) Overload '>>' operator to input complex number
    friend istream &operator>>(istream &in, Complex &c) {
        cout << "Enter real part: ";
        in >> c.real;
        cout << "Enter imaginary part: ";
        in >> c.imag;
        return in;
    }

    // d) Overload '<<' operator to output complex number
    friend ostream &operator<<(ostream &out, const Complex &c) {
        if (c.imag >= 0)
            out << c.real << " + " << c.imag << "i";
        else
            out << c.real << " - " << -c.imag << "i";
        return out;
    }
};

int main() {
    Complex c1, c2, sum, product;

    cout << "Enter first complex number:" << endl;
    cin >> c1;

    cout << "Enter second complex number:" << endl;
    cin >> c2;

    sum = c1 + c2;
    product = c1 * c2;

    cout << "\nFirst Complex Number: " << c1 << endl;
    cout << "Second Complex Number: " << c2 << endl;
    cout << "\nSum: " << sum << endl;
    cout << "Product: " << product << endl;

    return 0;
}
