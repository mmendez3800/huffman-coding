/******************************************************************************
File Name:    compress.cpp
Description:  This program executes the compression for our file. It takes in
              two parameters, the infile and the outfile. This program reads
              the infile, calculating the total number of symbols and the
              frequencies of each symbol. It then encodes these symbols into
              our outfile.
******************************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include "helper_files/HCTree.hpp"

using namespace std;

int main(int argc, char* argv[]){

  /* If statement checks to see if the number of arguments are correct */
  if (argc != 3) {
    cerr << "Invalid number of arguments. Format should be:" << endl;
    cerr << "./compress infile outfile" << endl;
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

  /* If statement checks to see if we were able to open our infile */
  if ( !in.good() ) {
    cerr << "The infile specified does not exist. Please choose a file" <<
      " which exists" << endl;
    return -1;
  }

  /* Variables are created to hold the frequency of symbols in our infile, the
   * total number of symbols in our file, and the next character in our file */
  vector<int> values(256,0);
  unsigned char nextChar;
  int totalSymbols = 0;

  /* While loops keeps executing until we reach the end of file */
  while(true){
    nextChar = in.get();

    if ( in.eof() )
      break;

    /* If statement is executed if we are able to get the character. We then
     * update the frequency and total number of symbols */
    if ( in.good() )
      values[(int) nextChar]++;
      totalSymbols++;
  }

  in.close();

  /* A Huffman tree is constructed using our vector holding our frequencies */
  HCTree tree;
  tree.build(values);

  ofstream out;
  out.open(outfile);

  BitOutputStream* bitOutput = new BitOutputStream(out);

  /* If statement checks to see if we were able to open our outfile */
  if ( !out.good() ) {
    cerr << "The outfile specified does not exist. Please choose a " <<
      "file which exists" << endl;
    return -1;
  }

  /* We print the ASCII symbol and its frequency
   * into out outfile, representing our header */
  out << totalSymbols << " ";
  for(int index = 0; index < values.size(); index++){
    if(values[index] != 0)
      out << index << " " << values[index] << " ";
  }

  in.open(infile);

  /* While loops keeps executing until we reach the end of file */
  while(true){
    nextChar = in.get();

    if ( in.eof() )
      break;

    /* If statement is executed if we are able to get our character. We the
     * encode our symbol */
    if ( in.good() )
      tree.encode(nextChar, *bitOutput);
  }

  bitOutput -> flush();
  in.close();
  out.close();
}
