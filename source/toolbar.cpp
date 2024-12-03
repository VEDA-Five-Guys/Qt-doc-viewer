#include <QVBoxLayout>
#include <QToolButton>

#include "toolbar.h"

ToolBar::ToolBar() {
    create_action();
    create_widgets();
}

void ToolBar::create_action() {
    prev_page = new QAction("▲");
    prev_page->setToolTip("Go to previous page");

    next_page = new QAction("▼");
    next_page->setToolTip("Go to next page");

    full_screen = new QAction("❖");
    full_screen->setToolTip("full screen");
}

void ToolBar::create_widgets() {
    current_page = new QLineEdit();
    current_page->setFixedSize(30, 30);
    current_page->setFrame(false);
    current_page->setAlignment(Qt::AlignCenter);

    total_page = new QLabel();
    total_page->setFixedSize(30, 30);
    total_page->setAlignment(Qt::AlignCenter);
}

QWidget* ToolBar::create_spacer(QWidget *toolbar) {
    QWidget *spacer = new QWidget(toolbar);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    return spacer;
}

QWidget* ToolBar::create_container(QWidget *toolbar) {
    QWidget *container = new QWidget(toolbar);
    return container;
}

void ToolBar::setup_layout(QWidget *container) {
    QVBoxLayout *layout = new QVBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(5);

    QToolButton *prev_button = new QToolButton();
    prev_button->setDefaultAction(prev_page);

    QToolButton *next_button = new QToolButton();
    next_button->setDefaultAction(next_page);

    QToolButton *full_screen_button = new QToolButton();
    full_screen_button->setDefaultAction(full_screen);
    
    layout->addWidget(current_page, 0, Qt::AlignRight);
    layout->addWidget(total_page, 0, Qt::AlignRight);
    layout->addWidget(prev_button, 0, Qt::AlignRight);
    layout->addWidget(next_button, 0, Qt::AlignRight);
    layout->addWidget(full_screen_button, 0, Qt::AlignRight);
}

void ToolBar::setup(QToolBar *toolbar) {
    QWidget *spacer = create_spacer(toolbar);
    toolbar->addWidget(spacer);

    QWidget *container = create_container(toolbar);
    setup_layout(container);
    toolbar->addWidget(container);
}
