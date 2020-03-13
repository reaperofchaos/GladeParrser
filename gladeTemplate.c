#include "gladeTempate.h"
void GladeTemplate::read(std::istream& is){
	
	while(is)
	{
		string line; 
		//read line by line
		getLine(is, line);
		//find <object class
		GladeTemplate::getTag(line, "object");
	}
}

void GladeTemplate::getTag(const string &text, string tag){
                                                          
   vector<GtkWidget> collection;
   unsigned int pos = 0, start, 
				classStart, classEnd = 0, 
				idStart, idEnd=0
				handlerStart, handlerEnd = 0;
   std::string handler; 
   std::string class;
   std::string id;
   std::string attribute;
   GtkWidget myWidget;
   while ( true )
   {
	   //find gtk objects
	  if(tag == "object")
	  {
		  //find the position of start tag
		  start = text.find( "<" + tag, pos );   
		  if(start != string::npos)
		  {
			  //find the class
			  attribute = "\"class\"=";
			  classStart = text.find(attribute, classEnd);
			  classStart += attribute.length();
			  classEnd = text.find("\"", classStart);
			  class = text.substr(classStart, classEnd-classStart; 
			  
			  //find id
			  attribute = "\"id\"=";
			  idStart = text.find(attribute, idEnd);
			  idStart += attribute.length(); 
			  idEnd = text.find("\"", idStart);
			  id = text.substr(idStart, idEnd-idStart; 
		  }
		  //create a label and store in the appropriate vector
		  myWidget = GtkWidget(id, class); 
		  if(myWidget.getType == "button")
		  {
			  gtkButtons.push_back(myWidget); 
		  }
		  else if(myWidget.getType == "label")
		  {
			  gtkLabels.push_back(myWidget); 
		  }
	  }
	  //find signal handler
	  else if(tag == "signal")
	  {
		  start = text.find( "<" + tag, pos );
		  if(start != string::npos)
		  {
			  //find the attribute
			  //<signal name="clicked" handler="on_btn_print_txt_clicked" object="lbl_text" swapped="no"/>

			  attribute = "\"handler\"=";
			  handlerStart = text.find(attribute, handlerEnd);
			  handlerStart += attribute.length(); 
			  handlerEnd = text.find("\"", handlerStart);
			  handler = text.substr(handlerStart, handlerEnd-handlerStart; 
			  signalHandlers.push_back(handler); 
	  }
   }
   
}
