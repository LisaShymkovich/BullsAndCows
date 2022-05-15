#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLineEdit>
#include <QSettings>
#include <QLabel>
#include <QMessageBox>
#include <QTextEdit>
#include "entername.h"
using namespace std;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void StartNewGame();
    void CheckClicked();
    void ShowRecords();
    void AddNewRecord();
    void CloseEnterName();

private:
    QGridLayout layout{this};
    QPushButton pbNewGame{"Новая игра", this};
    QLabel label{"Игра не начата", this};
    QPushButton pbRecords{"Рекорды", this};
    QLabel labelNumber{"Введите число", this};
    QLineEdit edit{this};
    QPushButton pbCheck{"Проверить!", this};
    QTableWidget twAttempts{0, 2, this};
    string correct{};
    QSettings settings{this};
    QTableWidget records{0, 2};
    enterName enter_name{};
};
#endif // MAINWINDOW_H
