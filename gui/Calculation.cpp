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
    playBackTimer_->start(); // Запуск таймера (h * 1e3)
    ui->pushButtonCalculate->setEnabled(false); // Отключение кнопки начала расчета
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
    listTrace_[0].clear(); listTrace_[1].clear();// Очистка следов точек
    clearPendulum(); // Очистка маятника
    ui->pushButtonCalculate->setEnabled(true); // Включение кнопки начала расчета
    updateInitPendulum(); // Обновление начального положения маятника
}

// Функция отрисовки по таймеру
void MainWindow::playBackStep(){
    if (isPaused_) return; // Проверка паузы
    plotPendulum(solution_, timeInd_); // Построение маятника
    // Приращение индекса решения
    if (timeInd_ != nTime_ - 1){
        ++timeInd_;
    }
    else
        playBackTimer_->stop(); // Остановка таймера
}
