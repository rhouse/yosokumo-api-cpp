// Role.h

#ifndef ROLE_H
#define ROLE_H

#include <bitset>

#include "Privilege.h"

namespace Yosokumo
{
/**
 * A set of privileges granted to a particular user for a particular study. 
 * One of the privileges granted to a study creator is the authority to 
 * create new roles on the study for other enrolled users.  In this way, 
 * the study creator can allow others to load data, get predictions, view 
 * study statistics, or even themselves grant privileges on the study to 
 * other users. Roles may be severely limited or provide full access and 
 * may be changed or revoked at any time.
 * <p>
 * When an enrolled user creates a study, he is authorized automatically to 
 * perform any action on that study. More precisely, when a study is created, 
 * the service simultaneously creates a role for the creator on the newly 
 * created study in which all privileges are set to <code>true</code>. 
 * <p>
 * A single user may have a role on many studies; conversely, many users may 
 * have a role on a single study. The list of studies on which a particular 
 * user has a role is called the catalog for that user. The list of users 
 * that have a role on a particular study is called the roster for that study.
 * <p>
 * A <code>Role</code> has these attributes:
 * <ul>
 * <li>a user identifier and a user name
 * <li>a study identifier and a study name
 * <li>a set of 13 booleans specifying which operations the user may perform
 *         on the study
 * </ul>
 *
 * @author  Roger House
 * @version 0.9
 */
class Role
{
    std::string userIdentifier;
    std::string userName;

    std::string studyIdentifier;
    std::string studyName;

    std::string roleLocation;

    std::bitset<Privilege::NUMBER_OF_PRIVILEGES> privilegeSet;

public:

    // Constructors

    /**
     * Initializes a newly created <code>Role</code> object with default 
     * attributes. 
     *
     */
    Role();

    /**
     * Initializes a newly created <code>Role</code> object with attributes 
     * specified by the input parameters.
     *
     * @param  userIdentifier  the user who has the role.
     * @param  studyIdentifier the study on which the user has the role.
     */
    Role(
        const std::string &userIdentifier, 
        const std::string &studyIdentifier);

    /**
     * Copy constructor - initializes a newly created <code>Role</code> 
     * object with a copy of another <code>Role</code> object. 
     *
     * @param  rhs  the <code>Role</code> to make a copy of.
     */
    Role(const Role &rhs);


    /**
     * Destructor - destroy a <code>Role</code> object.
     */
    virtual ~Role();

    /**
     * Assignment operator - assign one <code>Role</code> to another.
     *
     * @param  rhs  the righthand side of the assignment.
     *
     * @return a reference to <code>this</code> Role.
     */
    Role& operator=(const Role& rhs);

    /**
     * Equality operator - compare two <code>Roles</code> for equality.
     *
     * @param  rhs  the righthand side of the equality.
     *
     * @return <code>true</code> if and only if <code>this</code> 
     *              <code>Roles</code> and the righthand side 
     *              <code>Roles</code> are identically equal.
     */
    bool operator==(const Role &rhs) const;

    /**
     * Inequality operator - compare two <code>Roles</code> for inequality.
     *
     * @param  rhs  the righthand side of the inequality.
     *
     * @return <code>true</code> if and only if <code>this</code> 
     *              <code>Roles</code> and the righthand side 
     *              <code>Roles</code> are not identically equal.
     */
    bool operator!=(const Role &rhs) const;


    // Setters and getters

    /**
     * Set the role location.
     *
     * @param  loc  the location to assign to this role.  May be null.
     *
     * @return this <code>Role</code>.
     */
    Role &setRoleLocation(const std::string &loc);

    /**
     * Return the role location.
     *
     * @return the location of this role.  May be null.
     */
    std::string getRoleLocation() const;

    /**
     * Set the user identifier.
     *
     * @param  userIdentifier  the user identifier to assign to this role.  
     *
     * @return this <code>Role</code>.
     */
    Role &setUserIdentifier(const std::string &userIdentifier);

    /**
     * Return the user identifier.
     *
     * @return the user identifier of this role.  May be null.
     */
    std::string getUserIdentifier() const;


    /**
     * Set the user name.
     *
     * @param  name  the user name to assign to this role.  May be null.
     *
     * @return this <code>Role</code>.
     */
    Role &setUserName(const std::string &name);

    /**
     * Return the user name.
     *
     * @return the name of the user of this role.  May be null.
     */
    std::string getUserName() const;


    /**
     * Set the study identifier.
     *
     * @param  studyIdentifier  the study identifier to assign to this role.  
     *
     * @return this <code>Role</code>.
     */
    Role &setStudyIdentifier(const std::string &studyIdentifier);

    /**
     * Return the study identifier.
     *
     * @return the study identifier of this role.  May be null.
     */
    std::string getStudyIdentifier() const;


    /**
     * Set the study name.
     *
     * @param  name  the name to assign to the study of this role.  
     *               May be null.
     *
     * @return this <code>Role</code>.
     */
    Role &setStudyName(const std::string &name);

    /**
     * Return the study name.
     *
     * @return the name of the study of this role.  May be null.
     */
    std::string getStudyName() const;


    // Get and set privileges

    /**
     * Add a privilege.  Grant a specific privilege.
     *
     * @param  privilege is the privilege to grant.
     *
     * @return this <code>Role</code>.
     */
    Role &addPrivilege(Privilege privilege);

    /**
     * Remove a privilege.  A specific privilege is removed.
     *
     * @param  privilege is the privilege to remove.
     *
     * @return this <code>Role</code>.
     */
    Role &removePrivilege(Privilege privilege);

    /**
     * Add all privileges.  All privileges are granted.
     *
     * @return this <code>Role</code>.
     */
    Role &addAllPrivileges();

    /**
     * Remove all privileges.
     *
     * @return this <code>Role</code>.
     */
    Role &removeAllPrivileges();

    /**
     * Get a specific privilege.
     *
     * @param  privilege is the privilege to check for.
     *
     * @return <code>true</code> if <code>privilege</code> is granted, 
     *         <code>false</code> otherwise.
     */
    bool getPrivilege(Privilege privilege) const;

    // Utility

    /**
     * Return a string representation of this <code>Role</code>.
     *
     * @return  the string representation of this <code>Role</code>.
     */
    std::string toString() const;

    /**
     * Return a string representation of this <code>Role</code>.
     *
     * @param  showAll specifies if internal data members should be shown.
     * @return  the string representation of this <code>Role</code>.
     */
    std::string toStringInternal(bool showAll) const;

};  // end class Role

}   // end namespace Yosokumo

#endif  // ROLE_H

// end Role.h
