///////////////////////////////////////////////////////////
// SemVer.cpp
// Implementation of the class SemVersion
//
// Original version: https://github.com/KokaKiwi/semver-implementations
// Qt port by: Nicolai Enke
//
// The Artistic License 2.0
///////////////////////////////////////////////////////////

#include "SemVer.h"



using SemanticVersioning::SemVersion;



SemVersion::SemVersion(quint16 aMajorVersion, quint16 aMinorVersion, quint16 aPatchVersion)
{
    this->set(aMajorVersion, aMinorVersion, aPatchVersion);
}


SemVersion::SemVersion(quint16 aMajorVersion, quint16 aMinorVersion, quint16 aPatchVersion, QString const& aPreReleaseVersion, QString const& aBuildVersion)
{
    this->set(aMajorVersion, aMinorVersion, aPatchVersion, aPreReleaseVersion, aBuildVersion);
}


SemVersion::SemVersion(QString const& aVersionStringToParse)
{
    this->set(aVersionStringToParse);
}



bool SemVersion::operator==(SemVersion const& aVersionToCompareTo) const
{
    return (this->str() == aVersionToCompareTo.str());
}


bool SemVersion::operator>(SemVersion const& aVersionToCompareTo) const
{
    if (this->major > aVersionToCompareTo.major)
    {
        return true;
    }

    if (this->major < aVersionToCompareTo.major)
    {
        return false;
    }

    if (this->minor > aVersionToCompareTo.minor)
    {
        return true;
    }

    if (this->minor < aVersionToCompareTo.minor)
    {
        return false;
    }

    if (this->patch > aVersionToCompareTo.patch)
    {
        return true;
    }

    if (this->patch < aVersionToCompareTo.patch)
    {
        return false;
    }

    return false;
}



void SemVersion::set(quint16 aMajorVersion, quint16 aMinorVersion, quint16 aPatchVersion)
{
    this->major = aMajorVersion;
    this->minor = aMinorVersion;
    this->patch = aPatchVersion;
    this->pre_release = QString();
    this->build = QString();
}


void SemVersion::set(quint16 aMajorVersion, quint16 aMinorVersion, quint16 aPatchVersion, QString const& aPreReleaseVersion, QString const& aBuildVersion)
{
    this->set(aMajorVersion, aMinorVersion, aPatchVersion);
    this->pre_release = QString(aPreReleaseVersion);
    this->build = QString(aBuildVersion);
}


void SemVersion::set(QString const& aVersionStringToSet)
{
    unsigned int firstDotPos;
    unsigned int secondDotPos;
    unsigned int dashPos;
    unsigned int plusPos;
    bool ok;

    firstDotPos = aVersionStringToSet.indexOf('.');
    secondDotPos = aVersionStringToSet.indexOf('.', firstDotPos + 1);
    dashPos = aVersionStringToSet.indexOf('-', secondDotPos + 1);
    plusPos = aVersionStringToSet.indexOf('+', secondDotPos + 1);

    if (secondDotPos == -1)
    {
        throw bad_format_exception();
    }

    this->major = static_cast<quint16>(aVersionStringToSet.mid(0, firstDotPos).toUInt(&ok, 10));
    this->minor = static_cast<quint16>(aVersionStringToSet.mid(firstDotPos + 1, secondDotPos - firstDotPos - 1).toUInt(&ok, 10));

    if (dashPos == -1 && plusPos == -1)
    {
        this->patch = static_cast<quint16>(aVersionStringToSet.mid(secondDotPos + 1).toUInt(&ok, 10));
        this->pre_release = QString();
        this->build = QString();
    }
    else if (plusPos == -1)
    {
        this->patch = static_cast<quint16>(aVersionStringToSet.mid(secondDotPos + 1, dashPos - secondDotPos - 1).toUInt(&ok, 10));
        this->pre_release = QString(aVersionStringToSet.mid(dashPos + 1));
        this->build = QString();
    }
    else if (dashPos == -1)
    {
        this->patch = static_cast<quint16>(aVersionStringToSet.mid(secondDotPos + 1, plusPos - secondDotPos - 1).toUInt(&ok, 10));
        this->pre_release = QString();
        this->build = QString(aVersionStringToSet.mid(plusPos + 1));
    }
    else
    {
        if (plusPos < dashPos)
        {
            throw bad_format_exception();
        }

        this->patch = static_cast<quint16>(aVersionStringToSet.mid(secondDotPos + 1, dashPos - secondDotPos - 1).toUInt(&ok, 10));
        this->pre_release = QString(aVersionStringToSet.mid(dashPos + 1, plusPos - dashPos - 1));
        this->build = QString(aVersionStringToSet.mid(plusPos + 1));
    }
}



QString SemVersion::str() const
{
    QString stream;

    stream.append(this->major).append('.').append(this->minor).append('.').append(this->patch);

    if (this->pre_release.length() > 0)
    {
        stream.append('-').append(this->pre_release);
    }

    if (this->build.length() > 0)
    {
        stream.append('+').append(this->build);
    }

    return stream;
}
