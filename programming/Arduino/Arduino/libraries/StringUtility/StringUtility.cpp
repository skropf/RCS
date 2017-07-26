#include "StringUtility.h"
#include <iterator> 
#include <list> 
#include <vector>
#include <Log.h>
#include <MemoryFree.h>
#include <memory>

void StringUtility::split(char* input,char* splitChars,std::vector<char*> &params)
{
	Log::serial("spliting text: ");
	Log::serial(input);
	
	
	char * pch;
  	pch = strtok (input,splitChars);
  	while (pch != NULL)
  {
    params.push_back(pch);
    pch = strtok (NULL, splitChars);
  }
			
	/*Log::serial("Elems: intern");
	Log::serial(params[0]);
	Log::serial(params[1]);
	Log::serial(params[2]);
	Log::serial(params[3]);*/
}
//char* StringUtility::merge(std::vector<char*> params,char splitChar)
//{
//	String erg = String("");
//	std::vector<String>::const_iterator it;
//	for(it=params.begin();it!=params.end();it++)
//	{
//		erg+=*it;
//		erg+=splitChar;
//	}
//	return erg;
//}
int callatoi(char* param)
{
	return atoi(param);
}
int StringUtility::atoi(char* param)
{
  	int id = callatoi(param);
  	return id;
}
char* callitoa(int param,char* buffer, int n)
{
	itoa(param,buffer,n);
}
char* StringUtility::itoa(int param)
{
	char* buffer = (char*)malloc(10);
	callitoa(param,buffer,10);
	int len = strlen(buffer);
	char* returnvalue = (char*) malloc(len+2);
	free(buffer);
	strncpy(returnvalue,buffer,len+1);
  	return returnvalue;
}
