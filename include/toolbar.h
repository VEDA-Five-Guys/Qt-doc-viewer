#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QAction>
#include <QLineEdit>
#include <QLabel>

class ToolBar {
public:
    ToolBar();
    
    void setup(QToolBar*);

    QAction *prev_page;
    QAction *next_page;
    QAction *full_screen;
    
    QLineEdit *current_page;
    QLabel *total_page;

private:
    void create_action();
    void create_widgets();
    QWidget* create_spacer(QWidget*);
    QWidget* create_container(QWidget*);
    void setup_layout(QWidget*);
};

#endif // TOOLBAR_H
