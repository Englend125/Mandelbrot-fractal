//
// Created by Artem  on 10.09.2024.
//

#include "cint.h"

#include <cmath>

cint::cint(double a_) {
    a = a_;
    b = 0;
}

cint::cint(double a_, double b_) {
    a = a_;
    b = b_;
}

void cint::operator=(const cint& a_) {
    a = a_.a;
    b = a_.b;
}

void cint::operator=(const double &other) {
    a = other;
    b = 0;
}

void cint::operator+=(const cint& a_) {
    *this = *this + a_;
}

void cint::operator+=(const double &other) {
    *this = *this + other;
}

cint cint::operator+(const cint &other) {
    cint result;
    result.a = a + other.a;
    result.b = b + other.b;
    return result;
}

cint cint::operator+(const double &other) {
    cint result;
    result.a = a + other;
    result.b = b;
    return result;
}

cint cint::operator*(const cint &other) {
    cint result;
    result.a = a*other.a - b*other.b;
    result.b = a*other.b + b*other.a;
    return result;
}

cint cint::operator*(const double &other) {
    cint result;
    result.a = a*other;
    result.b = b*other;
    return result;
}

double cint::abs() {
    return sqrt(a*a + b*b);
}

cint st(cint a, int x) {
    if (x == 0) return 1;
    if (x % 2) return a * st(a, x - 1);
    return st(a * a, x / 2);
}

cint cint::step(int x) {
    return st(*this, x);
}

bool cint::operator==(cint other) {
    return a == other.a && b == other.b;
}

double cint::get_a() {
    return a;
}

double cint::get_b() {
    return b;
}

void cint::set_a(double a_) {
    a = a_;
}

void cint::set_b(double b_) {
    b = b_;
}
