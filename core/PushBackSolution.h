#ifndef PUSHBACKSOLUTION_H
#define PUSHBACKSOLUTION_H

#include <QVector>
#include "core/Macroses.h"

// Заполнение контейнеров решения
struct PushBackSolution {
    PushBackSolution(std::vector<state_type> & solu , std::vector<double> & time); // Получение ссылок на контейнеры
    void operator()(state_type const& y, double t); // Заполнение контейнеров
private:
    std::vector<state_type> & solu_; // Вектор-решение для каждого из моментов времени (y_1, y_2, ..., y_{n-1})
    std::vector<double> & time_; // Вектор времени
};

#endif // PUSHBACKSOLUTION_H
