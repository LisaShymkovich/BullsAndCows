#include <set>
#include <random>
#include "mainwindow.h"
using namespace std;

MainWindow::MainWindow() : QWidget(nullptr)
{
    layout.addWidget(&pbNewGame, 0, 0, 1, 1);
    layout.addWidget(&label, 0, 1, 1, 1);
    layout.addWidget(&pbRecords, 0, 2, 1, 1);
    layout.addWidget(&labelNumber, 1, 0, 1, 1);
    layout.addWidget(&edit, 1, 1, 1, 1);
    layout.addWidget(&pbCheck, 1, 2, 1, 1);
    layout.addWidget(&twAttempts, 2, 0, 4, 3);

  setMinimumSize(500, 500);
  twAttempts.resize(500, 500);
  twAttempts.setHorizontalHeaderLabels({"Число", "Результат"});
  twAttempts.setColumnWidth(0, twAttempts.width() / 2 -20);
  twAttempts.setColumnWidth(1, twAttempts.width() / 2 -20);

  records.setWindowTitle("Рекорды");
  for (int i = 1; i <= 10; i++)
  {
    if (!settings.contains(QString::number(i) + "_name"))
    {
      break;
    }
    records.insertRow(i - 1);
    auto model = records.model();
    model->setData(model->index(i - 1, 0),
                   settings.value(QString::number(i) + "_attempts"));
    model->setData(model->index(i - 1, 1),
                   settings.value(QString::number(i) + "_name"));
  }

  records.setHorizontalHeaderLabels({"Попыток", "Имя"});
  records.setMinimumSize(330, 330);
  records.resize(330, 330);
  records.setColumnWidth(0, records.width() / 2 -11);
  records.setColumnWidth(1, records.width() / 2 -11);
  pbCheck.setEnabled(false);
  edit.setValidator( new QIntValidator(0, 9999, this) );


  connect(&pbNewGame, SIGNAL(clicked()), this, SLOT(StartNewGame()));
  connect(&pbCheck, SIGNAL(clicked()), this, SLOT(CheckClicked()));
  connect(&pbRecords, SIGNAL(clicked()), this, SLOT(ShowRecords()));
  connect(&enter_name.ok, SIGNAL(clicked(bool)),
          this, SLOT(AddNewRecord()));
  connect(&enter_name.cancel, SIGNAL(clicked(bool)),
          this, SLOT(CloseEnterName()));
}


void MainWindow::StartNewGame()
{
  string str = "0123456789";
  shuffle(str.begin(), str.end(), mt19937(random_device()()));
  correct = str.substr(0, 4);
  pbCheck.setEnabled(true);
  enter_name.hide();
  while (twAttempts.rowCount() > 0)
  {
    twAttempts.removeRow(0);
  }
  edit.clear();
  label.setText("Угадайте число!");
}

void MainWindow::CheckClicked()
{
  string input = edit.text().toStdString();
  if (input.size() != 4)
  {
    QMessageBox::information(this, "Неправильное количество!", "Нужно ввести 4 цифры!");
    return;
  }

  set<char> unique{};
  for (char& ch: input)
  {
    unique.insert(ch);
  }
  if (unique.size() != 4)
  {
     QMessageBox::information(this, "Дубликаты!", "Цифры не должны совпадать!");
    return;
  }

  int bulls = 0;
  int cows = 0;
  unique.clear();
  for (int i = 0; i < correct.size(); i++)
  {
    unique.insert(correct[i]);
  }
  for (int i = 0; i < input.size(); i++)
  {
    if (input[i] == correct[i])
    {
      bulls++;
    }
    else if (unique.count(input[i]))
    {
      cows++;
    }
  }

  twAttempts.setColumnCount(2);
  twAttempts.insertRow(twAttempts.rowCount());
  QTableWidgetItem *newItem = new QTableWidgetItem(QString::fromStdString(input));
  twAttempts.setItem(twAttempts.rowCount()-1, 0, newItem);
  QString result = "Bulls: " + QString::number(bulls) + "; Cows: " + QString::number(cows);
  twAttempts.setItem(twAttempts.rowCount()-1, 1, new QTableWidgetItem(result));

  if (bulls == correct.size())
  {
    QMessageBox::information(this, "Победа!", "Победа!");
    label.setText("Вы угадали!");
    pbCheck.setEnabled(false);
    if (records.rowCount() != 10 ||twAttempts.rowCount() < records.item(9, 0)->text().toInt())
    {
      enter_name.edit.clear();
      enter_name.show();
    }
  }
  else
  {
    label.setText("Не угадали, попробуйте ещё...");
  }
}


void MainWindow::ShowRecords()
{
  records.show();
}


void MainWindow::AddNewRecord()
{
  int i = records.rowCount() - 1;
  for (; i >= 0; i--)
  {
    if (records.item(i, 0)->text().toInt() <= twAttempts.rowCount())
    {
      break;
    }
  }
  records.insertRow(i + 1);
  auto model = records.model();
  model->setData(model->index(i + 1, 0),
                 QString::number(twAttempts.rowCount()));
  model->setData(model->index(i + 1, 1), enter_name.edit.text());

  if (records.rowCount() > 10)
  {
    records.removeRow(10);
  }

  for (int j = 0; j < records.rowCount(); j++)
  {
    settings.setValue(QString::number(j + 1) + "_attempts",
                       records.item(j, 0)->text());
    settings.setValue(QString::number(j + 1) + "_name",
                       records.item(j, 1)->text());
  }
  enter_name.hide();
}



void MainWindow::CloseEnterName()
{
  enter_name.hide();
}
