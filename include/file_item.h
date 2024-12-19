#ifndef FILE_ITEM_H
#define FILE_ITEM_H

#include <QWidget>

namespace Ui {
    class FileItem;
}

class Viewer;

class FileItem : public QWidget {
    Q_OBJECT

public:
    explicit FileItem(QString file_name, Viewer *viewer, QWidget *parent = nullptr);
    ~FileItem();

    Viewer* get_viewer() const;

protected:
    void resizeEvent(QResizeEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void handle_remove();

private:
    Ui::FileItem *ui;
    Viewer *viewer;
    QString file_name;

    void set_elided_text();

signals:
    void select(const QString&);
    void remove(const QString&);
    void page_changed(int);

};

#endif // FILE_ITEM_H
