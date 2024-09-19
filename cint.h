#pragma once


class cint {
public:

    cint() = default;
    cint(double a_, double b_);
    cint(double a_);
    void operator=(const cint &other);
    void operator=(const double &other);
    void operator+=(const cint &other);
    void operator+=(const double &other);

    cint operator+(const cint &other);
    cint operator+(const double &other);

    cint operator*(const cint &other);
    cint operator*(const double &other);

    bool operator==(cint other);

    cint step(int x);

    double abs();

    void set_a(double a_);
    void set_b(double b_);
    double get_a();
    double get_b();

private:
    double a = 0;
    double b = 0;
};

