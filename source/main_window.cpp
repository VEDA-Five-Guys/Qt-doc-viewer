#include "ui_main_window.h"
#include "main_window.h"
#include "file_manager.h"

#include <QFileDialog>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), 
    ui(new Ui::MainWindow), 
    toolbar(new ToolBar),
    dialog(nullptr) {
    ui->setupUi(this);

    file_manager = new FileManager(ui->contents, ui->file_view, this);

    toolbar->setup(ui->navigator);

    ui->contents->layout()->setAlignment(Qt::AlignTop);

    connect(ui->open_file, &QPushButton::clicked, this, [this]() {
        QUrl url = get_url();
        file_manager->add_file(url);
    });

    connect(file_manager, &FileManager::cur_page_changed, this, &MainWindow::update_cur_page);
    connect(file_manager, &FileManager::total_page_changed, this, &MainWindow::update_total_page);

    connect(toolbar->prev_page, &QAction::triggered, this, &MainWindow::move_prev);
    connect(toolbar->next_page, &QAction::triggered, this, &MainWindow::move_next);
}

MainWindow::~MainWindow() {}

void MainWindow::update_cur_page(int cur) {
    toolbar->current_page->setText(QString::number(cur));
}

void MainWindow::update_total_page(int total) {
    toolbar->total_page->setText(QString::number(total));
}

void MainWindow::move_prev() {
    file_manager->prev_page();
}

void MainWindow::move_next() {
    file_manager->next_page();
}

QUrl MainWindow::get_url() {
    if (dialog) {
        qDebug() << "Dialog already open";
        return QUrl();
    }

    dialog = new QFileDialog(this, tr("Open File"), QStandardPaths::writableLocation(QStandardPaths::DownloadLocation));
    dialog->setAcceptMode(QFileDialog::AcceptOpen);
    dialog->setMimeTypeFilters({"application/pdf"});

    QUrl url;
    if (dialog->exec() == QFileDialog::Accepted) {
        url = dialog->selectedUrls().constFirst();
    }

    dialog->deleteLater();
    dialog = nullptr;

    return url;
}
