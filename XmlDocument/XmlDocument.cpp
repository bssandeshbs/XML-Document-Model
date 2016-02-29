////////////////////////////////////////////////////////////////////////////////////////
//  XmlDocument.cpp - Container of XML Element Nodes							      //
//  ver 1.3																			  //
//  Language:      Visual C++ 2013, Update 2										  //
//  Platform:      ASUS TP300L, Windows 8.1											  //
//  Application:   XML Document Model Project										  //
//  Author:        Sandesh Bellur Shashidhara, Syracuse University					  //
//                 (315) 751-4826, sbellurs@syr.edu									  //
//	Original																		  //
//  Intial Author:      Jim Fawcett, jfawcett@twcny.rr.com						      //
//              																      //
////////////////////////////////////////////////////////////////////////////////////////

#include "XmlDocument.h"

using namespace XmlProcessing;

//----< xml document constructor taking fileName and type as input >------------------------------------
XmlProcessing::XmlDocument::XmlDocument(const std::string& fileName, const std::string& src){
	pDocElement_ = makeDocElement();
	tokens = processFile(fileName, src);
	buildTree();
}

//----< default constructor >
XmlProcessing::XmlDocument::XmlDocument() {
	pDocElement_ = makeDocElement();
}

//----< move constructor >
XmlDocument::XmlDocument(XmlDocument&& s) :rootStarted(s.rootStarted), pDocElement_(s.pDocElement_), found_(s.found_), taggedElementstack(s.taggedElementstack), rootTagNode(s.rootTagNode), tokens(s.tokens), processFl(s.processFl){
	s.rootStarted = false;
	s.pDocElement_.reset();
	found_.clear();
	while (!s.taggedElementstack.empty()) {
		s.taggedElementstack.pop();
	}
	s.taggedElementstack.empty();
	s.rootTagNode = "";
	s.tokens.clear();
}

//----< move assignment operator >
XmlDocument& XmlDocument::operator = (XmlDocument&& s){
	rootStarted = s.rootStarted;
	pDocElement_ = s.pDocElement_;
	found_ = s.found_;
	taggedElementstack = s.taggedElementstack;
	rootTagNode = s.rootTagNode;
	tokens = s.tokens;
	processFl = s.processFl;

	//clearing all the values
	s.rootStarted = false;
	s.pDocElement_.reset();
	found_.clear();
	while (!s.taggedElementstack.empty()) {
		s.taggedElementstack.pop();
	}
	s.rootTagNode = "";
	s.tokens.clear();
	return *this;
}

//----< Build tokens taking fileName and type as input >------------------------------------
std::vector<std::string> XmlDocument::processFile(const std::string& fileName, const std::string& src) {
	return processFl.processFile(fileName, src);
}

//----< Find Element by attribute Id >------------------------------------
std::shared_ptr < AbstractXmlElement > XmlProcessing::XmlDocument::
elementByAttr(const std::string& id){

	std::vector<std::shared_ptr<AbstractXmlElement>> sPtr = pDocElement_->getChildren();
	std::shared_ptr<AbstractXmlElement> res;
	for (auto a : sPtr){
		res = findAttr(a, id);
		if (res) {
			return res;
		}
	}
	return false;
}

//----< Find elements based on tag >------------------------------------
XmlDocument& XmlProcessing::XmlDocument::elements(const std::string& tag){
	found_.clear();
	std::vector<std::shared_ptr<AbstractXmlElement>> sPtr = pDocElement_->getChildren();
	for (auto a : sPtr){
		findElement(a, tag);
	}
	return *this;
}

//----< Find descendents of an element >------------------------------------
XmlDocument& XmlProcessing::XmlDocument::descendents(const std::string& tag) {
	if (found_.size() >= 1) {
		std::shared_ptr < AbstractXmlElement > sptr = found_[0];
		found_.clear();
		std::vector<std::shared_ptr<AbstractXmlElement>> sPtr = sptr->getChildren();
		for (auto e : sPtr) {
			findDescendents(e, tag);
		}
	}
	return *this;
}

