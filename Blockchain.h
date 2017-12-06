/***************************************************************************
 * File: Blockchain.h
 * Author: Noemi Glaeser
 * Function: Blockchain methods
 * Input: 
 * Output: 
 * Created: 4-Dec-2017
 * Last Modified: 4-Dec-2017
 ***************************************************************************/
#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Block.h"

class Blockchain
{
  private:
    std::vector<Block> blocks;

  public:
    Blockchain();
    Blockchain(std::vector<Block> &);
    Blockchain(const Blockchain &); //copy constructor
    virtual ~Blockchain(); //destructor

    bool isValid();
    std::string toString();
    void add(Block &);
    std::vector<Block> getChain() const;
};

#endif
