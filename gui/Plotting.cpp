#include "MainWindow.h"
#include "ui_MainWindow.h"

// Построение положения маятника
void MainWindow::plotPendulum(std::vector<state_type> const& solution, size_t plotInd){
    std::vector<double> pointCartCoord = solOpt_.diffEqu().calcCartesianCoordinates(solution[plotInd]); // Получение декартовых координат маятника
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
    // Следы точек
    if (!ui->pushButtonCalculate->isEnabled()){ // Если отрисовка идет
        if (plotInd >= TRACE_LENGTH){ // Удаление первых элементов, если след достиг целевой длины
            listTrace_[0].pop_front(); // Первая точка
            listTrace_[1].pop_front(); // Вторая точка
        }
        listTrace_[0].push_back({pointCartCoord[0], pointCartCoord[1]}); // Первая точка
        listTrace_[1].push_back({pointCartCoord[2], pointCartCoord[3]}); // Вторая точка
        // След первой точки
        ui->plotPendulum->graph(4)->setData(sliceTrace(0, 0), sliceTrace(0, 1));
        // След второй точки
        ui->plotPendulum->graph(5)->setData(sliceTrace(1, 0), sliceTrace(1, 1));
    }
    // Масштабирование осей
    ui->plotPendulum->rescaleAxes(true);
    double tLenSum = solOpt_.diffEqu().length()[0] + solOpt_.diffEqu().length()[1]; // Суммарная длина
    ui->plotPendulum->xAxis->setRange(-tLenSum, tLenSum); // Пределы по оси X
    ui->plotPendulum->yAxis->setRange(-tLenSum, tLenSum); // Пределы по оси Y
    double zoomShift = 1.25; // Коэффициент отдаления
    ui->plotPendulum->xAxis->scaleRange(zoomShift, ui->plotPendulum->xAxis->range().center()); // Отдалить по оси X
    ui->plotPendulum->yAxis->scaleRange(zoomShift, ui->plotPendulum->yAxis->range().center()); // Отдалить по оси Y
    ui->plotPendulum->replot(); // Обновление окна построения
}

// Очистка маятника
void MainWindow::clearPendulum(){
    ui->plotPendulum->graph(0)->data()->clear(); // Первый стержень
    ui->plotPendulum->graph(1)->data()->clear(); // Второй стержень
    ui->plotPendulum->graph(2)->data()->clear(); // Первая точечная масса
    ui->plotPendulum->graph(3)->data()->clear(); // Вторая точечная масса
    ui->plotPendulum->graph(4)->data()->clear(); // След первой массы
    ui->plotPendulum->graph(5)->data()->clear(); // След второй массы
    ui->plotPendulum->rescaleAxes(false); // Масштабирование осей
    ui->plotPendulum->replot(); // Обновление окна построения
}

// Обновление начального положения маятника
void MainWindow::updateInitPendulum(){
    if (ui->pushButtonCalculate->isEnabled()) // Отрисовка только при начале нового расчета
        plotPendulum({solOpt_.initCond()}, 0);
}

// -- Вспомогательные ------------------------------------------------------------------------------------------------

// Срез следа по индексам
QVector<double> MainWindow::sliceTrace(size_t indPoint, size_t indCoord){
    QVector<double> resCoordTrace(listTrace_[indPoint].size());
    int iTrace = 0;
    auto iter = listTrace_[indPoint].begin();
    for (; iter != listTrace_[indPoint].end(); ++iTrace, ++iter)
        resCoordTrace[iTrace] = (*iter)[indCoord];
    return resCoordTrace;
}
