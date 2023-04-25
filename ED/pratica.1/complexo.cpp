#include <iostream>
#include <math.h>

using namespace std;

class complexo {
  private:
    double real, imag;
  public:
    complexo();
    complexo(double real, double imag);

    complexo conjugado();
    complexo operator=(complexo c);

    void operator-();
    void operator+(complexo c);
    void operator-(complexo c);
    void operator*(complexo c);
    void operator/(complexo c);

    double modulo();
    double getReal();
    double getImag();
};

complexo::complexo() {
  this->real = 0;
  this->imag = 0;
}

complexo::complexo(double _real, double _imag) {
  this->real = _real;
  this->imag = _imag;
}

complexo complexo::conjugado() {
  this->imag *= -1;
  return complexo(real, imag);
}

void complexo::operator-() {
  this->real *= -1;
  this->imag *= -1;
}

void complexo::operator+(complexo c){
  this->real += c.real;
  this->imag += c.imag;
}

void complexo::operator-(complexo c){
  this->real -= c.real;
  this->imag -= c.imag;
}

void complexo::operator*(complexo c){
  double aux;

  aux = (this->real * c.real) - (this->imag * c.imag);
  this->imag = (this->real * c.imag) + (this->imag * c.real);
  this->real = aux;
}

void complexo::operator/(complexo c){
  double a, b;

  this->operator*(c.conjugado());
}

double complexo::modulo(){
  double m = pow(this->real, 2) + pow(this->imag, 2) ;
  return sqrt(m);
}

double complexo::getReal() {
  return this->real;
}

double complexo::getImag() {
  return this->imag;
}

int main() {
  complexo r(5, 10);
  complexo c(4, 3);

  // r.operator*(c);
  r.operator/(c);
  cout << r.getReal() << " " << r.getImag() << "i" << endl;

  return 0;
}
