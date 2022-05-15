#ifndef ENTERNAME_H
#define ENTERNAME_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

class enterName : public QWidget
{
 public:
  enterName();
  QLabel label{"Name: ", this};
  QPushButton ok{"Ok", this};
  QPushButton cancel{"Cancel", this};
  QLineEdit edit{this};
  QGridLayout layout{this};
};

#endif // ENTERNAME_H
