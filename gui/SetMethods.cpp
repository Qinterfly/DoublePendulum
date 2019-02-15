#include "MainWindow.h"
#include "ui_MainWindow.h"

// Массы
void MainWindow::setMass(){
    solOpt_.setMass({ui->doubleSpinBoxMass1->value(), ui->doubleSpinBoxMass2->value()});
    if (!ui->pushButtonCalculate->isEnabled()) stop(); // Остановка расчета
}
// Длины
void MainWindow::setLength(){
    solOpt_.setLength({ui->doubleSpinBoxLength1->value(), ui->doubleSpinBoxLength2->value()});
    if (!ui->pushButtonCalculate->isEnabled()) stop(); // Остановка расчета
}
// Гравитация
void MainWindow::setGravity(){
    solOpt_.setGravity(ui->doubleSpinBoxGravity->value());
    if (!ui->pushButtonCalculate->isEnabled()) stop(); // Остановка расчета
}
// Начальное условие
void MainWindow::setInitCond(){
    solOpt_.setInitCond({ui->doubleSpinBoxInitAngle1->value(), ui->doubleSpinBoxInitAngle2->value(), // Углы
                        ui->doubleSpinBoxInitVelocity1->value(), ui->doubleSpinBoxInitVelocity2->value()}); // Скорости
    if (!ui->pushButtonCalculate->isEnabled()) stop(); // Остановка расчета
}
// Интервал интегрирования
void MainWindow::setTimeBound(){
    solOpt_.setTimeBound({ui->doubleSpinBoxInitTime->value(), ui->doubleSpinBoxEndTime->value()});
    if (!ui->pushButtonCalculate->isEnabled()) stop(); // Остановка расчета
}
// Шаг по времен
void MainWindow::setTimeStep(){
    solOpt_.setTimeStep(ui->doubleSpinBoxTimeStep->value());
    if (!ui->pushButtonCalculate->isEnabled()) stop(); // Остановка расчета
}

// Длина временного следа
void MainWindow::setTraceLength(){
    traceLength_ = size_t(ui->spinBoxTraceLength->value());
    if (!ui->pushButtonCalculate->isEnabled()) stop(); // Остановка расчета
}

// Интервал срабатывания таймера
void MainWindow::setTimerInterval(){ playBackTimer_->setInterval(scrollBarTimerInterval_->value()); }
