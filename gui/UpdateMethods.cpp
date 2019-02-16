#include "MainWindow.h"
#include "ui_MainWindow.h"

// Обновление начального положения маятника
void MainWindow::updateInitPendulum(){
    // Отрисовка только при начале нового расчета
    if (ui->pushButtonCalculate->isEnabled()){
        setPlotPendulumRange(1.5); // Границы отображения
        plotPendulum({solOpt_.initCond()}, 0);
    }
}
