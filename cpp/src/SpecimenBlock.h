// SpecimenBlock.h

#ifndef SPECIMENBLOCK_H
#define SPECIMENBLOCK_H

#include "Block.h"
#include "Specimen.h"

#include <vector>
#include <list>
#include <iostream>
#include <sstream>

namespace Yosokumo
{

/**
 * A block of <code>Specimen*</code>.  Note that a <code>SpecimenBlock</code> 
 * does not own the <code>Specimens</code> pointed to by the elements of the 
 * <code>SpecimenBlock</code>.  This class never constructs or destroys a 
 * <code>Specimen</code>.
 */
class SpecimenBlock : public Block
{
    // At present the specimenSequence list is implemented as a
    // vector<Specimen*> because this implementation has O(1) performance 
    // for all three of "get", "add", and "next".  The latter is used to 
    // iterate over the list, and thus we do not want it to be expensive.  
    // The "add" method appends to the end of the list. --  Essentially, we 
    // want an array which can grow in size.  

    // The sequence is defined in Block.h

public:

    // Constructors

    /**
     * Initializes a newly created <code>SpecimenBlock</code> object with 
     * default attributes.
     */
    SpecimenBlock();

    /**
     * Initializes a newly created <code>SpecimenBlock</code> object with a 
     * study identifier.
     *
     * @param  id a study identifier for the block.
     */
    SpecimenBlock(std::string id);

    /**
     * Initializes a newly created <code>SpecimenBlock</code> object with the 
     * Specimen vector specified by the input parameters.  Note that the 
     * Specimens *must* not be deleted while the SpecimenBlock exists.
     *
     * @param  begin an iterator specifying the beginning of the Specimen 
     *             vector.
     * @param  end an iterator specifying the end of the Specimen 
     *             vector.
     */
    SpecimenBlock(
        std::vector<Specimen>::iterator begin, 
        std::vector<Specimen>::iterator end);

    /**
     * Initializes a newly created <code>SpecimenBlock</code> object with the 
     * Specimen list specified by the input parameters.  Note that the 
     * Specimens *must* not be deleted while the SpecimenBlock exists.
     *
     * @param  begin an iterator specifying the beginning of the Specimen 
     *             list.
     * @param  end an iterator specifying the end of the Specimen 
     *             list.
     */
    SpecimenBlock(
        std::list<Specimen>::iterator begin, 
        std::list<Specimen>::iterator end);

    /**
     * Initializes a newly created <code>SpecimenBlock</code> object with the 
     * study identifier and the Specimen vector specified by the input 
     * parameters.  Note that the Specimens *must* not be deleted while the 
     * SpecimenBlock exists.
     *
     * @param  id a study identifier for the block.
     * @param  begin an iterator specifying the beginning of the Specimen 
     *             vector.
     * @param  end an iterator specifying the end of the Specimen 
     *             vector.
     */
    SpecimenBlock(
        std::string id,
        std::vector<Specimen>::iterator begin, 
        std::vector<Specimen>::iterator end);

    /**
     * Initializes a newly created <code>SpecimenBlock</code> object with the 
     * study identifier and the Specimen list specified by the input 
     * parameters.  Note that the Specimens *must* not be deleted while the 
     * SpecimenBlock exists.
     *
     * @param  id a study identifier for the block.
     * @param  begin an iterator specifying the beginning of the Specimen 
     *             list.
     * @param  end an iterator specifying the end of the Specimen 
     *             list.
     */
    SpecimenBlock(
        std::string id,
        std::list<Specimen>::iterator begin, 
        std::list<Specimen>::iterator end);

    /**
     * Destructor.
     */
    virtual ~SpecimenBlock();

private:

    /**
     * Copy constructor - NOT IMPLEMENTED.
     */
    SpecimenBlock(const SpecimenBlock &rhs);

    /**
     * Assignment operator - NOT IMPLEMENTED.
     */
    SpecimenBlock& operator=(const SpecimenBlock& rhs);

public:

    // Access to the specimen sequence

