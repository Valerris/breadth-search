#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QDir>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::parent(int *nambePredVersh, int versh, int predVersh)
{//nambePredVersh-содержит номера предыдущих вершин на пути от исходной вершины к i-ой;
    nambePredVersh[versh]=predVersh; //versh - текущая вершина; predVersh - предыдущая(родительская) вершина
}
void MainWindow::designing(int *path, int end)
{
    int ver = path[end];
    QString s;
    s += QString::number(end) + " ";
    do
    {
        s += QString::number(ver) + " ";
        ver = path[ver];
    } while (ver != -1);
    ui->label_4->setText(s);
}
void MainWindow::on_openFile_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"), QDir::currentPath(),"*.txt");
    if(filePath.isEmpty()) return;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in(&file);
    QString s; bool ok;
    //strNumbers = in.readAll();
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            in >> s;
            A[i][j] = s.toInt(&ok, 10);
        }
    }
    file.close();
    fClosed = true;
    ui->statusBar->showMessage("Файл был открыт");
}

void MainWindow::on_saveFile_triggered()
{
    if(!fClosed)
    {
        QString filePath = QFileDialog::getSaveFileName(this, QString::fromUtf8("Сохранить файл"), QDir::currentPath(), ".txt");
        if(filePath.isEmpty()) return;
        QFile file(filePath.append(".txt"));
        if(!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }
        file.close();
        ui->statusBar->showMessage("Файл сохранён");
    }
    else
    {
    QString filePath = QFileDialog::getSaveFileName(this, QString::fromUtf8("Сохранить файл"), QDir::currentPath(), ".txt");
    if(filePath.isEmpty()) return;
    QFile file(filePath.append(".txt"));
    bool ok;
    if(!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream out(&file);
    out << QString("Вершины ");
    for(int i = 0; i < SIZE; i++)
    {
        out << i << " ";
    }
    int ver = VON_PUNKT[end.toInt(&ok, 10)];
    out << QString("\r\nПуть: ") << end << " ";
    do
    {
        out << ver << " ";
        ver = VON_PUNKT[ver];
    } while (ver != -1);
    //designing(VON_PUNKT, end.toInt(&ok, 10));
    file.close();
    ui->statusBar->showMessage("Файл сохранён");
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->label_3->clear();
    ui->label_4->clear();
    bool ok;
    start = ui->lineEdit->text();
    end = ui->lineEdit_2->text();

    QRegExp e("\\d+");
    if(!fClosed)
        QMessageBox::information(0, "Предупреждение", "Откройте файл");
    else if(e.exactMatch(start) && e.exactMatch(end) && start.toInt(&ok, 10) >= 0 && start.toInt(&ok, 10) < SIZE && end.toInt(&ok, 10) >= 0 && end.toInt(&ok, 10) < SIZE)
    {
        if(start.toInt(&ok, 10) == end.toInt(&ok, 10))
            QMessageBox::information(0, "Предупреждение", "Вершины совпадают");
        else
        {
            //Начальная инициализация  массивов
            for(int i = 0; i < SIZE; i++)
            {
                besuchtet[i] = 0;
                 visited[i] = 0;
            }
            parent(VON_PUNKT, start.toInt(&ok, 10), -1);   //у стартовой вершины не может быть предыдущей
            front.push(start.toInt(&ok, 10)); //заносим стартувую вершину в очередь
            while(!front.empty())  //emply() принимает значение true, если очередь пуста
            {
                int ver = front.front();   //получаем ссылку на первый элемент очереди
                front.pop();
                for(int i = 0; i < SIZE; i++)
                {
                    if(besuchtet[i] == 0 && visited[i] == 0 && A[i][ver] == 1) //если вершина ещё не посещена, её нет в очереди и она смежна с текущей
                    {
                        front.push(i);     //добавляем вершину в очередь
                        visited[i] = 1;     //отмечаем как присутствующую
                        besuchtet[ver] = 1;   //и как посещённую
                        parent(VON_PUNKT, i, ver);
                    }
                }
            }
            QString str;
            for(int i = 0; i < SIZE; i++)
            {
                str += QString::number(i) + " ";
            }
            ui->label_3->setText(str);
            designing(VON_PUNKT, end.toInt(&ok, 10));
            ui->statusBar->showMessage("Поиск выполнен");
        }
    }
    else
        QMessageBox::information(0, "Предупреждение", "Неверный формат ввода");
}
