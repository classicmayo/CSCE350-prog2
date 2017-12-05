/***************************************************************************
 * File: Block.h
 * Author: Noemi Glaeser
 * Function: Class to manage blocks in blockchain
 * Input: 
 * Output: 
 * Date: 3-Dec-2017
 ***************************************************************************/
#ifndef BLOCK_H
#define BLOCK_H

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Block
{
  private:
    std::string prevHash;
    std::string merkleRoot;
    std::string nonce;

  public:
    Block();
    Block(std::string str);
    Block(std::vector<Block>&, std::string);
    Block(std::string, std::string, std::string);
    Block(const Block &); //copy constructor
    virtual ~Block(); //destructor

    bool isValid();
    std::string toString();
    std::string mine() const;
    std::string calcHash();
    std::string getPrevHash() const;
    std::string getMerkleRoot() const;
    std::string getNonce() const;
};

#endif
