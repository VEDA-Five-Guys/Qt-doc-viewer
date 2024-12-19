#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "toolbar.h"

#include <QMainWindow>

class QFileDialog;
class FileManager;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void update_cur_page(int);
    void update_total_page(int);

    void move_prev();
    void move_next();
    
private:
    Ui::MainWindow *ui;
    QFileDialog *dialog;
    ToolBar *toolbar;
    FileManager *file_manager;

    QUrl get_url();
};

#endif // MAIN_WINDOW_H
