#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <list>
#include "include/QCustomPlot.h"
#include "core/SolutionOptions.h"
#include "core/PushBackSolution.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void calculate(); // Запуск общей процедуры расчета
    void pauseOrContinue(); // Пауза или возобновление
    void stop(); // Остановка
    void playBackStep(); // Функция отрисовки по таймеру
    void updateInitPendulum(); // Обновление начального положения маятника
    // Set методы
    void setMass();          // Массы
    void setLength();        // Длины
    void setGravity();       // Гравитация
    void setInitCond();      // Начальное условие
    void setTimeBound();     // Интервал интегрирования
    void setTimeStep();      // Шаг по времени
    void setMaxTraceLength();   // Длина временного следа
    void setTimerInterval(); // Интервал срабатывания таймера
private:
    void initializeSolutionOptions(); // Инициализация параметров решения
    void initializeShowParams(); // Инициализация параметров построения
    void initializeAllPlot(); // Инициализация всех графических окон
    void initializePlotPendulum(); // Инициализация окна с маятником
    void initializePhasePortrait(); // Инициализация окна с фазовым портретом
    void solve(); // Решить ДУ с заданными условиями
    void plotPendulum(std::vector<state_type> const& solution, size_t plotInd); // Построение положения маятника
    void plotPhasePortrait(size_t plotInd); // Построение фазового портрета
    void setPlotPendulumRange(double zoomShift); // Установка границ отображения маятника
    void setPlotPhasePortraitRange(double zoomShift); // Установка границ отображения фазового потрета
    void clearPendulum(); // Очистка положения маятника
    void clearPhasePortrait(); // Очистка фазового портрета
    // Вспомогательные
    void addTraceData(QCPCurve* curve, double const& x, double const& y); // Добавление данных к временному следу
    void findSolutionMinMax(); // Нахождение максимумов и минимумов решения
private:
    Ui::MainWindow *ui;
    SolutionOptions solOpt_; // Опции решения
    std::vector<state_type> solution_; // Вектор-решение для каждого из моментов времени (y_1, y_2, ..., y_{n-1})
    std::vector<double> time_; // Вектор времени
    size_t nTime_; // Число шагов по времени, включая начальный момент
    // Анимация
    QTimer* playBackTimer_; // Таймер
    QScrollBar* scrollBarTimerInterval_; // Интервал срабатывания таймера
    QLabel* labelTimeInterval_; // Метка интервала срабатывания
    bool isPaused_ = false; // Флаг паузы
    size_t timeInd_ = 0; // Индекс решения
    int maxTraceLength_; // Максимальная длина временного следа
    QVector<QCPCurve *> tracePendulum_; // Временные следы маятника
    QVector<QCPCurve *> tracePhasePortrait_; // Временные следы на фазовом портрете
    std::pair<state_type, state_type> solutionMinMax_; // Минимумы и максимумы решения
};

#endif // MAINWINDOW_H
