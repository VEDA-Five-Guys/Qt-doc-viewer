#include "pdf_viewer_widget.h"

#include <QPdfView>
#include <QPdfDocument>
#include <QPdfPageNavigator>
#include <QUrl>
#include <QVBoxLayout>

Pdf_Viewer_Widget::Pdf_Viewer_Widget(const QUrl &url, QWidget *parent)
    : QWidget{parent}
    , view(new QPdfView(this)), document(new QPdfDocument(this)), page_navigator(new QPdfPageNavigator(this)){

    initialize(url);
}

void Pdf_Viewer_Widget::initialize(const QUrl &url){
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);

    view->setPageMode(QPdfView::PageMode::MultiPage);
    view->setZoomMode(QPdfView::ZoomMode::FitInView);
    view->setDocumentMargins(QMargins(0, 0, 0, 0));
    view->setDocument(document);

    document->load(url.toLocalFile());

    page_navigator = view->pageNavigator();
    curr_page_idx = page_navigator->currentPage();
    page_navigator->jump(curr_page_idx, {}, page_navigator->currentZoom());

    setLayout(layout);
}
