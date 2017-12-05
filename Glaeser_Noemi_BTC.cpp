/***************************************************************************
 * File: Glaeser_Noemi_BTC.cpp
 * Author: Noemi Glaeser
 * Function: Simulates Block Chain as described in readme.
 * Input: Blockchain file, transaction file
 * Output: If the chain is invalid, Merkle root of transactions
 *         If the chain is valid, new block to point to the last block
 *              in the chain. 
 * Date: 3-Dec-2017
 ***************************************************************************/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Block.h"
#include "Transaction.h"
#include "picosha2.h"

int main(int argc, char ** argv)
{
  int numblocks = 0;
  int numtransactions = 0;
  vector<Block> blocks;
  vector<Transaction> transactions;

  if(argc != 3)
  {
    std::cout << "Usage: Glaeser_Noemi_BTC [blockchain.txt] [transaction.txt]" << endl;
    exit(1);
  }

  string blockchainFileName = std::to_string(argv[1]);
  string transactionFileName = std::to_string(argv[2]);

  std::ifstream blockchainFile(blockchainFileName);
  std::ifstream transactionFile(transactionFileName);
  if(!blockchainFile)
  {
    std::cout << "Cannot open " << blockchainFileName << endl;
    exit(1);
  }
  if(!transactionFile)
  {
    std::cout << "Cannot open " << transactionFileName << endl;
    exit(1);
  }

  /*** Read in blockchain ***/
  std::string line;
  while(std::getline(blockchainFile, line))
  {
    blocks.push_back(new Block(line));
  }

  /*** Read in Transactions ***/
  while(std::getline(transactionFile, line))
  {
    transactions.push_back(new Transaction(line));
  }

  /*** Generate Merkle Root ***/
  std::string merkle = merkleRoot(transactions);

  /*** Check if chain is valid ***/
  
  // check if each block is valid
  for(Block b : blocks)
  {
    if(!b.isValid())
    { 
      std::cout << merkle << endl;
      exit(0);
    }
  }
  
  // check if chain is unbroken
  Blockchain bchain(blocks);
  if(!chain.isValid())
  {
    std::cout << merkle << endl;
    exit(0);
  }
  
  /*** We have now established that the chain is valid ***/
  Block newBlock(blocks, merkle);
  std::cout << newBlock << endl;
  exit(0);

}
