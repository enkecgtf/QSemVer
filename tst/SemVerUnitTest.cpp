#include "SemVerUnitTest.h"
#include "SemVer.h"

using SemanticVersioning::SemVersion;
using SemanticVersioning::bad_format_exception;

void SemVerUnitTest::testCreation()
{
    // call constructor with parameters 1 2 3 for a SemVersion instance
    SemVersion sv1(1, 2, 3);
    SemVersion sv2(1, 2, 3, "pre", "build");
    SemVersion sv3("1.2.3-pre+build");
}

void SemVerUnitTest::testSet()
{
    // call constructor for a SemVersion instance
    SemVersion sv(1, 2, 3);

    // check whether values are as expected
    Q_ASSERT(sv.getMajor() == 1);
    Q_ASSERT(sv.getMinor() == 2);
    Q_ASSERT(sv.getPatch() == 3);

    // test set method with 5 input parameters
    sv.set(1, 2, 3, "pre_release", "build");
    Q_ASSERT(sv.getMinor() == 2);
    Q_ASSERT(sv.getPatch() == 3);
    Q_ASSERT(sv.getPreRelease() == "pre_release");
    Q_ASSERT(sv.getBuild() == "build");

    // test set method with 1 string that contains 5 parameters
    sv.set("2.30.401-pre+build");
    Q_ASSERT(sv.getMajor() == 2);
    Q_ASSERT(sv.getMinor() == 30);
    Q_ASSERT(sv.getPatch() == 401);
    Q_ASSERT(sv.getPreRelease() == "pre");
    Q_ASSERT(sv.getBuild() == "build");

    // test set method with 1 string that contains 4 parameters I
    sv.set("2.3.4-test");
    Q_ASSERT(sv.getMajor() == 2);
    Q_ASSERT(sv.getMinor() == 3);
    Q_ASSERT(sv.getPatch() == 4);
    Q_ASSERT(sv.getPreRelease() == "test");
    Q_ASSERT(sv.getBuild() == "");

    // test set method with 1 string that contains 4 parameters II
    sv.set("2.3.4+test");
    Q_ASSERT(sv.getMajor() == 2);
    Q_ASSERT(sv.getMinor() == 3);
    Q_ASSERT(sv.getPatch() == 4);
    Q_ASSERT(sv.getPreRelease() == "");
    Q_ASSERT(sv.getBuild() == "test");

    // test set method with 1 string that contains only 3 parameters
    sv.set("2.3.4");
    Q_ASSERT(sv.getMajor() == 2);
    Q_ASSERT(sv.getMinor() == 3);
    Q_ASSERT(sv.getPatch() == 4);

    // test set method with 1 string when + and - are switched
    try
    {
        sv.set("2.3.4+pre-build");
    }
    catch (bad_format_exception&)
    {
        // this is what we expect
        Q_ASSERT(true);
    }
    catch (std::exception&)
    {
        // this shall never happen thus fail the test
        Q_ASSERT(false);
    }

    // test set method with 1 string when no second dot occurs
    try
    {
        sv.set("2.34+pre-build");
    }
    catch (bad_format_exception&)
    {
        // this is what we expect
        Q_ASSERT(true);
    }
    catch (std::exception&)
    {
        // this shall never happen thus fail the test
        Q_ASSERT(false);
    }
}

void SemVerUnitTest::testComparison()
{
    // call constructor for three different SemVersion instances
    SemVersion sv1(1, 2, 3);
    SemVersion sv2(1, 2, 4);
    SemVersion sv3(1, 2, 3);
    SemVersion sv4(2, 3, 4);
    SemVersion sv5(2, 4, 4);
    // set SemVersion instance 1 and 3 to :
    sv1.set("1.2.3-pre+build");
    sv3.set("1.2.3-pre+build");

    // for > operator only major, minor and patch are compared
    Q_ASSERT(sv1 == sv3);
    Q_ASSERT(sv2 > sv1);
    Q_ASSERT((sv1 > sv2) == FALSE);
    Q_ASSERT((sv1 > sv4) == FALSE);
    Q_ASSERT(sv4 > sv1);
    Q_ASSERT((sv4 > sv5) == FALSE);
    Q_ASSERT(sv5 > sv4);
}
