/***************************************************************************
 * File: Glaeser_Noemi_FileGen.cpp
 * Author: Noemi Glaeser
 * Function: Randomly generates 100 input files for each input size in
 *           {10, 100, 1000, 10000, 100000}.
 * Input: 
 * Output: output.txt (ASCII file of sorted floating point numbers separated 
 *         by space)
 * Date: 23-Oct-2017
 ***************************************************************************/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include <vector>

int main(int argc, char * * argv)
{
  static const int filesizes[] = {10, 100, 1000, 10000, 100000};
  const int sampleSize = 100;
  const float MIN(-1e10), MAX(1e10);

  std::default_random_engine generator;
  std::uniform_real_distribution<float> distribution(MIN, MAX);

  for(int size : filesizes)
  {
    for(int i=0; i < sampleSize; i++)
    {
      // create new file with name e.g. "input1000num34"
      std::string filename = "input" + std::to_string(size) + "num" + std::to_string(i);
      std::ofstream file(filename);
  
      if(!file)
      {
        std::cout << "Error creating output file\n";
        exit(1);
      }
  
      for(int j=0; j < size; j++)
      { 
        int num = distribution(generator);
        file << distribution(generator) << " ";
      }
      file.close();
    }
  }
}