    /**
     * Add a <code>Specimen*</code> to the block. The Specimen* parameter is 
     * appended to the end of the Specimen* sequence.
     *
     * @param   specimen  the <code>Specimen*</code> to add to the block.
     */
    void addSpecimen(Specimen* specimen);


    /**
     * Add a collection of <code>Specimen</code> to the block.  The 
     * <code>Specimen</code> in the vector specified by the parameters are 
     * appended to the end of the Specimen* sequence.  Note that the Specimens 
     * *must* not be deleted while the SpecimenBlock exists.
     *
     * @param  begin an iterator specifying the beginning of the Specimen 
     *             vector to add to the block.
     * @param  end an iterator specifying the end of the Specimen 
     *             vector to add to the block.
     *
     * @return true if and only if the Specimen* sequence changes.
     */
    bool addSpecimens(
        std::vector<Specimen>::iterator begin, 
        std::vector<Specimen>::iterator end);

    /**
     * Add a collection of <code>Specimen</code> to the block.  The 
     * <code>Specimen</code> in the list specified by the parameter are 
     * appended to the end of the Specimen* sequence.  Note that the Specimens 
     * *must* not be deleted while the SpecimenBlock exists.
     *
     * @param  begin an iterator specifying the beginning of the Specimen 
     *             list to add to the block.
     * @param  end an iterator specifying the end of the Specimen 
     *             list to add to the block.
     *
     * @return true if and only if the Specimen* sequence changes.
     */
    bool addSpecimens(
        std::list<Specimen>::iterator begin, 
        std::list<Specimen>::iterator end);

    /**
     * Remove Specimen* from the end of the block.  The specified number of 
     * specimens are removed from the end of the Specimen* sequence.
     *
     * @param   numSpecimensToRemove is the number of specimens to remove 
     *          from the end of the block.  If this value is zero, 
     *          no specimens are removed.  If this value exceeds the number 
     *          of specimens in the block, then all specimens are removed.
     *
     * @return true if and only if the sequence is changed.
     */
    bool removeSpecimens(uint64_t numSpecimensToRemove);


    /**
     * Return a Specimen* from the block.  This makes it possible to iterate 
     * over all specimens in the sequence like this:
     * <pre>
     *   for (int i = 0;  i < specimenBlock.size();  ++i)
     *   {
     *       Specimen *c = specimenBlock.getSpecimen(i)
     *       process specimen *c
     *   }
     * </pre>
     *
     * @param   index specifying the Specimen* of the 0-based block.
     *
     * @return  the <code>Specimen*</code> at the location specified by the index.
     */
    Specimen *getSpecimen(uint64_t index) const;


    /**
     * Remove all Specimen* from the block.  After a call of this method,
     * the sequence is empty, i.e., it contains no specimens.
     *
     */
    void clearSpecimens();

    /**
     * Return the number of specimens in the block.
     *
     * @return  the number of specimens in the block.
     */
    uint64_t size() const;

    /**
     * Return <code>true</code> if the block contains no specimens.
     *
     * @return <code>true</code> if the block contains no specimens.
     *         <code>false</code> otherwise.
     */
    bool isEmpty() const;


    // Utility

    /**
     * Return a string representation of this <code>SpecimenBlock</code>.
     *
     * @return  the string representation of this <code>SpecimenBlock</code>.
     */
    virtual std::string toString();

};  // end class SpecimenBlock

}   // end namespace Yosokumo


/** Output stream insertion operator.
 *
 * @param  os  the output stream.
 * @param  sb  the <code>SpecimenBlock</code> to insert in the stream.
 *
 * @return the output stream.
 */
std::ostream &operator<<(std::ostream &os, Yosokumo::SpecimenBlock &sb);

/** String stream insertion operator.
 *
 * @param  s   the string stream.
 * @param  sb  the <code>SpecimenBlock</code> to insert in the stream.
 *
 * @return the string stream.
 */
std::stringstream &operator<<(std::stringstream &s, Yosokumo::SpecimenBlock &sb);

#endif  // SPECIMENBLOCK_H

// end SpecimenBlock.h
