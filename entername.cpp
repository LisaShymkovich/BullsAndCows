#include "entername.h"

enterName::enterName(): QWidget(nullptr)
{
    setWindowTitle("Input");
    layout.addWidget(&label, 0, 0, 1, 2);
    layout.addWidget(&edit, 1, 0, 1, 2);
    layout.addWidget(&cancel, 2,0,1,1);
    layout.addWidget(&ok, 2,1,1,1);
  }
