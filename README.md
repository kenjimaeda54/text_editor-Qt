# Mini editor 
Apliquei conceitos do qt para criar um mini editor de texto

## Motivação
Praticar concetios de qt para criar  um mini editor, com recursos comuns  presentes no mercado


## Feature
- Os cabeçalhos foram todos definidos no arquivo .h
- Neste arquivo também criei as variáveis globais, uma responsável pelo nome do arquivo atual e uma string com filtro dos arquivos aceitáveis
- Para deixar componente text_editor centralizado da forma correta centralizei usando setCentralWidget
- Os tipos de arquivos aceitáveis e txt e md
- Para lidar com impressora usei a lib printsupport

``` c++
// .pro

QT       += core gui printsupport


//.h

Text_Editor(QWidget *parent = nullptr);
~Text_Editor();
 QString filenameCurrent = "";
 QString allFiles = "File text (*.txt);;Makdown  text(*.md)"; 


//=========================
//.cpp

Text_Editor::Text_Editor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Text_Editor)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->text_edit); //centralizar o editor de texto no centro certinho

}
```


##
- Para trabalhar com os diretórios usei seguinte raciocínio
- Primeiro capturo o nome diretório do arquivo, usando a classe QFileDialog
- Depois  passo para o QFile, esta classe vai receber o nome do diretório em um construtor, o nome do construtor pode ser qualquer um
- Para semântica usei o nome do construtor de file,  QFile file()
- Apos instanciado a classe  retribui a   variável filenameCurrent, sera essa variável usada para a lógica da aplicação
- Exemplo de uso da variável filenameCurrent: momento de salvar o arquivo primeiro  verificar se possui algo nessa variável
- Casso possua e para apenas subscrever conteúdo caso a contrário e para criar um arquivo, pois não existe o arquivo na máquina
- Apos instanciar o componente Qfile vou verificar se possuí as permissões
- Caso  possua, retribuo para a classe QFile o texto do arquivo(QFile::ReadOnly | QFile::Text)
- Precisa sempre realizar essa logica apos instanciar a classe QFile, sera nesse momento que consigo ter o conteúdo do arquivo
- Apos tudo pronto sera o momento de stream dos textos, com QTexteStream uso o  construtor com qualquer nome no caso usei nome semântico stream
- QTextStream stream(&file) => essa classe precisa de um ponteiro dos arquivos que desejamos transmitir os textos
- Apos isto leio todo o arquivo e seto text_edit
- Essencial sempre fechar o arquivo com o close, caso a contrário o text_edit vai ficar esperando ser fechado.



``` c++
void Text_Editor::on_action_open_triggered()
{
    QString nameFile = QFileDialog::getOpenFileName(this,"Open file",QDir::homePath(),allFiles);
    QFile file(nameFile);
    filenameCurrent = nameFile; 

    if(!file.open(QFile::ReadOnly | QFile::Text) && file.exists()){

         QMessageBox::warning(this,"Can`t open file","Probaly this file need permission");
         return;
    }

    QTextStream stream(&file);
    QString text= stream.readAll();
    ui->text_edit->setText(text);
    file.close();
}

```


## 
- Para salvar os arquivos princípio e idêntico da  abertura dos diretórios, diferenças são sucintas
- Uma das diferenças e no momento de salvar o  arquivo, preciso saber se e um arquivo existente na máquina ou arquivo novo
- Outra diferença e  no momento de fazer a stream do texto.
- Primeiro recebo o texto em uma string  reatribuída a partir do ui->text-editor->toPlainText();
- Essa função toPlainText(), e util para enviar todo arquivo escrito no editor
- Após receber o valor na variável envio para arquivo stream << text "\n"
- Barra n e para pular uma linha e não ficar grudado
- No momento de salvar possivelmente vai possuir algo na variável filenameCurrent, desde que o arquivo acabou de ser aberto de um diretorio
- Porque no momento de abrir  retribuo na função open  para variável
- Para garantir o bom funcionamento no if verifiquei se realmente existe algo nessa variável 
- O if com file.exists()  e importante para fazer stream do texto caso a contrário não conseguira, esse processo ocorre de forma assíncrona


``` c++


void Text_Editor::on_action_save_triggered()
{


     QFile file(filenameCurrent);



     if(filenameCurrent.isEmpty()  || !file.exists()) {
         on_action_save_with_triggered();
         return;

     }


     if(!file.open(QFile::WriteOnly | QFile::Text)){
         QMessageBox::warning(this,"Error save","Probaly need permission save");
         return;
     }


     if(file.exists()){
        QTextStream stream(&file);
         QString text = ui->text_edit->toPlainText(); 
         stream << text << "\n";

         file.flush();
         file.close();

     }

}


```
##
- Para salvar como e muito semelhante ao salvar, inclusive reaproveitei a função "salvar como" na função salvar
- Salvar  poderá esta relacionada diretamente a um arquivo novo criado, então preciso novamente pegar o diretório
- Nesse caso estou pegando o diretório que ele deseja salvar
- Se a variável filenameCurrent estiver vazio, porque pessoa não escolheu um arquivo existente então eu retorno e não deixo salvar
- Tanto "salvar" e "salvar como" preciso usar o file.open com as permissões, sem essa classe não conseguira pegar os valores 

``` c++

void Text_Editor::on_action_save_with_triggered()
{

     QString nameFile = QFileDialog::getSaveFileName(this,"Save file",QDir::homePath(),allFiles);
     QFile file(nameFile);
     filenameCurrent = nameFile;

     if(filenameCurrent.isEmpty()) return;

     if(!file.open(QFile::WriteOnly | QFile::Text)){

         QMessageBox::warning(this,"Can`t save file","Probraly need permission");
         return;
     };
     QTextStream stream(&file);
     QString text = ui->text_edit->toPlainText();
     stream << text << "\n";

     file.flush();
     file.close();

}
```

## 
- As outras feature, como copiar, colar,recortar existem funções prontas para serem aplicadas


``` c++


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

```







