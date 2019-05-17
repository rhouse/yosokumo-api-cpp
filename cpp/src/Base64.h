// Base64.h

#ifndef BASE64_H
#define BASE64_H

#include <stdint.h>
#include <string>
#include <vector>
#include <stdexcept>

namespace Yosokumo
{

/**
 * Provides methods for converting bytes sequences to Base64 character strings 
 * and vice versa.
 *
 * <ul>
 * <li><code>static void encodeBytes(const std::vector<uint8_t> &source, std::string &dest)</code>
 * <li><code>static void decodeString(const std::string &source, std::vector<uint8_t> &dest)</code>
 * </ul>
 *
 * Be aware that there is not a one-to-one correspondence between byte 
 * sequences and Base64 character sequences.  Given any character sequence C
 * created by <code>encodeBytes</code>, the call <code>decodeString(C)</code> 
 * will return the original byte sequence.  However, there exist character 
 * sequences which are never produced by <code>encodeBytes</code>, and, hence, 
 * applying <code>decodeString</code> to such character sequences produces 
 * byte sequences from which the original character sequences cannot be 
 * recovered.  For example, <code>decodeString</code> converts both AA== and 
 * AB== to the single byte 0, and <code>encodeBytes</code> converts the 
 * single byte 0 to AA==.  There does not exist a sequence of bytes which 
 * will cause <code>encodeBytes</code> to return AB==.
 *
 * @author  Roger House
 * @version 0.9
 */

class Base64
{
    /** 
     * Base64 character set:  A-Z, a-z, 0-9, +, /.
     **/

    static char encode64[];

    /**
     * Convert a sequence of three bytes to a sequence of four characters.
     *
     * Map three 8-bit bytes to four 6-bit bytes:
     *
     *<pre>
     *       765432 10 7654 3210 76 543210 
     *      +---------+---------+---------+
     *      |AAAAAA AA|BBBB BBBB|CC CCCCCC|
     *      +------+-------+-------+------+
     *      |aaaaaa|bb bbbb|cccc cc|dddddd|
     *      +------+-------+-------+------+
     *       543210 54 3210 5432 10 543210
     *</pre>
     *
     * @param  A        the first byte.
     * @param  B        the second byte.
     * @param  C        the third byte.
     * @param  abcd     the resulting four characters are appended to abcd.
     */

    static void map3to4(uint8_t A, uint8_t B, uint8_t C, std::string &abcd);

public:

    /**
     * Convert a sequence of bytes to a Base64 string.
     *
     * @param  source is the input to this function, a sequence of zero or 
     *              more 8-bit bytes.
     * @param  dest is the output from this function, a string containing 
     *              the Base64 representation of the input bytes, 6-bits per 
     *              character.
     */

    static void encodeBytes(
        const std::vector<uint8_t> &source, 
        std::string &dest);

    /**
     * Convert a 6-bit Base64 character to an 8-bit byte.
     *
     * @param  c a 6-bit Base64 character.
     * @return the 8-bit byte corresponding to the input character.
     * @throws std::invalid_argument if the input character is not a
     *             Base64 character.
     */

    static uint8_t decode64(char c) throw(std::invalid_argument);

private:

    /**
     * Convert a sequence of four characters to a sequence of three bytes.
     * See the comment for map3to4 for the exact mapping.
     *
     * @param  a        the first character.
     * @param  b        the second character.
     * @param  c        the third character.
     * @param  d        the fourth character.
     * @param  ABC      the resulting three bytes are stored here.
     * @param  j        an index to the first byte in ABC to change.
     * @param  n        1, 2, or 3, indicating how many bytes to store in ABC.
     * @throws std::invalid_argument if any input character is not a
     *             Base64 character.
     */

    static void map4to3(
        char a, char b, char c, char d, 
        std::vector<uint8_t> &ABC, int j,
        int n) throw(std::invalid_argument);

public:

    /**
     * Convert a Base64 string to a sequence of bytes.
     *
     * @param  source is the input to this function, a string of zero or 
     *              more 6-bit Base64 characters.
     * @param  dest is the output from this function, a a byte sequence 
     *              containing the 8-bit bytes corresponding to the input 
     *              characters.
     * @throws std::invalid_argument if the length of the input string is 
     *             not a multiple of four.
     * @throws std::invalid_argument if the input string contains a 
     *             character which is not a Base64 character.
     */

    static void decodeString(
        const std::string &source, 
        std::vector<uint8_t> &dest) throw(std::invalid_argument);

};   //  end class Base64

}   // end namespace Yosokumo

#endif  // BASE64_H

// end Base64.h
