#include "ui_main_window.h"
#include "main_window.h"

#include "pdf_viewer_widget.h"
#include "file_item_widget.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QStackedLayout>

Main_Window::Main_Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Main_Window)
    , dialog(nullptr){

    ui->setupUi(this);

    toolbar = new ToolBar();
    toolbar->setup(ui->navigator);

    initialize();
    set_connects();
}

Main_Window::~Main_Window(){
    delete ui;
}

void Main_Window::initialize(){
    ui->contents->layout()->setAlignment(Qt::AlignTop); // file_list 내 버튼 정렬 설정
}

void Main_Window::set_connects(){
    connect(ui->open_file, &QPushButton::clicked, this, [this](){
        update_central_widget(get_url());
    });
}

QUrl Main_Window::get_url(){
    if(dialog == nullptr){
        dialog = new QFileDialog(this, tr("Open File")
                                      , QStandardPaths::writableLocation(QStandardPaths::DownloadLocation)); // 경로 설정
        dialog->setAcceptMode(QFileDialog::AcceptOpen);    // 열기 모드
        dialog->setMimeTypeFilters({"application/pdf"});   // pdf 문서만 표시

        QUrl url;
        if(dialog->exec() == QFileDialog::Accepted){
            url = dialog->selectedUrls().constFirst();
        }
        dialog->deleteLater();
        dialog = nullptr;

        return url;
    }
    else{
        qDebug() << "dialog already open";
        return QUrl();
    }
}

void Main_Window::update_central_widget(const QUrl &url){
    if(url.isValid()){
        if(url.isLocalFile()){
            // 1. pdf_viewer 동적 생성
            Pdf_Viewer_Widget *pdf_viewer = new Pdf_Viewer_Widget(url, this);
            // 2. doc_viewer connect 설정

            // 3. name 설정
            int num = 1;
            QString original_name = url.fileName().remove(".pdf");
            QString name = original_name;
            while(hash.contains(name)){
                name = QString("%1(%2)").arg(original_name, QString::number(num++));
            }
            // 4. page, item 생성 및 해시 연결
            hash.insert(name, {make_page(pdf_viewer, name), make_item(name)});
            // 5. page 변경 시그널 전송
        }
        else{
            qDebug() << "it's not local file";
        }
    }
    else{
        qDebug() << "url is invalid";
    }
}

QWidget *Main_Window::make_page(Pdf_Viewer_Widget *pdf_viewer, const QString &name){
    QWidget *page = new QWidget(ui->file_view);
    page->setObjectName(QString("%1_%2").arg(name, "page"));

    QStackedLayout *stacked_layout = new QStackedLayout(page);
    stacked_layout->setContentsMargins(0, 0, 0, 0);
    stacked_layout->setStackingMode(QStackedLayout::StackAll);
    stacked_layout->addWidget(pdf_viewer);

    page->setLayout(stacked_layout);

    ui->file_view->addWidget(page);
    ui->file_view->setCurrentWidget(page);

    return page;
}

File_Item_Widget *Main_Window::make_item(const QString &name){
    File_Item_Widget *file_item = new File_Item_Widget(name, ui->file_list);
    file_item->setObjectName(QString("%1_%2").arg(name, "item"));

    ui->contents->layout()->addWidget(file_item);

    connect(file_item, &File_Item_Widget::remove, this, [this](const QString &name){
        QWidget *named_page = hash.value(name).first;
        if(named_page){
            ui->file_view->removeWidget(named_page);
            named_page->deleteLater();

            qDebug() << ui->file_view->currentWidget()->objectName();
        }
        else{
            qDebug() << "named_page is null or invalid";
            return;
        }

        File_Item_Widget *named_file_item = hash.value(name).second;
        if(named_file_item){
            ui->contents->layout()->removeWidget(named_file_item);
            named_file_item->deleteLater();
        }
        else{
            qDebug() << "named_file_item is null or invalid";
            return;
        }
    });

    return file_item;
}
