/******************************************************************************
File Name:    BitOutputStream.cpp
Description:  This program defines the functions called in BitOutputStream.hpp.
              For the functions in hpp that were declared, we write the code
              to execute those functions in this file
******************************************************************************/

#include "BitOutputStream.hpp"

/******************************************************************************
Function Name:  flush
Purpose:        This function sends the buffer to the output and clears it
Description:    This function first puts the buffer to the output. Once this is
                done, it resets the values of buf and nbits to 0
Result:         The buffer is sent to output
******************************************************************************/
void BitOutputStream::flush() {
  out.put(buf);
  out.flush();
  buf = nbits = 0;
}

/******************************************************************************
Function Name:  writeBit
Purpose:        This function writes the least significant bit of the argument
                to the bit buffer
Description:    This function first checks to see if buffer is full. If it is,
                it calls flush to have a new buffer. We then write the least
                significant bit of i into the buffer and increase nbits
Input:          i - the integer we are placing into buffer
Result:         The least significant bit is placed into buffer
******************************************************************************/
void BitOutputStream::writeBit(int i) {

  /* If statement is when the buffer is full, meaning the value of nbits is
   * equal to 8 */
  if (nbits == 8)
    flush();

  buf = buf | ( (i & 1) << nbits );
  nbits++;
}
