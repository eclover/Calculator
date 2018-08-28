#ifndef QCALCULATORDEC_H
#define QCALCULATORDEC_H

#include <QString>
#include <QQueue>
#include <QStack>

class QCalculatorDec
{
public:
    QCalculatorDec();


    QString m_result;
    QString m_exp;

    bool isNumberOrDot(QChar c);
    bool isNumber(QString s);
    bool isSign(QString s);
    bool isLeft(QString s);
    bool isRight(QString s);
    bool isSymbol(QString s);
    bool isOperator(QString s);
    int priority(QString s);
    bool isMatch(const QQueue< QString>& exp );
    bool transform( QQueue<QString>&exp,QQueue<QString>& output);
    QQueue<QString> split(const QString& exp);

};

#endif // QCALCULATORDEC_H
