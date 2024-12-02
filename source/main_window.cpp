#include "ui_main_window.h"
#include "main_window.h"

#include "pdf_viewer_widget.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QStackedLayout>

using namespace std;

Main_Window::Main_Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Main_Window)
    , file_dialog(nullptr){

    ui->setupUi(this);
    ui->contents->layout()->setAlignment(Qt::AlignTop); // file_list 내 버튼 정렬 설정

    set_connects();
}

Main_Window::~Main_Window(){
    delete ui;
}

void Main_Window::set_connects(){
    connect(ui->open_file, &QPushButton::clicked, this, [this](){
        update_central_widget(get_url());
    });
}

QUrl Main_Window::get_url(){
    if(file_dialog == nullptr){
        file_dialog = new QFileDialog(this, tr("Open File")
                                      , QStandardPaths::writableLocation(QStandardPaths::DownloadLocation)); // 경로 설정
        file_dialog->setAcceptMode(QFileDialog::AcceptOpen);    // 열기 모드
        file_dialog->setMimeTypeFilters({"application/pdf"});   // pdf 문서만 표시

        QUrl url;
        if(file_dialog->exec() == QFileDialog::Accepted){
            url = file_dialog->selectedUrls().constFirst();
        }
        file_dialog->deleteLater();
        file_dialog = nullptr;

        return url;
    }
    else{
        qDebug() << "file_dialog already open";
        return QUrl();
    }
}

void Main_Window::update_central_widget(const QUrl &url){
    if(url.isValid()){
        if(url.isLocalFile()){
            /*
             * doc_viewer 동적 생성 및 설정
             * object_name 설정
             * page, button 생성 및 object_name과 해시로 연결
             */

            // 1. doc_viewer 생성
            Pdf_Viewer_Widget *pdf_viewer_widget = new Pdf_Viewer_Widget(url, this);
            // 2. doc_viewer connect 설정

            // 3. object_name 설정

            // 4. doc_viewer와 대응되는 page, button 생성 및 object_name과 해시 연결
            QWidget *tmp_widget = make_page(pdf_viewer_widget, "");
            if(tmp_widget){
                qDebug() << "success!";
            }
            else{
                qDebug() << "failed...";
            }
            // 5. page 변경 신호 발생
        }
        else{
            qDebug() << "it's not local file";
        }
    }
    else{
        qDebug() << "url is invalid";
    }
}

QWidget *Main_Window::make_page(Pdf_Viewer_Widget *pdf_viewer_widget, const QString &name){
    QWidget *page = new QWidget(ui->file_view);
    page->setObjectName(name);

    QStackedLayout *stacked_layout = new QStackedLayout(page);
    stacked_layout->setContentsMargins(0, 0, 0, 0);
    stacked_layout->setStackingMode(QStackedLayout::StackAll);
    stacked_layout->addWidget(pdf_viewer_widget);

    page->setLayout(stacked_layout);

    ui->file_view->addWidget(page);
    ui->file_view->setCurrentWidget(page);

    return page;
}
