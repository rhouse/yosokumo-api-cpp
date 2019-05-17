// YosokumoDIF.h

#ifndef YOSOKUMODIF_H
#define YOSOKUMODIF_H

#include <string>

#include "Block.h"
#include "Catalog.h"
#include "Cell.h"
#include "Message.h"
#include "Panel.h"
#include "Predictor.h"
#include "Role.h"
#include "Roster.h"
#include "ServiceException.h"
#include "Specimen.h"
#include "Study.h"

namespace Yosokumo
{
/**
 * Defines methods which transform bytes obtained from HTTP requests into 
 * Yosokumo C++ objects (such as <code>Catalog</code> and <code>Study</code>) 
 * and vice versa.  Each class implementing this interface handles a different 
 * DIF, e.g., XML and Google Protocol Buffers.
 */

class YosokumoDIF
{
protected:
    ServiceException exception;

public:

    YosokumoDIF();

    virtual ~YosokumoDIF();

    /**
     * Return a content type string for use in Accept and Content-Type HTTP
     * header lines.  For example, "application/yosokumo+protobuf".
     *
     * @return a content type string for use in Accept and other HTTP headers.
     */
    virtual std::string getContentType() = 0;

    /**
     * Test if an exception has occurred.
     *
     * @return <code>true</code> means there is an exception.
     *         <code>false</code> means there is no exception.
     */
    bool isException();

    /**
     * Test if really an exception.
     *
     * @param  e  the exception to be tested.
     *
     * @return <code>true</code> means e is an exception.
     *         <code>false</code> means e is not an exception.
     */
    static bool isException(const ServiceException &e);

    /**
     * Return a <code>ServiceException</code> from the code-decode process.
     *
     * @param  e  if there is an exception, it is placed here.
     *
     * @return <code>true</code> means there is an exception, and it has been
     *          placed in e.
     *         <code>false</code> means there is no exception, e is unchanged.
     */
    bool getException(ServiceException &e);

    /**
     * Clear the exception.
     */
    void clearException();

    /**
     * Make a Yosokumo <code>Catalog</code> object out of the bytes of an HTTP 
     * Entity. 
     *
     * @param  catalogAsBytes  a catalog as bytes from an HTTP Entity.
     * @param  catalog         the output catalog created from the bytes.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             catalog may be incomplete.  Call getException() for details.
     */
    virtual bool makeCatalogFromBytes(
        const std::vector<uint8_t> &catalogAsBytes,
        Catalog &catalog) = 0;

    /**
     * Make the bytes for an HTTP Entity out of a Yosokumo <code>Catalog</code> 
     * object.
     *
     * @param  catalog  a Yosokumo <code>Catalog</code> object.
     * @param  catalogAsBytes  the output bytes created from the catalog.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             bytes may be incomplete.  Call getException() for details.
     */
    virtual bool makeBytesFromCatalog(
        const Catalog &catalog,
        std::vector<uint8_t> &catalogAsBytes) = 0;

    /**
     * Make a Yosokumo <code>Study</code> object out of the bytes of an HTTP 
     * Entity. 
     *
     * @param  studyAsBytes  a study as bytes from an HTTP Entity.
     * @param  study         the output study created from the bytes.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             study may be incomplete.  Call getException() for details.
     */
    virtual bool makeStudyFromBytes(
        const std::vector<uint8_t> &studyAsBytes,
        Study &study) = 0;

    /**
     * Make the bytes for an HTTP Entity out of a Yosokumo <code>Study</code> 
     * object.
     *
     * @param  study  a Yosokumo <code>Study</code> object.
     * @param  studyAsBytes  the output bytes created from the study.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             bytes may be incomplete.  Call getException() for details.
     */
    virtual bool makeBytesFromStudy(
        const Study &study,
        std::vector<uint8_t> &studyAsBytes) = 0;

    /**
     * Make a Yosokumo <code>Study</code> name out of the bytes of an HTTP 
     * Entity. 
     *
     * @param  studyNameAsBytes  a study name as bytes from an HTTP Entity.
     * @param  name              the output study name created from the bytes.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output study
     *             name may be incomplete.  Call getException() for details.
     */
    virtual bool makeStudyNameFromBytes(
        const std::vector<uint8_t> &studyNameAsBytes,
        std::string &name) = 0;

    /**
     * Make the bytes for an HTTP Entity out of a Yosokumo <code>Study</code> 
     * name.
     *
     * @param  name a Yosokumo <code>Study</code> name.
     * @param  studyNameAsBytes  the output bytes created from the study name.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             bytes may be incomplete.  Call getException() for details.
     */
    virtual bool makeBytesFromStudyName(
        const std::string &name,
        std::vector<uint8_t> &studyNameAsBytes) = 0;

