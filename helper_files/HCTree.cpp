/******************************************************************************
File Name:    HCTree.cpp
Description:  This program defines the functions called in HCTree.hpp. For
              the functions in HCTree.hpp that were declared, we write the code
              to execute those functions in this file
******************************************************************************/

#include "HCTree.hpp"

/******************************************************************************
Function Name:  deleteAll
Purpose:        This helper function deletes all of the nodes in our Huffman
                tree 
Description:    This helper function checks to see if the node exists. It then
                checks to see if the node has a c0 child. If it does, it
                recursively calls the function. This process is done again for
                the c1 child. Afterwards, it deletes the current node. This
                operation deletes all of the nodes in our tree starting with
                the leaves
Input:          node - the current node we are starting from. This will be
                       the root when called from the destructor
Result:         An partial Huffman tree, where nodes after the node in the
                parameter are deleted
******************************************************************************/
static void deleteAll(HCNode* node) {

  /* If statement checks to see if the node exists */
  if (node) {

    /* If statement checks to see if the node has a c0 child */
    if (node -> c0)
      deleteAll(node -> c0);

    /* If statement checks to see if the node has a c1 child */
    if (node -> c1)
      deleteAll(node -> c1);

    delete node;
  }
}

/******************************************************************************
Function Name:  ~HCTree
Purpose:        This function is the deconstructor for our HCTree class
Description:    This function deallocates all memory created from our HCTree
                class by calling the deleteAll function starting at the root.
                This then deletes every node in our Huffman tree
Result:         An empty Huffman tree
******************************************************************************/
HCTree::~HCTree() {
  deleteAll(root);
}

/******************************************************************************
Function Name:  parentSymbol
Purpose:        This helper function helps determine the parent symbol when
                creating our Huffman tree
Description:    This helper function helps to determine the symbol for the
                parent node of two existing nodes in our priority queue. It
                ensures that the parent symbol is larger than the symbols of
                its children. It increases the symbol by 1 if it the symbol
                of the largest child does not exceed 255. If it does, the
                symbol of the parent is 255 since this is the maximum for an
                unsigned char
Input:          one   - the first node we are comparing symbols with
                other - the second node we are comparing symbols with
Result:         Returns the symbol for the parent node being created
******************************************************************************/
static unsigned char parentSymbol(HCNode* one, HCNode* other) {

  /* If statement checks to see if symbol of one is less than symbol of other */
  if(one -> symbol < other -> symbol) {

    /* If statemetn checks to see if symbol of other is not at maximum range */
    if (other -> symbol != 255)
      return (other -> symbol + 1);

    return other -> symbol;
  }

  /* If statement checks to see if symbol of one is not at maximum range */
  if (one -> symbol != 255)
    return (one -> symbol + 1);

  return one -> symbol;
}

/******************************************************************************
Function Name:  build
Purpose:        This function builds a Huffman tree using a vector containing
                the frequencies of each character in a file
Description:    This function creages a Huffman tree by constructing a priority
                queue. It then checks through the vector of frequencies,
                creating nodes if a frequency exists and pusing it into the
                priority queue. When done, it combines the two lowest nodes in
                our queue and constructs a parent for these nodes. This newly
                created node is pushed into our queue and the process repeats.
                This keeps going until we only have one root node in our queue,
                containing all of the other nodes in our Huffman tree
Input:          freqs - the frequencies of each character in a file
Result:         A Huffman tree constructed to accomodate the frequencies of a
                character in a file
******************************************************************************/
void HCTree::build(const vector<int>& freqs) {
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> HCQueue;

  /* For loop loops through our entire vector of frequencies */
  for(int index = 0; index < freqs.size(); index++) {

    /* If statement chekcs to see if the value at an index in our vector is
     * greater than zero, meaning this character exists in our file */
    if (freqs[index] != 0) {

      /* We create a node for each existing symbol and push it into our
       * priority queue */
      leaves[index] = new HCNode(freqs[index], index);
      HCQueue.push(leaves[index]);
    }
  }

  /* If statement is executed when the priority queue contains only one node */
  if (HCQueue.size() == 1) {
    HCNode* temp = new HCNode(0, 0);
    HCQueue.push(temp);
  }

  /* While loop keeps executing while the queue has a size greater than 1 */
  while(HCQueue.size() > 1) {

    /* We create two temporary nodes from the first two nodes in our priority
     * queue and pop them off when done */
    HCNode* temp1 = HCQueue.top();
    HCQueue.pop();
    HCNode* temp2 = HCQueue.top();
    HCQueue.pop();

    /* We determine the new frequency and new character symbol for the parent
     * node of these two temporary nodes, then create the parent node */
    int newFrequency = temp1 -> count + temp2 -> count;
    unsigned char newSymbol = parentSymbol(temp1, temp2);
    HCNode* parent = new HCNode(newFrequency, newSymbol);

    /* We then ensure that the fields of all three nodes are updated to ensure
     * that we can find any leaf node in our tree */
    temp1 -> p = parent;
    temp2 -> p = parent;
    parent -> c1 = temp1;
    parent -> c0 = temp2;

    /* The new parent node is then pushed into our priority queue */
    HCQueue.push(parent);
  }

  /* If statement is executed if the priority queue has a size of 1 */
  if ( HCQueue.size() != 0)
    root = HCQueue.top();
}

