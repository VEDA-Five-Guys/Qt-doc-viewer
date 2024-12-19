#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "toolbar.h"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ToolBar *toolbar;

};


#endif
