/******************************************************************************
File Name:    uncompress.cpp
Description:  This program executes the uncompression for our file. It takes in
              two parameters, the infile and the outfile. This program reads
              the infile, using the header to construct the Huffman tree. It
              then uses the encoded data in the infile to interpret them as
              symbols. These translated symbols are then written into the
              outfile, thus being uncompressed
******************************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cstdlib>
#include "helper_files/HCTree.hpp"

using namespace std;

int main(int argc, char* argv[]){

  /* If statement checkst to see if the number of arguments are correct */
  if (argc != 3) {
    cerr << "Invalid number of arguments. Format should be:" << endl;
    cerr << "./uncompress infile outfile" << endl;
    return -1;
  }

  const char* infile = argv[1];
  const char* outfile = argv[2];

  /* If statement checks to see if the infile and the outfile have the same
   * name */
  if (strcmp(infile, outfile) == 0) {
    cerr << "Infile and Outfile have the same name. Please ensure that" <<
      " the name of outfile is different from the name of infile" << endl;
    return -1;
  }

  ifstream in;
  in.open(infile);

  BitInputStream* bitInput = new BitInputStream(in);

  /* If statement checks to see if we were able to open our infile */
  if ( !in.good() ) {
    cerr << "The infile specified does not exist. Please choose a file" <<
      " which exists" << endl;
    return -1;
  }

  /* These variables are created to hold the symbols in our header, the vector
   * to hold these frequencies, and the character to be able to read the
   * numbers in our header */
  vector<int> values(256, 0);
  unsigned char nextChar;
  int symbol = 0;
  int frequency = 0;

  /* These variables are used to hold the total number of symbols going into
   * our outfile, the total frequencies of all of symbols, eventually
   * equaling totalSymbols, and a string to hold the information of which
   * symbol we need and what are its frequency */
  int totalSymbols = 0;
  int totalFrequencies = 0;
  string info = "";

  while (true) {
    nextChar = in.get();

    /* If statement is executed when we reach the end of file or when the
     * ' ' character is reached */
    if ( in.eof() || nextChar == ' ')
      break;

    /* Each character is added to our string */
    info += nextChar;
  }

  /* We now obtain the total number of symbols and our string is reset */
  totalSymbols = atoi( info.c_str() );
  info = "";

  /* While loop executes as long as totalFrequencies is less than
   * totalSymbols */
  while (totalFrequencies < totalSymbols) {

    while (1) {
      nextChar = in.get();

      /* If statement is executed when the ' ' character is reached */
      if (nextChar == ' ')
        break;

      info += nextChar;
    }

    /* We now obtain our symbol and our string is reset */
    symbol = atoi( info.c_str() );
    info = "";

    while (1) {
      nextChar = in.get();

      /* If statement is executed when ' ' character is reached */
      if (nextChar == ' ')
        break;

      info += nextChar;
    }

    /* We now obtain the frequency of the above symbol and our string is
     * reset */
    frequency = atoi ( info.c_str() );
    info = "";

    /* The frequency is added to the corresponding symbol in our vector and
     * the value of totalFrequencies is updated */
    values[symbol] = frequency;
    totalFrequencies += frequency;
  }

  HCTree tree;
  tree.build(values);

  ofstream out;
  out.open(outfile);

  /* If statement checks to see if we were able to open our outfile */
  if ( !out.good() ) {
    cerr << "The outfile specified does not exist. Please choose a " <<
      "file which exists" << endl;
    return -1;
  }

  /* totalFrequencies is reset to 0 to determine when decode should stop
   * reading from buffer */
  totalFrequencies = 0;

  while (totalFrequencies < totalSymbols) {
    nextChar = tree.decode(*bitInput);

    if ( in.eof() )
      break;

    /* Once we find the corresponding symbol from our encoded data in the
     * infile, we write it into our outfile */
    out << nextChar;
    totalFrequencies++;
  }

  in.close();
  out.close();
}
