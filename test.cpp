#include "picosha2.h"
#include <iostream> 
#include <string>

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

int main(int, char**)
{
  
  std::string hex_str = "000000000000000000ad6e90c0790e83760a9d13728c23474352a2c8c7a6e0eb";
  std::string hex_str2 = "026765a1c8235d4ac23d2582cda3b9f5c062f805540320173eb9e9148c0dc518704b42e4b11ca131b443c2b02a07ec0b45407f1b125027e3e68b86ace692445800000001";

  std::cout << picosha2::hash256_hex_string(hexToString(hex_str2)) << std::endl;

  return 0;
}
