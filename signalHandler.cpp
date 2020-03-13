#include "signalHandler.h"

void SignalHandler::setWidget(std::string widget)
{
	SignalHandler::widget = widget;
};

void SignalHandler::setObject(std::string object)
{
	SignalHandler::object = object;
}

void SignalHandler::setObjectType(std::string objectType)
{
	SignalHandler::objectType = objectType;
}



std::string SignalHandler::findObjectType(std::vector<GtkWidget> &widgets)
{
	for(GtkWidget w: widgets)
	{
		if(SignalHandler::getObject() == w.getID())
		{
			return w.getType();
		}
	}
	return "";
}

std::string SignalHandler::getWidgetParameter(std::string widgetName)
{
	if(widgetName == "GtkButton")
	{
		return "button";
	}
	else if(widgetName =="GtkLabel")
	{
		return "label";
	}
	else
	{
		return widgetName; 
	}
}