#include "main_window.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    // qSetMessagePattern("[%{type}] %{file} : %{line}");

    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
