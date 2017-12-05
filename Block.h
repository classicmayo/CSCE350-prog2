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

class Block
{
  private:
    string prevHash;
    string merkleRoot;
    string nonce;

  public:
    Block();
    Block(string str);
    Block(Block[]&, string);
    Block(string, string, string);
    Block(const Block &); //copy constructor
    virtual ~Block(); //destructor

    bool isValid();
    string toString();
    string mine(string, string);
    string getPrevHash();
    string getMerkleRoot();
    string getNonce();
}

#endif
