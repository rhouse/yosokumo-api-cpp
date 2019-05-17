// Catalog.h

#ifndef CATALOG_H
#define CATALOG_H

#include <string>
#include <map>

#include "Study.h"

namespace Yosokumo
{
/**
 * An index to all the studies on which a given user has a role.  A catalog 
 * has these attributes:
 * <ul>
 * <li>an identifier and a name of the user to whom the catalog belongs
 * <li>a collection of all the studies for which the user has a role, indexed
 *          by study identifier
 * </ul>
 *
 * @author  Roger House
 * @version 0.9
 */

class Catalog
{
    /**
     * Identifier of the user to whom the catalog belongs.
     */
    std::string userIdentifier;

    /**
     * User name of the user to whom the catalog belongs.
     */
    std::string userName;

    /**
     * URI of the catalog.
     */
    std::string catalogLocation;

    // At present the studyCollection map is implemented as an STL map
    // because this implementation has O(ln n) performance for insert, remove,
    // and find, and O(1) for "next".  The latter is used to iterate 
    // over the map, and thus we do not want it to be expensive.  

    typedef std::map<std::string, Study> StudyMap;

    /**
     * Collection of studies comprising the catalog.
     */
    StudyMap studyCollection;

public:

    /*
     * For iterating over studies in a catalog.
     */

    typedef StudyMap::iterator StudyIterator;
    typedef StudyMap::const_iterator StudyConstIterator;


    // Constructors

    /**
     * Initializes a newly created <code>Catalog</code> object with default 
     * attributes.
     * <ul>
     * <li>user identifier "ABCDEF0123456789"
     * <li>user name ""
     * </ul>
     */
    Catalog();

    /**
     * Initializes a newly created <code>Catalog</code> object with attributes 
     * specified by the input parameters.
     *
     * @param  userIdentifier  the unique identifier for the user.
     * @param  userName        the name of the user.
     */
    Catalog(
        const std::string &userIdentifier, const std::string &userName);

    /**
     * Copy constructor - initializes a newly created <code>Catalog</code> 
     * object with a copy of another <code>Catalog</code> object. 
     *
     * @param  rhs  the <code>Catalog</code> to make a copy of.
     */
    Catalog(const Catalog &rhs);

    /**
     * Destructor - destroy a <code>Catalog</code> object.
     */
    virtual ~Catalog();

    /**
     * Assignment operator - assign one <code>Catalog</code> to another.
     *
     * @param  rhs  the righthand side of the assignment.
     *
     * @return a reference to <code>this</code> Catalog.
     */
    Catalog &operator=(const Catalog& rhs);

    // Equality operators

    /**
     * Equality operator - compare two <code>Catalog</code> for equality.
     *
     * @param  rhs  the righthand side of the equality.
     *
     * @return <code>true</code> if and only if <code>this</code> 
     *              <code>Catalog</code> and the righthand side 
     *              <code>Catalog</code> are identically equal.
     */
    bool operator==(const Catalog &rhs) const;

    /**
     * Inequality operator - compare two <code>Catalog</code> for inequality.
     *
     * @param  rhs  the righthand side of the inequality.
     *
     * @return <code>true</code> if and only if <code>this</code> 
     *              <code>Catalog</code> and the righthand side 
     *              <code>Catalog</code> are not identically equal.
     */
    bool operator!=(const Catalog &rhs) const;

    // Copy catalog

    /**
     * Make a copy of a catalog.
     *
     * @param  t        the catalog to copy to   (destination).
     * @param  s        the catalog to copy from (source).
     * @return          a copy of s.
     */
    static void copyCatalog(Catalog &t, const Catalog &s);


    // Setters and getters

    /**
     * Set the user identifier.
     *
     * @param  id  the identifier of the user to whom the catalog belongs. 
     * May be null.
     */
    void setUserIdentifier(const std::string &id);

    /**
     * Return the user identifier.
     *
     * @return the identifier of the user to whom the catalog belongs.
     * May be null.
     */
    std::string getUserIdentifier() const;

    /**
     * Set the user name.
     *
     * @param  name  the name of the user to whom the catalog belongs.  
     * May be null.
     */
    void setUserName(const std::string &name);

    /**
     * Return the user name.
     *
     * @return the name of the user to whom the catalog belongs.  May be null.
     */
    std::string getUserName() const;

    /**
     * Set the catalog location.
     *
     * @param  loc  the location of this catalog.  May be null.
     */
    void setCatalogLocation(const std::string &loc);

    /**
     * Return the catalog location.
     *
     * @return the location of this catalog.  May be null.
     */
    std::string getCatalogLocation() const;

    // Access to the study collection
    //
    // That a map is used to implement the study collection is hidden 
    // from the Catalog client, as much as this makes sense.

