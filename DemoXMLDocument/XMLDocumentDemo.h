#ifndef XML_DOC_DEMO
#define XML_DOC_DEMO
////////////////////////////////////////////////////////////////////////////////////////
//  XMLDocumentDemo.h - Demo Class to test all the XML Document Functionalities		  //
//  ver 1.0																			  //
//  Language:      Visual C++ 2013, Update 2										  //
//  Platform:      ASUS TP300L, Windows 8.1											  //
//  Application:   File Catalogue Project											  //
//  Author:        Sandesh Bellur Shashidhara, Syracuse University					  //
//                 (315) 751-4826, sbellurs@syr.edu									  //
////////////////////////////////////////////////////////////////////////////////////////
/*
*
* Package Operations:
* ===================
* This Class contains all test functions inorder to test the XML Document Functionalities
*
* Required Files:
* ===============
* XmlDocumentDemo.h, XmlDocumentDemo.cpp xmlElementParts.h, Tokenizer.h, XmlParts.cpp, Toker.cpp
* 
* Build Process:
* =============
* cl /TEST_XMLDOCUMENTDEMO /EHsc ../XmlDocument/XmlDocument.cpp ../Display/Display.cpp
* ../XMLParsing/Toker.cpp ../XMLParsing/XmlParts.cpp XmlDocumentDemo.cpp
*
* Public Interface:
* =================
* testFunctionalities() - Base function which invokes all the functions
* testFindAttributes() - Test Function to find element by passing attribute name
* testAddRoot() -  Test function to add root for a empty document tree
* testElements() - Test Function to get all the elements for a empty document tree
* testAddRemoveChildElements() - Test function to add and remove child elements
* testGetAllChildren() - Test function to get all the children related to a element 
* testGetAllAttributes() - Test function to get all the attributes for a element 
* testAddRemoveAttributes() - Test function to add or remove attributes for a element 
* testMoveAndWriteXMLDocument() - Test function to write to a file and invoke move operations
*
* Maintenance History:
* ====================
* ver 1.0 : 18 Mar 14
* - first release
*/

#include <iostream>
#include "../XmlDocument/XmlDocument.h"
#include "../Display/Display.h"
#include "../XMLParsing/Tokenizer.h"
#include "../XMLParsing/xmlElementParts.h"

class XmlDocumentDemo {
	public :
		XmlDocumentDemo(XmlProcessing::XmlDocument &doc) :document_(doc){

		};
		void testFunctionalities();
		void testFindAttributes();
		void testAddRoot();
		void testElements();
		void testAddRemoveChildElements();
		void testGetAllChildren();
		void testGetAllAttributes();
		void testAddRemoveAttributes();
		void testMoveAndWriteXMLDocument();
	private:
		XmlProcessing::XmlDocument& document_;
		Display display;		
};
#endif