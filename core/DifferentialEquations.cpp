#include "core/DifferentialEquations.h"

// Конструктор по умолчанию
DifferentialEquations::DifferentialEquations() : mass_(POINT_MASS_NUMBER), length_(POINT_MASS_NUMBER), gravity_(0) {}

// Уравнения
void DifferentialEquations::operator()(state_type const& y, state_type & dydt, double const t) const {
    // Нахождение коэффициентов
    // При alpha_1
    QVector<double> A(5);
    A[0] = -1 / ( 2 * length_[0] * (mass_[0] + mass_[1] * qPow(qSin(y[0] - y[1]), 2)) );
    A[1] = -mass_[1] * length_[0] * qSin(2 * (y[0] - y[1])) * qPow(y[2], 2);
    A[2] = 2 * mass_[1] * length_[1] * qSin(y[0] - y[1]) * qPow(y[3], 2);
    A[3] = (2 * gravity_ * mass_[0] + gravity_ * mass_[1]) * qSin(y[0]);
    A[4] = gravity_ * mass_[1] * qSin(y[0] - 2 * y[1]);
    // При alpha_2
    QVector<double> B(5);
    B[0] = 1 / ( 2 * length_[1] * (mass_[0] + mass_[1] * qPow(qSin(y[0] - y[1]), 2)) );
    B[1] = gravity_ * (mass_[0] + mass_[1]) * qSin(2 * y[0] - y[1]);
    B[2] = -gravity_ * (mass_[0] + mass_[1]) * qSin(y[1]);
    B[3] = 2 * length_[0] * (mass_[0] + mass_[1]) * qPow(y[2], 2) * qSin(y[0] - y[1]);
    B[4] = length_[1] * mass_[1] * qPow(y[3], 2) * qSin(2 * (y[0] - y[1]));
    // Вычисление правой части
    dydt[0] = y[2];
    dydt[1] = y[3];
    dydt[2] = A[0] * (A[1] + A[2] + A[3] + A[4]);
    dydt[3] = B[0] * (B[1] + B[2] + B[3] + B[4]);
}

// Пересчет углов в декартовы координаты
std::vector<double> DifferentialEquations::calcCartesianCoordinates(state_type const& y) const {
    std::vector<double> cartCoord(y.size());
    // Для первой точечной массы
    cartCoord[0] = length_[0] * qSin(y[0]); // X_1
    cartCoord[1] = -length_[0] * qCos(y[0]); // Y_1
    // Для второй точечной массы
    cartCoord[2] = cartCoord[0] + length_[1] * qSin(y[1]); // X_2
    cartCoord[3] = cartCoord[1] - length_[1] * qCos(y[1]); // Y_2
    return cartCoord;
}

// Get методы
std::vector<double> const& DifferentialEquations::mass() const { return mass_; }
std::vector<double> const& DifferentialEquations::length() const { return length_; }
double const& DifferentialEquations::gravity() const { return gravity_; }