//----< Recursive function to find descendents of an element >------------------------------------
void XmlProcessing::XmlDocument::findDescendents(std::shared_ptr<AbstractXmlElement> sptr, const std::string& tag){
	if (tag == "") {
		found_.push_back(sptr);
		for (auto sp : sptr->getChildren()) {
			findDescendents(sp, tag);
		}
	}
	else {
		if (tag == sptr->value()) {
			found_.push_back(sptr);
		}
		for (auto sp : sptr->getChildren()) {
			findDescendents(sp, tag);
		}
	}
}


//----< Get all children related to a element >------------------------------------
std::vector<std::pair<std::string, std::string>> XmlProcessing::XmlDocument::getAttributes() {
	std::vector<std::pair<std::string, std::string>> v;
	if (found_.size() >= 1) {
		std::shared_ptr < AbstractXmlElement > sptr = found_[0];
		found_.clear();
		return sptr->getAttributes();
	}
	return v;
}

//----< Get all the children related to a tag >------------------------------------
XmlDocument& XmlProcessing::XmlDocument::children(const std::string& tag) {
	if (found_.size() >= 1) {
		std::shared_ptr < AbstractXmlElement > sptr = found_[0];
		found_.clear();
		std::vector<std::shared_ptr<AbstractXmlElement>> childrens = sptr->getChildren();
		for (auto sp : childrens) {
			found_.push_back(sp);
		}
	}
	return *this;
}

//----< Recursive function to find elements based on tag >------------------------------------
void XmlProcessing::XmlDocument::findElement(std::shared_ptr<AbstractXmlElement> sptr,
	const std::string& tag){
	if (dynamic_cast<XmlProcessing::TaggedElement*>(sptr.get()) != nullptr || dynamic_cast<XmlProcessing::XmlDeclarElement*>(sptr.get()) != nullptr ||
		dynamic_cast<XmlProcessing::ProcInstrElement*>(sptr.get()) != nullptr) {
		if (sptr->value() == tag) {
			found_.push_back(sptr);
		}
	}

	for (auto sp : sptr->getChildren()) {
		findElement(sp, tag);
	}
}

//----< find attribute for each element,by taking attribute Id and value as input >----------------
std::shared_ptr<AbstractXmlElement> XmlProcessing::XmlDocument::findAttr(std::shared_ptr<AbstractXmlElement> sptr, const std::string& id){
	std::vector<std::pair<std::string, std::string>> keyPair = sptr->getAttributes();
	std::shared_ptr<AbstractXmlElement> spRes;

	for (auto k : keyPair){
		if (k.first == id){
			spRes = sptr;
			return spRes;
		}
	}

	for (auto sp : sptr->getChildren()) {
		std::shared_ptr<AbstractXmlElement> spRes = findAttr(sp, id);
		if (spRes) {
			return spRes;
		}
	}
	return spRes;
}

//----< add child to a tag>--------------------------------------------------------
bool XmlProcessing::XmlDocument::addChild(const std::string& parentTag, const std::string& childTag){
	std::vector<std::shared_ptr<AbstractXmlElement>> sPtr = pDocElement_->getChildren();
	for (auto a : sPtr){
		if (dynamic_cast<XmlProcessing::TaggedElement*>(a.get()) != nullptr) {
			findElement(a, parentTag);
		}
		if (found_.size() > 0) {
			std::shared_ptr<AbstractXmlElement> parent = found_[0];
			found_.clear();
			std::string parsedString = processFl.parseSingleInput(childTag);
			std::vector<std::string> res = split(parsedString, ' ');
			std::shared_ptr < AbstractXmlElement >  sp1 = determineType(res);
			addAttribute(res, sp1);
			parent->addChild(sp1);
			return true;
		}
	}
	return false;
}

