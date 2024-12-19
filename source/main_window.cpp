#include "ui_main_window.h"
#include "main_window.h"

#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent), 
    ui(new Ui::MainWindow),
    toolbar(new ToolBar) {

    ui->setupUi(this);

    toolbar->setup(ui->navigator);
}

MainWindow::~MainWindow() {
    delete ui;
}
