#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
    * Constructor for MainWindow object
    */
    MainWindow(QWidget *parent = nullptr);

private:
    /**
    * The UI element of the window
    */
    Ui::MainWindowClass ui;
};
