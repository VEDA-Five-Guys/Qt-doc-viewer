#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>

class QPdfView;
class QPdfDocument;
class QPdfPageNavigator;

class Viewer : public QWidget {
    Q_OBJECT

public:
    explicit Viewer(const QUrl &url, QWidget *parent = nullptr);

    int get_cur_idx() const;
    int get_total_pages() const;

    bool next_page();
    bool prev_page();

signals:
    void page_changed(int);

private:
    QPdfView *view;
    QPdfDocument *document;
    QPdfPageNavigator *page_navigator;
};

#endif // VIEWER_H
