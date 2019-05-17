// Message.h

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

namespace Yosokumo
{

/**
 * A text message with a type indicating if the message is information or 
 * an error.  Some responses from the Yokosumo service return messages, 
 * especially in case of error.
 */
class Message
{
public:

    /**
     * Indicates whether the message is informational or an error message.
     */
    enum Type
    {
        /**
         * the message is informational.
         */
        INFORMATION,
        /**
         * the message indicates an error.
         */
        ERROR
    };

private:

    /**
     * The type of message.
     */
    Type type;

    /**
     * The message text.
     */
    std::string text;

public:

    // Constructors

    /**
     * Initializes a newly created <code>Message</code> object with default 
     * attributes:  type == INFORMATION and text == "".
     */
    Message();

    /**
     * Initializes a newly created <code>Message</code> object with attributes 
     * specified by the input parameters.
     *
     * @param  type   the type of the message:  INFORMATION or ERROR.
     * @param  text   the text of the message.
     */
    Message(Type type, const std::string &text);


    // Getters

    /**
     * Return the message text.
     *
     * @return the text of the message.
     */
    std::string getText() const;

    /**
     * Return the message type.
     *
     * @return the type of this message.
     */
    Type getType() const;


    // Setters

    /**
     * Set the message text.
     *
     * @param  text   the text of the message is set to this.
     */
    void setText(const std::string &text);

    /**
     * Set the message type.
     *
     * @param  type   the type of the message is set to this.
     */
    void setType(Type type);


    // Utility

    /**
     * Return a string representation of this <code>Message</code>.
     *
     * @return  the string representation of this <code>Message</code>.
     */
    std::string toString() const;

};  // end class Message

}   // end namespace Yosokumo

#endif  // MESSAGE_H

// end Message.h
