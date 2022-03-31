/******************************************************************************
File Name:    BitInputStream.cpp
Description:  This program defines the functions called in BitInputStream.hpp.
              For the functions that were declared in the hpp file, we write
              the code to execute those functions in this file
******************************************************************************/

#include "BitInputStream.hpp"

/******************************************************************************
Function Name:  fill
Purpose:        This function fills the buffer from the input
Description:    This function calls get in order to obtain the character for
                buffer. It then sets nbits to 0, signaling that the buffer
                is ready to be read
Result:         The buffer is set from input
******************************************************************************/
void BitInputStream::fill() {
  buf = in.get();
  nbits = 0;
}

/******************************************************************************
Function Name:  readBit
Purpose:        This function reads the next bit from the bit buffer and
                returns this bit
Description:    This function first checks to see if nbits is equal to 8. This
                indicates that all of the bits in the buffer are read and that
                we must fill the buffer again. It then obtains the bit to
                return and increases nbits
Result:         Return 1 if the bit read is 1
                Return 0 if the bit read is 0
******************************************************************************/
int BitInputStream::readBit() {

  /* If statement checks to see if all of the bits in buffer have been read,
   * this happens when nbits equals 8 */
  if (nbits == 8)
    fill();

  int bitToReturn = (buf >> nbits) & 1;
  nbits++;

  return bitToReturn;
}