    /**
     * Make a Yosokumo <code>Study</code> status out of the bytes of an HTTP 
     * Entity. 
     *
     * @param  studyStatusAsBytes  a study status as bytes from an HTTP Entity.
     * @param  status              the output study status created from the bytes.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output study
     *             status may be incomplete.  Call getException() for details.
     */
    virtual bool makeStudyStatusFromBytes(
        const std::vector<uint8_t> &studyStatusAsBytes,
        Study::Status &status) = 0;

    /**
     * Make the bytes for an HTTP Entity out of a Yosokumo <code>Study</code> 
     * status.
     *
     * @param  status a Yosokumo <code>Study</code> status.
     * @param  studyStatusAsBytes  the output bytes created from the study status.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             bytes may be incomplete.  Call getException() for details.
     */
    virtual bool makeBytesFromStudyStatus(
        const Study::Status status,
        std::vector<uint8_t> &studyStatusAsBytes) = 0;

    /**
     * Make a Yosokumo <code>Study</code> visibility out of the bytes of an 
     * HTTP  Entity. 
     *
     * @param  studyVisibilityAsBytes  a study visibility as bytes from an 
     *                                 HTTP Entity.
     * @param  visibility  the output study visibility created from the bytes.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output study
     *             visibility may be incomplete.  Call getException() for details.
     */
    virtual bool makeStudyVisibilityFromBytes(
        const std::vector<uint8_t> &studyVisibilityAsBytes,
        Study::Visibility &visibility) = 0;

    /**
     * Make the bytes for an HTTP Entity out of a Yosokumo <code>Study</code> 
     * visibility.
     *
     * @param  visibility a Yosokumo <code>Study</code> visibility.
     * @param  studyVisibilityAsBytes  the output bytes created from the study 
     *             visibility.
     */
    virtual bool makeBytesFromStudyVisibility(
        const Study::Visibility visibility,
        std::vector<uint8_t> &studyVisibilityAsBytes) = 0;


    /**
     * Make a Yosokumo <code>Panel</code> object out of the bytes of an HTTP 
     * Entity. 
     *
     * @param  panelAsBytes  a panel as bytes from an HTTP Entity.
     * @param  panel         the output panel created from the bytes.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             panel may be incomplete.  Call getException() for details.
     */
    virtual bool makePanelFromBytes(
        const std::vector<uint8_t> &panelAsBytes,
        Panel &panel) = 0;

    /**
     * Make the bytes for an HTTP Entity out of a Yosokumo <code>Panel</code> 
     * object.
     *
     * @param  panel  a Yosokumo <code>Panel</code> object.
     * @param  panelAsBytes  the output bytes created from the panel.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             bytes may be incomplete.  Call getException() for details.
     */
    virtual bool makeBytesFromPanel(
        const Panel &panel,
        std::vector<uint8_t> &panelAsBytes) = 0;

    /**
     * Make a Yosokumo <code>Role</code> object out of the bytes of an HTTP 
     * Entity. 
     *
     * @param  roleAsBytes  a role as bytes from an HTTP Entity.
     * @param  role         the output role created from the bytes.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             role may be incomplete.  Call getException() for details.
     */
    virtual bool makeRoleFromBytes(
        const std::vector<uint8_t> &roleAsBytes,
        Role &role) = 0;

    /**
     * Make the bytes for an HTTP Entity out of a Yosokumo <code>Role</code> 
     * object.
     *
     * @param  role  a Yosokumo <code>Role</code> object.
     * @param  roleAsBytes  the output bytes created from the role.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             bytes may be incomplete.  Call getException() for details.
     */
    virtual bool makeBytesFromRole(
        const Role &role,
        std::vector<uint8_t> &roleAsBytes) = 0;

    /**
     * Make a Yosokumo <code>Roster</code> object out of the bytes of an HTTP 
     * Entity. 
     *
     * @param  rosterAsBytes  a roster as bytes from an HTTP Entity.
     * @param  roster         the output roster created from the bytes.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             roster may be incomplete.  Call getException() for details.
     */
    virtual bool makeRosterFromBytes(
        const std::vector<uint8_t> &rosterAsBytes,
        Roster &roster) = 0;

    /**
     * Make the bytes for an HTTP Entity out of a Yosokumo <code>Roster</code> 
     * object.
     *
     * @param  roster  a Yosokumo <code>Roster</code> object.
     * @param  rosterAsBytes  the output bytes created from the roster.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             bytes may be incomplete.  Call getException() for details.
     */
    virtual bool makeBytesFromRoster(
        const Roster &roster,
        std::vector<uint8_t> &rosterAsBytes) = 0;