   /**
     * Add a study to the catalog.  In all cases the <code>Study</code> 
     * parameter is added to the catalog.  The return value distinguishes two 
     * possibilities.
     *
     * @param   newStudy  the <code>Study</code> to add to the catalog.
     * @param   oldStudy  where to save an existing study with the same study
     *                     id as newStudy.
     *
     * @return  <code>true</code> means there was no study already in the 
     *              catalog with the same study identifier as newStudy.  The
     *              contents of oldStudy are unchanged.
     *          <code>false</code> means there was a study with the same study 
     *              identifier already in the catalog, and it has been replaced
     *              by the newStudy.  The old study is saved in oldStudy.
     *          In both cases, newStudy has been added to the catalog.
     */
    bool addStudy(const Study &newStudy, Study &oldStudy);

    /**
     * Add a study to the catalog.  In all cases the <code>Study</code> 
     * parameter is added to the catalog.  The return value distinguishes two 
     * possibilities.
     *
     * @param   newStudy  the <code>Study</code> to add to the catalog.
     *
     * @return  <code>true</code> means there was no study already in the 
     *              catalog with the same study identifier as newStudy.
     *          <code>false</code> means there was a study with the same study 
     *              identifier already in the catalog, and it has been replaced
     *              by the newStudy.  The old study is no longer available.
     *          In both cases, newStudy has been added to the catalog.
     */
     bool addStudy(const Study &newStudy);

    /**
     * Remove a study from the catalog.
     *
     * @param   studyIdentifier the study identifier of the <code>Study</code> 
     *              to remove from the catalog.
     * 
     * @return  <code>false</code> means there was no study in the catalog with 
     *              the study identifier specified by the parameter; the 
     *              catalog is left unchanged.
     *          <code>true</code> means that there was a study in the 
     *              catalog with the study identifier specified by the 
     *              parameter; the study has been removed from the catalog.
     */
    bool removeStudy(const std::string &studyIdentifier);

    /**
     * Remove all studies from the catalog.  After a call of this method,
     * the catalog is empty, i.e., it contains no studies.
     *
     */
    void clearStudies();

    /**
     * Return a study from the catalog.
     *
     * @param   studyIdentifier the identifier of the <code>Study</code> to 
     *                          get from the catalog.
     * @param   foundStudy      where to place the found <code>Study</code>.
     *
     * @return  <code>false</code> means there is no study in the catalog with 
     *              the study identifier specified by the parameter.  In this 
     *              case foundStudy is unchanged.
     *          <code>true</code> means that there is a study in the catalog
     *              with the study identifier specified by the parameter.
     *              foundRound contains the found study.
     */
    bool getStudy(const std::string &studyIdentifier, Study &foundStudy) const;

    /**
     * Test if a study is in the catalog.
     *
     * @param   studyIdentifier the identifier of the <code>Study</code> to 
     *                          test for.
     * @return  <code>false</code> means there is no study in the catalog with the 
     *              identifier specified by the parameter.
     *          <code>true</code> means that there is a study in the catalog
     *              with the identifier specified by the parameter.
     */
    bool containsStudy(const std::string &studyIdentifier) const;

    /**
     * Return the number of studies in the catalog.
     *
     * @return  the number of studies in the catalog.
     */
    int size() const;

    /**
     * Return <code>true</code> if the catalog contains no studies.
     *
     * @return <code>true</code> if the catalog contains no studies.
     *         <code>false</code> otherwise.
     */
    bool isEmpty() const;

    /**
     * Return an iterator referring to the first study in the catalog.  This 
     * method can be used with the end() method to iterate over all studys in
     * a catalog like this:
     * <pre>
     *   Catalog catalog; 
     *   ...
     *   StudyIterator iter;
     *
     *   for (iter = catalog.begin();  iter != catalog.end();  ++iter)
     *   {
     *       Study study = iter->second;
     *       process study 
     *   }
     * </pre>
     *
     * @return an iterator referring to the first study in the catalog.
     */
    StudyIterator begin();
    StudyConstIterator begin() const;

    /**
     * Return an iterator referring to the past-the-end study in the catalog.
     * See begin() for an example of how to use end() to iterate over studys.
     *
     * @return an iterator referring to the past-the-end study in the catalog.
     */
    StudyIterator end();
    StudyConstIterator end() const;

    // Utility

    /**
     * Return a string representation of this <code>Catalog</code>.  Note that 
     * for a study in the catalog only the study identifier and study name 
     * are represented as a string, not the entire study.
     *
     * @return  the string representation of this <code>Catalog</code>.
     */
    std::string toString() const;

    /**
     * Return a string representation of this <code>Catalog</code>.  Note that 
     * for a study in the catalog only the study identifier and study name 
     * are represented as a string, not the entire study.
     *
     * @param  showAll specifies if internal data members should be shown.
     * @return  the string representation of this <code>Catalog</code>.
     */
    std::string toStringInternal(bool showAll) const;

};  // end class Catalog

}   // end namespace Yosokumo

#endif  // CATALOG_H

// end Catalog.h
