#include "MainWindow.h"
#include "ui_MainWindow.h"

// Решить ДУ с заданными условиями
void MainWindow::solve(){
    state_type Y = solOpt_.initCond(); // Контейнер решения на каждом временном шаге
    nTime_ = integrate_const(solOpt_.stepper(), solOpt_.diffEqu(), Y, solOpt_.timeBound()[0],
            solOpt_.timeBound()[1], solOpt_.timeStep(), PushBackSolution(solution_, time_));
    ++nTime_; // Включая начальный момент времени
}

// Запуск общей процедуры расчета
void MainWindow::calculate(){
    solve(); // Решить ДУ с заданными условиями
    findSolutionMinMax(); // Нахождение максимумов и минимумов решения
    playBackTimer_->start(); // Запуск таймера (h * 1e3)
    ui->pushButtonCalculate->setEnabled(false); // Отключение кнопки начала расчета
    setPlotPhasePortraitRange(1.25); // Установка границ отображения фазового портрета
    setPlotPhaseAnglesRange(1.1); // Установка границ отображения фазовых углов
}

// Пауза или возобнолвение
void MainWindow::pauseOrContinue(){
    if (isPaused_) // В случае, если нажато возобновление
        ui->pushButtonPauseOrContinue->setText("Пауза");
    else
        ui->pushButtonPauseOrContinue->setText("Продолж.");
    isPaused_ = !isPaused_;
}

// Остановка
void MainWindow::stop(){
    playBackTimer_->stop(); // Остановка тайемера
    timeInd_ = 0; // Сброс индекса решения
    time_.clear(); // Очистка вектора времени
    solution_.clear(); // Очистка вектора решения
    clearPendulum(); // Очистка маятника
    clearPhasePortrait(); // Очистка фазового портрета
    clearPhaseAngles(); // Очистка фазовых углов
    labelCurrentTime_->setText("Время: 0"); // Сброс индикатора времени
    ui->pushButtonCalculate->setEnabled(true); // Включение кнопки начала расчета
    updateInitPendulum(); // Обновление начального положения маятника
}

// Функция отрисовки по таймеру
void MainWindow::playBackStep(){
    if (isPaused_) return; // Проверка паузы
    switch (ui->tabPlotWidget->currentIndex()){
    case 0:
        plotPendulum(solution_, timeInd_); // Построение маятника
        break;
    case 1:
        plotPhasePortrait(timeInd_); // Построение фазового портрета
        break;
    case 2:
        plotPhaseAngles(timeInd_); // Построение фазовых углов
    }
    labelCurrentTime_->setText("Время: " + QString::number(time_[timeInd_])); // Сброс индикатора времени
    // Приращение индекса решения
    if (timeInd_ != nTime_ - 1){
        ++timeInd_;
    }
    else
        playBackTimer_->stop(); // Остановка таймера
}

// --- Вспомогательные -----------------------------------------------------------------------------------------

// Нахождение максимумов и минимумов решения
void MainWindow::findSolutionMinMax(){
    size_t nY = solOpt_.initCond().size();
    solutionMinMax_.first = solution_[0]; // Минимумы
    solutionMinMax_.second = solutionMinMax_.first; // Максимумы
    for (size_t iTime = 1; iTime != nTime_; ++iTime){
        for (size_t jY = 0; jY != nY; ++jY){
            // Минимумы
            if (solution_[iTime][jY] < solutionMinMax_.first[jY])
                solutionMinMax_.first[jY] = solution_[iTime][jY];
            // Максимумы
            if (solution_[iTime][jY] > solutionMinMax_.second[jY])
                solutionMinMax_.second[jY] = solution_[iTime][jY];
        }
    }
}

