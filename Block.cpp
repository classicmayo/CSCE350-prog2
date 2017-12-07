/***************************************************************************
 * File: Block.cpp
 * Author: Noemi Glaeser
 * Function: Class to manage blocks in blockchain
 * Input: 
 * Output: 
 * Date: 3-Dec-2017
 ***************************************************************************/

#include "Block.h"

/**** constructors ****/
Block::Block()
{
  prevHash = "";
  merkleRoot = "";
  nonce = "";
}

Block::Block(std::string str)
{
  std::vector<std::string> strings;
  std::string word;

  int pos = str.find(" ");
  while(pos != std::string::npos)
  {
    word = str.substr(0, pos);
    strings.push_back(word);

    pos = str.find(" ");
    str = str.substr(pos+1);
  }
  
  if(strings.size() != 3)
  {
    prevHash = "";
    merkleRoot = "";
    nonce = "";
  }
  else
  {
    prevHash = strings.at(0);
    merkleRoot = strings.at(1);
    nonce = strings.at(2);
  }
}

Block::Block(std::vector<Block> &blocks, std::string merkle)
{
  // use prev block from Block vector to get hash of prev block
  Block prevBlock = blocks.at(0);
  prevHash = picosha2::hash256_hex_string(utils::hexToString(prevBlock.toString()));
  merkleRoot = merkle;
  nonce = mine();
}

Block::Block(std::string hash, std::string merkle, std::string n)
{
  prevHash = hash;
  merkleRoot = merkle;
  nonce = n;
}

Block::Block(const Block &b) //copy constructor
{
  prevHash = b.getPrevHash();
  merkleRoot = b.getMerkleRoot();
  nonce = b.mine();
}

Block::~Block() //destructor
{
}

/**** public methods ****/
bool Block::isValid()
{
  std::string hash = picosha2::hash256_hex_string(utils::hexToString(this->toString()));
  if(hash[0] == '0')
    return true;
  return false;
}

std::string Block::toString()
{
  return prevHash + merkleRoot + nonce;
}

std::string Block::mine() const
{
  // brute force nonces so hash begins with zero/block is valid
  // all possible 4 byte combinations (8 bits, hence pow(2, 8))
  for(int i = 0; i < pow(2, 8); i++)
  {
    Block temp(this->getPrevHash(), this->getMerkleRoot(), std::to_string(i)); 
    if(temp.isValid())
    {
      // convert i to hex string and return
      std::stringstream stream;
      stream << std::hex << std::to_string(i);
      return stream.str(); 
    }
  }
  std::cout << "No nonce found." << std::endl;
  return "";
}

// calculate this block's hash
std::string Block::calcHash()
{
  std::string hash = picosha2::hash256_hex_string(utils::hexToString(this->toString()));
  return hash;
}

std::string Block::getPrevHash() const
{
  return prevHash;
}

std::string Block::getMerkleRoot() const
{
  return merkleRoot;
}

std::string Block::getNonce() const
{
  return nonce;
}
