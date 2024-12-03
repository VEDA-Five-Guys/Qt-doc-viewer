#include "main_window.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    // qSetMessagePattern("[%{type}] %{file} : %{line}");

    QApplication app(argc, argv);

    Main_Window w;
    w.show();

    return app.exec();
}
