#include "ui_main_window.h"
#include "main_window.h"
#include <iostream>

using namespace std;

Main_Window::Main_Window(QWidget *parent) 
    : QMainWindow(parent), ui(new Ui::Main_Window) {

    ui->setupUi(this);
    ui->contents->layout()->setAlignment(Qt::AlignTop);
}

Main_Window::~Main_Window() {
    delete ui;
}
