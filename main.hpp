#include <iostream>
#include "rapidxml-1.13/rapidxml_ext.hpp" 
#include "rapidxml-1.13/rapidxml_utils.hpp" 
#include <sstream>
#include <fstream>

using namespace std;
using namespace rapidxml; //Namespace de la librería

void extractXMLData(xml_document<>* doc);
void extractNodeData(xml_node<>* node);