#ifndef SOLUTIONOPTIONS_H
#define SOLUTIONOPTIONS_H

#include "core/DifferentialEquations.h"

struct SolutionOptions {
    SolutionOptions();
    // Get методы
    DifferentialEquations const& diffEqu() const;
    state_type initCond() const;
    std::vector<double> const& timeBound() const;
    double const& timeStep() const;
    runge_kutta4<state_type> const& stepper() const;
    // Set методы
    //   Физические параметры
    void setMass(std::vector<double> const& mass); // Массы
    void setLength(std::vector<double> const& length); // Длины
    void setGravity(double const& gravity); // Гравитация
    //   Параметры решения
    void setInitCond(std::vector<double> const& initCond); // Начальное условие
    void setTimeBound(std::vector<double> const& timeBound); // Интервал интегрирования
    void setTimeStep(double const& timeStep); // Шаг по времени
private:
    unsigned int const EQU_NUMBER = 4;       // Число уравнений
    DifferentialEquations diffEqu_;          // Параметры ДУ
    state_type initCond_;                    // Начальные условия
    std::vector<double> timeBound_;          // Границы по времени для решения
    double timeStep_;                        // Временной шаг
    runge_kutta4<state_type> const stepper_; // Тип решателя
};

#endif // SOLUTIONOPTIONS_H
