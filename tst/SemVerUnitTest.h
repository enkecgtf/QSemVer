#ifndef SEMVER_UNITTEST_H_
#define SEMVER_UNITTEST_H_

#include <QObject>

class SemVerUnitTest:
    public QObject
{
    Q_OBJECT

private slots:

    void initTestCase() {};
    void cleanupTestCase() {};
    void testCreation();
    void testSet();
    void testComparison();
};

#endif /* SEMVER_UNITTEST_H_ */
