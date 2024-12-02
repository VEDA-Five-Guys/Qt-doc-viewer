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

signals:

private:
    void initialize(const QUrl &url);
    QPdfView *pdf_view;                         // pdf를 표시
    QPdfDocument *pdf_document;                 // pdf의 데이터를 제공
    QPdfPageNavigator *pdf_page_navigator;      // pdf의 페이지 탐색
    int prev_page_idx, curr_page_idx;
};

#endif // PDF_VIEWER_WIDGET_H
