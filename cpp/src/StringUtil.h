// StringUtil.h

#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <string>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

namespace Yosokumo
{
/**
 * String utility functions.  ltrim, rtrim, and trim come from 
 *     http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
 *
 * endswith comes from
 *     http://stackoverflow.com/questions/874134/find-if-string-endswith-another-string-in-c
 *
 * startswith comes from
 *     http://stackoverflow.com/questions/8095088/how-to-check-string-start-in-c
 */

    /**
     * Trim left end of a string.
     *
     * @param  s  the string to trim.
     *
     * @return the input string with all leading whitespace removed from 
     *             the left end.
     */
    static inline std::string &ltrim(std::string &s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),   
            std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
    }

    /**
     * Trim right end of a string.
     *
     * @param  s  the string to trim.
     *
     * @return the input string with all trailing whitespace removed from 
     *             the right end.
     */
    static inline std::string &rtrim(std::string &s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), 
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
    }

    /**
     * Trim both ends of a string.
     *
     * @param  s  the string to trim.
     *
     * @return the input string with all leading whitespace removed from 
     *             the left end, and all trailing whitespace removed from 
     *             the right end.
     */
    static inline std::string &trim(std::string &s)
    {
        return ltrim(rtrim(s));
    }

    /**
     * Test if a string ends with another string.
     *
     * @param  fullString the string whose ending is to be tested.
     * @param  ending     the string to compare against the end of fullString.
     *
     * @return true means that fullString ends with the ending string.
     *         false means that fullString doesn't end with the ending string.
     */
    static inline bool endsWith(
        const std::string &fullString, 
        const std::string &ending)
    {
        if (fullString.length() < ending.length())
            return false;

        return (fullString.compare(fullString.length() - ending.length(), 
            ending.length(), ending) == 0);
    }

    /**
     * Test if a string starts with another string.
     *
     * @param  fullString the string whose start is to be tested.
     * @param  start   the string to compare against the start of fullString.
     *
     * @return true means that fullString starts with the ending string.
     *         false means that fullString doesn't start with the ending string.
     */
    static inline bool startsWith(
        const std::string &fullString, 
        const std::string &start)
    {
        return start.length() <= fullString.length() 
            && equal(start.begin(), start.end(), fullString.begin());
    }

}   // end namespace Yosokumo

#endif  // STRINGUTIL_H

// end StringUtil.h
