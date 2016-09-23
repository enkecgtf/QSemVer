///////////////////////////////////////////////////////////
// SemVer.cpp
// Implementation of the class SemVersion
//
// Original version: https://github.com/KokaKiwi/semver-implementations
// Qt port by: Nicolai Enke, some adoptions by Soeren Sproessig
//
// The Artistic License 2.0
///////////////////////////////////////////////////////////

#include "SemVer.h"



using SemanticVersioning::SemVersion;



SemVersion::SemVersion(quint16 aMajorVersion, quint16 aMinorVersion, quint16 aPatchVersion)
{
    set(aMajorVersion, aMinorVersion, aPatchVersion);
}


SemVersion::SemVersion(quint16 aMajorVersion, quint16 aMinorVersion, quint16 aPatchVersion, QString const& aPreReleaseVersion, QString const& aBuildVersion)
{
    set(aMajorVersion, aMinorVersion, aPatchVersion, aPreReleaseVersion, aBuildVersion);
}


SemVersion::SemVersion(QString const& aVersionStringToParse)
{
    set(aVersionStringToParse);
}



bool SemVersion::operator==(SemVersion const& aVersionToCompareTo) const
{
    return (str() == aVersionToCompareTo.str());
}


bool SemVersion::operator>(SemVersion const& aVersionToCompareTo) const
{
    if (major > aVersionToCompareTo.major)
    {
        return true;
    }

    if (major < aVersionToCompareTo.major)
    {
        return false;
    }

    if (minor > aVersionToCompareTo.minor)
    {
        return true;
    }

    if (minor < aVersionToCompareTo.minor)
    {
        return false;
    }

    if (patch > aVersionToCompareTo.patch)
    {
        return true;
    }

    if (patch < aVersionToCompareTo.patch)
    {
        return false;
    }

    return false;
}



void SemVersion::set(quint16 aMajorVersion, quint16 aMinorVersion, quint16 aPatchVersion)
{
    major = aMajorVersion;
    minor = aMinorVersion;
    patch = aPatchVersion;
    pre_release = QString();
    build = QString();
}


void SemVersion::set(quint16 aMajorVersion, quint16 aMinorVersion, quint16 aPatchVersion, QString const& aPreReleaseVersion, QString const& aBuildVersion)
{
    set(aMajorVersion, aMinorVersion, aPatchVersion);
    pre_release = QString(aPreReleaseVersion);
    build = QString(aBuildVersion);
}


void SemVersion::set(QString const& aVersionStringToSet)
{
    auto firstDotPos = aVersionStringToSet.indexOf('.');
    auto secondDotPos = aVersionStringToSet.indexOf('.', firstDotPos + 1);
    auto dashPos = aVersionStringToSet.indexOf('-', secondDotPos + 1);
    auto plusPos = aVersionStringToSet.indexOf('+', secondDotPos + 1);

    if (secondDotPos == -1)
    {
        throw bad_format_exception();
    }

    bool ok;
    major = static_cast<quint16>(aVersionStringToSet.mid(0, firstDotPos).toUInt(&ok, 10));
    minor = static_cast<quint16>(aVersionStringToSet.mid(firstDotPos + 1, secondDotPos - firstDotPos - 1).toUInt(&ok, 10));

    if (dashPos == -1 && plusPos == -1)
    {
        patch = static_cast<quint16>(aVersionStringToSet.mid(secondDotPos + 1).toUInt(&ok, 10));
        pre_release = QString();
        build = QString();
    }
    else if (plusPos == -1)
    {
        patch = static_cast<quint16>(aVersionStringToSet.mid(secondDotPos + 1, dashPos - secondDotPos - 1).toUInt(&ok, 10));
        pre_release = QString(aVersionStringToSet.mid(dashPos + 1));
        build = QString();
    }
    else if (dashPos == -1)
    {
        patch = static_cast<quint16>(aVersionStringToSet.mid(secondDotPos + 1, plusPos - secondDotPos - 1).toUInt(&ok, 10));
        pre_release = QString();
        build = QString(aVersionStringToSet.mid(plusPos + 1));
    }
    else
    {
        if (plusPos < dashPos)
        {
            throw bad_format_exception();
        }

        patch = static_cast<quint16>(aVersionStringToSet.mid(secondDotPos + 1, dashPos - secondDotPos - 1).toUInt(&ok, 10));
        pre_release = QString(aVersionStringToSet.mid(dashPos + 1, plusPos - dashPos - 1));
        build = QString(aVersionStringToSet.mid(plusPos + 1));
    }
}



QString SemVersion::str() const
{
    QString stream = QStringLiteral("%1.%2.%3").arg(major).arg(minor).arg(patch);

    if (pre_release.length() > 0)
    {
        stream.append('-').append(pre_release);
    }

    if (build.length() > 0)
    {
        stream.append('+').append(build);
    }

    return stream;
}
