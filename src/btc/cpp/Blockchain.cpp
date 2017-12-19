/***************************************************************************
 * File: Blockchain.cpp
 * Author: Noemi Glaeser
 * Function: Blockchain methods
 * Input: 
 * Output: 
 * Created: 4-Dec-2017
 * Last Modified: 4-Dec-2017
 ***************************************************************************/

#include "Blockchain.h"

/*** constructors ***/
Blockchain::Blockchain()
{
  // blocks = NULL;
}

Blockchain::Blockchain(std::vector<Block>& v)
{
  for(Block b : v)
  {
    this->add(b);
  }
}

//copy constructor
Blockchain::Blockchain(const Blockchain & b)
{
  std::vector<Block> blocks(b.getChain());
}

// destructor
Blockchain::~Blockchain()
{
}

/*** public methods ***/
bool Blockchain::isValid()
{
  // blocks are in reverse chronological order
  for(int i = blocks.size()-1; i > 0; i--)
  {
    // the hash of the previous block
    std::string prev(blocks.at(i).calcHash());

    // the hash of the previous block as recorded by current block
    std::string compare(blocks.at(i-1).getPrevHash());

    if(compare != prev)
      return false;
  }
  return true;
}

std::string Blockchain::toString()
{
  std::string ans;
  for(Block b : blocks)
  {
    ans += b.toString() + "\n";
  }
  return ans;
}

void Blockchain::add(Block &b)
{
  blocks.push_back(b);
}

std::vector<Block> Blockchain::getChain() const
{
  return blocks;
}
