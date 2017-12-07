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

#include "Glaeser_Noemi_BTC.h"

// function prototype
std::string merkleRoot(std::vector<Transaction> &);

int main(int argc, char ** argv)
{
  int numblocks = 0;
  int numtransactions = 0;
  Block temp;
  std::vector<Block> blocks;
  std::vector<Transaction> transactions;

  if(argc != 3)
  {
    std::cout << "Usage: Glaeser_Noemi_BTC [blockchain.txt] [transaction.txt]" << std::endl;
    exit(1);
  }

  std::string blockchainFileName = argv[1];
  std::string transactionFileName = argv[2];

  std::cout << "blockchainFileName: " << blockchainFileName << std::endl;
  std::cout << "transactionFileName: " << transactionFileName << std::endl;

  std::ifstream blockchainFile(blockchainFileName);
  std::ifstream transactionFile(transactionFileName);
  if(!blockchainFile)
  {
    std::cout << "Cannot open " << blockchainFileName << std::endl;
    exit(1);
  }
  if(!transactionFile)
  {
    std::cout << "Cannot open " << transactionFileName << std::endl;
    exit(1);
  }

  /*** Read in blockchain ***/
  std::string line;
  int count = 0;
  while(std::getline(blockchainFile, line))
  {
    std::vector<Block> temp;
    Block newBlock(line);
    blocks.push_back(newBlock);
  }

  /*** Read in Transactions ***/
  while(std::getline(transactionFile, line))
  {
    Transaction newTransaction(line);
    transactions.push_back(newTransaction);
  }

  /*** Generate Merkle Root ***/
  std::string merkle(merkleRoot(transactions));
  std::cout << "merkle root: " << merkle << std::endl;

  /*** Check if chain is valid ***/
  
  // check if each block is valid
  for(int i = 0; i < blocks.size(); i++)
  {
    Block currBlock(blocks.at(i));
    std::cout << currBlock.toString() << std::endl;
    std::cout << "isValid: " << currBlock.isValid() << std::endl;
    if(!(currBlock.isValid()))
    { 
      std::cout << merkle << std::endl;
      exit(0);
    }
  }
  
  // check if chain is unbroken
  Blockchain bchain(blocks);
  if(!bchain.isValid())
  {
    std::cout << merkle << std::endl;
    exit(0);
  }
  
  /*** We have now established that the chain is valid ***/
  Block newBlock(blocks, merkle);
  std::cout << newBlock.toString() << std::endl;
  exit(0);

}

// recursive function
std::string merkleRoot(std::vector<Transaction> & tr)
{
  int size = tr.size();

  if(size == 1)
  {
    return picosha2::hash256_hex_string(tr.at(0).toString());
  }
  else
  {
    // create subvector (this constructor is inclusive)
    std::vector<Transaction> firstHalf(tr.begin(), tr.end() - size/2);
    std::vector<Transaction> secondHalf(tr.begin() + size/2, tr.end());

    std::string leftHash(merkleRoot(firstHalf));
    std::string rightHash(merkleRoot(secondHalf));

    return picosha2::hash256_hex_string(leftHash+rightHash);
  }
}
