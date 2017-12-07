/***************************************************************************
 * File: Transaction.cpp
 * Author: Noemi Glaeser
 * Function: Class to manage transactions
 * Input: 
 * Output: 
 * Created: 4-Dec-2017
 * Last Modified: 4-Dec-2017
 ***************************************************************************/

#include "Transaction.h"

/*** constructors ***/
Transaction::Transaction()
{
  sender = "";
  recipient = "";
  amount = "0.0";
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

    str = str.substr(pos+1);
    pos = str.find(" ");
  }
  strings.push_back(str); // don't forget about the double

  if(strings.size() != 3)
  {
    sender = "";
    recipient = "";
    amount = "0.0";
  }
  else
  {
    sender = strings.at(0);
    recipient = strings.at(1);
    amount = strings.at(2);
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
  // string needs spaces
  return sender + " " + recipient + " " +  amount;
}

std::string Transaction::getSender() const
{
  return sender;
}

std::string Transaction::getRecipient() const
{
  return recipient;
}

std::string Transaction::getAmount() const
{
  return amount;
}
