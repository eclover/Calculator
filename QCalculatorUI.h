#ifndef _QCALCULATORUI_H_
#define _QCALCULATORUI_H_

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "QCalculatorDec.h"


class QCalculatorUI : public QWidget
{
public:
    ~QCalculatorUI();
    static QCalculatorUI *NewInstance();
    void show();

public:
    QCalculatorUI();
    bool Construct();

    QLineEdit* m_edit;
    QPushButton* m_buttons[20];
    QCalculatorDec dec;
    bool calFlag ;

public slots:
    void ButtonClicked();
};

#endif
