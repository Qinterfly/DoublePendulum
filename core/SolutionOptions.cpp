#include "core/SolutionOptions.h"

// Конструктор по умолчанию
SolutionOptions::SolutionOptions() : diffEqu_(), initCond_(EQU_NUMBER), timeBound_(2), timeStep_(), stepper_() {}

// Get методы
DifferentialEquations const& SolutionOptions::diffEqu() const { return diffEqu_; }
state_type SolutionOptions::initCond() const { return initCond_; }
std::vector<double> const& SolutionOptions::timeBound() const { return timeBound_; }
double const& SolutionOptions::timeStep() const { return timeStep_; }
runge_kutta4<state_type> const& SolutionOptions::stepper() const { return stepper_; }

// Set методы
// Физические параметры
void SolutionOptions::setMass(std::vector<double> const& mass) { diffEqu_.mass_ = mass; }           // Массы
void SolutionOptions::setLength(std::vector<double> const& length){ diffEqu_.length_ = length; }    // Длины
void SolutionOptions::setGravity(double const& gravity){ diffEqu_.gravity_ = gravity; }             // Гравитация
// Параметры решения
void SolutionOptions::setInitCond(std::vector<double> const& initCond){ initCond_ = initCond; }     // Начальное условие
void SolutionOptions::setTimeBound(std::vector<double> const& timeBound){ timeBound_ = timeBound; } // Интервал интегрирования
void SolutionOptions::setTimeStep(double const& timeStep){ timeStep_ = timeStep; }                  // Шаг по времени
