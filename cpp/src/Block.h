// Block.h


#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>

#include "Predictor.h"
#include "Specimen.h" 

namespace Yosokumo
{

/**
 * A base class for <code>EmptyBlock</code>, <code>CellBlock</code>, 
 * <code>PredictorBlock</code>, and <code>SpecimenBlock</code>.  The 
 * <code>Block</code> class is not visible in the API.  It is a way to package 
 * up <code>Cells</code>, <code>Predictors</code> and <code>Specimens</code> 
 * for transmission to the Yosokumo web service via HTTP, so that HTTP requests
 * are never too large.  
 */

class Block
{
public:

    /**
     * Indicates what is stored in the <code>Block</code>, e.g., 
     * <code>Cells</code>, <code>Predictors</code>, or <code>Specimens</code>.
     */
    enum Type
    {
        /**
         * an empty block.
         */
        EMPTY,
        /**
         * a <code>Predictor</code> block.
         */
        PREDICTOR,
        /**
         * a <code>Specimen</code> block.
         */
        SPECIMEN,
        /**
         * a <code>Cell</code> block.
         */
        CELL
    };

private:

    /**
     * The type of the block.
     */

    Type type;

    /**
     * Specifies the study which the block is associated with.
     */

    std::string studyIdentifier;

protected:

    // An empty block has no need of any of the following, and cell blocks, 
    // predictor blocks, and specimen blocks each need only one of the 
    // following.  However, this somewhat space-inefficient approach is taken 
    // anyway, because it means that a Block contains all the data needed by 
    // each of EmptyBlock, CellBlock, PredictorBlock, and SpecimenBlock, 
    // which makes reading of blocks in protocol buffer form much easier.
    //
    // Of course, the first question is why not use a union?  Unfortunately
    // union members must be POD, so that doesn't work. 

    /**
     * A sequence of <code>Cell</code>.
     */
     std::vector<Cell> cellSequence;

    /**
     * A sequence of <code>Predictor</code>.
     */
     std::vector<Predictor> predictorSequence;

    /**
     * A sequence of <code>Specimen*</code>. 
     */
    std::vector<Specimen*> specimenSequence;


public:

    /**
     * Initializes a newly created <code>Block</code> object with default 
     * attributes.
     */
    Block();

    /**
     * Initializes a newly created <code>Block</code> object with a study 
     * identifier.
     *
     * @param  id a study identifier for the block.
     */
    Block(std::string id);

    /**
     * Destructor.
     */
    virtual ~Block();

    /**
     * Set the type of the block.
     *
     * @param t the type to assign to the block.
     */
    void setType(Type t);

    /**
     * Return the type of the block.
     *
     * @return the type of the block.
     */
    Type getType() const;

    /**
     * Set the study identifier of the block.
     *
     * @param id the identifier to assign to the block.
     */
    void setStudyIdentifier(std::string id);

    /**
     * Return the study identifier of the block.
     *
     * @return the study identifier of the block.
     */
    std::string getStudyIdentifier() const;

    /**
     * Return the block as a string.
     *
     * @return the block as a string.
     */
    virtual std::string toString();

};   // end class Block

}   // end namespace Yosokumo

#endif  // BLOCK_H

// end Block.h
