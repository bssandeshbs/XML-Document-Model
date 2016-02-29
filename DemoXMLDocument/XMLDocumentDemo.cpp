////////////////////////////////////////////////////////////////////////////////////////
//  XMLDocumentDemo.cpp - Demo Class to test all the XML Document Functionalities	  //
//  ver 1.0																			  //
//  Language:      Visual C++ 2013, Update 2										  //
//  Platform:      ASUS TP300L, Windows 8.1											  //
//  Application:   XML Document Model Project										  //
//  Author:        Sandesh Bellur Shashidhara, Syracuse University					  //
//                 (315) 751-4826, sbellurs@syr.edu									  //
////////////////////////////////////////////////////////////////////////////////////////
#include "XMLDocumentDemo.h"

//----< invokes all the XML Document functions >------------------------------------------
void XmlDocumentDemo::testFunctionalities() {
	std::cout << "\n|-------------------------------------------------------------------|\n";
	std::cout << "|-----------------Demonstrating Requirement 3 & 10------------------|\n";
	display.generateDisplay("Initial", document_.getDocumentString());
	testFindAttributes();
	testElements();
	testAddRemoveChildElements();
	testAddRoot();
	testGetAllAttributes();
	testGetAllChildren();
	testAddRemoveAttributes();
	std::cout << "\n|-------------------------------------------------------------------|\n";
	std::cout << "|-----------------Demonstrating Requirement 10----------------------|\n";
	display.generateDisplay("Final",document_.getDocumentString());
	testMoveAndWriteXMLDocument();
}

//----< find elements by attribute name >------------------------------------------
void XmlDocumentDemo::testFindAttributes() {
	std::cout << "\n|------------------------------------------------------------------|\n";
	std::cout << "|-----------------Demonstrating Requirement 5----------------------|\n";
	std::cout << "|-----------------Find Element By Attribute Id---------------------|\n";
	std::string attributeName = "id";
	std::shared_ptr < XmlProcessing::AbstractXmlElement > attFnd = document_.
		elementByAttr(attributeName);

	display.generateAttributeSearch(attributeName, attFnd);

	std::cout << "\n|-------------------------------------------------------------------|\n";
	std::cout << "|-----------------Demonstrating Requirement 5-----------------------|\n";
	std::cout << "|-----------------Find Element By Attribute Id----------------------|\n";
	std::string attributeNameNew = "rid";
	std::shared_ptr < XmlProcessing::AbstractXmlElement > attNotFnd = document_.elementByAttr(attributeNameNew);
	display.generateAttributeSearch(attributeNameNew, attNotFnd);
}

//----< get all the elements for a tag >-------------------------------------------------------
void XmlDocumentDemo::testElements() {
	std::cout << "\n|--------------------------------------------------------------------|\n";
	std::cout << "|-------------------Demonstrating Requirement 6----------------------|\n";
	std::cout << "|-------------------Find Collection of elements ---------------------|\n";
	std::string tag = "colleges";
	std::vector<XmlProcessing::XmlDocument::sPtr> elementsNotFound = document_.elements(tag)
		.select();
	display.generateElementSearch(tag,elementsNotFound);
	std::cout << "\n|--------------------------------------------------------------------|\n";
	std::cout << "|-------------------Demonstrating Requirement 6----------------------|\n";
	std::cout << "|-------------------Find Collection of elements ---------------------|\n";
	std::string tags = "college";
	std::vector<XmlProcessing::XmlDocument::sPtr> elementsFound = document_.elements(tags)
		.select();
	display.generateElementSearch(tags,elementsFound);
}

