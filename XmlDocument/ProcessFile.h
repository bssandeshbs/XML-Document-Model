#ifndef PROCESS_FILE
#define PROCESS_FILE
/////////////////////////////////////////////////////////////////////
//  ProcessFile.h - Reads the XML file or String and               //
//					Generates a set of tokens					   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013, Update 2                       //
//  Platform:      ASUS TP300L, Windows 8.1						   //
//  Application:   XML Document Project 		                   //
//  Author:        Sandesh Bellur Shashidhara, Syracuse University //
//                 (315) 751-4826, sbellurs@syr.edu		           //
/////////////////////////////////////////////////////////////////////
/*
*
* Module Operations:
* ===================
* The purpose of this module is to call the parser based on the type of the file type passed and  
* return the set of strings as tokens. 
* 
* Required Files:
* ===============
* ProcessFile.h, ProcessFile.cpp, xmlElementParts.h, Tokenizer.h, XmlParts.cpp, Toker.cpp
*
* Build Process:
* ==============
* cl /DTEST_PROCESSFILE ../XMLParsing/Toker.cpp ../XMLParsing/XmlParts.cpp ProcessFile.cpp
*
* Public Interface:
* =================
* std::vector<std::string> processFile(const std::string& src, const std::string& fileName); 
*  - output : Set of tokens generated by the parser for the input
* std::string parseSingleInput(std::string inputString);
*  - ouput - parse a single Input String
*
* Usage :
* ==================
* processFile("file","LectureNotes.xml"); 
* parseSingleInput("<a></a>");
*
* Maintenance History:
* ====================
* ver 1.0 : 18 Mar 14
* - first release
*/

#include <iostream>
#include <string>
#include "../XMLParsing/Tokenizer.h"
#include "../XMLParsing/xmlElementParts.h"
#include <vector>

class ProcessFile {
	public: std::vector<std::string> processFile(const std::string& src, const std::string& fileName);
			std::string parseSingleInput(std::string inputString);
};
#endif