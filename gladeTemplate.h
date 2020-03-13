#ifndef GLADE_TEMPLATE_H
#define GLADE_TEMPLATE_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "gtkWidget.h"
#include "signalHandler.h"

class GladeTemplate
{
	private: 
		std::string windowName; 
		std::string projectName;
		std::vector<GtkWidget> gtkWidgets; 
		std::vector<SignalHandler> signalHandlers; 
		std::string fileName;
		std::string srcFileName;
		
		
	public: 
		void setFileName(std::string fileName);
		void setWindowName(std::string windowName);
	    void setProjectName(std::string projectName);
		void setSrcFileName(std::string srcFileName);
		
		std::string getFileName(){ return fileName;};
		std::string getWindowName(){ return windowName;};
		std::string getProjectName(){ return projectName;};
		std::string getSrcFileName(){ return srcFileName;};
		std::vector<SignalHandler> getSignalHandlers(){ return signalHandlers;};
		
		void read(std::ifstream& is);
		void getTag(const std::string &text, std::string tag);
		void write(std::ostream& os);
		void make(std::ostream& os);
		void getObjectTypes();
		bool checkIfHandlerExists(SignalHandler handler);
};

#endif