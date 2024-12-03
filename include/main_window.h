#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QHash>

class Pdf_Viewer_Widget;
class File_Item_Widget;

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
    QFileDialog *dialog;

    void initialize();
    void set_connects();
    QUrl get_url();
    void update_central_widget(const QUrl &url);
    QWidget *make_page(Pdf_Viewer_Widget *pdf_viewer, const QString &name);
    File_Item_Widget *make_item(const QString &name);

    QHash<QString, QPair<QWidget*, File_Item_Widget*>> hash;

};


#endif
