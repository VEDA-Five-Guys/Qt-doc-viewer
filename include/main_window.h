#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class Pdf_Viewer_Widget;

class QFileDialog;

namespace Ui {
    class Main_Window;
}

class Main_Window : public QMainWindow {
    Q_OBJECT

public:
    explicit Main_Window(QWidget *parent = nullptr);
    ~Main_Window();

private:
    Ui::Main_Window *ui;

    void set_connects();

    QFileDialog *file_dialog;
    QUrl get_url();
    void update_central_widget(const QUrl &url);
    QWidget *make_page(Pdf_Viewer_Widget *pdf_viewer_widget, const QString &name);

};


#endif
