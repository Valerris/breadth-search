#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <queue>

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_openFile_triggered();
    void on_saveFile_triggered();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    static const int SIZE = 12;
    std::queue <int> front;   //объект класса очередь типа int
    QString start, end;   //объявление начальной и конечной вершины
    int A[SIZE][SIZE]; //матрица смежности
    int besuchtet[SIZE];  //массив,хранящий информацию о том была ли посещена вершина или нет
    int visited[SIZE];  //массив,хранящий информацию о том присутствует ли вершина в очереди или нет
    int VON_PUNKT[SIZE]; //массив,хранящий для каждой iой вершины номер предыдущей вершины на пути от исходной до iой
    char st[256];
    void parent(int *nambePredVersh, int versh, int predVersh);
    void designing(int *path, int end);
    bool fClosed = false;
};

#endif // MAINWINDOW_H
