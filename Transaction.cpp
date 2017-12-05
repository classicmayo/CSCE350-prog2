/***************************************************************************
 * File: Transaction.cpp
 * Author: Noemi Glaeser
 * Function: Class to manage transactions
 * Input: 
 * Output: 
 * Created: 4-Dec-2017
 * Last Modified: 4-Dec-2017
 ***************************************************************************/
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Transaction.h"

/*** constructors ***/
Transaction::Transaction()
{
  sender = "";
  recipient = "";
  amount = 0.0;
}

Transaction::Transaction(std::string str)
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
    sender = "";
    recipient = "";
    amount = 0.0;
  }
  else
  {
    sender = strings.at(0);
    recipient = strings.at(1);
    // TODO: make sure third argument is a double
    amount = std::stod(strings.at(2));
  }
}

//copy constructor
Transaction::Transaction(const Transaction &t)
{
  sender = t.getSender();
  recipient = t.getRecipient();
  amount = t.getAmount();
}

//destructor
Transaction::~Transaction()
{
}

/*** public methods ***/
std::string Transaction::toString()
{
  // string may need spaces?
  return sender + recipient + std::to_string(amount);
}

std::string Transaction::getSender() const
{
  return sender;
}

std::string Transaction::getRecipient() const
{
  return recipient;
}

double Transaction::getAmount() const
{
  return amount;
}
