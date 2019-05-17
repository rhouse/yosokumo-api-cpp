// Specimen.h

#ifndef SPECIMEN_H
#define SPECIMEN_H

#include <string>
#include <vector>
#include <list>

#include "Cell.h"

namespace Yosokumo
{
/**
 * A row of values.  Other terminology that is sometimes used:  An 
 * observation, a record, an example, or an instance.  These are 
 * the primary characteristics of a <code>Specimen</code>: 
 *
 * <ul>
 * <li>a key - unsigned integer
 * <li>a status - active or inactive
 * <li>a weight - positive integer
 * <li>a predictand - value for this specimen
 * <li>a sequence of zero or more <code>Cells</code> containing the values 
 *          of the row
 * </ul>
 *
 * @author  Roger House
 * @version 0.9
 */
class Specimen
{
public: 
    /**
     * Provides a logical delete facility.  The default value is 
     * <code>ACTIVE</code>.
     */
    enum Status
    {
        /**
         * the specimen is active, i.e., it should be considered when 
         * constructing the model.
         */
        ACTIVE,
        /**
         * the specimen is inactive, i.e., it should not be considered when 
         * constructing the model.
         */
        INACTIVE
    };

private:

    uint64_t key;
    Status   status;
    uint64_t weight;
    Value    predictand;

    // At present the cellSequence list is implemented as a vector<Cell>
    // because this implementation has O(1) performance for all three of 
    // "get", "add", and "next".  The latter is used to iterate over the 
    // list, and thus we do not want it to be expensive.  The "add" method 
    // appends to the end of the list. --  Essentially, we want an array 
    // which can grow in size.  

    /**
     * A sequence of cells.
     */
    std::vector<Cell> cellSequence;

public:

    // Constructors

    /**
     * Initializes a newly created <code>Specimen</code> object with default 
     * values:
     * <ul>
     * <li>key - 0
     * <li>status - ACTIVE
     * <li>weight - 1
     * <li>predictand - EmptyValue
     * <li>cell sequence - empty
     * </ul>
     */
    Specimen();

    /**
     * Initializes a newly created <code>Specimen</code> object with key 
     * specified by the input parameter.  Other attributes are set to default 
     * values:
     * <ul>
     * <li>status - ACTIVE
     * <li>weight - 1
     * <li>predictand - EmptyValue
     * <li>cell sequence - empty
     * </ul>
     *
     * @param  key  the key of the specimen.
     */
    Specimen(uint64_t key);

    /**
     * Initializes a newly created <code>Specimen</code> object with key and 
     * cell sequence as specified by the input parameters.  Other attributes 
     * are set to default values:
     * <ul>
     * <li>status - ACTIVE
     * <li>weight - 1
     * <li>predictand - EmptyValue
     * </ul>
     *
     * @param  key      the key of the specimen.
     * @param  begin    an iterator specifying the beginning of a cell vector.
     * @param  end      an iterator specifying the end of a cell vector.
     */
    Specimen
    (
        uint64_t key, 
        std::vector<Cell>::iterator begin,
        std::vector<Cell>::iterator end
    );

    /**
     * Initializes a newly created <code>Specimen</code> object with key and 
     * cell sequence as specified by the input parameters.  Other attributes 
     * are set to default values:
     * <ul>
     * <li>status - ACTIVE
     * <li>weight - 1
     * <li>predictand - EmptyValue
     * </ul>
     *
     * @param  key      the key of the specimen.
     * @param  begin    an iterator specifying the beginning of a cell list.
     * @param  end      an iterator specifying the end of a cell list.
     */
    Specimen
    (
        uint64_t key, 
        std::list<Cell>::iterator begin,
        std::list<Cell>::iterator end
    );

    /**
     * Initializes a newly created <code>Specimen</code> object with key,
     * predictand, and cell sequence as specified by the input parameters.  
     * Other attributes are set to default values:
     * <ul>
     * <li>status - ACTIVE
     * <li>weight - 1
     * </ul>
     *
     * @param  key          the key of the specimen.
     * @param  predictand   the predictand of the specimen.
     * @param  begin    an iterator specifying the beginning of a cell vector.
     * @param  end      an iterator specifying the end of a cell vector.
     */
    Specimen
    (
        uint64_t    key,
        Value       predictand,
        std::vector<Cell>::iterator begin,
        std::vector<Cell>::iterator end
    );

    /**
     * Initializes a newly created <code>Specimen</code> object with key,
     * predictand, and cell sequence as specified by the input parameters.  
     * Other attributes are set to default values:
     * <ul>
     * <li>status - ACTIVE
     * <li>weight - 1
     * </ul>
     *
     * @param  key          the key of the specimen.
     * @param  predictand   the predictand of the specimen.
     * @param  begin    an iterator specifying the beginning of a cell list.
     * @param  end      an iterator specifying the end of a cell list.
     */
    Specimen
    (
        uint64_t    key,
        Value       predictand,
        std::list<Cell>::iterator begin,
        std::list<Cell>::iterator end
    );

    /**
     * Initializes a newly created <code>Specimen</code> object with 
     # attributes specified by the input parameters.
     *
     * @param  key          the key of the specimen.
     * @param  status       the status of the specimen.
     * @param  weight       the weight of the specimen.
     * @param  predictand   the predictand of the specimen.
     * @param  begin    an iterator specifying the beginning of a cell vector.
     * @param  end      an iterator specifying the end of a cell vector.
     */
    Specimen
    (
        uint64_t    key,
        Status      status,
        uint64_t    weight,
        Value       predictand,
        std::vector<Cell>::iterator begin,
        std::vector<Cell>::iterator end
    );

