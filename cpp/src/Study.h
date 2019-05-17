// Study.h

#ifndef STUDY_H
#define STUDY_H

#include <stdint.h>
#include <string>

namespace Yosokumo
{

/**
 * A container for all resources associated with an analytic project.  A 
 * study has these attributes:
 * <ul>
 * <li>a study identifier and a study name
 * <li>a type, a status, and a visibility
 * <li>an identifier and a name of the user who owns the study 
 * <li>references to the table, model, panel, and roster for the study
 * </ul>
 *
 * @author  Roger House
 * @version 0.9
 */
class Study
{
public:

    /**
     * Indicates the quality of the predictands associated with subjects in 
     * the study.  The <code>Type</code> determines the type of the predictive 
     * model that will be built for the study.  The type attribute may not 
     * be changed after it has been set at study creation.  If the type 
     * attribute is not included in the posted study document, the default 
     * value is <code>NUMBER</code>.
     */
    enum Type
    {
        /**
         * the predictand is categorical and nominal.
         */
        CLASS,
        /**
         * the predictand is categorical, but also ordinal.
         */
        RANK,
        /**
         * the predictand is continuous and ratio.
         */
        NUMBER,
        /**
         * the predictand represents a probability given 
         * as a continuous value between zero and one inclusive. 
         */
        CHANCE
    };

    /**
     * Describes the state of the study, whether it is running, on standby, 
     * or stopped.  The <code>Status</code> can be changed at any time. If the 
     * status attribute is not included in the posted study document, the 
     * default status is <code>RUNNING</code>.
     */
    enum Status
    {
        /**
         * the service is accepting data into the study's table, analyzing 
         * the data to improve the study's predictive model and estimating 
         * predictands based on the model.
         */
        RUNNING,
        /**
         * the service is no longer accepting or analyzing data, but is still 
         * estimating predictands for the study based on the current model.
         */
        STANDBY,
        /**
         * the service is neither accepting nor analyzing data, and is not 
         * estimating predictands for the study. 
         */
        STOPPED
    };

    /**
     * Tells whether unidentified users can get estimated predictands from 
     * the model of the study.  The visibility of a study can be changed at 
     * any time.  If the visibility is not included in the posted study 
     * document, the default visibility is <code>PRIVATE</code>.
     */
    enum Visibility
    {
        /**
         * only users that are authenticated and authorized may make a Get 
         * Model request for the study.
         */
        PRIVATE,
        /**
         * any web client may make a Get Model request for the study.
         */
        PUBLIC
    };

private:

    std::string studyIdentifier;
    std::string studyName      ;
    std::string studyLocation  ;

    Type       type       ;
    Status     status     ;
    Visibility visibility ;

    std::string ownerIdentifier;
    std::string ownerName      ;

    std::string tableLocation  ;
    std::string modelLocation  ;
    std::string panelLocation  ;
    std::string rosterLocation ;

    // Panel info

    std::string nameControlLocation      ;
    std::string statusControlLocation    ;
    std::string visibilityControlLocation;

    uint64_t blockCount   ;
    uint64_t cellCount    ;
    uint64_t prospectCount;

    std::string creationTime      ;
    std::string latestBlockTime   ;
    std::string latestProspectTime;

public:

    // Constructors

    /**
     * Initializes a newly created <code>Study</code> object with default 
     * attributes.
     * <ul>
     * <li>identifier = ""
     * <li>name = ""
     * <li>type = NUMBER
     * <li>status = RUNNING
     * <li>visibility = PRIVATE
     * </ul>
     * The type of a Study cannot be changed after construction.
     */
    Study();

    /**
     * Initializes a newly created <code>Study</code> object with attributes 
     * specified by the input parameters.
     *
     * @param  studyName        the name of the study.
     * @param  type             the type of the study.
     * @param  status           the status of the study.
     * @param  visibility       the visibility of the study.
     *
     * The type of a Study cannot be changed after construction.
     */
    Study
    (
        const std::string &studyName, 
        Type               type, 
        Status             status,
        Visibility         visibility
    );

    /**
     * Copy constructor - initializes a newly created <code>Study</code> 
     * object with a copy of another <code>Study</code> object. 
     *
     * @param  rhs  the <code>Study</code> to make a copy of.
     */
    Study(const Study &rhs);


