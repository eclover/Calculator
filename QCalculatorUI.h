#ifndef _QCALCULATORUI_H_
#define _QCALCULATORUI_H_

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>


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

public slots:
    void ButtonClicked();
};

#endif
