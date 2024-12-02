#include "pdf_viewer_widget.h"

#include <QPdfView>
#include <QPdfDocument>
#include <QPdfPageNavigator>
#include <QUrl>
#include <QVBoxLayout>

Pdf_Viewer_Widget::Pdf_Viewer_Widget(const QUrl &url, QWidget *parent)
    : QWidget{parent}
    , pdf_view(new QPdfView(this)), pdf_document(new QPdfDocument(this)), pdf_page_navigator(new QPdfPageNavigator(this)){

    initialize(url);
}

void Pdf_Viewer_Widget::initialize(const QUrl &url){
    QVBoxLayout *vertical_layout = new QVBoxLayout(this);
    vertical_layout->setContentsMargins(0, 0, 0, 0);
    vertical_layout->addWidget(pdf_view);

    pdf_view->setPageMode(QPdfView::PageMode::MultiPage);
    pdf_view->setZoomMode(QPdfView::ZoomMode::FitInView);
    pdf_view->setDocumentMargins(QMargins(0, 0, 0, 0));
    pdf_view->setDocument(pdf_document);

    pdf_document->load(url.toLocalFile());

    pdf_page_navigator = pdf_view->pageNavigator();
    curr_page_idx = pdf_page_navigator->currentPage();
    pdf_page_navigator->jump(curr_page_idx, {}, pdf_page_navigator->currentZoom());

    setLayout(vertical_layout);
}