    /**
     * Make a Yosokumo <code>Predictor</code> object out of the bytes of an 
     * HTTP Entity. 
     *
     * @param  predictorAsBytes  a predictor as bytes from an HTTP Entity.
     * @param  predictor         the output predictor created from the bytes.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             predictor may be incomplete.  Call getException() for details.
     */
    virtual bool makePredictorFromBytes(
        const std::vector<uint8_t> &predictorAsBytes,
        Predictor &predictor) = 0;

    /**
     * Make the bytes for an HTTP Entity out of a Yosokumo 
     * <code>Predictor</code> object.
     *
     * @param  predictor  a Yosokumo <code>Predictor</code> object.
     * @param  predictorAsBytes  the output bytes created from the predictor.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             bytes may be incomplete.  Call getException() for details.
     */
    virtual bool makeBytesFromPredictor(
        const Predictor &predictor,
        std::vector<uint8_t> &predictorAsBytes) = 0;

    /**
     * Make a Yosokumo <code>Cell</code> object out of the bytes of an 
     * HTTP Entity. 
     *
     * @param  cellAsBytes  a cell as bytes from an HTTP Entity.
     * @param  cell         the output cell created from the bytes.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             cell may be incomplete.  Call getException() for details.
     */
    virtual bool makeCellFromBytes(
        const std::vector<uint8_t> &cellAsBytes,
        Cell &cell) = 0;

    /**
     * Make the bytes for an HTTP Entity out of a Yosokumo <code>Cell</code> 
     * object.
     *
     * @param  cell  a Yosokumo <code>Cell</code> object.
     * @param  cellAsBytes  the output bytes created from the cell.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             bytes may be incomplete.  Call getException() for details.
     */
    virtual bool makeBytesFromCell(
        const Cell &cell,
        std::vector<uint8_t> &cellAsBytes) = 0;

    /**
     * Make a Yosokumo <code>Specimen</code> object out of the bytes of an 
     * HTTP Entity. 
     *
     * @param  specimenAsBytes  a specimen as bytes from an HTTP Entity.
     * @param  specimen         the output specimen created from the bytes.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             specimen may be incomplete.  Call getException() for details.
     */
    virtual bool makeSpecimenFromBytes(
        const std::vector<uint8_t> &specimenAsBytes,
        Specimen &specimen) = 0;

    /**
     * Make the bytes for an HTTP Entity out of a Yosokumo <code>Specimen</code> 
     * object.
     *
     * @param  specimen  a Yosokumo <code>Specimen</code> object.
     * @param  specimenAsBytes  the output bytes created from the specimen.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             bytes may be incomplete.  Call getException() for details.
     */
    virtual bool makeBytesFromSpecimen(
        const Specimen &specimen,
        std::vector<uint8_t> &specimenAsBytes) = 0;

    /**
     * Make a Yosokumo <code>Block</code> object out of the bytes of an 
     * HTTP Entity. 
     *
     * @param  blockAsBytes  a block as bytes from an HTTP Entity.
     * @param  block         the output block created from the bytes.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             block may be incomplete.  Call getException() for details.
     */
    virtual bool makeBlockFromBytes(
        const std::vector<uint8_t> &blockAsBytes,
        Block &block) = 0;

    /**
     * Make the bytes for an HTTP Entity out of a Yosokumo <code>Block</code> 
     * object.
     *
     * @param  block  a Yosokumo <code>Block</code> object.
     * @param  blockAsBytes  the output bytes created from the block.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             bytes may be incomplete.  Call getException() for details.
     */
    virtual bool makeBytesFromBlock(
        const Block &block,
        std::vector<uint8_t> &blockAsBytes) = 0;


    /**
     * Make a Yosokumo <code>Message</code> object out of the bytes of an HTTP 
     * Entity. 
     *
     * @param  messageAsBytes  a message as bytes from an HTTP Entity.
     * @param  message         the output message created from the bytes.
     */
    virtual bool makeMessageFromBytes(
        const std::vector<uint8_t> &messageAsBytes,
        Message &message) = 0;

    /**
     * Make the bytes for an HTTP Entity out of a Yosokumo <code>Message</code> 
     * object.
     *
     * @param  message  a Yosokumo <code>Message</code> object.
     * @param  messageAsBytes  the output bytes created from the message.
     *
     * @return <code>true</code> means everything worked out fine.
     *         <code>false</code> means there was a problem; the output
     *             bytes may be incomplete.  Call getException() for details.
     */
    virtual bool makeBytesFromMessage(
        const Message &message,
        std::vector<uint8_t> &messageAsBytes) = 0;

};  // end class YosokumoDIF

}   // end namespace Yosokumo

#endif  // YOSOKUMODIF_H

// end YosokumoDIF.h
