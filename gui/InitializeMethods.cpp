#include "MainWindow.h"
#include "ui_MainWindow.h"

// Инициализация параметров решения
void MainWindow::initializeSolutionOptions(){
    setMass();      // Массы
    setLength();    // Длины
    setGravity();   // Гравитация
    setInitCond();  // Начальное условие
    setTimeBound(); // Интервал интегрирования
    setTimeStep();  // Шаг по времен
}

// Инициализация параметров построения
void MainWindow::initializeShowParams(){
    playBackTimer_ = new QTimer(this); // Таймер
    // Интервал срабатывания таймера
        // Текстовая метка
    labelTimeInterval_ = new QLabel();
    labelTimeInterval_->setText("Интервал таймера: ");
    ui->statusBar->addPermanentWidget(labelTimeInterval_);
        // Полоса прокрутки
    scrollBarTimerInterval_ = new QScrollBar(Qt::Horizontal);
    scrollBarTimerInterval_->setMinimum(0); // Минимальное значение
    scrollBarTimerInterval_->setMaximum(128); // Максимальное значение
    scrollBarTimerInterval_->setValue(8); // Текущее значение
    scrollBarTimerInterval_->setMinimumWidth(180); // Минимальная ширина
    ui->statusBar->addPermanentWidget(scrollBarTimerInterval_); // Добавление в информационную строку
    setTimerInterval(); // Установка интервала таймера
    // Текущее время моделирования
   labelCurrentTime_ = new QLabel();
   labelCurrentTime_->setText("Время: 0");
   ui->statusBar->addWidget(labelCurrentTime_);
    // Временные следы
    tracePendulum_.resize(solOpt_.diffEqu().pointNumber()); // Маятника
    tracePhasePortrait_.resize(solOpt_.diffEqu().pointNumber()); // Фазовый портрет
    setMaxTraceLength(); // Выставление максимальной длины временного следа
}

// Инициализация всех графических окон
void MainWindow::initializeAllPlot(){
    // -- PlotPendulum --
    initializePlotPendulum(); // Графическое окно с маятником
    updateInitPendulum(); // Обновление начального положения маятника
    // -- PlotPhasePortrait --
    initializePlotPhasePortrait(); // Графическое окно с фазовым портретом
    // -- PlotPhaseAngles --
    initializePlotPhaseAngles(); // Графическое окно с фазовыми углами
}

// Инициализация окна с маятником
void MainWindow::initializePlotPendulum(){
    for (int i = 0; i != 4; ++i) ui->plotPendulum->addGraph(); // Добавление графиков для 2ух-стержней и 2ух-точек со следами
    ui->plotPendulum->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom); // Установить пользовательские взаимодействия (перетаскивание + масштабирование)
    // Первый стержень
    QPen rodPen;
    rodPen.setStyle(Qt::SolidLine); // Тип линии
    rodPen.setWidth(5); // Толщина линии
    rodPen.setColor(QColor(Qt::red)); // Цвет линии
    ui->plotPendulum->graph(0)->setPen(rodPen) ; // Установка линии
    // Второй стержень
    rodPen.setColor(QColor(Qt::blue)); // Цвет линии
    ui->plotPendulum->graph(1)->setPen(rodPen) ; // Установка линии
    // Первая точечная масса
    QCPScatterStyle pointScatterStyle; // Стиль точки
    pointScatterStyle.setShape(QCPScatterStyle::ssDisc); // Тип точки
    pointScatterStyle.setPen(QPen(Qt::red)); // Цвет линии
    pointScatterStyle.setBrush(QColor(Qt::red)); // Цвет заливки
    pointScatterStyle.setSize(25); // Размер точки
    ui->plotPendulum->graph(2)->setLineStyle(QCPGraph::lsNone); // Тип линии графика
    ui->plotPendulum->graph(2)->setScatterStyle(pointScatterStyle); // Тип точки графика
    // Вторая точечная масса
    pointScatterStyle.setPen(QPen(Qt::blue)); // Цвет линии
    pointScatterStyle.setBrush(QColor(Qt::blue)); // Цвет заливки
    ui->plotPendulum->graph(3)->setLineStyle(QCPGraph::lsNone); // Тип линии графика
    ui->plotPendulum->graph(3)->setScatterStyle(pointScatterStyle); // Тип точки графика
    // Следы
    for (int i = 0; i != tracePendulum_.size(); ++i)
        tracePendulum_[i] = new QCPCurve(ui->plotPendulum->xAxis, ui->plotPendulum->yAxis);
    // След первой массы
    QPen tracePen; // Стиль точки
    tracePen.setColor(Qt::red); // Цвет
    tracePendulum_[0]->setPen(tracePen); // Задание типа графика
    // След второй массы
    tracePen.setColor(Qt::blue); // Цвет
    tracePendulum_[1]->setPen(tracePen); // Задание типа графика
}

// Инициализация окна с фазовым портретом
void MainWindow::initializePlotPhasePortrait(){
    ui->plotPhasePortrait->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom); // Установить пользовательские взаимодействия (перетаскивание + масштабирование)
    ui->plotPhasePortrait->legend->setVisible(true); // Отображение легенды
    ui->plotPhasePortrait->legend->setFont(ui->labelInitAngle1->font()); // Шрифт
    // Следы
    for (int i = 0; i != tracePhasePortrait_.size(); ++i)
        tracePhasePortrait_[i] = new QCPCurve(ui->plotPhasePortrait->xAxis, ui->plotPhasePortrait->yAxis);
    // След первой массы
    QPen tracePen; // Стиль точки
    tracePen.setColor(Qt::red); // Цвет
    tracePhasePortrait_[0]->setPen(tracePen); // Задание типа графика
    tracePhasePortrait_[0]->setName("a1t(a1)"); // Имя графика
    // След второй массы
    tracePen.setColor(Qt::blue); // Цвет
    tracePhasePortrait_[1]->setPen(tracePen); // Задание типа графика
    tracePhasePortrait_[1]->setName("a2t(a2)"); // Имя графика
}

// Инициализация окна с фазовым углами
void MainWindow::initializePlotPhaseAngles(){
    ui->plotPhaseAngles->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom); // Установить пользовательские взаимодействия (перетаскивание + масштабирование)
    ui->plotPhaseAngles->legend->setVisible(true); // Отображение легенды
    ui->plotPhaseAngles->legend->setFont(ui->labelInitAngle1->font()); // Шрифт
    tracePhaseAngles_ = new QCPCurve(ui->plotPhaseAngles->xAxis, ui->plotPhaseAngles->yAxis); // След
    QPen tracePen; // Стиль точки
    tracePen.setColor(Qt::black); // Цвет
    tracePhaseAngles_->setPen(tracePen); // Задание типа графика
    tracePhaseAngles_->setName("a2(a1)"); // Имя графика
}
