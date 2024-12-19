#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <QObject>
#include <QUrl>
#include <QHash>
#include <QString>

class FileItem;
class QScrollArea;
class QWidget;
class QStackedWidget;
class Viewer;

class FileManager : public QObject {
    Q_OBJECT

public:
    explicit FileManager(QWidget* contents, QStackedWidget *view, QObject *parent = nullptr);

    void add_file(const QUrl &url);
    void next_page();
    void prev_page();

signals:
    void cur_page_changed(int);
    void total_page_changed(int);

public slots:
    void handle_select(const QString&);
    void handle_remove(const QString&);

private:
    QHash<QString, FileItem*> file_hash;
    QHash<Viewer*, QWidget*> page_hash;
    QWidget *contents;
    QStackedWidget *view;
    Viewer *current_viewer;

    void update_view(const QString&, Viewer*);
    void handle_deleted_viewer(Viewer*);

};

#endif // FILE_MANAGER_H