/******************************************************************************
Function Name:  traverseTree
Purpose:        This helper function allows up to traverse the tree when
                when encoding the symbols from our file
Description:    This helper function is used in our encode function to determine
                the coding for our symbol. This helper function is called
                recursevily, climbing up the tree until we reach the root. Once
                we reach the topmost root, we then go down our tree, determining
                the appropriate encoding for our symbol. We check to see if the
                node is equal to its parent's c1 child. If so, a 1 is given to
                the symbol. If the node is equal to its parent's c0 child, a 0
                is given to the symbol. This process is repeated until we reach
                the node containing our symbol, the leaf node
Input:          node -  the node we are attempting to encode
                out  -  the manner in which we are writing our information into
                        the output file
Result:         An encoding for our symbol is placed into our output file
******************************************************************************/
static void traverseTree(HCNode* node, BitOutputStream& out) {

  int bit;

  /* If statement checks to see if our node exists, breaking our recursive
   * function if not */
  if (!node)
    return;

  traverseTree(node -> p, out);

  /* If statment checks to see the node has a parent */
  if (node -> p) {

    /* If statment checks to see if the node is equalt to its parent's c1
     * child */
    if (node == node -> p -> c1)
      bit = 1;

    else
      bit = 0;

    /* We write out the bits to represent our symbol */
    out.writeBit(bit);
  }
}

/******************************************************************************
Function Name:  encode
Purpose:        This function uses the symbol found in the vector of leaf
                nodes and creates an encoding for it
Description:    This function creates a temporary node from the vector of leaf
                nodes. It then uses the helper function, traverseTree, to
                obtain an encoding for the selected symbol
Input:          symbol -  the symbol we are encoding
                out    -  the stream from which we are putting our encoded
                          symbols
Result:         An encoding for the selected symbol is achieved
******************************************************************************/
void HCTree::encode(byte symbol, BitOutputStream& out) const {
  HCNode* temp = leaves[symbol];
  traverseTree(temp, out);
}

/******************************************************************************
Function Name:  decode
Purpose:        This function obtains the encoding from a file and interprets
                it into the corresponding symbols
Description:    This function creates a temporary node starting at the root.
                It then obtains the characters in our infile, determining
                the encoded bits. Using the encoded bits, we traverse down
                our Huffman tree, eventually reaching to a leaf node. This leaf
                node is the encoded representation of our symbol
Input:          in -  the stream from which we are reading our encoded bits
Result:         Returns an int representation of our symbol
******************************************************************************/
int HCTree::decode(BitInputStream& in)const {
  HCNode* temp = root;

  /* While loop executes as long as temp has either a c1 child or a c0 child */
  while(temp -> c1 || temp -> c0) {
    int bit = in.readBit();

    /* If statement checks to see if the bit obtained is a 1 */
    if (bit == 1)
      temp = temp -> c1;

    else
      temp = temp -> c0;
  }

  return temp -> symbol;
}
