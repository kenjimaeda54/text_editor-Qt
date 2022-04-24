#include "text_editor.h"
#include "ui_text_editor.h"

Text_Editor::Text_Editor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Text_Editor)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->text_edit); //centralizar o editor de texto no centro certinho

}

Text_Editor::~Text_Editor()
{
    delete ui;
}

void Text_Editor::on_action_file_triggered()
{
    ui->text_edit->clear();
    ui->text_edit->setFocus();
}

