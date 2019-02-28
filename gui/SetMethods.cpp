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

// Установка границ отображения фазовых углов
void MainWindow::setPlotPhaseAnglesRange(double zoomShift){
    ui->plotPhaseAngles->rescaleAxes(true);
    // Выставление пределов по осям
    ui->plotPhaseAngles->xAxis->setRange(solutionMinMax_.first[0], solutionMinMax_.second[0]); // X
    ui->plotPhaseAngles->yAxis->setRange(solutionMinMax_.first[1], solutionMinMax_.second[1]); // Y
    ui->plotPhaseAngles->xAxis->scaleRange(zoomShift, ui->plotPhaseAngles->xAxis->range().center()); // Отдалить по оси X
    ui->plotPhaseAngles->yAxis->scaleRange(zoomShift, ui->plotPhaseAngles->yAxis->range().center()); // Отдалить по оси Y
    ui->plotPhaseAngles->replot();
}

// Переопределение событий программы
bool MainWindow::eventFilter(QObject * obj, QEvent * event){
    // Параметры размеров
    static const float RELATIVE_WIDTH_DOCK = 0.28f;
    static const float RELATIVE_HEIGHT_DOCK = 0.2398f;
    static const float RELATIVE_WIDTH_MAINWINDOW = 0.4813f;
    static const float RELATIVE_HEIGHT_MAINWINDOW = 0.5546f;
    // В случае изменения размера
    if (event->type() == QEvent::Resize){
        QResizeEvent * resizeEvent = static_cast<QResizeEvent*>(event); // Событие
        // Для главного окна
        if (obj == this){
            // При инициализации окна
            if (resizeEvent->oldSize().width() == -1){
                QRect screenGeometry = QApplication::primaryScreen()->geometry(); // Параметры текущего монитора
                QRect winGeometry = this->geometry(); // Геометрия старого окна
                // Установка параметров окна с учетом разрешения монитора
                    // Размеры
                winGeometry.setWidth(qRound(screenGeometry.width() * RELATIVE_WIDTH_MAINWINDOW));
                winGeometry.setHeight(qRound(screenGeometry.height() * RELATIVE_HEIGHT_MAINWINDOW));
                this->setGeometry(winGeometry); // Установка геометрии
                this->move(qRound((screenGeometry.width() - winGeometry.width()) / 2.0), // Позиция по центру
                           qRound((screenGeometry.height() - winGeometry.height()) / 2.0));
            }
            // Установка процентного максимума от ширины окна для левой панели
            int leftPanelMaxWidth = qRound(this->width() * RELATIVE_WIDTH_DOCK);
            ui->dockPhysicalParamsWidget->setMaximumWidth(leftPanelMaxWidth); // Физические параметры
            ui->dockSolutionParamsWidget->setMaximumWidth(leftPanelMaxWidth); // Свойства решения
            // Установка процентного максимума от высоты для физических параметров
            int leftPanelMaxHeight = qRound(this->height() * RELATIVE_HEIGHT_DOCK);
            ui->dockPhysicalParamsWidget->setMaximumHeight(leftPanelMaxHeight); // Физические параметры
        }
    }
    return QObject::eventFilter(obj, event); // Стандартная обработка событий
}
