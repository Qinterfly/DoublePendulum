#include "MainWindow.h"
#include "ui_MainWindow.h"

// Построение положения маятника
void MainWindow::plotPendulum(std::vector<state_type> const& solution, size_t plotInd){
    std::vector<double> const pointCartCoord = solOpt_.diffEqu().calcCartesianCoordinates(solution[plotInd]); // Получение декартовых координат маятника
    // Первый стержень
    QVector<double> XRod1 = {0, pointCartCoord[0]};
    QVector<double> YRod1 = {0, pointCartCoord[1]};
    ui->plotPendulum->graph(0)->setData(XRod1, YRod1); // Передача данных
    // Второй стержень
    QVector<double> XRod2 = {pointCartCoord[0], pointCartCoord[2]};
    QVector<double> YRod2 = {pointCartCoord[1], pointCartCoord[3]};   
    ui->plotPendulum->graph(1)->setData(XRod2, YRod2); // Передача данных
    // Первая точечная масса  
    ui->plotPendulum->graph(2)->setData({pointCartCoord[0]}, {pointCartCoord[1]}); // Передача данных
    // Вторая точечная масса
    ui->plotPendulum->graph(3)->setData({pointCartCoord[2]}, {pointCartCoord[3]}); // Передача данных
    // След первой точки
    addTraceData(tracePendulum_[0], pointCartCoord[0], pointCartCoord[1]);
    // След второй точки
    addTraceData(tracePendulum_[1], pointCartCoord[2], pointCartCoord[3]);
    ui->plotPendulum->replot(); // Обновление окна построения
}

// Построение фазового портрета
void MainWindow::plotPhasePortrait(size_t plotInd){
    state_type const & tSolu = solution_[plotInd];
    // След первой точки
    addTraceData(tracePhasePortrait_[0], tSolu[0], tSolu[2]);
    // След второй точки
    addTraceData(tracePhasePortrait_[1], tSolu[1], tSolu[3]);
    ui->plotPhasePortrait->replot(); // Обновление окна построения
}

// --- Вспомогательные -----------------------------------------------------------------------------------------

// Добавление данных к временному следу
void MainWindow::addTraceData(QCPCurve * curve, double const& x, double const& y){
    if (ui->pushButtonCalculate->isEnabled()) return; // Проверка режима отрисовки
    // Срез данных по длине следа (pop_front)
    while (curve->data()->size() >= maxTraceLength_)
        curve->data()->remove(curve->data()->begin()->sortKey());
    curve->addData(x, y); // Добавление новых данных
}


