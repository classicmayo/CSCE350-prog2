/***************************************************************************
 * File: utils.h
 * Author: Noemi Glaeser - adapted from Dr. Gabriel Terejanu
 * Function: Class to manage blocks in blockchain
 * Input: 
 * Output: 
 * Date: 4-Dec-2017
 ***************************************************************************/
#ifndef UTILS
#define UTILS

#include "picosha2.h"
#include <iostream> 
#include <string>

namespace utils
{
    int hexCharToInt(char a){
        if(a>='0' && a<='9')
            return(a-48);
        else if(a>='A' && a<='Z')
            return(a-55);
        else
            return(a-87);
    }

    std::string hexToString(std::string str){
        std::stringstream HexString;
        for(int i=0;i<str.length();i++){
            char a = str.at(i++);
            char b = str.at(i);
            int x = hexCharToInt(a);
            int y = hexCharToInt(b);
            HexString << (char)((16*x)+y);
        }
        return HexString.str();
    }
}

#endif