//----< add or remove child elements to a element >------------------------------------------
void XmlDocumentDemo::testAddRemoveChildElements() {
	std::cout << "\n|------------------------------------------------------------------|\n";
	std::cout << "|-----------------Demonstrating Requirement 7----------------------|\n";
	std::cout << "|-----------------Add Tagged element as child element--------------|\n";
	std::string child = "<MyLecture crs=\"CSE681\"></MyLecture>";
	std::string parentTag = "title";
	bool addChildRes = document_.addChild(parentTag, child);
	display.addChildResult(parentTag,child, addChildRes);
	std::cout << "\n|------------------------------------------------------------------|\n";
	std::cout << "|-----------------Demonstrating Requirement 7----------------------|\n";
	std::cout << "|-----------------Add comment child element------------------------|\n";
	std::string child2 = "<!-- Book Library -->";
	std::string parentTag2 = "title";
	bool addChildRes2 = document_.addChild(parentTag2, child2);
	display.addChildResult(parentTag2, child2, addChildRes2);
	std::cout << "\n|------------------------------------------------------------------|\n";
	std::cout << "|-----------------Demonstrating Requirement 7----------------------|\n";
	std::cout << "|-----------------Add Invalid child element------------------------|\n";
	std::string child1 = "<MyLecture crs=\"CSE681\"></MyLecture>";
	std::string parentTag1 = "InvalidTitle";
	bool addChildRes1 = document_.addChild(parentTag1, child1);
	display.addChildResult(parentTag1, child1, addChildRes1);	
	std::cout << "\n|------------------------------------------------------------------|\n";
	std::cout << "|-----------------Demonstrating Requirement 7----------------------|\n";
	std::cout << "|-----------------Remove Invalid child element---------------------|\n";
	std::string pTag1 = "author";
	std::string cTag1 = "Invalidnote";
	bool removeRes1 = document_.removeChild(pTag1, cTag1);
	display.removeChildResult(pTag1, cTag1, removeRes1);
	std::cout << "\n|------------------------------------------------------------------|\n";
	std::cout << "|-----------------Demonstrating Requirement 7----------------------|\n";
	std::cout << "|-----------------Remove Tagged child Element----------------------|\n";
	std::string pTag = "reference";
	std::string cTag = "date";
	bool removeRes = document_.removeChild(pTag, cTag);
	display.removeChildResult(pTag, cTag, removeRes);
	std::cout << "\n|------------------------------------------------------------------|\n";
	std::cout << "|-----------------Demonstrating Requirement 7----------------------|\n";
	std::cout << "|-----------------Remove Comment child Element---------------------|\n";
	std::string pTag2 = "reference";
	std::string cTag2 = "Book Information";
	bool removeRes2 = document_.removeChild(pTag2, cTag2);
	display.removeChildResult(pTag2, cTag2, removeRes2);
}


//----< add root to empty document >----------------------------------------------------------
void XmlDocumentDemo::testAddRoot() {
	std::cout << "\n|-------------------------------------------------------------------|\n";
	std::cout << "|-----------------Demonstrating Requirement 7-----------------------|\n";
	std::cout << "|----------------Add Root to Empty Document Tree--------------------|";
	std::string root = "NewRoot";
	XmlProcessing::XmlDocument doc;
	bool rootRes = doc.generateRootElement(root);
	display.addRootResult(root, rootRes);
	std::cout << doc.getDocumentString();

	std::cout << "\n|-------------------------------------------------------------------|\n";
	std::cout << "|-----------------Demonstrating Requirement 7-----------------------|\n";
	std::cout << "|----------------Add Root to Empty Document Tree--------------------|";
	bool rootRes1 = document_.generateRootElement(root);
	display.addRootResult(root, rootRes1);
	std::cout << doc.getDocumentString();
}


//----< get all the children for a element >------------------------------------------
void XmlDocumentDemo::testGetAllChildren() {
	std::cout << "\n|-------------------------------------------------------------------|\n";
	std::cout << "|-----------------Demonstrating Requirement 8B----------------------|\n";
	std::cout << "|-----------------Find All the Children for Element-----------------|\n";
	std::string elementTag = "reference";
	std::vector<XmlProcessing::XmlDocument::sPtr> eleVector = document_.elements(elementTag)
		.children().select();

	display.generateElementChildrens(elementTag, eleVector);

	std::cout << "\n|-------------------------------------------------------------------|\n";
	std::cout << "|-----------------Demonstrating Requirement 8B----------------------|\n";
	std::cout << "|-----------------Find All the Children for Element-----------------|\n";
	std::string elementTag1 = "referenceInvalid";
	std::vector<XmlProcessing::XmlDocument::sPtr> eleVector1 = document_.elements(elementTag1)
		.children().select();

	display.generateElementChildrens(elementTag1, eleVector1);
}

