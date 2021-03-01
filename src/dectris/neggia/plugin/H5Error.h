/**
MIT License

Copyright (c) 2017 DECTRIS Ltd.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef H5ERROR_H
#define H5ERROR_H
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>

template <class... ARGS>
struct StringConcatenator;
template <class HEAD, class... TAIL>
struct StringConcatenator<HEAD, TAIL...> {
    static std::string getString(HEAD head, TAIL... tail);
};
template <>
struct StringConcatenator<> {
    static std::string getString() { return ""; }
};
template <class HEAD, class... TAIL>
std::string StringConcatenator<HEAD, TAIL...>::getString(HEAD head,
                                                         TAIL... tail) {
    std::stringstream ss;
    ss << head << StringConcatenator<TAIL...>::getString(tail...);
    return ss.str();
}

class H5Error : public std::runtime_error {
public:
    H5Error(int errorCode, const std::string& message)
          : std::runtime_error(message), _errorCode(errorCode) {}
    template <class... OUTPUT_ARGS>
    H5Error(int errorCode, OUTPUT_ARGS... args)
          : H5Error(errorCode,
                    StringConcatenator<OUTPUT_ARGS...>::getString(args...)) {}
    const char* what() const throw() { return std::runtime_error::what(); }
    int getErrorCode() const { return _errorCode; }

private:
    int _errorCode;
};

#endif  // H5ERROR_H
