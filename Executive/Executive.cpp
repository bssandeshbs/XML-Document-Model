/////////////////////////////////////////////////////////////////////
//  Exceution.cpp - The first package that gets called             //
//					Oversees the control flow in the application   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013, Update 2                       //
//  Platform:      ASUS TP300L, Windows 8.1						   //
//  Application:   XML Document Model Project	                   //
//  Author:        Sandesh Bellur Shashidhara, Syracuse University //
//                 (315) 751-4826, sbellurs@syr.edu		           //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include "../XmlDocument/XmlDocument.h"
#include "../DemoXMLDocument/XMLDocumentDemo.h"

std::string processCommandLine(int argc, char* argv[]);

//----< First entry point to the applcation which contains user inputs >------------------------
int main(int argc, char* argv[]) {
	try {
		std::string type = processCommandLine(argc, argv);
		if (type != "") {
			XmlProcessing::XmlDocument document(argv[1], type);
			XmlDocumentDemo demo(document);
			demo.testFunctionalities();
		}
	}
	catch (...) {
		std::cout << "Exception \n\n";
	}
}

//----< Process Command Line Inputs >------------------------
std::string processCommandLine(int argc, char* argv[]){
	std::string type;
	try
	{
		if (argc < 2){
			std::cout<< "\n  please enter name of file to process on command line\n\n";
			return "";
		}
		std::string filename = argv[1];
		std::string substr = "txt";
		if (0 == filename.compare(filename.length() - substr.length(), substr.length(), substr)) {
			return "string";
		}
		else {
			return "file";
		}
	}
		catch (std::exception ex)
	{
		std::cout << "\n  " << ex.what() << "\n\n";
	}
	return "";
}
