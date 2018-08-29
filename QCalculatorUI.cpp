#include "QCalculatorUI.h"
#include <QDebug>

QCalculatorUI::QCalculatorUI() : QWidget(NULL,Qt::WindowCloseButtonHint)
{

}

bool QCalculatorUI::Construct()
{
    const char* btnText[20] =
    {
        "7", "8", "9", "+", "(",
        "4", "5", "6", "-", ")",
        "1", "2", "3", "*", "<-",
        "0", ".", "=", "/", "C",
    };

    bool ret = true;
    m_edit = new QLineEdit(this);
    if(m_edit != NULL)
    {
        m_edit->move(10, 10);
        m_edit->resize(240, 30);
        m_edit->setReadOnly(true);
        m_edit->setAlignment(Qt::AlignRight);
    }
    else
        ret = false;
    for(int i=0; i<4 && ret; i++)
    {
        for(int j=0; j<5 && ret; j++)
        {
            m_buttons[i*5 + j] = new QPushButton(this);
            if(m_buttons[i*5 + j] != NULL)
            {
                connect(m_buttons[i*5 + j],&QPushButton::clicked,this,&QCalculatorUI::ButtonClicked);
                m_buttons[i*5 + j]->resize(40, 40);
                m_buttons[i*5 + j]->move(10 + (10 + 40)*j, 50 + (10 + 40)*i);
                m_buttons[i*5 + j]->setText(btnText[i*5 + j]);
            }
            else
                ret = false;

        }
    }
    return ret;

}

QCalculatorUI::~QCalculatorUI()
{
}

QCalculatorUI* QCalculatorUI::NewInstance()
{
    QCalculatorUI *calulator = new QCalculatorUI();
    if(calulator == NULL || !calulator->Construct())
    {
        delete calulator;
        calulator = NULL;
    }
    return calulator;

}

void QCalculatorUI::show()
{
    QWidget::show();
    setFixedSize(width(), height());

}

void QCalculatorUI::ButtonClicked()
{
    QPushButton *button = (QPushButton*)sender();
    QString btnText = button->text();
    QString editText = m_edit->text();
    if(btnText == "=")
    {
        QString result = "";
        result = dec.expression(editText);
        m_edit->setText(dec.m_exp +"=" + dec.m_result);
    }
    else if(btnText == "C")
    {
        m_edit->setText("");
    }
    else if(btnText == "<-")
    {
        m_edit->setText(editText.left(editText.length()-1));
    }
    else
    {
        m_edit->setText(editText.append(button->text()));
    }

}
