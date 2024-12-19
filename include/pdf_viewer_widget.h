#ifndef PDF_VIEWER_WIDGET_H
#define PDF_VIEWER_WIDGET_H

#include <QWidget>

class QPdfView;
class QPdfDocument;
class QPdfPageNavigator;

class Pdf_Viewer_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Pdf_Viewer_Widget(const QUrl &url, QWidget *parent = nullptr);

private:
    QPdfView *view;
    QPdfDocument *document;
    QPdfPageNavigator *page_navigator;

    void initialize(const QUrl &url);

    int prev_page_idx, curr_page_idx;

signals:

};

#endif // PDF_VIEWER_WIDGET_H