//----< remove child from a tag>--------------------------------------------------------
bool XmlProcessing::XmlDocument::removeChild(const std::string& parentTag, const std::string& tag) {
	std::vector<std::shared_ptr<AbstractXmlElement>> sPtr = pDocElement_->getChildren();
	for (auto a : sPtr){		
			findElement(a, parentTag);
		if (found_.size() > 0) {
			std::shared_ptr<AbstractXmlElement> parent = found_[0];
			found_.clear();
			TaggedElement* te = dynamic_cast<TaggedElement*>(parent.get());
			if (te != nullptr){
				bool res =  te->removeChild(tag);
				return res;
			}
		}
	}
	return false;
}

//----< add attribute to a element>--------------------------------------------------------
bool  XmlProcessing::XmlDocument::addAttribute(const std::string& parentTag, const std::string& attributeName, const std::string& attributeValue) {
	std::vector<std::shared_ptr<AbstractXmlElement>> sPtr = pDocElement_->getChildren();
	for (auto a : sPtr){
		if (dynamic_cast<XmlProcessing::TaggedElement*>(a.get()) != nullptr || dynamic_cast<XmlProcessing::XmlDeclarElement*>(a.get()) != nullptr ||
			dynamic_cast<XmlProcessing::ProcInstrElement*>(a.get()) != nullptr) {
			findElement(a, parentTag);
		}
		if (found_.size() > 0) {
			std::shared_ptr<AbstractXmlElement> parent = found_[0];
			found_.clear();
			return parent->addAttrib(attributeName, attributeValue);
		}
	}
	return false;
}

//----< remove attribute from a element>--------------------------------------------------------
bool  XmlProcessing::XmlDocument::removeAttribute(const std::string& parentTag, const std::string& attributeName) {
	std::vector<std::shared_ptr<AbstractXmlElement>> sPtr = pDocElement_->getChildren();
	for (auto a : sPtr){
		if (dynamic_cast<XmlProcessing::TaggedElement*>(a.get()) != nullptr || dynamic_cast<XmlProcessing::XmlDeclarElement*>(a.get()) != nullptr ||
			dynamic_cast<XmlProcessing::ProcInstrElement*>(a.get()) != nullptr) {
			findElement(a, parentTag);
		}
		if (found_.size() > 0) {
			std::shared_ptr<AbstractXmlElement> parent = found_[0];
			found_.clear();
			return parent->removeAttrib(attributeName);
		}
	}
	return false;
}

//----< function to attributes from  input>--------------------------------------------------------
void XmlProcessing::XmlDocument::addAttribute(std::vector<std::string> res,
	std::shared_ptr < AbstractXmlElement > sp1){
	std::vector<std::string>::iterator it;
	int counter = 0;
	bool rec = false;
	std::string multiAttr = "";
	std::string key;
	char c;
	for (it = res.begin(); it != res.end(); ++it){
		if (*it == "="){
			std::string val = res[it - res.begin() + 1];
			key = res[it - res.begin() - 1];
			if (val[0] == val[val.size() - 1]) {
				sp1->addAttrib(key, val.substr(1, val.size() - 2));
			}
			else {
				c = val[0];
				rec = true;
			}
		}
		else {
			if (rec) {
				multiAttr = multiAttr + " " + *it;
				std::string val = *it;
				if (val[val.size() - 1] == c) {
					rec = false;
					sp1->addAttrib(key, multiAttr.substr(2, multiAttr.size() - 3));
					multiAttr.clear();
				}
			}
		}
	}
}

//----< build comment element>--------------------------------------------------------
std::string XmlProcessing::XmlDocument::addComment(std::vector<std::string> res){
	int i = 0;
	std::vector<std::string>::iterator it;
	std::string commentString = "";
	for (it = res.begin() + 4; it != res.end()-1; ++it){
		commentString = commentString + " " + *it;
	}

	unsigned found = commentString.find_last_of("-");
	commentString = commentString.substr(0, found);
	unsigned found1 = commentString.find_last_of("-");
	commentString = commentString.substr(0, found1);

	while (std::isspace(*commentString.begin()))
		commentString.erase(commentString.begin());

	while (std::isspace(*commentString.rbegin()))
		commentString.erase(commentString.length() - 1);
	return commentString;
}

