#include "file_manager.h"
#include "file_item.h"
#include "viewer.h"

#include <QWidget>
#include <QStackedWidget>
#include <QStackedLayout>

FileManager::FileManager(QWidget *contents, QStackedWidget *view, QObject *parent)
    : QObject(parent),
    contents(contents),
    view(view),
    current_viewer(nullptr) {}

void FileManager::add_file(const QUrl &url) {
    if (!url.isValid()) {
        qDebug() << "Invalid URL.";
        return; 
    }

    if (!url.isLocalFile()) {
        qDebug() << "It's not a local file.";
        return;
    }

    QString file_name = url.fileName().remove(".pdf");
    if (file_hash.contains(file_name)) {
        update_view(file_name, file_hash.value(file_name)->get_viewer());
        return;
    }

    Viewer *viewer = new Viewer(url);
    update_view(file_name, viewer);
    
    FileItem *cur_file = new FileItem(file_name, viewer, contents);
    contents->layout()->addWidget(cur_file);

    file_hash.insert(file_name, cur_file);

    connect(cur_file, &FileItem::remove, this, &FileManager::handle_remove);
    connect(cur_file, &FileItem::select, this, &FileManager::handle_select);
    connect(cur_file, &FileItem::page_changed, this, [=](int cur) {
        emit cur_page_changed(viewer->get_cur_idx() + 1);
    });
}

void FileManager::next_page() {
    if (!current_viewer) return;

    current_viewer->next_page();
}

void FileManager::prev_page() {
    if (!current_viewer) return;

    current_viewer->prev_page();
}

void FileManager::handle_select(const QString &file_name) {
    if (!file_hash.contains(file_name)) {
        qWarning() << "File not found:" << file_name;
        return;
    }

    FileItem *file_item = file_hash.value(file_name);
    if (!file_item) {
        qWarning() << "FileItem is null for file:" << file_name;
        return;
    }

    Viewer *selected_viewer = file_item->get_viewer();
    if (!selected_viewer) {
        qWarning() << "Viewer is null for file:" << file_name;
        return;
    }

    update_view(file_name, selected_viewer);
}

void FileManager::handle_remove(const QString &file_name) {
    if (!file_hash.contains(file_name)) {
        qWarning() << "File not found:" << file_name;
        return;
    }

    FileItem* file_item = file_hash.value(file_name);
    if (file_item && file_item->get_viewer() == current_viewer) {
        current_viewer = nullptr;
    }

    file_hash.remove(file_name);
}

void FileManager::update_view(const QString &file_name, Viewer *viewer) {
    if (page_hash.contains(viewer)) {
        QWidget *existing_page = page_hash.value(viewer);
        view->setCurrentWidget(existing_page);
        current_viewer = viewer;
        emit cur_page_changed(viewer->get_cur_idx() + 1);
        emit total_page_changed(viewer->get_total_pages());
        return;
    }

    QWidget *page = new QWidget(view);
    page->setObjectName(file_name);

    QStackedLayout *layout = new QStackedLayout(page);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setStackingMode(QStackedLayout::StackAll);
    layout->addWidget(viewer);

    page->setLayout(layout);

    view->addWidget(page);
    view->setCurrentWidget(page);

    page_hash.insert(viewer, page);
    current_viewer = viewer;

    emit cur_page_changed(1);
    emit total_page_changed(viewer->get_total_pages());

    connect(viewer, &QObject::destroyed, [this, viewer]() {
        handle_deleted_viewer(viewer); 
    });
}

void FileManager::handle_deleted_viewer(Viewer *deleted_viewer) {
    if (!view || !deleted_viewer) {
        qWarning() << "Invalid view or deleted_page.";
        return;
    }
    QWidget *deleted_page = page_hash.value(deleted_viewer);

    int idx = view->indexOf(deleted_page);

    if (idx == -1) {
        qWarning() << "The deleted_page is not found in the view.";
        return;
    }

    bool is_current = (view->currentWidget() == deleted_page);

    view->removeWidget(deleted_page);
    deleted_page->deleteLater();

    page_hash.remove(deleted_viewer);
    
    if (!is_current) return;

    int new_count = view->count();

    if (!new_count) {
        current_viewer = nullptr;
        return;
    }

    int new_index = (idx < new_count) ? idx : (new_count - 1);
    view->setCurrentIndex(new_index);

    QString file_name = (view->currentWidget())->objectName();
    if (!file_hash.contains(file_name)) {
        return;
    }

    current_viewer = file_hash.value(file_name)->get_viewer();
}

