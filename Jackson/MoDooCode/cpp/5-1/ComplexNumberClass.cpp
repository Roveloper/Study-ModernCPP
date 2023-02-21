#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

// Complex A = Complex(1, 2) + "1+1j";
// Complex A = "1+1j" + Complex(1, 2); --> operator+(std::string, Complex) --> operator+(Complex, Complex)


// friend keyword --> class 내부 변수에 접근할 수 있는 권한을 전달하는 기능 (외부 함수 또는 클래스에게)

// a@b --> a.operator@(b) 또는 operator@(a, b)로 변환이 됨
// a.operator@(b)는 a 객체 내부에 선언된 operator@ 함수를 호출
// *operator(a, b)는 전역 함수로 선언된 operator 함수를 호출 (입력 a와 b의 타입에 따라 호출되는 함수가 정해짐 (overloading))
// [], ->, =, () 등은 멤버 함수로만 존재할 수 있음 (전역 함수로 선언할 수 없음)

// cout << a; --> cout.operator<<(a) 또는 operator<<(cout, a)로 변환

// cin >> a; --> cin.operator>>(a) 또는 operator>>(cin, a)로 변환

// friend는 꽤나 유용하게 쓰일 수 있는 경우가 많기는 하지만, 사용을 자제하는 것이 좋음 (C++의 캡슐화를 깨뜨림 (외부에 공개될 필요가 없는데, 공개되므로))
// 하지만 friend를 잘 사용하면, 테스트 코드 작성 등에서는 꽤나 유용하게 사용할 수 있음 (아예 외부 공개는 피하면서, 테스트에서는 사용할 수 있으므로)

// 다음은 [] (첨자 연산자)를 오버로딩 해보자
// a[0] --> a.operator[](0) 또는 operator[](a, 0)으로 변환됨 (당연히 전자로 사용하는 경우가 많을 것 같음, 왜냐면 스스로를 반환하는 케이스기 때문
// char& string_class::opeator[](const int index) { return string_content[index]; }


class ComplexNumber {
  friend ComplexNumber operator+(const ComplexNumber &a, const ComplexNumber &b);
  friend std::ostream& operator<<(std::ostream& os, ComplexNumber a);
  friend std::istream& operator>>(std::istream& is, ComplexNumber& a);


  public:
    ComplexNumber() = default;
    ComplexNumber(const double real, const double imag);
    ComplexNumber(const ComplexNumber &complex);
    ComplexNumber(const std::string &complex);
    ~ComplexNumber() = default;
    void set_real(const double real);
    void set_imag(const double imag);
    void set_value(const double real, const double imag);
    double get_real();
    double get_imag();
    bool operator==(const ComplexNumber &complex);
    // ComplexNumber operator+(const ComplexNumber &complex) const;
    ComplexNumber operator-(const ComplexNumber &complex) const;
    ComplexNumber &operator=(const ComplexNumber &complex);
    ComplexNumber operator*(const ComplexNumber &c) const;
    ComplexNumber operator/(const ComplexNumber &c) const;
    ComplexNumber operator+(const std::string &complex) const;
    ComplexNumber operator-(const std::string &complex) const;
    ComplexNumber operator*(const std::string &c) const;
    ComplexNumber operator/(const std::string &c) const;
    ComplexNumber &operator+=(const ComplexNumber &c);
    ComplexNumber &operator-=(const ComplexNumber &c);
    ComplexNumber &operator*=(const ComplexNumber &c);
    ComplexNumber &operator/=(const ComplexNumber &c);

    void print_number() const;

  private:
    double real_;
    double imag_;
};

ComplexNumber::ComplexNumber(const double real, const double imag) : real_(real), imag_(imag) {}

ComplexNumber::ComplexNumber(const ComplexNumber &complex) // l-value reference
    : real_(complex.real_), imag_(complex.imag_) {}

ComplexNumber::ComplexNumber(const std::string &complex)
{
    if (complex.find('j') == std::string::npos) { // 허수부가 존재하지 않을 때
        imag_ = 0.0;
        real_ = std::stod(complex);
    } else { // 허수부가 존재할 때
        int index;
        if (complex.rfind('+') == std::string::npos) {
            index = complex.rfind('-');
        } else {
            index = complex.rfind('+');
        }
        std::cout << index << std::endl;
        imag_ = std::stod(complex.substr(index, complex.length() - index));
        real_ = std::stod(complex.substr(0, index));
    }
    // std::cout << std::showpos << real << ", " << imag << std::noshowpos << std::endl;
    // return *this + ComplexNumber(real, imag);
}

void ComplexNumber::set_real(const double real) { real_ = real; }

void ComplexNumber::set_imag(const double imag) { imag_ = imag; }

void ComplexNumber::set_value(const double real, const double imag) {
    real_ = real;
    imag_ = imag;
}

double ComplexNumber::get_real() { return real_; }

double ComplexNumber::get_imag() { return imag_; }

bool ComplexNumber::operator==(const ComplexNumber &complex) {
    if (real_ == complex.real_ && imag_ == complex.imag_) {
        return true;
    } else {
        return false;
    }
}

// ComplexNumber ComplexNumber::operator+(const ComplexNumber &complex) const {
//     return ComplexNumber(real_ + complex.real_, imag_ + complex.imag_);
// }

