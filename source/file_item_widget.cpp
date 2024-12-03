#include "file_item_widget.h"
#include "ui_file_item_widget.h"

#include <QMetaObject>
#include <QMetaMethod>
#include <QPushButton>

File_Item_Widget::File_Item_Widget(const QString &name, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::File_Item_Widget){

    ui->setupUi(this);
    initialize(name);
    set_connects(name);
}

File_Item_Widget::~File_Item_Widget(){
    delete ui;
}

bool File_Item_Widget::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::Enter || event->type() == QEvent::Leave){
        ui->remove->setVisible(
            event->type() == QEvent::Enter
            ? true
            : false
        );
        QMetaObject::invokeMethod(this, [this]{
            emit width_changed();
        }, Qt::QueuedConnection);

        return true;
    }

    if(event->type() == QEvent::Resize){
        emit width_changed();

        return true;
    }

    return QWidget::eventFilter(obj, event);
}

void File_Item_Widget::initialize(const QString &name){
    ui->remove->setVisible(false);
    installEventFilter(this);
}

void File_Item_Widget::set_connects(const QString &name){
    QMetaObject::Connection width_changed_connection =
        connect(this, &File_Item_Widget::width_changed, this, [this, name](){
            set_elided_text(name);
            qDebug() << ui->file->width();
    });
    connect(ui->file, &QPushButton::clicked, this, [this, name](){

    });
    connect(ui->remove, &QPushButton::clicked, this, [this, name, width_changed_connection](){
        disconnect(width_changed_connection);
        disconnect();
        removeEventFilter(this);
        emit remove(name);
    });

}

void File_Item_Widget::set_elided_text(const QString &name){
    int width = ui->file->width();
    QString elided_name = ui->file->fontMetrics().elidedText(name, Qt::ElideRight, width);
    ui->file->setText(elided_name);
}
