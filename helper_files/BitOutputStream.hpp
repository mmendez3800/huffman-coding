/******************************************************************************
File Name:    BitOutputStream.hpp
Description:  This program creates the BitOutputStream class. This object
              delegates to an object of an existing iostream class, allowing
              us to do I/O a bit at a time instead of only by bytes
******************************************************************************/

#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

/******************************************************************************
class BitOutputStream

Description: Creates an object which delegates to an object of an existing
    iostream class. We are able to, instead of only using input and output with
    bytes, use these same operations with bits instead

Data Fields:
    buf (char)          - one byte buffer of bits
    nbits (int)         - how many bits have been read from buf
    in (std::ostream &) - the output stream to use

Public Functions:
    BitOutputStream - constructor for the BitOutputStream class
    flush           - sends the buffer to the output and clears it
    writeBit        - writes the least significant bit into buffer
******************************************************************************/
class BitOutputStream {

private:
    char buf;
    int nbits;
    std::ostream & out;

public:

    /**************************************************************************
    Function Name:  BitOutputStream
    Purpose:        This function is the constructor for the class
    Description:
    Input:
    Result:
    Description:    This function initializes the data fields of the
                    BitOutputStream class. The values of buf and nbits are set
                    to 0 while out is set to the ostream being used by the file
    Input:          os  - the given ostream we will be using
    Result:         The BitOutputStream object is initialized
    **************************************************************************/
    BitOutputStream(std::ostream & os) : out(os) {
      buf = 0;
      nbits = 0;
    }

    /* The functions for the class are declared in this file and are defined in
     * the cpp file */
    void flush();
    void writeBit(int i);
};

#endif
