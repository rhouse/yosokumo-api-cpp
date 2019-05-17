// Predictor.h

#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <stdint.h>
#include <sstream>
#include <ostream>
#include <string>

namespace Yosokumo
{

/**
 * A column of values, an independent variable.  Other terminology that is 
 * sometimes used:  An attribute or an input.  These are the primary 
 * characteristics of a <code>Predictor</code>: 
 * <ul>
 * <li>a name - unsigned positive integer
 * <li>a status - active or inactive
 * <li>a type - categorical or continuous
 * <li>a level - nominal, ordinal, interval, ratio
 * </ul>
 *
 * @author  Roger House
 * @version 0.9
 */
class Predictor
{
public:

    /**
     * Provides a logical delete facility.  The default value is 
     * <code>ACTIVE</code>.
     */
    enum Status
    {
        /**
         * the predictor is active, i.e., it should be considered when 
         * constructing the model.
         */
        ACTIVE,
        /**
         * the predictor is inactive, i.e., it should not be considered when 
         * constructing the model.
         */
        INACTIVE
    };


    /**
     * Describes the quality of the predictor and determines the statistical 
     * operations that can be performed on the feature.  The default value 
     * is <code>CONTINUOUS</code>.
     */
    enum Type
    {
        /**
         * the feature takes on discrete values.
         */
        CATEGORICAL,
        /**
         * the feature may take any real value.
         */
        CONTINUOUS
    };

    /**
     * Indicates the level of measurement for the feature. The default value 
     * is <code>RATIO</code>.
     */
    enum Level
    {
        /**
         * the values are names or labels for certain characteristics, 
         * without any implied order among them.
         */
        NOMINAL,
        /**
         * the feature takes values that represent the rank order of the 
         * specimen, but the distance between the values is not meaningful. 
         */
        ORDINAL,
        /**
         * the predictor values can be ranked and have a standard unit of 
         * measurement, but the zero value is arbitrary.
         */
        INTERVAL,
        /**
         * The values taken by the predictor have a standard unit of 
         * measurement, are rankable, and the zero value is non-arbitrary.
         */
        RATIO
    };

private:

    int64_t name;
    Status  status;
    Type    type;
    Level   level;

public:

    // Constructors, destructor, operator==

    /**
     * Default constructor - initializes a newly created <code>Predictor</code>
     *  object with default attributes.
     * <ul>
     * <li>name 1
     * <li>status ACTIVE
     * <li>type CONTINUOUS
     * <li>level RATIO
     * </ul>
     */
    Predictor();

    /**
     * Initializes a newly created <code>Predictor</code> object with default 
     * attributes.
     * <ul>
     * <li>status ACTIVE
     * <li>type CONTINUOUS
     * <li>level RATIO
     * </ul>
     *
     * @param  name        the name of the predictor.
     */
    Predictor(int64_t name);

    /**
     * Initializes a newly created <code>Predictor</code> object with attributes 
     * specified by the input parameters.
     *
     * @param  name    the name of the predictor.
     * @param  status  the status of the predictor.
     * @param  type    the type of the predictor.
     * @param  level   the level of the predictor.
     */
    Predictor
    (
        int64_t name,
        Status  status,
        Type    type, 
        Level   level
    );

    /**
     * Copy constructor - initializes a newly created <code>Predictor</code> 
     * object with a copy of another <code>Predictor</code> object. 
     *
     * @param  rhs  the <code>Predictor</code> to make a copy of.
     */
    Predictor(const Predictor &rhs);


    /**
     * Destructor - destroy a <code>Predictor</code> object.
     */
    virtual ~Predictor();

    /**
     * Assignment operator - assign one <code>Predictor</code> to another.
     *
     * @param  rhs  the righthand side of the assignment.
     *
     * @return a reference to <code>this</code> Predictor.
     */
    Predictor& operator=(const Predictor& rhs);

private:

    /**
     * Initializes a <code>Predictor</code> object with attributes 
     * specified by the input parameters.
     *
     * @param  name    the name of the predictor.
     * @param  status  the status of the predictor.
     * @param  type    the type of the predictor.
     * @param  level   the level of the predictor.
     */
    void initPredictor
    (
        int64_t name,
        Status  status,
        Type    type, 
        Level   level
    );

public:

    // Equality operators

    /**
     * Equality operator - compare two <code>Predictors</code> for equality.
     *
     * @param  rhs  the righthand side of the equality.
     *
     * @return <code>true</code> if and only if <code>this</code> 
     *              <code>Predictors</code> and the righthand side 
     *              <code>Predictors</code> are identically equal.
     */
    bool operator==(const Predictor &rhs) const;

    /**
     * Inequality operator - compare two <code>Predictors</code> for inequality.
     *
     * @param  rhs  the righthand side of the inequality.
     *
     * @return <code>true</code> if and only if <code>this</code> 
     *              <code>Predictors</code> and the righthand side 
     *              <code>Predictors</code> are not identically equal.
     */
    bool operator!=(const Predictor &rhs) const;

    // Setters and getters

    /**
     * Set the predictor name.
     *
     * @param  name  the name to assign to this predictor.  This is the 
     * unique identification of the predictor.  It must be positive.
     */
    void setPredictorName(int64_t name);

    /**
     * Return the predictor name.
     *
     * @return the name of this predictor, which is the unique 
     * identification of the predictor.  
     */
    int64_t getPredictorName() const;


    /**
     * Set the predictor status.
     *
     * @param  s  the status to assign to this predictor.
     */
    void setStatus(Status s);

    /**
     * Return the predictor status.
     *
     * @return the status of this predictor.
     */
    Status getStatus() const;


    /**
     * Set the predictor type.
     *
     * @param  t  the type to assign to this predictor.
     */
    void setType(Type t);

    /**
     * Return the predictor type.
     *
     * @return the type of this predictor.
     */
    Type getType() const;


    /**
     * Set the predictor level.
     *
     * @param  L  the level to assign to this predictor.
     */
    void setLevel(Level L);

    /**
     * Return the predictor level.
     *
     * @return the level of this predictor.
     */
    Level getLevel() const;


    // Utility

    /**
     * Return a string representation of this <code>Predictor</code>.
     *
     * @return  the string representation of this <code>Predictor</code>.
     */
    std::string toString();


};  // end class Predictor


    /** Output stream insertion operator.
     *
     * @param  os  the output stream.
     * @param  p   the <code>Predictor</code> to insert in the stream.
     *
     * @return the output stream.
     */
    std::ostream &operator<<(std::ostream &os, Predictor &p);


    /** String stream insertion operator.
     *
     * @param  s   the string stream.
     * @param  p   the <code>Predictor</code> to insert in the stream.
     *
     * @return the string stream.
     */
    std::stringstream &operator<<(std::stringstream &s, Predictor &p);

}   // end namespace Yosokumo

#endif  // PREDICTOR_H

// end Predictor.h
