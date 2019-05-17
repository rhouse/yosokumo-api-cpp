// EmptyBlock.h

#ifndef EMPTYBLOCK_H
#define EMPTYBLOCK_H

#include "Block.h"

namespace Yosokumo
{

/**
 * Represents an empty block, i.e., a block containing no 
 * <code>Predictors</code> and no <code>Specimens</code>. An empty block can 
 * be used to test whether the requesting user has permission to post to the 
 * table or whether the study is 'running' and therefore accepting blocks 
 * into the table.
 */

class EmptyBlock : public Block
{
public:

    /**
     * Initializes a newly created <code>EmptyBlock</code> object with default 
     * attributes.
     */
    EmptyBlock();

    /**
     * Initializes a newly created <code>EmptyBlock</code> object with a study 
     * identifier.
     *
     * @param  id a study identifier for the block.
     */
    EmptyBlock(std::string id);

    /**
     * Destructor - destroy an <code>EmptyBlock</code> object.
     */
    virtual ~EmptyBlock();

private:

    /**
     * Copy constructor - NOT IMPLEMENTED.
     */
    EmptyBlock(const EmptyBlock &rhs);

    /**
     * Assignment operator - NOT IMPLEMENTED.
     */
    EmptyBlock& operator=(const EmptyBlock& rhs);

public:

    /**
     * Return the empty block type.
     *
     * @return the empty block type:  Type.EMPTY.
     */
    virtual Type getType() const;

    /**
     * Return the empty block as a string.
     *
     * @return the empty block as a string.
     */
    virtual std::string toString();

};  // end class EmptyBlock

}   // end namespace Yosokumo

#endif  // EMPTYBLOCK_H

// end EmptyBlock.h
