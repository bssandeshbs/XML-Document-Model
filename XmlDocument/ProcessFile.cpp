/////////////////////////////////////////////////////////////////////
//  ProcessFile.cpp - Reads the XML file or String and             //
//					Generates a set of tokens					   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013, Update 2                       //
//  Platform:      ASUS TP300L, Windows 8.1						   //
//  Application:   XML Document Model Project	                   //
//  Author:        Sandesh Bellur Shashidhara, Syracuse University //
//                 (315) 751-4826, sbellurs@syr.edu		           //
/////////////////////////////////////////////////////////////////////
#include "ProcessFile.h"

//----< contructs tokens using parser for the input file >------------------------------------------
std::vector<std::string> ProcessFile::processFile(const std::string& fileName, const std::string& src){

	std::vector<std::string> tokens;
	try {
		std::string input;
		bool type = true;
		if (src == "file") {
			input = fileName;
		}
		else {
			type = false;
			std::ifstream t(fileName);
			std::string inputRes((std::istreambuf_iterator<char>(t)),
				std::istreambuf_iterator<char>());
			input = inputRes;
		}

		if (input.size() >= 1) {
			Toker toker(input, type);
			toker.setMode(Toker::xml);
			XmlParts parts(&toker);
			bool firstToken = true;
			while (parts.get()) {
				std::string val = parts.show().c_str();
				if (val.size() == 3 && firstToken) {
					firstToken = false;
				}
				else {
					firstToken = true;
					tokens.push_back(parts.show().c_str());
				}
			}
			return tokens;
		}
		else {
			return tokens;
		}
	}
	catch (std::exception ex)
	{
		std::cout << "\n  " << ex.what() << "\n\n";
		return tokens;
	}
}

//----< parse a single string >------------------------------------------
std::string ProcessFile::parseSingleInput(std::string inputString) {
	try {
		if (inputString.size() > 1) {
			Toker toker(inputString, false);
			toker.setMode(Toker::xml);
			XmlParts parts(&toker);
			//bool firstVal = true;
			while (parts.get()) {
				std::string res = parts.show().c_str();
				return res;
			}
		}
		return "";
	}
	catch (std::exception ex)
	{
		std::cout << "\n  " << ex.what() << "\n\n";
		return "";
	}
}
