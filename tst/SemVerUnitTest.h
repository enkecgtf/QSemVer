#pragma once

#include <QObject>

class SemVerUnitTest:
    public QObject
{
    Q_OBJECT

private slots:
    void testCreation();
    void testSet();
    void testComparison();
};
