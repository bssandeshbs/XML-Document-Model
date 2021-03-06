# XML-Document-Model. 

Purpose:

This project requires you to develop an XML parsing facility that reads XML strings or text files, builds a Document object that can be queried for information about the XML contents, supports programmatic modification of the Document, and can write the revisions to another XML string or file. The project requires you to develop C++ modules to: parse the input, build a tree-based in-memory representation of the XML called a parse tree1, and support modifications of that representation. This facility will support read and write operations. It will also support the programmatic creation of new XML strings and files.

Requirements:

Your XML Framework:
1. Shall use standard C++2 and the standard library, compile and link from the command line, using Visual Studio 2013, as provided in the ECS clusters and operate in the environment provided there3.

2. Shall use services of the C++ std::iostream library for all input and output to and from the user’s console and C++ operator new and delete for all dynamic memory management.

3. Shall provide a facility to read XML strings and files and build an internal parse tree representation wrapped in a Document object. Each XML element is represented by a node in the tree. Each element may have a finite number of attributes, e.g., name-value pairs, stored in a std::vector in the element node. The Document shall support copy, move, and assignment operations4 as well as read and write operations to and from both strings and files.

4. Shall provide the capability to find any element based on its unique id attribute5 for all those elements that possess id attributes. If an element with the specified id attribute is found, a pointer to the element node is returned. If no such element exists a null pointer is returned.

5. Shall provide the capability to find a collection of elements that have a specified tag. The elements are returned with a std::vector that holds pointers to each element that has the specified tag. If no such elements exist, an empty vector is returned.

6. Shall provide the capability to add a child element to, and remove a child from, any element in the tree, found by id or tag. Addition returns a pointer to the added element. Removal returns a pointer to the parent from which the element was removed. Shall also provide the ability to add a root element to an empty document tree6.

7. Shall, given a pointer to any element, provide a facility to return a std::vector containing all the name-value attribute pairs attached to that element. If the element has no attributes an empty std::vector is returned.

8. Shall provide the ability to add or remove an attribute name-value pair from any element node.
 
9. Shall provide the capability to read an XML string or file and build the corresponding internal tree representation. Shall also provide the capability to write an XML string or file corresponding to the internal tree representation.

10. Shall provide an executive module that accepts a command line argument specifying an XML file to parse, displays the corresponding tree structure, adds a child element with tag “testTag” to an element with id “testId” and display the resulting tree, then remove the added element and redisplay the tree. The executive shall repeat this demonstration
