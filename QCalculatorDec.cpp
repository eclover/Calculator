#include "QCalculatorDec.h"
#include <QDebug>

QCalculatorDec::QCalculatorDec()
{
    QQueue<QString> queue = split("1+(2-3)*4+10/5.5");

    QQueue<QString> output ;
    transform(queue,output);
    for(int i=0;i<output.length();i++)
    {
        qDebug()<<output[i];
    }
}

//1.判断是否为数字或小数点
bool QCalculatorDec::isNumberOrDot(QChar c)
{
    return ((c >= '0') && (c <= '9')) || (c=='.');
}

bool QCalculatorDec::isNumber(QString s)
{
   bool ret = false;
   s.toDouble(&ret);
   return ret;
}

//2.是否为符号位
bool QCalculatorDec::isSign(QString s)
{
    return (s == "+") || (s == "-");
}

//3.是否为括号
bool QCalculatorDec::isLeft(QString s)
{
    return (s == "(");
}

bool QCalculatorDec::isRight(QString s)
{
    return (s == ")");
}

//4.是否为运算符
bool QCalculatorDec::isOperator(QString s)
{
    return (s == "+") || (s == "-") || (s == "*") || (s == "/");
}


bool QCalculatorDec::isSymbol(QString s)
{
    return isLeft(s) || isRight(s) || isOperator(s);
}

//5.分离
QQueue<QString>  QCalculatorDec::split(const QString &exp)
{
    QQueue<QString> ret;
    QString number = "";
    QString pre = "";
    for(int i=0;i<exp.length();i++)
    {
        if(isNumberOrDot(exp[i]))
        {
            number += exp[i];
            pre = exp[i];
        }
        else if(isSymbol(exp[i]))
        {
            if(!number.isEmpty())
            {
                ret.enqueue(number);
                number.clear();
            }
            if(isSign(exp[i]) && (isLeft(pre) || isOperator(pre) || pre == ""))
            {
                number += exp[i];
            }
            else
            {
                ret.enqueue(exp[i]);
            }

            pre = exp[i];
        }
    }
    if(!number.isEmpty())
    {
        ret.enqueue(number);
    }
    return ret;
}

//6.判断运算符优先级
int QCalculatorDec::priority(QString s)
{
    int ret = 0;
    if(s == "+" || s == "-")
    {
        ret = 1;
    }
    if(s == "*" || s == "/")
    {
        ret = 2;
    }
    return ret;
}

//7.判断括号是否匹配
bool QCalculatorDec::isMatch(const QQueue<QString> &exp)
{
    bool ret = true;
    QStack<QString> stack;
    for(int i=0;i<exp.length();i++)
    {
        if(isLeft(exp[i]))
        {
            stack.push(exp[i]);
        }
        else if(isRight(exp[i]))
        {
            if(stack.isEmpty() || !isLeft(stack.top()))
            {
                ret = false;
                break;
            }
            else
                stack.pop();
        }
    }
    if(!stack.isEmpty())
        ret = false;

    return ret;
}

//8.中缀转后缀
bool QCalculatorDec::transform( QQueue<QString>& exp, QQueue<QString>& output)
{
    bool ret = isMatch(exp);
    QStack<QString> stack;
    stack.clear();

    while(!exp.isEmpty() && ret)
    {
        QString e = exp.dequeue();
        if(isNumber(e))
            output.enqueue(e);
        else
        {
            if(stack.isEmpty())
                stack.push(e);
            else if(isOperator(e))
            {
                while( !stack.isEmpty() && priority(stack.top())>=priority(e))
                {
                    output.enqueue(stack.pop());

                }
                stack.push(e);
            }
            else if(isLeft(e))
            {
                stack.push(e);
            }
            else if(isRight(e))
            {
                while(!stack.isEmpty() && !isLeft(stack.top()))
                    output.enqueue(stack.pop());
                if(!stack.isEmpty())
                    stack.pop();
            }
            else
            {
                ret = false;
            }
        }

    }

    while(!stack.isEmpty())
    {
        output.enqueue(stack.pop());
    }
    if(!ret)
    {
        output.clear();
    }

    return ret;
}
