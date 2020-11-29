#pragma once

#include <QObject>

class Number : public QObject
{
    Q_OBJECT

public:
    Number() = default;
    ~Number() = default;

signals:
    void numberChanged();

public slots:
    void increment()
    {
        ++number;
        emit numberChanged();
    }

    void decrement()
    {
        --number;
        emit numberChanged();
    }

    int getNumber() {return number;}
    void setNumber(int num) {number = num;}


private:
    std::atomic_int number {0};
};
