#ifndef StringUtility_h
#define StringUtility_h

#include <iterator> 
#include <list> 
#include <vector>
#include <memory>


class StringUtility
{
	public:
  	static void split(char* input,char* splitChar,std::vector<char*>& params);
  	//static String merge(std::vector<char*>,char);
  	static int atoi(char*);
  	static char* itoa(int);
};

#endif