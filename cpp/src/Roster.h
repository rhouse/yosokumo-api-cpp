// Roster.h

#ifndef ROSTER_H
#define ROSTER_H

#include <string>
#include <map>

#include "Role.h"

namespace Yosokumo
{
/**
 * For each study, a list of users that have a role on the study.  A roster 
 * has these attributes:
 * <ul>
 * <li>an identifier and a name of the study to which the roster belongs
 * <li>a collection of all the roles associated with the study, indexed by 
 *     user identifier
 * </ul>
 *
 * @author  Roger House
 * @version 0.9
 */
class Roster
{
    std::string studyIdentifier;
    std::string studyName;

    std::string rosterLocation;

    // At present the roleCollection map is implemented as an STL map
    // because this implementation has O(ln n) performance for insert, remove,
    // and find, and O(1) for "next".  The latter is used to iterate 
    // over the map, and thus we do not want it to be expensive.  

    typedef std::map<std::string, Role> RoleMap;

    RoleMap roleCollection;

public:

    /**
     * For iterating over roles in a roster.
     */
    typedef RoleMap::iterator RoleIterator;
    typedef RoleMap::const_iterator RoleConstIterator;


    // Constructors

    /**
     * Initializes a newly created <code>Roster</code> object with default 
     * attributes.
     */
    Roster();

    /**
     * Initializes a newly created <code>Roster</code> object with attributes 
     * specified by the input parameters.
     *
     * @param  studyIdentifier  the identifier of the study the roster is for.
     * @param  studyName        the name of the study the roster is for.
     */
    Roster(const std::string &studyIdentifier, const std::string &studyName);


    // Equality operators

    /**
     * Equality operator - compare two <code>Roster</code> for equality.
     *
     * @param  rhs  the righthand side of the equality.
     *
     * @return <code>true</code> if and only if <code>this</code> 
     *              <code>Roster</code> and the righthand side 
     *              <code>Roster</code> are identically equal.
     */
    bool operator==(const Roster &rhs) const;

    /**
     * Inequality operator - compare two <code>Roster</code> for inequality.
     *
     * @param  rhs  the righthand side of the inequality.
     *
     * @return <code>true</code> if and only if <code>this</code> 
     *              <code>Roster</code> and the righthand side 
     *              <code>Roster</code> are not identically equal.
     */
    bool operator!=(const Roster &rhs) const;


    // Setters and getters

    /**
     * Set the study identifier.
     *
     * @param  id  the identifier of the study to which the roster belongs. 
     * May be null.
     */
    void setStudyIdentifier(const std::string &id);

    /**
     * Return the study identifier.
     *
     * @return the identifier of the study to which the roster belongs.
     * May be null.
     */
    std::string getStudyIdentifier() const;

    /**
     * Set the study name.
     *
     * @param  name  the name of the study to which the roster belongs.  
     * May be null.
     */
    void setStudyName(const std::string &name);

    /**
     * Return the study name.
     *
     * @return the name of the study to which the roster belongs.  May be null.
     */
    std::string getStudyName() const;

    /**
     * Set the roster location.
     *
     * @param  loc  the location to assign to this roster.  May be null.
     */
    void setRosterLocation(const std::string &loc);

    /**
     * Return the roster location.
     *
     * @return the location of this roster.  May be null.
     */
    std::string getRosterLocation() const;

    // Access to the role collection
    //
    // That a map is used to implement the role collection is hidden 
    // from the Roster client, as much as this makes sense.

    /**
     * Add a role to the roster.  In all cases the <code>Role</code> parameter
     * is added to the roster.  The return value distinguishes two 
     * possibilities.
     *
     * @param   newRole  the <code>Role</code> to add to the roster.
     * @param   oldRole  where to save an existing role with the same user
     *                     id as newRole.
     *
     * @return  <code>true</code> means there was no role already in the 
     *              roster with the same user identifier as newRole.  The
     *              contents of oldRole are unchanged.
     *          <code>false</code> means there was a role with the same user 
     *              identifier already in the roster, and it has been replaced
     *              by the newRole.  The old role is saved in oldRole.
     *          In both cases, newRole has been added to the roster.
     */
    bool addRole(const Role &newRole, Role &oldRole);

