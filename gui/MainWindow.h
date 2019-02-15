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
    void setMass();      // Массы
    void setLength();    // Длины
    void setGravity();   // Гравитация
    void setInitCond();  // Начальное условие
    void setTimeBound(); // Интервал интегрирования
    void setTimeStep();  // Шаг по времени
private:
    void initializeSolutionOptions(); // Инициализация параметров решения
    void initializeAllPlot(); // Инициализация всех графических окон
    void solve(); // Решить ДУ с заданными условиями
    void plotPendulum(std::vector<state_type> const& solution, size_t plotInd); // Построение положения маятника
    void clearPendulum(); // Очистка положения маятника
    // Вспомогательные
    QVector<double> sliceTrace(size_t indPoint, size_t indCoord); // Срез следа по индексам
private:
    Ui::MainWindow *ui;
    SolutionOptions solOpt_; // Опции решения
    std::vector<state_type> solution_; // Вектор-решение для каждого из моментов времени (y_1, y_2, ..., y_{n-1})
    std::vector<double> time_; // Вектор времени
    size_t nTime_; // Число шагов по времени, включая начальный момент
    // Анимация
    QTimer* playBackTimer; // Таймер
    bool isPaused_ = false; // Флаг паузы
    size_t timeInd_ = 0; // Индекс решения
    const int TRACE_LENGTH = 150; // Длина следа
    TraceContainer listTrace_; // Контейнер следов точек
};

#endif // MAINWINDOW_H