//----< Builds the abstract syntax tree by reading all the tokens>-----------------------------
void XmlProcessing::XmlDocument::buildTree(){
	for (auto token : tokens) {
		std::vector<std::string> res = split(token, ' ');
		if (res[1] == "<" && res[2] == "?") //Its a xml declaration element of processing Instruction
		{
			std::vector <std::string>::iterator i = res.begin();
			if (!(std::find(res.begin(), res.end(), "version") == res.end()) && res[3] == "xml") {
				std::shared_ptr < AbstractXmlElement >  sp1 = makeXmlDeclarElement();
				addAttribute(res, sp1);
				pDocElement_->addChild(sp1);
			}
			else { //check if its a Procesing Instruction
				std::shared_ptr < AbstractXmlElement >  sp1 = makeProcInstrElement(res[3]);
				std::vector<std::string>::iterator it;
				addAttribute(res, sp1);
				pDocElement_->addChild(sp1);
			}
		}
		else if (res[1] == "<" && res[2] == "!"&& res[3] == "--") { //check if its a comment
			if (!rootStarted) {
				std::shared_ptr < AbstractXmlElement >  sp1 = makeCommentElement(addComment(res));
				pDocElement_->addChild(sp1);
			}
			else buildTaggedRoot(token);
		}
		else { // called buildTaggedElement to process the complete tagged Element
			if (res.size() >= 3 && res[1] == "<") rootStarted = true;
			if (rootStarted) buildTaggedRoot(token);
			else if (res.size() >= 3) buildTaggedRoot(token);
		}
	}
}

//----< Detect Tagged Element >-------------------------------------
void XmlProcessing::XmlDocument::buildTaggedRoot(std::string token) {
	try {
		std::vector<std::string> res = split(token, ' ');
		std::string endingtoken = res[res.size() - 2];
		if (taggedElementstack.empty()){
			rootTagNode = res[2];
			std::shared_ptr < AbstractXmlElement >  sp1 = determineType(res);
			if (dynamic_cast<XmlProcessing::TaggedElement*>(sp1.get()) != nullptr) {
				taggedElementstack.push(sp1);
			}
			addAttribute(res, sp1);
			pDocElement_->addChild(sp1);
			return;
		}
		if (res.size() >= 3 && res[2] == "/") {
			std::shared_ptr < AbstractXmlElement > top = taggedElementstack.top();
			if (top->value() == rootTagNode) rootStarted = false;
			taggedElementstack.pop();
			return;
		}
		//opening tag is ending, so just add to parent, no need to push to vector
		if (endingtoken == "/") {
			std::shared_ptr < AbstractXmlElement >  sp1 = taggedElementstack.top();
			std::shared_ptr < AbstractXmlElement >  sp2 = determineType(res);
			std::vector<std::string>::iterator it;
			addAttribute(res, sp2);
			sp1->addChild(sp2);
		}
		//Add the element and push to the stack
		else {
			std::shared_ptr < AbstractXmlElement >  sp1 = taggedElementstack.top();
			std::shared_ptr < AbstractXmlElement >  sp2 = determineType(res);
			std::vector<std::string>::iterator it;
			addAttribute(res, sp2);
			sp1->addChild(sp2);
		}
	}
	catch (...) {
	}
}

