#include "gtkWidget.h"

void GtkWidget::setType(std::string type)
		{

			GtkWidget::type = type; 
		};
std::string GtkWidget::getType()
{
	return GtkWidget::type; 
}

std::string GtkWidget::getID()
{
	return GtkWidget::id; 
}
