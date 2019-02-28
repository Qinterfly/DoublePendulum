#ifndef DIFFERENTIALEQUATIONS_H
#define DIFFERENTIALEQUATIONS_H

#include "core/Macroses.h"

// Дифференциальные уравнения (функтор)
struct DifferentialEquations {
    friend struct SolutionOptions;
    DifferentialEquations();
    // Вычисление правой части ДУ
    void operator()(state_type const& y, state_type & dydt, double const t) const;
    std::vector<double> calcCartesianCoordinates(state_type const& y) const; // Пересчет углов в декартовы координаты
    // Get методы
    std::vector<double> const& mass() const;
    std::vector<double> const& length() const;
    double const& gravity() const;
    int const& pointNumber() const;
private: 
    int const POINT_MASS_NUMBER = 2; // Число точечных масс
    std::vector<double> mass_;                // Массы
    std::vector<double> length_;              // Длины
    double gravity_;                          // Ускорение свободного падения
};

#endif // DIFFERENTIALEQUATIONS_H