//----< get all the attributes for a element >------------------------------------------
void XmlDocumentDemo::testGetAllAttributes() {
	std::cout << "\n|-------------------------------------------------------------------|\n";
	std::cout << "|-----------------Demonstrating Requirement 8A----------------------|\n";
	std::cout << "|-----------------Find all the attributes for an Element------------|\n";
	std::string elementTag = "publisher";
	std::vector<std::pair<std::string, std::string>> attrRes = document_.elements(elementTag)
		.getAttributes();
	display.generateElementAttributes(elementTag,attrRes);

	std::cout << "\n|-----------------Demonstrating Requirement 8A----------------------|\n";
	std::cout << "|-----------------Find all the attributes for an Element------------|\n";
	std::string elementTag1 = "LectureNoteInvalid";
	std::vector<std::pair<std::string, std::string>> attrRes1 = document_.elements(elementTag1)
		.getAttributes();
	display.generateElementAttributes(elementTag1, attrRes1);
}

//----< add or remove attributes for a element >------------------------------------------
void XmlDocumentDemo::testAddRemoveAttributes() {
	std::cout << "\n|-----------------Demonstrating Requirement 9------------------------|\n";
	std::cout << "|-----------------Add attribute for an Element-----------------------|\n";
	std::string elementNam = "page";
	std::string key = "section";
	std::string value = "lecture 4";
	bool addAttr = document_.addAttribute(elementNam, key, value);
	display.addAttrResult(elementNam, key, value, addAttr);

	std::cout << "\n|-----------------Demonstrating Requirement 9------------------------|\n";
	std::cout << "|-----------------Add attribute for an Element-----------------------|\n";
	std::string elementNam1 = "Invalidpage";
	std::string key1 = "section";
	std::string value1 = "lecture 4";
	bool addAttr1 = document_.addAttribute(elementNam1, key1, value1);
	display.addAttrResult(elementNam1, key1, value1, addAttr1);

	std::cout << "\n|-----------------Demonstrating Requirement 9-----------------------|\n";
	std::cout << "|-----------------Remove attribute for an Element-------------------|\n";
	std::string removeKey = "course";
	std::string parentElementName = "LectureNote";
	bool removeAttr = document_.removeAttribute(parentElementName, removeKey);
	display.removeAttrResult(parentElementName, removeKey,removeAttr);
}

//----< functiont to test move operations and write to file >------------------------------------
void XmlDocumentDemo::testMoveAndWriteXMLDocument() {
	std::cout << "\n|-----Demonstrating Requirement 4 ---Move Constructor ------|\n";
	XmlProcessing::XmlDocument doc2 = std::move(document_);

	std::cout << "Move constructor is moving the contents of the current xmlDocument \nto the new object, doc2 and after move the old document object is null\nand cannot be referenced\n";

	std::cout << "\n|-------------Demonstrating Requirement 10-------------------|\n";
	std::cout << "Writing to XML file at location../Debug/output-new.xml using new object after move\n";
	std::ofstream myfile;
	myfile.open("output-new.xml");
	myfile << doc2.getDocumentString();

	XmlProcessing::XmlDocument doc;
	std::string root = "NewRoot";
	bool rootRes = doc.generateRootElement(root);
	doc2 = std::move(doc);
		
	std::cout << "\n|-----Demonstrating Requirement 4 ---Move Assignment ------|\n";
	std::cout << "Move Assignment is moving the xmldocument doc object to xmldocument doc2 object\n";
	std::cout << "\nDisplaying the tree after Move Assignment\n";
	std::cout << doc2.getDocumentString() <<"\n\n";
}

//----< test stub >--------------------------------------------

#ifdef TEST_XMLDOCUMENTDEMO
int main() {
	std::cout<<" Since its a Demo Class, The test stub is not applicable \n";
}
#endif