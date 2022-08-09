#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"

extern Game * game;

bool ordenar(tuple<QString, int, int, int> a, tuple<QString, int, int, int> b)
{
    if(get<2>(a) < get<2>(b)){
        return true;
    }else if(get<2>(a) == get<2>(b) && get<1>(a) < get<1>(b)){
        return true;
    }
    return false;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    endStartScreen(false);

    QFont myFont("Courier",10);
    ui->listWidget->setFont(myFont);

    actualDifficulty = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::endStartScreen(bool screen)
{
    ui->titleLabel->setVisible(!screen);
    ui->easyButton->setVisible(!screen);
    ui->mediumButton_2->setVisible(!screen);
    ui->hardButton_3->setVisible(!screen);
    ui->extremeButton_4->setVisible(!screen);
    ui->lineNickname->setEnabled(screen);
    ui->sendButton->setEnabled(screen);
    ui->labelCongrats->setVisible(screen);
    ui->lineNickname->setVisible(screen);
    ui->sendButton->setVisible(screen);
    ui->closeButton->setVisible(screen);
    ui->newGameButton->setVisible(screen);
    ui->listWidget->setVisible(screen);
}

bool MainWindow::LoadDatabase(string filename)
{
    ifstream filereader(filename);
    if(!filereader.is_open()){
        cout << "didn't worked!" << endl;
        return false;
    }

    string tmpp;
    while(getline(filereader, tmpp))
    {
        tuple<QString, int, int, int> tmp;

        string name = tmpp;
        string moves;
        string segs;
        string diff;

        //getline(filereader, name);
        getline(filereader, moves);
        getline(filereader, segs);
        getline(filereader, diff);

//        qDebug() << QString::fromStdString(name) + " " + QString::fromStdString(moves) + " " + QString::fromStdString(segs) + " " + QString::fromStdString(diff);

        get<0>(tmp) = QString::fromStdString(name);
        get<1>(tmp) = stoi(moves);
        get<2>(tmp) = stoi(segs);
        get<3>(tmp) = stoi(diff);

        record.push_back(tmp);
        continue;
    }
    filereader.close();

    return true;
}

bool MainWindow::SaveDatabase(string filename, vector< tuple<QString, int, int, int> > records)
{
    ofstream filewriter(filename);
    if(!filewriter.is_open()){
        cout << "didn't worked!" << endl;
        return false;
    }

    vector <tuple<QString, int, int, int>> tmp;

    for(size_t i=0; i<records.size(); i++)
    {
        string pTmp = get<0>(records.at(i)).toStdString();
        filewriter << pTmp << endl;
        filewriter << get<1>(records.at(i)) << endl;
        filewriter << get<2>(records.at(i)) << endl;
        filewriter << get<3>(records.at(i)) << endl;

    }

    filewriter.close();
    return true;
}



void MainWindow::refreshList(int difficulty)
{
    ui->listWidget->clear();
    sort(record.begin(),record.end(),ordenar);
    vector< tuple<QString, int, int, int> > difRecord;

    for(size_t i = 0; i < record.size(); i++){
        if(difficulty == get<3>(record.at(i))){
            difRecord.push_back({get<0>(record.at(i)),get<1>(record.at(i)),get<2>(record.at(i)),difficulty});
        }
    }


        while(difRecord.size() > 10){
            difRecord.pop_back();
        }
        spacing(difRecord);
}

void MainWindow::spacing(vector< tuple<QString, int, int, int> > diffRecord)
{
    for (size_t i = 0; i < diffRecord.size(); i++) {
        QString itm;
        QString itmName = QString::number(i+1) + "."
                + get<0>(diffRecord.at(i)) + " ";

        QString itmMove = QString::number(get<1>(diffRecord.at(i))) + " ";
        QString itmSec = QString::number(get<2>(diffRecord.at(i))) + "s";

        if(itmName.count() + itmMove.count() + itmSec.count() < 28){
            for(size_t y = 5 - itmSec.count();y > 0; y--){
                itmMove += " ";
            }

            for(size_t y = 28 - itmName.count() - itmMove.count() - itmSec.count(); y > 0;y--){
                itmName += " ";
            }
        }
        itm = itmName + itmMove + itmSec;

        ui->listWidget->addItem(itm);
    };
}

void MainWindow::on_easyButton_clicked()
{
    if(strPath == "empty")
        strPath = ":/img/3x3 copy.jpg";
    actualDifficulty = 0;
    game = new Game(3,QPixmap(strPath));
    game->show();
    game->mixIt(300);
    endStartScreen(true);
    refreshList(actualDifficulty);
    if(strPath == ":/img/3x3 copy.jpg")
        strPath = "empty";
}


void MainWindow::on_mediumButton_2_clicked()
{
    if(strPath == "empty")
        strPath = ":/img/4x4 copy.jpg";
    actualDifficulty = 1;
    game = new Game(4,QPixmap(strPath));
    game->show();
    game->mixIt(4000);
    endStartScreen(true);
    refreshList(actualDifficulty);
    if(strPath == ":/img/4x4 copy.jpg")
        strPath = "empty";
}


void MainWindow::on_hardButton_3_clicked()
{
    if(strPath == "empty")
        strPath = ":/img/5x5 copy.jpg";
    actualDifficulty = 2;
    game = new Game(5,QPixmap(strPath));
    game->show();
    game->mixIt(5500);
    endStartScreen(true);
    refreshList(actualDifficulty);
    if(strPath == ":/img/5x5 copy.jpg")
        strPath = "empty";
}


void MainWindow::on_extremeButton_4_clicked()
{
    if(strPath == "empty")
        strPath = ":/img/10x10 copy.jpg";
    actualDifficulty = 3;
    game = new Game(10,QPixmap(strPath));
    game->show();
    game->mixIt(15000);
    endStartScreen(true);
    refreshList(actualDifficulty);
    if(strPath == ":/img/10x10 copy.jpg")
        strPath = "empty";
}


void MainWindow::on_newGameButton_clicked()
{
    endStartScreen(false);
}


void MainWindow::on_sendButton_clicked()
{
    tuple<QString, int, int, int> fooTmp;

    get<0>(fooTmp)= ui->lineNickname->text();
    get<1>(fooTmp)= game->moves->getMoves();
    get<2>(fooTmp)= game->myTimer->getTime();
    get<3>(fooTmp)= actualDifficulty;
    record.push_back(fooTmp);
    refreshList(actualDifficulty);

    ui->lineNickname->clear();
    ui->lineNickname->setEnabled(false);
    ui->sendButton->setEnabled(false);

    int countTmp = 0;

    for(unsigned int i = 0; i < record.size(); i++){
        if(actualDifficulty == get<3>(record.at(i))){
            if(fooTmp == record.at(i)){
                ui->listWidget->setCurrentRow(countTmp);
            }else{
            countTmp++;
            }
        }
    }

    SaveDatabase("C:/Users/Eduardo Panizzon/Desktop/Database.dat",record);
}


void MainWindow::on_closeButton_clicked()
{
    this->close();
}


void MainWindow::on_actionadd_image_triggered()
{
    urlPath = QFileDialog::getOpenFileUrl();

    strPath = urlPath.path().remove(0,1);
}


void MainWindow::on_actionRemover_Imagem_triggered()
{
    strPath = "empty";
}

