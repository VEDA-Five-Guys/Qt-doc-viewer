#ifndef FILE_ITEM_WIDGET_H
#define FILE_ITEM_WIDGET_H

#include <QWidget>

namespace Ui {
class File_Item_Widget;
}

class File_Item_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit File_Item_Widget(const QString &name, QWidget *parent = nullptr);
    ~File_Item_Widget();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    Ui::File_Item_Widget *ui;

    void initialize(const QString &name);
    void set_connects(const QString &name);
    void set_elided_text(const QString &name);

signals:
    void remove(const QString &name);
    void width_changed();
};

#endif // FILE_ITEM_WIDGET_H
