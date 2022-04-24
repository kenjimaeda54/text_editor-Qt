#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Text_Editor; }
QT_END_NAMESPACE

class Text_Editor : public QMainWindow
{
    Q_OBJECT

public:
    Text_Editor(QWidget *parent = nullptr);
    ~Text_Editor();

private:
    Ui::Text_Editor *ui;
};
#endif // TEXT_EDITOR_H
