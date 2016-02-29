#ifndef DISPLAY_H
#define DISPLAY_H
/////////////////////////////////////////////////////////////////////
//  Display.h - Display the results of XML Document operations     //
//																   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013, Update 2                       //
//  Platform:      ASUS TP300L, Windows 8.1						   //
//  Application:   XML Document Model Project                      //
//  Author:        Sandesh Bellur Shashidhara, Syracuse University //
//                 (315) 751-4826, sbellurs@syr.edu		           //
/////////////////////////////////////////////////////////////////////
/*
*
* Module Operations:
* ===================
* The purpose of this module is to display the results of XML Document operations
*
* Required Files:
* ===============
* Display.h, Display.cpp, xmlElementParts.h, Tokenizer.h, XmlParts.cpp, Toker.cpp
*
* Build Process:
* ==============
* cl /DTEST_DISPLAY ../XMLParsing/Toker.cpp ../XMLParsing/XmlParts.cpp ProcessFile.cpp
*  ../XMLDocument/XMLDcoument.cpp ../XMLElement/XMLElement.cpp Display.cpp
*
* Public Interface:
* =================
* void generateDisplay(std::string,std::string); -> Displays the toString() of the pDocument
* void generateAttributeSearch(std::string input, XmlProcessing::XmlDocument::sPtr pointer);
*     - Get element for the attribute
* void generateElementSearch(std::string tags,std::vector<XmlProcessing::XmlDocument::sPtr>);
*	  - Get all the elements for the tag
* void addChildResult(std::string parentTag, std::string childTag, bool res);
*     - Displays the result of add child operation
* void removeChildResult(std::string parentTag, std::string childTag, bool res);
*     - Displays the result of remove child operation
* void removeAttrResult(std::string parentTag, std::string childTag, bool res);
*	  - Displays the result of remove attribute
* void addAttrResult(std::string tag, std::string att, std::string val, bool res);
*     - Displays the result of add attribute
* void addRootResult(std::string rootName,bool res);
*     - Displays the result of add root
* void generateElementChildrens(std::string tag, std::vector<XmlProcessing::XmlDocument::sPtr>);
*    - Displays all the children for the tag
* void Display::generateElementAttributes(std::string elementTag,std::vector<std::pair<std::string, std::string>> results); -> displays the attributes of child
*
*
* Usage :
* ==================
* Display display
* display.generateDisplay("Initial","pDocument");
* display.generateAttributeSearch("id",sharedPointer);
* display.generateElementSearch(tag,vector<sharedPointer>);
* display.addChildResult(parentTag,childTag,res);
* display.removeChildResult(parentTag,childTag,res);
* display.removeAttrResult(tag,attribute,val,res);
* display.addAttrResult(tag,attribute,val,res);
* display.addRootResult(rootName,res);
* display.generateElementChildrens(tag,vector<sharedPointers>);
*
*
* Maintenance History:
* ====================
* ver 1.0 : 18 Mar 14
* - first release
*/

#include <iostream>
#include <vector>
#include "../XmlDocument/XmlDocument.h"
#include "../XmlElement/XmlElement.h"

class Display{
	public: 
		void generateDisplay(std::string treeType, std::string document);
		void generateAttributeSearch(std::string input, XmlProcessing::XmlDocument::sPtr pointer);
		void generateElementSearch(std::string tags,std::vector<XmlProcessing::XmlDocument::sPtr>);
		void addChildResult(std::string parentTag, std::string childTag, bool res);
		void removeChildResult(std::string parentTag, std::string childTag, bool res);
		void removeAttrResult(std::string parentTag, std::string childTag, bool res);
		void addAttrResult(std::string tag, std::string att, std::string val, bool res);
		void addRootResult(std::string rootName,bool res);
		void generateElementChildrens(std::string tag, std::vector<XmlProcessing::XmlDocument::sPtr>);
		void generateElementAttributes(std::string elementTag, 
			std::vector<std::pair<std::string, std::string>> results);
};
#endif