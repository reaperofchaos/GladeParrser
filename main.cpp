#include <iostream>
#include <fstream>
#include <string>

#include "gladeTemplate.h"

int main(int argc, char* argv[])
{
	std::string outputFile;
	if(!argv[2]){
		outputFile = "src/main.c";
	}
	else
	{
		outputFile = argv[2];
	}
	if (argc != 2)
	{
		std::cout << "Usage:  GladeTemplateParser [input file] [output file]" << std::endl;
		return 0;
	}
	std::ifstream input(argv[1]);
	std::ofstream output(outputFile);
	std::ofstream makeFile("makefile");
	GladeTemplate glade;
	glade.setFileName(argv[1]);
	glade.setSrcFileName(outputFile);
	std::cout << "Reading glade/" << argv[1] << std::endl; 
	glade.read(input); 
	glade.getObjectTypes();
	std::cout << "Writing template c code to src/main.c" << std::endl; 
	glade.write(output); 
	std::cout << "Writing makefile" << std::endl; 
	glade.make(makeFile); 
}