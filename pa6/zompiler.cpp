// zompiler.cpp : Defines the entry point for the console application.
//

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "node.h"
#include <fstream>

extern int g_LineNumber;
extern NBlock* g_MainBlock;

extern int zompilerparse();
extern FILE* zompilerin;

int main(int argc, char* argv[])
{
	// Read input from the first command line parameter
	zompilerin = fopen(argv[1], "r");
	
	// Start the parse
	zompilerparse();
	
	// TODO: CodeGen from g_MainBlock
	CodeContext myContext;
	if (g_MainBlock != nullptr)
	{
		g_MainBlock->CodeGen(myContext);
	}
	// Close the file stream
	fclose(zompilerin);

	std::ofstream mFile;
	mFile.open("out.zom");
	for (std::string i : myContext.mOps)
	{
		mFile << i << "\n";
	}
	mFile.close();
	return 0;
}

void zompilererror(const char* s)
{
	std::cout << s << " on line " << g_LineNumber << std::endl;
}
