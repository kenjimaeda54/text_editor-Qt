#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QColorDialog>
#include <QColor>
#include <QFont>
#include <QFontDialog>
#include <QPrintDialog>
#include <QPrinter>

QT_BEGIN_NAMESPACE
namespace Ui { class Text_Editor; }
QT_END_NAMESPACE

class Text_Editor : public QMainWindow
{
    Q_OBJECT

public:
    Text_Editor(QWidget *parent = nullptr);
    ~Text_Editor();
    QString filenameCurrent = "";
    QString allFiles = "File text (*.txt);;Makdown  text(*.md)"; //tipos de arquivos permitidos, File text vai aparecer no canto inferior,importante e a extensao *.txt,*.md

private slots:




    void on_action_open_triggered();

    void on_action_new_file_triggered();

    void on_action_save_with_triggered();

    void on_action_save_triggered();

    void on_action_copy_triggered();

    void on_action_paste_triggered();

    void on_action_cut_triggered();

    void on_action_redo_triggered();

    void on_action_undo_triggered();

    void on_action_color_triggered();

    void on_action_font_triggered();

    void on_action_background_triggered();

    void on_action_about_triggered();

    void on_actionPrint_triggered();

private:
    Ui::Text_Editor *ui;
};
#endif // TEXT_EDITOR_H
