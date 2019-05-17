// PredictorBlock.h

#ifndef PREDICTORBLOCK_H
#define PREDICTORBLOCK_H

#include "Block.h"
#include "Predictor.h"

#include <vector>
#include <list>
#include <iostream>
#include <sstream>

namespace Yosokumo
{

/**
 * Represents a block of <code>Predictors</code>.
 */
class PredictorBlock : public Block
{
    // At present the predictorSequence list is implemented as a 
    // vector<Predictor> because this implementation has O(1) performance 
    // for all three of "get", "add", and "next".  The latter is used to 
    // iterate over the list, and thus we do not want it to be expensive.  
    // The "add" method appends to the end of the list. --  Essentially, we 
    // want an array which can grow in size.  

    // The sequence is defined in Block.h

public:

    // Constructors and destructor

    /**
     * Initializes a newly created <code>PredictorBlock</code> object with 
     * default attributes.
     */
    PredictorBlock();

    /**
     * Initializes a newly created <code>PredictorBlock</code> object with 
     * a study identifier.
     *
     * @param  id a study identifier for the block.
     */
    PredictorBlock(std::string id);

    /**
     * Initializes a newly created <code>PredictorBlock</code> object with the 
     * predictor vector specified by the input parameters.
     *
     * @param  begin an iterator specifying the beginning of the predictor 
     *             vector.
     * @param  end an iterator specifying the end of the predictor 
     *             vector.
     */
    PredictorBlock(
        std::vector<Predictor>::iterator begin, 
        std::vector<Predictor>::iterator end);

    /**
     * Initializes a newly created <code>PredictorBlock</code> object with the 
     * predictor list specified by the input parameters.
     *
     * @param  begin an iterator specifying the beginning of the predictor list.
     * @param  end an iterator specifying the end of the predictor list.
     */
    PredictorBlock(
        std::list<Predictor>::iterator begin, 
        std::list<Predictor>::iterator end);

    /**
     * Initializes a newly created <code>PredictorBlock</code> object with the 
     * study identifier and the predictor vector specified by the input 
     * parameters.
     *
     * @param  id a study identifier for the block.
     * @param  begin an iterator specifying the beginning of the predictor 
     *             vector.
     * @param  end an iterator specifying the end of the predictor 
     *             vector.
     */
    PredictorBlock(
        std::string id, 
        std::vector<Predictor>::iterator begin, 
        std::vector<Predictor>::iterator end);

    /**
     * Initializes a newly created <code>PredictorBlock</code> object with the 
     * study identifier and the predictor list specified by the input 
     * parameters.
     *
     * @param  id a study identifier for the block.
     * @param  begin an iterator specifying the beginning of the predictor list.
     * @param  end an iterator specifying the end of the predictor list.
     */
    PredictorBlock(
        std::string id, 
        std::list<Predictor>::iterator begin, 
        std::list<Predictor>::iterator end);

    /**
     * Destructor.
     */
    virtual ~PredictorBlock();

private:

    /**
     * Copy constructor - NOT IMPLEMENTED.
     */
    PredictorBlock(const PredictorBlock &rhs);

    /**
     * Assignment operator - NOT IMPLEMENTED.
     */
    PredictorBlock& operator=(const PredictorBlock& rhs);

public:

    // Access to the predictor sequence

    /**
     * Add a <code>Predictor</code> to the block. The predictor parameter is 
     * appended to the end of the predictor sequence.
     *
     * @param   predictor  the <code>Predictor</code> to add to the block.
     */
    void addPredictor(const Predictor &predictor);

    /**
     * Add a collection of <code>Predictors</code> to the block.  The 
     * <code>Predictors</code> in the vector specified by the parameters 
     * are appended to the end of the predictor sequence.  
     *
     * @param  begin an iterator specifying the beginning of the predictor 
     *             vector to add to the block.
     * @param  end an iterator specifying the end of the predictor 
     *             vector to add to the block.
     *
     * @return true if and only if the predictor sequence changes.
     */
    bool addPredictors(
        std::vector<Predictor>::iterator begin, 
        std::vector<Predictor>::iterator end);

    /**
     * Add a collection of <code>Predictors</code> to the block.  The 
     * <code>Predictors</code> in the list specified by the parameters 
     * are appended to the end of the predictor sequence.  
     *
     * @param  begin an iterator specifying the beginning of the predictor 
     *             list to add to the block.
     * @param  end an iterator specifying the end of the predictor 
     *             list to add to the block.
     *
     * @return true if and only if the predictor sequence changes.
     */
    bool addPredictors(
        std::list<Predictor>::iterator begin, 
        std::list<Predictor>::iterator end);

    /**
     * Remove predictors from the end of the block.  The specified number of 
     * predictors are removed from the end of the predictor sequence.
     *
     * @param   numPredictorsToRemove is the number of predictors to remove 
     *          from the end of the block.  If this value is zero no
     *          predictors are removed.  If this value exceeds the number 
     *          of predictors in the block, then all predictors are removed.
     *
     * @return true if and only if the sequence is changed.
     */
    bool removePredictors(uint64_t numPredictorsToRemove);


    /**
     * Return a predictor from the block.  This makes it possible to iterate 
     * over all predictors in the sequence like this:
     * <pre>
     *   for (uint64_t i = 0;  i < predictorSequence.size();  ++i)
     *   {
     *       Predictor c = predictorSequence.getPredictor(i)
     *       process predictor c
     *   }
     * </pre>
     *
     * @param   index specifying the predictor of the 0-based block.
     *
     * @return  the <code>Predictor</code> at the location specified by the 
     *              index.
     */
    Predictor getPredictor(uint64_t index) const;


    /**
     * Remove all predictors from the block.  After a call of this method,
     * the sequence is empty, i.e., it contains no predictors.
     *
     */
    void clearPredictors();

    /**
     * Return the number of predictors in the block.
     *
     * @return  the number of predictors in the block.
     */
    uint64_t size() const;

    /**
     * Return <code>true</code> if the block contains no predictors.
     *
     * @return <code>true</code> if the block contains no predictors.
     *         <code>false</code> otherwise.
     */
    bool isEmpty() const;


    // Utility

    /**
     * Return a string representation of this <code>PredictorBlock</code>.
     *
     * @return  the string representation of this <code>PredictorBlock</code>.
     */
    virtual std::string toString();

};  // end class PredictorBlock

}   // end namespace Yosokumo

/** Output stream insertion operator.
 *
 * @param  os  the output stream.
 * @param  p   the <code>PredictorBlock</code> to insert in the stream.
 *
 * @return the output stream.
 */
std::ostream &operator<<(std::ostream &os, Yosokumo::PredictorBlock &p);


/** String stream insertion operator.
 *
 * @param  s   the string stream.
 * @param  p   the <code>PredictorBlock</code> to insert in the stream.
 *
 * @return the string stream.
 */
std::stringstream &operator<<(std::stringstream &s, Yosokumo::PredictorBlock &p);

#endif  // PREDICTORBLOCK_H

// end PredictorBlock.h