    /**
     * Initializes a newly created <code>Specimen</code> object with 
     # attributes specified by the input parameters.
     *
     * @param  key          the key of the specimen.
     * @param  status       the status of the specimen.
     * @param  weight       the weight of the specimen.
     * @param  predictand   the predictand of the specimen.
     * @param  begin    an iterator specifying the beginning of a cell list.
     * @param  end      an iterator specifying the end of a cell list.
     */
    Specimen
    (
        uint64_t    key,
        Status      status,
        uint64_t    weight,
        Value       predictand,
        std::list<Cell>::iterator begin,
        std::list<Cell>::iterator end
    );


    /**
     * Copy constructor - initializes a newly created <code>Specimen</code> 
     * object with a copy of another <code>Specimen</code> object. 
     *
     * @param  rhs  the <code>Specimen</code> to make a copy of.
     */
    Specimen(const Specimen &rhs);


    /**
     * Destructor - destroy a <code>Specimen</code> object.
     */
    virtual ~Specimen();


    /**
     * Assignment operator - assign one <code>Specimen</code> to another.
     *
     * @param  rhs  the righthand side of the assignment.
     *
     * @return a reference to <code>this</code> Specimen.
     */
    Specimen& operator=(const Specimen& rhs);


    // Setters and getters

    /**
     * Set the specimen key.
     *
     * @param  key  the key to assign to this specimen.  This is the 
     * unique identification of the specimen.  It must be positive.
     */
    void setSpecimenKey(uint64_t key);

    /**
     * Return the specimen key.
     *
     * @return the key of this specimen, which is the unique 
     * identification of the specimen.  
     */
    uint64_t getSpecimenKey() const;


    /**
     * Set the specimen status.
     *
     * @param  s  the status to assign to this specimen.
     */
    void setStatus(Status s);

    /**
     * Return the specimen status.
     *
     * @return the status of this specimen.
     */
    Status getStatus() const;


    /**
     * Set the specimen weight.
     *
     * @param  w  the weight to assign to this specimen.
     */
    void setWeight(uint64_t w);

    /**
     * Return the specimen weight.
     *
     * @return the weight of this specimen.
     */
    uint64_t getWeight() const;


    /**
     * Set the specimen predictand.
     *
     * @param  v  the predictand to assign to this specimen.
     */
    void setPredictand(Value v);

    /**
     * Return the specimen predictand.
     *
     * @return the predictand of this specimen.
     */
    Value getPredictand() const;


    // Access to the cell sequence

    /**
     * Add a <code>Cell</code> to the cell sequence.  The <code>Cell</code> 
     * parameter is appended to the end of the cell sequence.
     *
     * @param   cell  the <code>Cell</code> to add to the cell sequence.
     */
    void addCell(const Cell &cell);


    /**
     * Add a collection of <code>Cell</code> to the cell sequence.  The 
     * <code>Cells</code> in the vector specified by the parameters are 
     * appended to the end of the cell sequence.  
     *
     * @param  begin an iterator specifying the beginning of the cell 
     *             vector to add to the block.
     * @param  end an iterator specifying the end of the cell
     *             vector to add to the block.
     *
     * @return true if and only if the cell sequence changes.
     */
    bool addCells
    (
        std::vector<Cell>::iterator begin,
        std::vector<Cell>::iterator end
    );

    /**
     * Add a collection of <code>Cells</code> to the cell sequence.  The 
     * <code>Cells</code> in the list specified by the parameters are 
     * appended to the end of the cell sequence.  
     *
     * @param  begin an iterator specifying the beginning of the cell 
     *             list to add to the block.
     * @param  end an iterator specifying the end of the cell
     *             list to add to the block.
     *
     * @return true if and only if the cell sequence changes.
     */
    bool addCells
    (
        std::list<Cell>::iterator begin, 
        std::list<Cell>::iterator end
    );

    /**
     * Remove cells from the end of the sequence.  The specified number of 
     * cells are removed from the end of the cell sequence.
     *
     * @param   numCellsToRemove is the number of cells to remove from the 
     *          end of the sequence.  If this value is zero, no cells are
     *          removed.  If this value exceeds the number of cells in the
     *          sequence, then all cells are removed.
     *
     * @return true if and only if the sequence is changed.
     */
    bool removeCells(uint64_t numCellsToRemove);


    /**
     * Return a cell from the cell sequence.  This makes it possible to 
     * iterate over all cells in the sequence like this:
     * <pre>
     *   for (int i = 0;  i < cellSequence.size();  ++i)
     *   {
     *       Cell c = cellSequence.getCell(i)
     *       process cell c
     *   }
     * </pre>
     *
     * @param   index specifying which cell of the sequence to return. 0-based.
     *
     * @return  the <code>Cell</code> at the location specified by the index.
     */
    Cell getCell(int index) const;

    /**
     * Remove all cells from the sequence.  After a call of this method,
     * the sequence is empty, i.e., it contains no cells.
     *
     */
    void clearCells();

    /**
     * Return the number of cells in the sequence.
     *
     * @return  the number of cells in the sequence.
     */
    uint64_t size() const;

    /**
     * Return <code>true</code> if the sequence contains no cells.
     *
     * @return <code>true</code> if the sequence contains no cells.
     *         <code>false</code> otherwise.
     */
    bool isEmpty() const;


    // Utility

    /**
     * Return a string representation of this <code>Specimen</code>.
     *
     * @return  the string representation of this <code>Specimen</code>.
     */
    std::string toString() const;

};  // end class Specimen

}   // end namespace Yosokumo

#endif  // SPECIMEN_H

// end Specimen.h
