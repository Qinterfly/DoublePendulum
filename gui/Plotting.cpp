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

// Обновление начального положения маятника
void MainWindow::updateInitPendulum(){
    // Отрисовка только при начале нового расчета
    if (ui->pushButtonCalculate->isEnabled()){
        setPlotPendulumRange(1.5); // Границы отображения
        plotPendulum({solOpt_.initCond()}, 0);
    }
}

// --- Вспомогательные -----------------------------------------------------------------------------------------

// Добавление данных к временному следу
void MainWindow::addTraceData(QCPCurve * curve, double const& x, double const& y){
    if (ui->pushButtonCalculate->isEnabled()) return; // Проверка режима отрисовки
    // Срез данных по длине следа (pop_front)
    if (curve->data()->size() == maxTraceLength_)
        curve->data()->remove(curve->data()->begin()->sortKey());
    curve->addData(x, y); // Добавление новых данных
}


