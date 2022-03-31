/******************************************************************************
File Name:    HCNode.cpp
Description:  This program defines the functions called in HCNode.hpp. For
              the functions in HCTree.hpp that were declared, we write the code
              to execute those functions in this file
******************************************************************************/

#include "HCNode.hpp"

/******************************************************************************
Function Name:  operator<
Purpose:        This function overloads the < operator for the use of comparing
                two HCNodes
Description:    This function overloads the < operator when we use our priority
                queue. This operator lets the node with the smaller count have
                a higher priority. This works best when arranging our queue. The
                function checks to see if the counts of the two nodes are
                different. If so, the comparision is made so that the node with
                the lower count has the higher priority. If the counts of the
                two nodes are the same, the symbols of the nodes are compared 
Input:          other - the node we are comparing to with this
Result:         true if the comparison is correct
                false if the comparison is incorrect
******************************************************************************/
bool HCNode::operator<(const HCNode& other) {

  /* If statement checks to see if the counts of the two nodes are different */
  if (count != other.count)
    return count > other.count;

  return symbol < other.symbol;
}

/******************************************************************************
Function Name:  comp
Purpose:        This function uses the < operator we overloaded to compare two
                nodes when implementing our priority queue
Description:    This function is used for our priority queue. It ensures that
                the nodes with the lowest counts are placed on top. This will
                benefit us when constructing our Huffman tree
Input:          one   - the first HCNode we are comparing
                other - the second HCNode we are comparing
Result:         true if the comparison is correct
                false if the comparison is incorrect
******************************************************************************/
bool comp(HCNode* one, HCNode* other) {
  return one < other;
}
