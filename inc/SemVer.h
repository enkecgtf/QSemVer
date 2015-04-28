///////////////////////////////////////////////////////////
// SemVer.h
// Declaration of the class SemVersion
//
// Original version: https://github.com/KokaKiwi/semver-implementations
// Qt port by: Nicolai Enke
//
// The Artistic License 2.0
///////////////////////////////////////////////////////////
#ifndef SEMVER_H_
#define SEMVER_H_

#include <QString>

// needed for exception error class
#include <stdexcept>


namespace SemanticVersioning
{
    /**
    * This class provides semantic versioning for Qt.
    * For further details see: http://semver.org/
    *
    * The class supports versions set by:
    *    - major, minor, patch each as quint16
    *    - major, minor, patch each as quint16 and pre_release, build as QString
    *    or as 1 string containing major, minor, patch, pre_release and build
    *
    *
    * @author Nicolai Enke
    * @version 1
    */
    class SemVersion
    {
    public:
        SemVersion(quint16 major, quint16 minor, quint16 patch);
        SemVersion(quint16 major, quint16 minor, quint16 patch, const QString& pre_release, const QString& build);
        explicit SemVersion(const QString& version);

        /// @name Semantic versioning implementation
        /// @{
        /**
        * Compares whether the given version equals the actual version
        *
        * @param version the version to compare to
        *
        * @retval true if comparison was successful
        * @retval false otherwise
        */
        bool operator==(const SemVersion& version) const;

        /**
        * Compares whether the given version is greater than the actual version
        *
        * @param version the version to compare to
        *
        * @retval true if comparison was successful
        * @retval false otherwise
        */
        bool operator>(const SemVersion& version) const;

        /**
        * Sets the version elements to given parameters.
        *
        * @param major the major version
        * @param minor the minor version
        * @param patch the patch version
        */
        void set(quint16 major, quint16 minor, quint16 patch);

        /**
        * Sets the version elements to given parameters.
        *
        * @param major the major version
        * @param minor the minor version
        * @param patch the patch version
        * @param pre_release the pre_release version
        * @param build the build version
        */
        void set(quint16 major, quint16 minor, quint16 patch, const QString& pre_release, const QString& build);

        /**
         * Sets the version elements to content of version.
         *
         * @param version the version string
         */
        void set(const QString& version);

        /**
        * Creates a version string with the current parameters.
        *
        * @return str the string that was build
        */
        QString str(void) const;
        /// @}

        /// @name Get version elements implementation
        /// @{
        /**
         * Get the major version
         */
        inline quint16 getMajor() const
        {
            return major;
        }

        /**
         * Get the minor version
         */
        inline quint16 getMinor() const
        {
            return minor;
        }

        /**
         * Get the patch version
         */
        inline quint16 getPatch() const
        {
            return patch;
        }

        /**
         * Get the pre-release version
         */
        inline QString getPreRelease() const
        {
            return pre_release;
        }

        /**
         * Get the build version
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
        bad_format_exception(): std::runtime_error("Bad version format.") {};
    };
}
#endif /* SEMVER_H_ */