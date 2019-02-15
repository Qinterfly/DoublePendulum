#include "test/Tests.h"
#include "core/SolutionOptions.h"
#include "core/PushBackSolution.h"

void testSolution(){
    // Контейнеры под решение
    std::vector<state_type> solu; // Вектор решения для каждого из моментов времени (y_1, y_2, ..., y_{n-1})
    std::vector<double> time; // Вектор времени
    SolutionOptions solOpt;
    // Физические константы
    solOpt.setMass({1.0, 1.0}); // Массы
    solOpt.setLength({1.0, 1.0}); // Длины
    solOpt.setGravity(9.807); // Ускорение свободного падения
    // Задание уравнение и определение граничных условий
    solOpt.setInitCond({0, 0, 1.0, 0}); // Начальные условия
    solOpt.setTimeBound({0.0, 1.0}); // Границы по времени для решения
    solOpt.setTimeStep(1e-2); // Временной шаг
    state_type Y = solOpt.initCond();
    size_t nTime = integrate_const(solOpt.stepper(), solOpt.diffEqu(), Y, solOpt.timeBound()[0], solOpt.timeBound()[1], solOpt.timeStep(), PushBackSolution(solu, time)); // Решение ДУ
    ++nTime; // Включая начальный момент времени
    qDebug();
}
