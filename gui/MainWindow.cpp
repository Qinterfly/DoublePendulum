#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeSolutionOptions(); // Инициализация параметров решения
    initializeShowParams(); // Инициализация параметров построения
    initializeAllPlot(); // Инициализация всех графических окон

    // Сигналы - слоты
    // Физические параметры
        // Массы
    connect(ui->doubleSpinBoxMass1, SIGNAL(editingFinished()), this, SLOT(setMass()));
    connect(ui->doubleSpinBoxMass2, SIGNAL(editingFinished()), this, SLOT(setMass()));
        // Длины
    connect(ui->doubleSpinBoxLength1, SIGNAL(valueChanged(double)), this, SLOT(setLength()));
    connect(ui->doubleSpinBoxLength2, SIGNAL(valueChanged(double)), this, SLOT(setLength()));
        // Ускорение свободного падения
    connect(ui->doubleSpinBoxGravity, SIGNAL(editingFinished()), this, SLOT(setGravity()));
        // Углы
    connect(ui->doubleSpinBoxInitAngle1, SIGNAL(valueChanged(double)), this, SLOT(setInitCond()));
    connect(ui->doubleSpinBoxInitAngle2, SIGNAL(valueChanged(double)), this, SLOT(setInitCond()));
        // Скорости
    connect(ui->doubleSpinBoxInitVelocity1, SIGNAL(editingFinished()), this, SLOT(setInitCond()));
    connect(ui->doubleSpinBoxInitVelocity2, SIGNAL(editingFinished()), this, SLOT(setInitCond()));
    // Параметры решения
        // Время решения
    connect(ui->doubleSpinBoxInitTime, SIGNAL(editingFinished()), this, SLOT(setTimeBound())); // Начальное время моделирования
    connect(ui->doubleSpinBoxEndTime, SIGNAL(editingFinished()), this, SLOT(setTimeBound()));  // Конечное время моделирования
    connect(ui->doubleSpinBoxTimeStep, SIGNAL(editingFinished()), this, SLOT(setTimeStep()));  // Временной шаг
    connect(ui->spinBoxTraceLength, SIGNAL(editingFinished()), this, SLOT(setTraceLength()));  // Длина временного следа
    // Контроль
    connect(playBackTimer_, SIGNAL(timeout()), this, SLOT(playBackStep())); // Таймер
    connect(ui->pushButtonCalculate, SIGNAL(clicked()), this, SLOT(calculate())); // Запуск расчета
    connect(ui->pushButtonPauseOrContinue, SIGNAL(clicked()), this, SLOT(pauseOrContinue())); // Пауза или возобновление
    connect(ui->pushButtonStop, SIGNAL(clicked()), this, SLOT(stop())); // Остановка
    connect(scrollBarTimerInterval_, SIGNAL(valueChanged(int)), this, SLOT(setTimerInterval())); // Установка интервала таймера
    // Обновление положения маятника
        // Длины
    connect(ui->doubleSpinBoxLength1, SIGNAL(valueChanged(double)), this, SLOT(updateInitPendulum()));
    connect(ui->doubleSpinBoxLength2, SIGNAL(valueChanged(double)), this, SLOT(updateInitPendulum()));
        // Углы
    connect(ui->doubleSpinBoxInitAngle1, SIGNAL(valueChanged(double)), this, SLOT(updateInitPendulum()));
    connect(ui->doubleSpinBoxInitAngle2, SIGNAL(valueChanged(double)), this, SLOT(updateInitPendulum()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


