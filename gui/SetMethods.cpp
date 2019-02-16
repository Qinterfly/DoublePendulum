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
void MainWindow::setMaxTraceLength(){
    maxTraceLength_ = ui->spinBoxMaxTraceLength->value();
}

// Интервал срабатывания таймера
void MainWindow::setTimerInterval(){ playBackTimer_->setInterval(scrollBarTimerInterval_->value()); }

// Установка границ отображения маятника
void MainWindow::setPlotPendulumRange(double zoomShift = 1){
    ui->plotPendulum->rescaleAxes(true);
    double tLenSum = solOpt_.diffEqu().length()[0] + solOpt_.diffEqu().length()[1]; // Суммарная длина
    ui->plotPendulum->xAxis->setRange(-tLenSum, tLenSum); // Пределы по оси X
    ui->plotPendulum->yAxis->setRange(-tLenSum, tLenSum); // Пределы по оси Y
    ui->plotPendulum->xAxis->scaleRange(zoomShift, ui->plotPendulum->xAxis->range().center()); // Отдалить по оси X
    ui->plotPendulum->yAxis->scaleRange(zoomShift, ui->plotPendulum->yAxis->range().center()); // Отдалить по оси Y
}

// Установка границ отображения фазового потрета
void MainWindow::setPlotPhasePortraitRange(double zoomShift = 1){
    ui->plotPhasePortrait->rescaleAxes(true);
    // Нахождение пределов построения
        // По X
    double minX = qMin(solutionMinMax_.first[0], solutionMinMax_.first[1]);
    double maxX = qMax(solutionMinMax_.second[0], solutionMinMax_.second[1]);
        // По Y
    double minY = qMin(solutionMinMax_.first[2], solutionMinMax_.first[3]);
    double maxY = qMax(solutionMinMax_.second[2], solutionMinMax_.second[3]);
    // Выставление пределов по осям
    ui->plotPhasePortrait->xAxis->setRange(minX, maxX); // X
    ui->plotPhasePortrait->yAxis->setRange(minY, maxY); // Y
    ui->plotPhasePortrait->xAxis->scaleRange(zoomShift, ui->plotPhasePortrait->xAxis->range().center()); // Отдалить по оси X
    ui->plotPhasePortrait->yAxis->scaleRange(zoomShift, ui->plotPhasePortrait->yAxis->range().center()); // Отдалить по оси Y
    ui->plotPhasePortrait->replot();
}
