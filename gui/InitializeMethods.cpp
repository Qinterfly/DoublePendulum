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
    scrollBarTimerInterval_->setValue(4); // Текущее значение
    scrollBarTimerInterval_->setMinimumWidth(180); // Минимальная ширина
    ui->statusBar->addPermanentWidget(scrollBarTimerInterval_); // Добавление в информационную строку
    setTimerInterval(); // Установка интервала таймера
    // Временной след
    setTraceLength(); // Выставление длины временного следа
    listTrace_.resize(2); // След для двух точек
}

// Инициализация всех графических окон
void MainWindow::initializeAllPlot(){
    // -- PlotPendulum --
    initializePlotPendulum(); // Графическое окно с маятником
    updateInitPendulum(); // Обновление начального положения маятника
}

// Инициализация окна с маятником
void MainWindow::initializePlotPendulum(){
    for (int i = 0; i != 6; ++i) ui->plotPendulum->addGraph(); // Добавление графиков для 2ух-стержней и 2ух-точек со следами
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
    // След первой массы
    QCPScatterStyle traceScatterStyle; // Стиль точки
    traceScatterStyle.setShape(QCPScatterStyle::ssDisc); // Тип точки
    traceScatterStyle.setPen(QPen(Qt::red)); // Цвет линии
    traceScatterStyle.setBrush(QColor(Qt::red)); // Цвет заливки
    traceScatterStyle.setSize(2); // Размер точки
    ui->plotPendulum->graph(4)->setLineStyle(QCPGraph::lsNone); // Тип линии графика
    ui->plotPendulum->graph(4)->setScatterStyle(traceScatterStyle); // Тип точки графика
    // След второй массы
    traceScatterStyle.setPen(QPen(Qt::blue)); // Цвет линии
    traceScatterStyle.setBrush(QColor(Qt::blue)); // Цвет заливки
    ui->plotPendulum->graph(5)->setLineStyle(QCPGraph::lsNone); // Тип линии графика
    ui->plotPendulum->graph(5)->setScatterStyle(traceScatterStyle); // Тип точки графика
}
