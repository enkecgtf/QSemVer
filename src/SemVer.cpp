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


SemVersion::SemVersion(quint16 major, quint16 minor, quint16 patch)
{
    this->set(major, minor, patch);
}


SemVersion::SemVersion(quint16 major, quint16 minor, quint16 patch, QString const& pre_release, QString const& build)
{
    this->set(major, minor, patch, pre_release, build);
}


SemVersion::SemVersion(QString const& version)
{
    this->set(version);
}


bool SemVersion::operator==(SemVersion const& other) const
{
    return (this->str() == other.str());
}


bool SemVersion::operator>(SemVersion const& other) const
{
    if (this->major > other.major)
    {
        return true;
    }

    if (this->major < other.major)
    {
        return false;
    }

    if (this->minor > other.minor)
    {
        return true;
    }

    if (this->minor < other.minor)
    {
        return false;
    }

    if (this->patch > other.patch)
    {
        return true;
    }

    if (this->patch < other.patch)
    {
        return false;
    }

    return false;
}


void SemVersion::set(quint16 major, quint16 minor, quint16 patch)
{
    this->major = major;
    this->minor = minor;
    this->patch = patch;
    this->pre_release = QString();
    this->build = QString();
}


void SemVersion::set(quint16 major, quint16 minor, quint16 patch, QString const& pre_release, QString const& build)
{
    this->set(major, minor, patch);
    this->pre_release = QString(pre_release);
    this->build = QString(build);
}


void SemVersion::set(QString const& version)
{
    unsigned int firstDotPos;
    unsigned int secondDotPos;
    unsigned int dashPos;
    unsigned int plusPos;
    bool ok;

    firstDotPos = version.indexOf('.');
    secondDotPos = version.indexOf('.', firstDotPos + 1);
    dashPos = version.indexOf('-', secondDotPos + 1);
    plusPos = version.indexOf('+', secondDotPos + 1);

    if (secondDotPos == -1)
    {
        throw bad_format_exception();
    }

    this->major = static_cast<quint16>(version.mid(0, firstDotPos).toUInt(&ok, 10));
    this->minor = static_cast<quint16>(version.mid(firstDotPos + 1, secondDotPos - firstDotPos - 1).toUInt(&ok, 10));

    if (dashPos == -1 && plusPos == -1)
    {
        this->patch = static_cast<quint16>(version.mid(secondDotPos + 1).toUInt(&ok, 10));
        this->pre_release = QString();
        this->build = QString();
    }
    else if (plusPos == -1)
    {
        this->patch = static_cast<quint16>(version.mid(secondDotPos + 1, dashPos - secondDotPos - 1).toUInt(&ok, 10));
        this->pre_release = QString(version.mid(dashPos + 1));
        this->build = QString();
    }
    else if (dashPos == -1)
    {
        this->patch = static_cast<quint16>(version.mid(secondDotPos + 1, plusPos - secondDotPos - 1).toUInt(&ok, 10));
        this->pre_release = QString();
        this->build = QString(version.mid(plusPos + 1));
    }
    else
    {
        if (plusPos < dashPos)
        {
            throw bad_format_exception();
        }

        this->patch = static_cast<quint16>(version.mid(secondDotPos + 1, dashPos - secondDotPos - 1).toUInt(&ok, 10));
        this->pre_release = QString(version.mid(dashPos + 1, plusPos - dashPos - 1));
        this->build = QString(version.mid(plusPos + 1));
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
