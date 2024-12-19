#include "viewer.h"

#include <QPdfView>
#include <QPdfDocument>
#include <QPdfPageNavigator>
#include <QUrl>
#include <QVBoxLayout>
#include <QSignalBlocker>

Viewer::Viewer(const QUrl &url, QWidget *parent)
    : QWidget(parent), 
    view(new QPdfView(this)), 
    document(new QPdfDocument(this)), 
    page_navigator(new QPdfPageNavigator(this)) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);

    view->setPageMode(QPdfView::PageMode::MultiPage);
    view->setZoomMode(QPdfView::ZoomMode::FitInView);
    view->setDocumentMargins(QMargins(0, 0, 0, 0));
    view->setDocument(document);

    document->load(url.toLocalFile());

    page_navigator = view->pageNavigator();
    int cur_idx = page_navigator->currentPage();
    page_navigator->jump(cur_idx, {}, page_navigator->currentZoom());

    setLayout(layout);

    connect(page_navigator, &QPdfPageNavigator::currentPageChanged, this, &Viewer::page_changed);
}

int Viewer::get_cur_idx() const {
    return page_navigator->currentPage();
}

int Viewer::get_total_pages() const {
    return document->pageCount();
}

bool Viewer::next_page() {
    int current = page_navigator->currentPage();
    if (current < document->pageCount() - 1) {
        page_navigator->jump(current + 1, QPointF());
        return true;
    }
    qDebug() << "Already at the last page.";
    return false;
}

bool Viewer::prev_page() {
    int current = page_navigator->currentPage();
    if (current > 0) {
        page_navigator->jump(current - 1, QPointF());
        return true;
    }
    qDebug() << "Already at the first page.";
    return false;
}
