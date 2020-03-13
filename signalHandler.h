#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H
#include <string>
#include <vector>
#include <iostream>
#include "gtkWidget.h"

class SignalHandler
{
	private: 
		std::string handler;
		std::string widget; 
		std::string object; 
		std::string objectType; 
		
	public: 
		SignalHandler(){
			SignalHandler::handler = "";
			SignalHandler::widget = "";
			SignalHandler::object = ""; 
			SignalHandler::objectType = "w"; 

		};
		
		SignalHandler(std::string handler, std::string widget)
		{
			SignalHandler::handler = handler;
			SignalHandler::widget = widget;
			SignalHandler::object = ""; 
			SignalHandler::objectType = "w"; 
		}
		
		void setWidget(std::string widget);
		void setObject(std::string object);
		void setObjectType(std::string objectType);
		
		std::string getHandler(){return handler;};
		std::string getWidget(){ return widget;}; 
		std::string getObject(){return object;};
		std::string getObjectType(){return objectType;};

		std::string getWidgetParameter(std::string widgetName);
		std::string findObjectType(std::vector<GtkWidget> &widgets);
};
#endif