//----< Determine type of element while building the tree>--------------------------------------
std::shared_ptr < AbstractXmlElement > XmlProcessing::XmlDocument::determineType(std::vector<std::string> token){
	if (token.size() > 2 && token[2] == "!") {
		return makeCommentElement(addComment(token));
	}
	else if (token.size() > 1 && token[1] == "<"){
		std::string endingtoken = token[token.size() - 2];
		std::shared_ptr < AbstractXmlElement >  sp2 = makeTaggedElement(token[2]);
		if (endingtoken != "/"){
			taggedElementstack.push(sp2);
		}
		return sp2;
	}
	else {
		std::string textElement;
		bool init = false;
		for (auto a : token){
			if (init) {
				textElement = textElement + " " + a;
			}
			else {
				textElement = a;
				init = true;
			}
		}
		while (std::isspace(*textElement.begin()))
			textElement.erase(textElement.begin());

		while (std::isspace(*textElement.rbegin()))
			textElement.erase(textElement.length() - 1);

		return makeTextElement(textElement);
	}
}

//----< Utility function to split the string >-------------------------------------
std::vector<std::string> XmlProcessing::XmlDocument::split(const std::string &str, const char &delim) {
	typedef std::string::const_iterator iter;
	iter beg = str.begin();
	std::vector<std::string> tokens;
	while (beg != str.end()) {
		iter temp = std::find(beg, str.end(), delim);
		if (beg != str.end())
			tokens.push_back(std::string(beg, temp));
		beg = temp;
		while ((beg != str.end()) && (*beg == delim))
			beg++;
	}
	return tokens;
}

//----< function to check if root element is present >-------------------------------------
bool XmlProcessing::XmlDocument::generateRootElement(const std::string& parentTag) {
	bool isRoot = false;
	for (auto s : pDocElement_->getChildren()){
		if (dynamic_cast<XmlProcessing::TaggedElement*>(s.get()) != nullptr)
			isRoot = true;
	}
	if (!isRoot) {
		pDocElement_->addChild(makeTaggedElement(parentTag));
		return true;
	}
	return false;
}

//----< function to return document string >--------------------------------------------
std::string XmlProcessing::XmlDocument::getDocumentString() {
	return pDocElement_->toString();
}

//----< function to return the found_ by clearing found_ >------------------------------
std::vector<std::shared_ptr < AbstractXmlElement >> XmlProcessing::XmlDocument::select() {
	return std::move(found_);
}


//----< test stub >----------------------------------------------------------

#ifdef TEST_XMLDOCUMENT
int main()
{
	title("Testing XmlDocument class");

	XmlDocument document("LectureNote.xml","file");
	std::cout<<"\n"<<document.getDocumentString();

	std::shared_ptr < XmlProcessing::AbstractXmlElement > attFnd = document.elementByAttr("course");
	if (attFnd) std::cout << "\n Found element: " << attFnd->value()<<"\n";

	XmlProcessing::XmlDocument doc;
	bool rootRes = doc.generateRootElement("NewRoot");
	if (rootRes) std::cout << "\n\nRoot added succesfully\n";

	std::vector<XmlProcessing::XmlDocument::sPtr> elementsNotFound = document.elements("college")
		.select();
	std::cout << "\n" << elementsNotFound.size() << " elements found for the tag college\n";

	std::string child = "<MyLecture crs=\"CSE681\"></MyLecture>";
	bool addTagRes = document.addChild("title", child);
	if (addTagRes) std::cout << "\ntag added succesfully\n";

	bool removeRes = document.removeChild("author", "note");
	if (removeRes) std::cout << "\ntag removed succesfully\n";

	std::vector<XmlProcessing::XmlDocument::sPtr> eleVector = document.elements("reference")
		.children().select();
	if (eleVector.size() > 0) std::cout << "\nchildren found for the tag reference\n";

	std::vector<std::pair<std::string, std::string>> attrRes = document.elements("publisher")
		.getAttributes();
	if (attrRes.size() >= 0) std::cout << "\n found " << attrRes.size() << " attributes \n\n";

	bool addAttr = document.addAttribute("page", "section", "lecture 4");
	if (addAttr) std::cout << "section attribute added successfully to page\n";

	bool removeAttr = document.removeAttribute("LectureNote", "course");
	if (removeAttr) std::cout << "\ncourse attribute removed succesfully\n";
}
#endif