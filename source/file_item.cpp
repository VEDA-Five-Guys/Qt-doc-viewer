#include "ui_file_item.h"
#include "file_item.h"
#include "viewer.h"

#include <QMetaObject>
#include <QMetaMethod>

FileItem::FileItem(QString file_name, Viewer *viewer, QWidget *parent) 
    : QWidget(parent), 
    file_name(file_name),
    viewer(viewer),
    ui(new Ui::FileItem) {
    ui->setupUi(this);

    ui->remove->setVisible(false);

    connect(ui->remove, &QPushButton::clicked, this, &FileItem::handle_remove);
    connect(ui->file, &QPushButton::clicked, this, [=](){
        emit select(file_name);
    });

    connect(viewer, &Viewer::page_changed, this, [this](int cur){
        emit page_changed(cur);        
    });

    installEventFilter(this);

    set_elided_text();
}

FileItem::~FileItem() {
    delete ui;
    delete viewer;
}

Viewer* FileItem::get_viewer() const {
    return this->viewer;
}

void FileItem::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    set_elided_text();
}

bool FileItem::eventFilter(QObject *obj, QEvent *event) {
    if (obj == this) {
        if (event->type() == QEvent::Enter || event->type() == QEvent::Leave) {
            ui->remove->setVisible(event->type() == QEvent::Enter);
            set_elided_text();

            return true;
        }   
    }

    return QWidget::eventFilter(obj, event);
}

void FileItem::handle_remove() {
    emit remove(file_name);
    this->deleteLater();
}

void FileItem::set_elided_text() {
    int width = ui->file->width();
    QString elided_name = ui->file->fontMetrics().elidedText(this->file_name, Qt::ElideRight, width);
    if (ui->file->text() != elided_name) {
        ui->file->setText(elided_name);
    }
}