// ComplexNumber ComplexNumber::operator+(const std::string& complex) const {
//     return *this + ComplexNumber(complex);
// }

ComplexNumber ComplexNumber::operator-(const std::string& complex) const {
    return *this - ComplexNumber(complex);
}
ComplexNumber ComplexNumber::operator*(const std::string& complex) const {
    return *this * ComplexNumber(complex);
}

ComplexNumber ComplexNumber::operator/(const std::string& complex) const {
    return *this / ComplexNumber(complex);
}
ComplexNumber ComplexNumber::operator-(const ComplexNumber &complex) const {
    return ComplexNumber(real_ - complex.real_, imag_ - complex.imag_);
}

ComplexNumber &ComplexNumber::operator=(const ComplexNumber &complex) {
    real_ = complex.real_;
    imag_ = complex.imag_;
    return *this;
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber &c) const {
    ComplexNumber temp(real_ * c.real_ - imag_ * c.imag_, real_ * c.imag_ + imag_ * c.real_);
    return temp;
}
ComplexNumber ComplexNumber::operator/(const ComplexNumber &c) const {
    ComplexNumber temp(
        (real_ * c.real_ + imag_ * c.imag_) / (c.real_ * c.real_ + c.imag_ * c.imag_),
        (imag_ * c.real_ - real_ * c.imag_) / (c.real_ * c.real_ + c.imag_ * c.imag_));
    return temp;
}

ComplexNumber &ComplexNumber::operator+=(const ComplexNumber &complex) {
    *this = *this + complex;
    return *this;
}

ComplexNumber &ComplexNumber::operator-=(const ComplexNumber &complex) {
    *this = *this - complex;
    return *this;
}

ComplexNumber &ComplexNumber::operator*=(const ComplexNumber &complex) {
    *this = *this * complex;
    return *this;
}

ComplexNumber &ComplexNumber::operator/=(const ComplexNumber &complex) {
    *this = *this / complex;
    return *this;
}

void ComplexNumber::print_number() const {
    std::cout << std::showpos << real_ << imag_ << "j" << std::noshowpos << std::endl;
}

ComplexNumber operator+(const ComplexNumber &a, const ComplexNumber &b) {
    // 이와 같은 함수를 정의하는 방법은 2가지
    // 1. friend로 선언하여, 직접적으로 멤버 변수에 접근할 수 있는 권한을 전달한다.
    // 2. Getter 함수를 통해서, 간접적으로 멤버 변수를 얻어서 연산을 수행한다.
    
    return ComplexNumber(a.real_ + b.real_, a.imag_ + b.imag_); // 1번 방법으로 수행하였으며, 이와 같이 작성하려면, friend 설정이 필수적!

    // return ComplexNumber(a.get_real() + b.get_real(), a.get_imag() + b.get_imag()); // 2번 방법으로 수행하였으며, 이와 같이 작성하려면 Getter 함수가 필수적!
}
std::ostream& operator<<(std::ostream& os, ComplexNumber a) {
    os << "real: " << a.real_ << ", imag: " << a.imag_;
    return os;
}

std::istream& operator>>(std::istream& is, ComplexNumber& a) {
    is >> a.real_ >> a.imag_;
    return is;
}


int main() {
    // ComplexNumber a = "1+1j" + ComplexNumber(1, 1);
    // a.print_number();
    ComplexNumber a;
    std::cin >> a;
    std::cout << a << std::endl;
    // ComplexNumber a(1, -1);
    // ComplexNumber b(a);
    // ComplexNumber c(1, 1);

    // // std::cout << a.get_real() << '+' << a.get_imag() << "j" << std::endl;

    // if (a == b) {
    //     std::cout << "a와 b는 같습니다" << std::endl;
    // } else {
    //     std::cout << "a와 b는 다릅니다" << std::endl;
    // }

    // if (b == c) {
    //     std::cout << "b와 c는 같습니다" << std::endl;
    // } else {
    //     std::cout << "b와 c는 다릅니다" << std::endl;
    // }

    // a.print_number();
    // ComplexNumber d = a + b;
    // a.print_number();
    // d.print_number();
    // (b + c).print_number();

    // ComplexNumber e(1.0, 2.0);
    // ComplexNumber f(3.0, -2.0);
    // ComplexNumber g(0.0, 0.0);
    // g = e * f + e / f + e + f;
    // g.print_number();

    // ComplexNumber aa(1.0, 2.0);
    // ComplexNumber bb(3.0, -2.0);
    // aa += bb;
    // aa.print_number();
    // bb.print_number();

    // std::string hello("-3+4j");

    // ComplexNumber cc(1.0, 2.0);
    // ComplexNumber dd(0.0, 0.0);
    // cc.print_number();
    // dd = cc + "4-4.3j";
    // dd.print_number();

    // std::cout << "last example " << std::endl;
    // ComplexNumber ee(0, 0);
    // ee = ee + "-1.1+3.923j";
    // ee.print_number();
    // ee = ee - "1.2-1.823j";
    // ee.print_number();
    // ee = ee * "2.3+22j";
    // ee.print_number();
    // ee = ee / "-12+55j";
    // ee.print_number();
    return 0;
}