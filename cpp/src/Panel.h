// Panel.h

#ifndef PANEL_H
#define PANEL_H

#include <stdint.h>
#include <string>

namespace Yosokumo
{

/**
 * Contains various data items associated with a study, e.g., creation time.
 *
 * @author  Roger House
 * @version 0.9
 */
class Panel
{
    std::string nameControlLocation;
    std::string statusControlLocation;
    std::string visibilityControlLocation;

    uint64_t blockCount;
    uint64_t cellCount;
    uint64_t prospectCount;

    std::string creationTime;
    std::string latestBlockTime;
    std::string latestProspectTime;

public:

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
    std::string getCreationTime() const ;

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

};  // end class Panel

}   // end namespace Yosokumo

#endif  // PANEL_H

// end Panel.h
