#include "Display.h"
/////////////////////////////////////////////////////////////////////
//  Display.cpp - Display the results of XML Document operations   //
//																   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013, Update 2                       //
//  Platform:      ASUS TP300L, Windows 8.1						   //
//  Application:   XML Document Model Project                      //
//  Author:        Sandesh Bellur Shashidhara, Syracuse University //
//                 (315) 751-4826, sbellurs@syr.edu		           //
/////////////////////////////////////////////////////////////////////

//----< display tree and output to file >----------------------------------------
void Display::generateDisplay(std::string treeType,std::string document){
	std::cout << "|-----------------Displaying " << treeType << " tree built---------------------|\n";
	std::cout << document ;
}

//----< display all the elements for a tag >----------------------------------------
void Display::generateElementSearch(std::string tags, std::vector<XmlProcessing::XmlDocument::sPtr> result){
	bool exists = false;
	std::cout << "\nInput Tag  '" << tags << "'\n";
	if (result.size() >=1) 
	std::cout <<"\n"<<  result.size()  << " below elements found for the tag "<< tags <<"\n";
	
	for each (auto var in result)
	{
		std::cout << var->toString();
		std::cout << "\n";
		exists = true;
	}
	if (!exists) {
		std::cout << "\n" << " No element found for the tag " << tags << "\n";
	}
}

//----< display element for a attribute  >----------------------------------------
void Display::generateAttributeSearch(std::string input,XmlProcessing::XmlDocument::sPtr pointer){
	std::cout << "Input Attribute  '" << input << "'\n";
	if (pointer) {
		std::cout << "Output : Attribute Id '" << input << "' is found in element '" << pointer->value()
			<< "'\n";
	}
	else {
		std::cout << "Output : Could not find any element for the attribute '" << input << "'\n";
	}
}

//----< display add child to a parent operation result >----------------------------------------
void Display::addChildResult(std::string parentTag, std::string childTag, bool res){
	std::cout << "\nInput Parent Element  '" << parentTag << "'\n";
	std::cout << "Input Child Element  '" << childTag << "'\n";
	if (res) {
		std::cout << "\n The below element was added successfully to the parent element '" 
			<< parentTag << "' \n'" << childTag << "'\n";
		std::cout << "\n The resultant tree is displayed at the end \n";
	}
	else {
		std::cout << "\n Failed to add the below element to the parent element '" << parentTag << 
			"'\n'" << childTag<<"'\n";
	}
}

//----< display remove child to a parent result >----------------------------------------
void Display::removeChildResult(std::string parentTag, std::string childTag, bool res){
	std::cout << "\nInput Parent Element  '" << parentTag << "'\n";
	std::cout << "Input Child Element  '" << childTag << "'\n";
	if (res) {
		std::cout <<"\n'"<< childTag <<"' element removed successfully from the parent element '" << parentTag  << "'\n";
		std::cout << "\n The resultant tree is displayed at the end \n";
	} else {
		std::cout <<"\n"<<" Failed to remove element '" << childTag << "' from the parent element '" << parentTag << "'\n";
	}
}

//----< display remove attribute result >----------------------------------------
void Display::removeAttrResult(std::string parentTag, std::string childTag, bool res){
	std::cout << "\nInput Element  '" << parentTag << "'\n";
	std::cout << "Input Attribute  '" << childTag << "'\n";
	if (res) {
		std::cout <<"\n'"<< childTag << "' attribute removed successfully from the element '" << parentTag << "\n";
		std::cout << "\n The resultant tree is displayed at the end \n";
	} else {
		std::cout <<"\n"<< " Failed to remove attribute '" << childTag << "' from the element '" << parentTag << "'\n";
	}
}

//----< display add attribute result >----------------------------------------
void Display::addAttrResult(std::string tag, std::string att, std::string val,bool res){
	std::cout << "\nInput Element  '" << tag << "'\n";
	std::cout << "Input Attribute  '" << att << "'\n";
	std::cout << "Input Attribute Value '" << val << "'\n";
	if (res) {
		std::cout << "\n'" << att <<  "' attribute added successfully to the element '" << tag << "'\n";
		std::cout << "\n The resultant tree is displayed at the end \n";
	}
	else {
		std::cout << "\n Failed to add attribute '"<< att<< "' to the tag :'" << tag <<
			 "'\n";
	}
}

//----< display all the children for a element >----------------------------------------
void Display::generateElementChildrens(std::string tag , std::vector<XmlProcessing::XmlDocument::sPtr> result) {
	std::cout << "\n Input Element '" << tag << "'\n";
	if (result.size() > 0) {
		std::cout << "\nFound below " << result.size() << " child elements for the parent element '" << tag <<"'\n\n";
	} else {
		std::cout << "\nFound O child elements for the parent element '" << tag << "'\n\n";
	}
	for each (auto var in result)
	{
		std::cout << var->value();
		std::cout << "\n";
	}
}

//----< find all the attributes for a element >----------------------------------------
void Display::generateElementAttributes(std::string elementTag, std::vector<std::pair<std::string, std::string>> results) {
	std::cout << "\n Input Element : '" << elementTag << "'\n";
	if (results.size() > 0) {
		std::cout << "\nFound below " << results.size() << " attributes for the tag '" << elementTag << "'\n";
	}
	else {
		std::cout << "\nFound O attributes for the tag '" << elementTag << "'\n";
	}
	for each (auto var in results)
	{
		std::cout << "Attribute ID : "<<var.first << "          Value :" << var.second;
		std::cout << "\n";
	}
}

//----< display adding root for a empty document >----------------------------------------
void Display::addRootResult(std::string rootName, bool res){
	std::cout << "\n\n Input Root Name '" << rootName << "'\n";
	if (res) {
		std::cout << "\nRoot '" << rootName << "' added successfully\n";
	}
	else {
		std::cout << "\nFailed to add '" << rootName <<"', Root already present\n";
	}
}

#ifdef TEST_DISPLAY
int main() {
	std::cout << "Test Stub of Display\n";

	XmlProcessing::XmlDocument document("LectureNote.xml", "file");
	Display display;

	display.generateDisplay("Initial",document.getDocumentString());
	std::cout << "\n\n";
	std::shared_ptr < XmlProcessing::AbstractXmlElement > attFnd = document.elementByAttr("course");
	display.generateAttributeSearch("course", attFnd);

	XmlProcessing::XmlDocument doc;
	bool rootRes = doc.generateRootElement("MyRoot");
	display.addRootResult("MyRoot", rootRes);

	std::vector<XmlProcessing::XmlDocument::sPtr> elementsNotFound = document.elements("college")
		.select();
	display.generateElementSearch("college", elementsNotFound);

	std::string child = "<MyLecture crs=\"CSE681\"></MyLecture>";
	bool addTagRes = document.addChild("title", child);
	display.addChildResult("title", child, addTagRes);

	bool removeRes = document.removeChild("author", "note");
	display.removeChildResult("author", "note", removeRes);

	std::vector<XmlProcessing::XmlDocument::sPtr> eleVector = document.elements("reference")
		.children().select();
	display.generateElementChildrens("reference", eleVector);

	std::vector<std::pair<std::string, std::string>> attrRes = document.elements("publisher")
		.getAttributes();
	display.generateElementAttributes("publisher", attrRes);

	bool addAttr = document.addAttribute("page", "section", "lecture 4");
	display.addAttrResult("page", "section", "lecture 4", addAttr);

	bool removeAttr = document.removeAttribute("LectureNote", "course");
	display.removeAttrResult("LectureNote", "course", removeAttr);
}
#endif