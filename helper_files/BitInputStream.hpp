/******************************************************************************
File Name:    BitInputStream.hpp
Description:  This program creates the BitInputStream class. This object
              delegates to an object of an existing iostream class, allowing
              us to do I/O a bit at a time instead of only by bytes
******************************************************************************/

#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

/******************************************************************************
class BitInputStream

Description: Creates an object which delegates to an object of an existing
    iostream class. We are able to, instead of only using input and output with
    bytes, use these same operations with bits instead

Data Fields:
    buf (char)          - one byte buffer of bits
    nbits (int)         - how many bits have been read from buf
    in (std::istream &) - the input stream to use

Public Functions:
    BitInputStream  - constructor for the BitInputStream class
    fill            - fills the buffer from the input
    readBit         - reads the next bit from the bit buffer
******************************************************************************/
class BitInputStream {

private:
    char buf;
    int nbits;
    std::istream & in;

public:

    /**************************************************************************
    Function Name:  BitInputStream
    Purpose:        This function is the constructor for the class
    Description:    This function initializes the data fields of the
                    BitInputStream class. The values of buf and nbits are set
                    to 0 and 8 respectively while in is set to the istream
                    being used by the file
    Input:          is  - the given istream we will be using
    Result:         The BitInputStream object is initialized
    **************************************************************************/ 
    BitInputStream(std::istream & is) : in(is) {
      buf = 0;
      nbits = 8;
    }

    /* The functions for the class are declared in this file and are defined in
     * the cpp file */
    void fill();
    int readBit();
};

#endif
