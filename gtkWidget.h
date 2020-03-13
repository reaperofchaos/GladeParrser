#ifndef GTK_WIDGET_H
#define GTK_WIDGET_H
#include <string>

class GtkWidget
{
	private: 
		std::string id;
		std::string type; 
		
	public: 
		GtkWidget(){
			id = "";
			type = "";
		};
		GtkWidget(std::string id, std::string type)
		{
			GtkWidget::id = id;
			GtkWidget::setType(type);
		}
		void setType(std::string type);
		std::string getType();
		std::string getID(); 
};
#endif