#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <QFile>
#include <vector>
#include <QDebug>
#include <tuple>
#include <QFileDialog>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void endStartScreen(bool screen);
    bool LoadDatabase(string filename);
    bool SaveDatabase(string filename, vector< tuple<QString, int, int, int> > records);
    void refreshList(int difficulty);
    void spacing(vector< tuple<QString, int, int, int> > diffrecord);

    vector< tuple<QString, int, int, int> > record;

    int actualDifficulty;
    QUrl urlPath;
    QString strPath = "empty";

private slots:
    void on_mediumButton_2_clicked();

    void on_easyButton_clicked();

    void on_hardButton_3_clicked();

    void on_extremeButton_4_clicked();

    void on_newGameButton_clicked();

    void on_sendButton_clicked();

    void on_closeButton_clicked();

    void on_actionadd_image_triggered();

    void on_actionRemover_Imagem_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