    /**
     * Destructor - destroy a <code>Study</code> object.
     */
    virtual ~Study();

    /**
     * Assignment operator - assign one <code>Study</code> to another.
     *
     * @param  rhs  the righthand side of the assignment.
     *
     * @return a reference to <code>this</code> Study.
     */
    Study& operator=(const Study& rhs);


    // Equality operators

    /**
     * Equality operator - compare two <code>Study</code> for equality.
     *
     * @param  rhs  the righthand side of the equality.
     *
     * @return <code>true</code> if and only if <code>this</code> 
     *              <code>Study</code> and the righthand side 
     *              <code>Study</code> are identically equal.
     */
    bool operator==(const Study &rhs) const;

    /**
     * Inequality operator - compare two <code>Study</code> for inequality.
     *
     * @param  rhs  the righthand side of the inequality.
     *
     * @return <code>true</code> if and only if <code>this</code> 
     *              <code>Study</code> and the righthand side 
     *              <code>Study</code> are not identically equal.
     */
    bool operator!=(const Study &rhs) const;


    /**
     * Initialize the data members of a study.
     */
    void initStudy();

    /**
     * Make a copy of a study.
     *
     * @param  t        the study to copy to   (destination).
     * @param  s        the study to copy from (source).
     * @return          a copy of s.
     */
    static void copyStudy(Study &t, const Study &s);

    // Setters and getters

    /**
     * Set the study identifier.
     *
     * @param  id  the identifier to assign to this study.  This is the 
     * unique identification of the study.  May be null.
     */
    void setStudyIdentifier(const std::string &id);

    /**
     * Return the study identifier.
     *
     * @return the identifier of this study, which is the unique 
     * identification of the study.  May be null.
     */
    std::string getStudyIdentifier() const;

    /**
     * Set the study name.
     *
     * @param  name  the name to assign to this study.  May be null.
     */
    void setStudyName(const std::string &name);

    /**
     * Return the study name.
     *
     * @return the name of this study.  May be null.
     */
    std::string getStudyName() const;

    /**
     * Set the study location.
     *
     * @param  loc  the location to assign to this study.  May be null.
     */
    void setStudyLocation(const std::string &loc);

    /**
     * Return the study location.
     *
     * @return the location of this study.  May be null.
     */
    std::string getStudyLocation() const;

    /**
     * Set the study type.
     *
     * @param  t  the type to assign to this study.
     */
    void setType(Type t);

    /**
     * Return the study type.
     *
     * @return the type of this study.
     */
    Type getType() const;

    /**
     * Set the study status.
     *
     * @param  s  the status to assign to this study.
     */
    void setStatus(Status s);

    /**
     * Return the study status.
     *
     * @return the status of this study.
     */
    Status getStatus() const;

    /**
     * Set the study visibility.
     *
     * @param  v  the type to assign to this study.
     */
    void setVisibility(Visibility v);

    /**
     * Return the study visibility.
     *
     * @return the visibility of this study.
     */
    Visibility getVisibility() const;

    /**
     * Set the owner identifier.
     *
     * @param  id  the identifier of the owner of this study.  May be null.
     */
    void setOwnerIdentifier(const std::string &id);

    /**
     * Return the owner identifier.
     *
     * @return the identifier of the owner of this study.  May be null.
     */
    std::string getOwnerIdentifier() const;

    /**
     * Set the owner name.
     *
     * @param  name  the name to assign to the owner of this study.  
     *     May be null.
     */
    void setOwnerName(const std::string &name);

    /**
     * Return the owner name.
     *
     * @return the name of the owner of this study.  May be null.
     */
    std::string getOwnerName() const;

    /**
     * Set the table location.
     *
     * @param  loc  the location of the table for this study.  May be null.
     */
    void setTableLocation(const std::string &loc);

    /**
     * Return the table location.
     *
     * @return the location of the table for this study.  May be null.
     */
    std::string getTableLocation() const;

    /**
     * Set the model location.
     *
     * @param  loc  the location of the model for this study.  May be null.
     */
    void setModelLocation(const std::string &loc);

    /**
     * Return the model location.
     *
     * @return the location of the model for this study.  May be null.
     */
    std::string getModelLocation() const;

