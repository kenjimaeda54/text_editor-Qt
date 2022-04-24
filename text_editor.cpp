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





void Text_Editor::on_action_new_file_triggered()
{
    filenameCurrent = "";
    ui->text_edit->clear();
    ui->text_edit->setFocus();
}


void Text_Editor::on_action_open_triggered()
{
    QString nameFile = QFileDialog::getOpenFileName(this,"Open file",QDir::homePath(),allFiles);
    QFile file(nameFile);
    filenameCurrent = nameFile; // garantir que ao abrir vai possuir nessa variavael um nome de arquivo,ele sera comparado ao longo da app

    if(!file.open(QFile::ReadOnly | QFile::Text) && file.exists()){//arquivos que tem permissao de leitura r e existem

         QMessageBox::warning(this,"Can`t open file","Probaly this file need permission");
         return;
    }

    QTextStream stream(&file);
    QString text= stream.readAll();
    ui->text_edit->setText(text);
    file.close();// e importante fechar  o file para o editor conseguir seguir em frente,enquanto  o file estiver aberto ele nao consegue
}



void Text_Editor::on_action_save_with_triggered()
{

     QString nameFile = QFileDialog::getSaveFileName(this,"Save file",QDir::homePath(),allFiles);
     QFile file(nameFile);
     filenameCurrent = nameFile;

     if(filenameCurrent.isEmpty()) return;

     if(!file.open(QFile::WriteOnly | QFile::Text)){//arquivos que nao tem permissao de escrita

         QMessageBox::warning(this,"Can`t save file","Probraly need permission");
         return;
     };
     QTextStream stream(&file);
     QString text = ui->text_edit->toPlainText();
     stream << text << "\n";

     file.flush();
     file.close();// e importante fechar  o file para o editor conseguir seguir em frente,enquanto  o file estiver aberto ele nao consegue

}


void Text_Editor::on_action_save_triggered()
{


      //nos estamos comparando o filenameCurrent para realizar a logica,ideal quando clicar em salvar  verifcar se e arquivo novo ou nao
      //entao preico colocar  variavel filnemaeCurrente vazio em new file,porque e um arquivo novo,assim  vai entrar em action_save_with
     QFile file(filenameCurrent);



     if(filenameCurrent.isEmpty()  || !file.exists()) {
         on_action_save_with_triggered();
         return;

     }


     if(!file.open(QFile::WriteOnly | QFile::Text)){
         QMessageBox::warning(this,"Error save","Probaly need permission save");
         return;
     }


     if(file.exists()){//trabalha de forma assincrona por isso preciso colocar file.exists()
         QTextStream stream(&file);
         QString text = ui->text_edit->toPlainText(); //estou pegando o arquivo que esta nosso editor e eviando para o computador dele
         stream << text << "\n";

         file.flush();
         file.close();

     }

}

void Text_Editor::on_action_copy_triggered()
{
    ui->text_edit->copy();
}


void Text_Editor::on_action_paste_triggered()
{
    ui->text_edit->paste();
}


void Text_Editor::on_action_cut_triggered()
{
    ui->text_edit->cut();
}


void Text_Editor::on_action_redo_triggered()
{
    ui->text_edit->redo();
}


void Text_Editor::on_action_undo_triggered()
{
    ui->text_edit->undo();
}


void Text_Editor::on_action_color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black,this,"Chosse your color");
    if(color.isValid()){

        ui->text_edit->setTextColor(color);
    }
}


void Text_Editor::on_action_font_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);

    if(ok) {

        ui->text_edit->setFont(font);

    }

}


void Text_Editor::on_action_background_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black,this,"Chosse your background");
    if(color.isValid()){

        ui->text_edit->setTextBackgroundColor(color);
    }
}


void Text_Editor::on_action_about_triggered()
{
    QMessageBox::about(this,"About program","This progam was created terminal root couse");
}


void Text_Editor::on_actionPrint_triggered()
{
     QPrinter printer;
     QPrintDialog printerDialog;


     if(printerDialog.exec() == QDialog::Rejected){
         QMessageBox::critical(this,"Can`t print","Error on pint");
         return;
     }

     ui->text_edit->print(&printer);
}

