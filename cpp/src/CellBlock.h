// CellBlock.h

#ifndef CELLBLOCK_H
#define CELLBLOCK_H

#include "Block.h"
#include "Cell.h"

#include <vector>
#include <list>
#include <iostream>
#include <sstream>

namespace Yosokumo
{

/**
 * Represents a block of <code>Cells</code>.
 */
class CellBlock : public Block
{
    // At present the cellSequence list is implemented as a 
    // vector<Cell> because this implementation has O(1) performance 
    // for all three of "get", "add", and "next".  The latter is used to 
    // iterate over the list, and thus we do not want it to be expensive.  
    // The "add" method appends to the end of the list. --  Essentially, we 
    // want an array which can grow in size.  

    // The sequence is defined in Block.h

public:

    // Constructors and destructor

    /**
     * Initializes a newly created <code>CellBlock</code> object with 
     * default attributes.
     */
    CellBlock();

    /**
     * Initializes a newly created <code>CellBlock</code> object with 
     * a study identifier.
     *
     * @param  id a study identifier for the block.
     */
    CellBlock(std::string id);

    /**
     * Initializes a newly created <code>CellBlock</code> object with the 
     * cell vector specified by the input parameters.
     *
     * @param  begin an iterator specifying the beginning of the cell 
     *             vector.
     * @param  end an iterator specifying the end of the cell 
     *             vector.
     */
    CellBlock(
        std::vector<Cell>::iterator begin, 
        std::vector<Cell>::iterator end);

    /**
     * Initializes a newly created <code>CellBlock</code> object with the 
     * cell list specified by the input parameters.
     *
     * @param  begin an iterator specifying the beginning of the cell list.
     * @param  end an iterator specifying the end of the cell list.
     */
    CellBlock(
        std::list<Cell>::iterator begin, 
        std::list<Cell>::iterator end);

    /**
     * Initializes a newly created <code>CellBlock</code> object with the 
     * study identifier and the cell vector specified by the input 
     * parameters.
     *
     * @param  id a study identifier for the block.
     * @param  begin an iterator specifying the beginning of the cell 
     *             vector.
     * @param  end an iterator specifying the end of the cell 
     *             vector.
     */
    CellBlock(
        std::string id, 
        std::vector<Cell>::iterator begin, 
        std::vector<Cell>::iterator end);

    /**
     * Initializes a newly created <code>CellBlock</code> object with the 
     * study identifier and the cell list specified by the input 
     * parameters.
     *
     * @param  id a study identifier for the block.
     * @param  begin an iterator specifying the beginning of the cell list.
     * @param  end an iterator specifying the end of the cell list.
     */
    CellBlock(
        std::string id, 
        std::list<Cell>::iterator begin, 
        std::list<Cell>::iterator end);

    /**
     * Destructor.
     */
    virtual ~CellBlock();

private:

    /**
     * Copy constructor - NOT IMPLEMENTED.
     */
    CellBlock(const CellBlock &rhs);

    /**
     * Assignment operator - NOT IMPLEMENTED.
     */
    CellBlock& operator=(const CellBlock& rhs);

public:

    // Access to the cell sequence

    /**
     * Add a <code>Cell</code> to the block. The cell parameter is 
     * appended to the end of the cell sequence.
     *
     * @param   cell  the <code>Cell</code> to add to the block.
     */
    void addCell(const Cell &cell);

    /**
     * Add a collection of <code>Cells</code> to the block.  The 
     * <code>Cells</code> in the vector specified by the parameters 
     * are appended to the end of the cell sequence.  
     *
     * @param  begin an iterator specifying the beginning of the cell 
     *             vector to add to the block.
     * @param  end an iterator specifying the end of the cell 
     *             vector to add to the block.
     *
     * @return true if and only if the cell sequence changes.
     */
    bool addCells(
        std::vector<Cell>::iterator begin, 
        std::vector<Cell>::iterator end);

    /**
     * Add a collection of <code>Cells</code> to the block.  The 
     * <code>Cells</code> in the list specified by the parameters 
     * are appended to the end of the cell sequence.  
     *
     * @param  begin an iterator specifying the beginning of the cell 
     *             list to add to the block.
     * @param  end an iterator specifying the end of the cell 
     *             list to add to the block.
     *
     * @return true if and only if the cell sequence changes.
     */
    bool addCells(
        std::list<Cell>::iterator begin, 
        std::list<Cell>::iterator end);

    /**
     * Remove cells from the end of the block.  The specified number of 
     * cells are removed from the end of the cell sequence.
     *
     * @param   numCellsToRemove is the number of cells to remove 
     *          from the end of the block.  If this value is zero no
     *          cells are removed.  If this value exceeds the number 
     *          of cells in the block, then all cells are removed.
     *
     * @return true if and only if the sequence is changed.
     */
    bool removeCells(uint64_t numCellsToRemove);


    /**
     * Return a cell from the block.  This makes it possible to iterate 
     * over all cells in the sequence like this:
     * <pre>
     *   for (uint64_t i = 0;  i < cellSequence.size();  ++i)
     *   {
     *       Cell c = cellSequence.getCell(i)
     *       process cell c
     *   }
     * </pre>
     *
     * @param   index specifying the cell of the 0-based block.
     *
     * @return  the <code>Cell</code> at the location specified by the 
     *              index.
     */
    Cell getCell(uint64_t index) const;


    /**
     * Remove all cells from the block.  After a call of this method,
     * the sequence is empty, i.e., it contains no cells.
     *
     */
    void clearCells();

    /**
     * Return the number of cells in the block.
     *
     * @return  the number of cells in the block.
     */
    uint64_t size() const;

    /**
     * Return <code>true</code> if the block contains no cells.
     *
     * @return <code>true</code> if the block contains no cells.
     *         <code>false</code> otherwise.
     */
    bool isEmpty() const;


    // Utility

    /**
     * Return a string representation of this <code>CellBlock</code>.
     *
     * @return  the string representation of this <code>CellBlock</code>.
     */
    virtual std::string toString();

};  // end class CellBlock

}   // end namespace Yosokumo

/** Output stream insertion operator.
 *
 * @param  os  the output stream.
 * @param  p   the <code>CellBlock</code> to insert in the stream.
 *
 * @return the output stream.
 */
std::ostream &operator<<(std::ostream &os, Yosokumo::CellBlock &p);


/** String stream insertion operator.
 *
 * @param  s   the string stream.
 * @param  p   the <code>CellBlock</code> to insert in the stream.
 *
 * @return the string stream.
 */
std::stringstream &operator<<(std::stringstream &s, Yosokumo::CellBlock &p);

#endif  // CELLBLOCK_H

// end CellBlock.h
