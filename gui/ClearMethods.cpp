#include "MainWindow.h"
#include "ui_MainWindow.h"

// Очистка маятника
void MainWindow::clearPendulum(){
    ui->plotPendulum->graph(0)->data()->clear(); // Первый стержень
    ui->plotPendulum->graph(1)->data()->clear(); // Второй стержень
    ui->plotPendulum->graph(2)->data()->clear(); // Первая точечная масса
    ui->plotPendulum->graph(3)->data()->clear(); // Вторая точечная масса
    tracePendulum_[0]->data()->clear(); // След первой массы
    tracePendulum_[1]->data()->clear(); // След второй массы
    ui->plotPendulum->rescaleAxes(false); // Масштабирование осей
    ui->plotPendulum->replot(); // Обновление окна построения
}

// Очистка фазового портрета
void MainWindow::clearPhasePortrait(){
    tracePhasePortrait_[0]->data()->clear(); // Первая точечная масса
    tracePhasePortrait_[1]->data()->clear(); // Вторая точечная масса
    ui->plotPhasePortrait->rescaleAxes(false); // Масштабирование осей
    ui->plotPhasePortrait->replot(); // Обновление окна построения
}

// Очистка фазовых углов
void MainWindow::clearPhaseAngles(){
    tracePhaseAngles_->data()->clear();
    ui->plotPhaseAngles->rescaleAxes(false); // Масштабирование осей
    ui->plotPhaseAngles->replot(); // Обновление окна построения
}
