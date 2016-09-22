#pragma once
///////////////////////////////////////////////////////////
// SemVer.h
// Declaration of the class SemVersion
//
// Original version: https://github.com/KokaKiwi/semver-implementations
// Qt port by: Nicolai Enke
//
// The Artistic License 2.0
///////////////////////////////////////////////////////////

#include <QString>

#include <stdexcept>



namespace SemanticVersioning
{
    /**
    * This class provides Semantic Versioning for Qt.
    * For further details see: http://semver.org/
    *
    * The class supports versions set by:
    *    - aMajorVersion, aMinorVersion, aPatchVersion each as quint16
    *    - aMajorVersion, aMinorVersion, aPatchVersion each as quint16 and aPreReleaseVersion, aBuildVersion as QString
    *    or as 1 string containing aMajorVersion, aMinorVersion, aPatchVersion, aPreReleaseVersion and aBuildVersion
    *
    * @author Nicolai Enke
    * @version 1
    */
    class SemVersion
    {
    public:
        /**
         * Creates a new Semantic Version from `aMajorVersion`, `aMinorVersion` and `aPatchVersion` values.
         *
         * @param aMajorVersion  major value to use
         * @param aMinorVersion  minor value to use
         * @param aPatchVersion  patch value to use
         */
        SemVersion(quint16 aMajorVersion, quint16 aMinorVersion, quint16 aPatchVersion);

        /**
         * Creates a new Semantic Version from `aMajorVersion`, `aMinorVersion` and `aPatchVersion` values AND `aPreReleaseVersion` and `aBuildVersion` info.
         *
         * @param aMajorVersion  major value to use
         * @param aMinorVersion  minor value to use
         * @param aPatchVersion  patch value to use
         * @param aPreReleaseVersion  pre-release value to use
         * @param aBuildVersion  build value to use
         */
        SemVersion(quint16 aMajorVersion, quint16 aMinorVersion, quint16 aPatchVersion, QString const& aPreReleaseVersion, QString const& aBuildVersion);

        /**
         * Creates a new Semantic Version by parsing the given `aVersionStringToParse` string.
         *
         * @param aVersionStringToParse  version string to parse
         */
        explicit SemVersion(QString const& aVersionStringToParse);

        /// @name Semantic Versioning implementation
        /// @{
        /**
        * Compares whether the given version equals the actual version
        *
        * @param aVersionToCompareTo the version to compare to
        *
        * @retval true if comparison was successful
        * @retval false otherwise
        */
        bool operator==(SemVersion const& aVersionToCompareTo) const;

        /**
        * Compares whether the given version is greater than the actual version
        *
        * @param aVersionToCompareTo the version to compare to
        *
        * @retval true if comparison was successful
        * @retval false otherwise
        */
        bool operator>(SemVersion const& aVersionToCompareTo) const;

        /**
         * Sets the version elements to given parameters.
         *
         * @param aMajorVersion the major version
         * @param aMinorVersion the minor version
         * @param aPatchVersion the patch version
         */
        void set(quint16 aMajorVersion, quint16 aMinorVersion, quint16 aPatchVersion);

        /**
         * Sets the version elements to given parameters.
         *
         * @param aMajorVersion the major version
         * @param aMinorVersion the minor version
         * @param aPatchVersion the patch version
         * @param aPreReleaseVersion the pre-release version
         * @param aBuildVersion the build version
         */
        void set(quint16 aMajorVersion, quint16 aMinorVersion, quint16 aPatchVersion, QString const& aPreReleaseVersion, QString const& aBuildVersion);

        /**
         * Sets the version elements to content of version.
         *
         * @param aVersionStringToSet the version string
         */
        void set(QString const& aVersionStringToSet);

        /**
         * Creates a version string with the current parameters.
         *
         * @return the string representation of the current parameters
         */
        QString str() const;
        /// @}

        /// @name Get version elements implementation
        /// @{
        /**
         * Queries the major version
         *
         * @return major version
         */
        inline quint16 getMajor() const
        {
            return major;
        }

        /**
         * Queries the minor version
         *
         * @return minor version
         */
        inline quint16 getMinor() const
        {
            return minor;
        }

        /**
         * Queries the patch version
         *
         * @return patch version
         */
        inline quint16 getPatch() const
        {
            return patch;
        }

        /**
         * Queries the pre-release version
         *
         * @return pre-release version
         */
        inline QString getPreRelease() const
        {
            return pre_release;
        }

        /**
         * Queries the build version
         *
         * @return build version
         */
        inline QString getBuild() const
        {
            return build;
        }
        /// @}

    private:
        /// Major version of current version
        quint16 major;

        /// Minor version of current version
        quint16 minor;

        /// Patch version of current version
        quint16 patch;

        /// Pre-release version of current version
        QString pre_release;

        /// Build version of current version
        QString build;
    };

    /**
     * Helper class for exception error format
     */
    class bad_format_exception: public std::runtime_error
    {
    public:
        bad_format_exception(): std::runtime_error("Bad version format.") {}
    };
}