    /**
     * Add a role to the roster.  In all cases the <code>Role</code> parameter
     * is added to the roster.  The return value distinguishes two 
     * possibilities.
     *
     * @param   newRole  the <code>Role</code> to add to the roster.
     *
     * @return  <code>true</code> means there was no role already in the 
     *              roster with the same user identifier as newRole.
     *          <code>false</code> means there was a role with the same user 
     *              identifier already in the roster, and it has been replaced
     *              by the newRole.  The old role is no longer available.
     *          In both cases, newRole has been added to the roster.
     */
    bool addRole(const Role &newRole);

    /**
     * Remove a role from the roster.
     *
     * @param   userIdentifier the user identifier of the <code>Role</code> to 
     *              remove from the roster.
     * @return  <code>false</code> means there was no role in the roster with 
     *              the user identifier specified by the parameter; the roster 
     *              is left unchanged.
     *          <code>true</code> means that there was a role in the roster
     *              with the user identifier specified by the parameter; the 
     *              role has been removed from the roster.
     */
    bool removeRole(const std::string &userIdentifier);

    /**
     * Remove all roles from the roster.  After a call of this method,
     * the roster is empty, i.e., it contains no roles.
     *
     */
    void clearRoles();

    /**
     * Return a role from the roster.
     *
     * @param   userIdentifier the identifier of the <code>Role</code> to 
     *                          get from the roster.
     * @param   foundRole      where to place the found <code>Role</code>.
     *
     * @return  <code>false</code> means there is no role in the roster with 
     *              the user identifier specified by the parameter.  In this 
     *              case foundRole is unchanged.
     *          <code>true</code> means that there is a role in the roster
     *              with the user identifier specified by the parameter.
     *              foundRound contains the found role.
     */
    bool getRole(const std::string &userIdentifier, Role &foundRole) const;

    /**
     * Test if a role is in the roster.
     *
     * @param   userIdentifier the identifier of the <code>Role</code> to 
     *              test for.
     * @return  <code>false</code> means there is no role in the roster with 
     *              the user identifier specified by the parameter.
     *          <code>true</code> means that there is a role in the roster
     *              with the user identifier specified by the parameter.
     */
    bool containsRole(std::string userIdentifier) const;

    /**
     * Return the number of roles in the roster.
     *
     * @return  the number of roles in the roster.
     */
    int size() const;

    /**
     * Return <code>true</code> if the roster contains no roles.
     *
     * @return <code>true</code> if the roster contains no roles.
     *         <code>false</code> otherwise.
     */
    bool isEmpty() const;

    /**
     * Return an iterator referring to the first role in the roster.  This 
     * method can be used with the end() method to iterate over all roles in
     * a roster like this:
     * <pre>
     *   Roster roster; 
     *   ...
     *   RoleIterator iter;
     *
     *   for (iter = roster.begin();  iter != roster.end();  ++iter)
     *   {
     *       Role role = iter->second;
     *       process role 
     *   }
     * </pre>
     *
     * @return an iterator referring to the first role in the roster.
     */
    RoleIterator begin();
    RoleConstIterator begin() const;

    /**
     * Return an iterator referring to the past-the-end role in the roster.
     * See begin() for an example of how to use end() to iterate over roles.
     *
     * @return an iterator referring to the past-the-end role in the roster.
     */
    RoleIterator end();
    RoleConstIterator end() const;


    // Utility

    /**
     * Return a string representation of this <code>Roster</code>.  Note that 
     * for a role in the roster only the role identifier is represented 
     * as a string, not the entire role.
     *
     * @return  the string representation of this <code>Roster</code>.
     */
    std::string toString() const;

    /**
     * Return a string representation of this <code>Roster</code>.  Note that 
     * for a role in the roster only the role identifier is represented 
     * as a string, not the entire role.
     *
     * @param  showAll specifies if internal data members should be shown.
     * @return  the string representation of this <code>Roster</code>.
     */
    std::string toStringInternal(bool showAll) const;

};  // end class Roster

}   // end namespace Yosokumo

#endif  // ROSTER_H

// end Roster.h