    /**
     * Set the panel location.
     *
     * @param  loc  the location of the panel for this study.  May be null.
     */
    void setPanelLocation(const std::string &loc);

    /**
     * Return the panel location.
     *
     * @return the location of the panel for this study.  May be null.
     */
    std::string getPanelLocation() const;

    /**
     * Set the roster location.
     *
     * @param  loc  the location of the roster for this study.  May be null.
     */
    void setRosterLocation(const std::string &loc);

    /**
     * Return the roster location.
     *
     * @return the location of the roster for this study.  May be null.
     */
    std::string getRosterLocation() const;

    // Panel setters and getters

    /**
     * Set the name control location.
     *
     * @param  nameControlLocation  the URI to use to change the 
     *                              name of the study.
     */
    void setNameControlLocation(const std::string &nameControlLocation);

    /**
     * Return the name control location.
     *
     * @return the URI to use to change the name of the study.
     */
    std::string getNameControlLocation() const;


    /**
     * Set the status control location.
     *
     * @param  statusControlLocation  the URI to use to change the 
     *                                status of the study.
     */
    void setStatusControlLocation(const std::string &statusControlLocation);

    /**
     * Return the status control location.
     *
     * @return the URI to use to change the status of the study.
     */
    std::string getStatusControlLocation() const;


    /**
     * Set the visibility control location.
     *
     * @param  visibilityControlLocation  the URI to use to change the 
     *                                    visibility of the study.
     */
    void setVisibilityControlLocation(
        const std::string &visibilityControlLocation);

    /**
     * Return the visibility control location.
     *
     * @return the URI to use to change the visibility of the study.
     */
    std::string getVisibilityControlLocation() const;

    /**
     * Set the block count.
     *
     * @param  blockCount  the number of posted blocks that have been 
     *         accepted into the study table.
     */
    void setBlockCount(uint64_t blockCount);

    /**
     * Return the block count.
     *
     * @return the number of posted blocks that have been accepted into 
     *         the study table.
     */
    uint64_t getBlockCount() const;

    /**
     * Set the cell count.
     *
     * @param  cellCount  the total number of cells contained in the blocks 
     *         reported in the block count. 
     */
    void setCellCount(uint64_t cellCount);

    /**
     * Return the cell count.
     *
     * @return the total number of cells contained in the blocks reported in 
     *         the block count. 
     */
    uint64_t getCellCount() const;

    /**
     * Set the prospect count.
     *
     * @param  prospectCount  the total number of specimens contained in 
     *                        all Post Model and Get Model requests for 
     *                        the study.
     */
    void setProspectCount(uint64_t prospectCount);

    /**
     * Return the prospect count.
     *
     * @return the total number of specimens contained in all Post Model 
     *         and Get Model requests for the study.
     */
    uint64_t getProspectCount() const;

    /**
     * Set the creation time.
     *
     * @param  creationTime  the UTC time the study was created. 
     */
    void setCreationTime(const std::string &creationTime);

    /**
     * Return the creation time.
     *
     * @return the UTC time the study was created. 
     */
    std::string getCreationTime() const;

    /**
     * Set the latest block time.
     *
     * @param  latestBlockTime  the UTC time that the service accepted 
     *                          the most recent block into the study table. 
     */
    void setLatestBlockTime(const std::string &latestBlockTime);

    /**
     * Return the latest block time.
     *
     * @return the UTC time that the service accepted the most recent block 
     *         into the study table. 
     */
    std::string getLatestBlockTime() const;

    /**
     * Set the latest prospect time.
     *
     * @param  latestProspectTime  the UTC time of the most recent Post 
     *                             Model or Get Model request.
     */
    void setLatestProspectTime(const std::string &latestProspectTime);

    /**
     * Return the latest prospect time.
     *
     * @return the UTC time of the most recent Post Model or Get Model request.
     */
    std::string getLatestProspectTime() const;

    // Utility

    /**
     * Return a string representation of this <code>Study</code>.
     *
     * @return  the string representation of this <code>Study</code>.
     */
    std::string toString();

};  // end class Study

}   // end namespace Yosokumo

#endif  // STUDY_H

// end Study.h
