#include "core/PushBackSolution.h"

// Получение ссылок на контейнеры
PushBackSolution::PushBackSolution(std::vector<state_type> & solu , std::vector<double> & time)
    : solu_(solu) , time_(time) {};

// Заполнение контейнеров
void PushBackSolution::operator()(const state_type & y, double t) {
    solu_.push_back(y); // Вектор-решение
    time_.push_back(t); // Временной вектор
}
