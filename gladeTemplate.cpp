#include "gladeTemplate.h"
void GladeTemplate::read(std::ifstream& is){
	int lines = 1;
	std::cout << "Widgets Found: \n";
	while(is)
	{
		std::string line; 
		//read line by line
		getline(is, line);
		//find <object class
		
		GladeTemplate::getTag(line, "object");
		GladeTemplate::getTag(line, "signal");
		GladeTemplate::getTag(line, "<property name=\"title\"");

		lines++;
	}
}

void GladeTemplate::setFileName(std::string fileName)
{
	GladeTemplate::fileName = fileName;
}

void GladeTemplate::setSrcFileName(std::string srcFileName)
{
	GladeTemplate::srcFileName = srcFileName;
}
void GladeTemplate::setWindowName(std::string windowName)
{
	GladeTemplate::windowName = windowName;
}

void GladeTemplate::setProjectName(std::string projectName)
{
	projectName.erase(std::remove_if(projectName.begin(), projectName.end(), ::isspace), projectName.end());
	GladeTemplate::projectName = projectName;
}


void GladeTemplate::getTag(const std::string &text, std::string tag){
                                                          
   unsigned int pos = 0; 
   unsigned int found = 0;
   unsigned int classStart = 0;
   unsigned int classEnd = 0, idStart, 
				idEnd= 0, handlerStart,
				handlerEnd = 0, projectStart,
				projectEnd = 0; 
   std::string handler; 
   std::string className;
   std::string id;
   std::string project;
   std::string attribute;
   std::string object; 
   GtkWidget myWidget;
	   //find gtk objects
	  if(tag == "object")
	  {
		  //find the position of start tag
		  found = text.find( "<" + tag);   
		  if(found <= 100)
		  {
			  //std::cout << "Found is " << found << std::endl;
			  //std::cout<< text << std::endl; 

			  //std::cout << "A widget was found " << std::endl;
			  //find the class
			  attribute = "class=\"";
			  classStart = text.find(attribute, classEnd);
			  if(classStart < 100)
			  {
				classStart += attribute.length();
				classEnd = text.find("\"", classStart);
				className = text.substr(classStart, classEnd-classStart); 
			  }
			  else
			  {
				  className = ""; 
			  }
			  std::cout << "\tClass: " << className;
			  //find id
			  attribute = "id=\"";
			  idStart = text.find(attribute, idEnd);
			  if(idStart < 100)
			  {
				idStart += attribute.length(); 
			 	idEnd = text.find("\"", idStart);
			  	id = text.substr(idStart, idEnd-idStart); 
			  }
			  else 
			  {
				  id = ""; 
			  }			  
			  std::cout << " ID: " << id << std::endl; 
		  }
		  //create a label and store in the appropriate vector
		  myWidget = GtkWidget(id, className); 
		  if(className == "GtkWindow") //get window id
		  {
			  GladeTemplate::setWindowName(id);
		  }
		  else if(className == "GtkBox" || className == "GtkGrid") //don't add container objects
		  {
		  }
		  else if(className != "" && id != "") //add everything else
		  {
			  gtkWidgets.push_back(myWidget);
		  }
	  }
	  //find signal handler
	  else if(tag == "signal")
	  {
		  found = text.find( "<" + tag, pos );
		  if(found <= 100)
		  {
			  //std::cout << "Found is " << found << std::endl;
			  //std::cout<< text << std::endl; 

			  //find the attribute
			  //<signal name="clicked" handler="on_btn_print_txt_clicked" object="lbl_text" swapped="no"/>

			  attribute = "handler=\"";
			  handlerStart = text.find(attribute, handlerEnd);
			  handlerStart += attribute.length(); 
			  handlerEnd = text.find("\"", handlerStart);
			  handler = text.substr(handlerStart, handlerEnd-handlerStart); 
			  std::cout << "\tHandler: " << handler << std::endl; 
			  SignalHandler myHandler;
			  if(handler == "on_window_main_destroy")
			  {
				  myHandler = SignalHandler(handler, "GtkWindow");
			  }
			  else
			  {
				myHandler = SignalHandler(handler, gtkWidgets.back().getType());
			  }
			  //check if object
			  attribute = "object=\"";
			  handlerStart = text.find(attribute, handlerEnd);
			  if(handlerStart < 100)
			  {
				handlerStart += attribute.length(); 
				handlerEnd = text.find("\"", handlerStart);
				object = text.substr(handlerStart, handlerEnd-handlerStart); 
				myHandler.setObject(object); 
			  }
			  //check if handler exists
			  if(!checkIfHandlerExists(myHandler))
			  {
				signalHandlers.push_back(myHandler); 
			  }

		}
	  }
	  else if(tag == "<property name=\"title\"")
	  {
		  //find the position of start tag
		  found = text.find(tag);   
		  if(found <= 100)
		  {
			  attribute = "\">";
			  projectStart = text.find(attribute, projectEnd);
			  projectStart += attribute.length();
			  projectEnd = text.find("</", projectStart);
			  project = text.substr(projectStart, projectEnd-projectStart); 
			 setProjectName(project);
			  std::cout<< "\tProject Name: " << getProjectName() << std::endl;
		  }
	}
}
bool GladeTemplate::checkIfHandlerExists(SignalHandler handler)
{
	bool found = false;
	for(SignalHandler h : signalHandlers)
	{
		if(h.getHandler() == handler.getHandler())
		{
			found = true; 
			return found;
		}
	}
	return found; 
}

void GladeTemplate::getObjectTypes()
{
	for(SignalHandler &handler : signalHandlers)
	{
		std::string objectType = handler.findObjectType(GladeTemplate::gtkWidgets);
		handler.setObjectType(objectType);
	}
	
}
void GladeTemplate::write(std::ostream& os)
{
	//include header
	os << "#include <gtk/gtk.h>\n\n";
	//create struct of pointers
	os << "typedef struct {\n";
	//get the widgets
	for (GtkWidget& widget: gtkWidgets){
		   os << "\tGtkWidget *w_" << widget.getID() << ";\n";
	}
	os << "}app_widgets;\n\n";
	//create main
	os << "int main(int argc, char *argv[])\n";
	os << "{\n";
	os << "\tGtkBuilder\t\t*builder;\n";
	os << "\tGtkWidget\t\t*window;\n\n";
	os << "\t//instantiate structure, allocating memory for it\n";
	os << "\tapp_widgets\t\t*widgets = g_slice_new(app_widgets);\n\n";
	os << "\tgtk_init(&argc, &argv);\n\n";
	os << "\tbuilder = gtk_builder_new();\n";
	os << "\tgtk_builder_add_from_file(builder, \"" << GladeTemplate::getFileName() << "\", NULL);\n\n";
	os << "\twindow = GTK_WIDGET(gtk_builder_get_object(builder, \"" << GladeTemplate::getWindowName() << "\"));\n";
	os << "\t//get pointers to widgets\n";
	//get pointers to widgets
	for (GtkWidget& widget: gtkWidgets){
		   os << "\twidgets->w_" << widget.getID() << " = GTK_WIDGET(gtk_builder_get_object(builder, \""
		   << widget.getID() << "\"));\n";
	}
	os << "\t//widgets pointers will be passed to all widget handler functions as user_data paramater\n";
	os << "\tgtk_builder_connect_signals(builder, widgets);\n";
	os << "\tg_object_unref(builder);\n\n";
	os << "\tgtk_widget_show(window);\n";
	os << "\tgtk_main();\n";
	os << "\t//free up memory used by widget structure\n";
	os << "\tg_slice_free(app_widgets, widgets);\n\n";
	os << "\treturn 0;\n";
	os << "}\n\n";
	//create functions for signals
	for(SignalHandler signal: signalHandlers){

		if(signal.getHandler() == "on_window_main_destroy")
		{
			os << "//called when window is closed\n";
			os << "void "<< signal.getHandler() << "()\n";
			os << "{\n";
			os << "\tgtk_main_quit();\n";
			os << "}\n\n";
		}
		else
		{
			os << "void " << signal.getHandler() << "(" << signal.getWidget() 
			   << " *";
			   os << signal.getWidgetParameter(signal.getWidget());
			   if(signal.getObject() != "")
			   {
				   os << ", " << signal.getObjectType() << " *"
					  << signal.getWidgetParameter(signal.getObjectType()) << ")\n";
			   }
			   else
			   {
				  os << ", app_widgets *app_wdgts)\n";
			   }
			os << "{\n";
			os << "\t//Type Function for handler here\n\n";
			os << "}\n\n";
		}
	}
}

//creates a make file
void GladeTemplate::make(std::ostream& os)
{
	os << "TARGET=" << GladeTemplate::getProjectName() << "\n\n"; 
	os << "CC=gcc\n";
	os << "DEBUG=-g\n";
	os << "OPT=-O0\n";
	os << "WARN=-Wall\n\n";
	os << "PTHREAD=-pthread\n\n";
	os << "CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe\n\n";
	os << "GTKLIB=`pkg-config --cflags --libs gtk+-3.0`\n\n";
	os << "LD=gcc\n";
	os << "LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic\n\n"; 
	os << "OBJS=\tmain.o\n\n"; 
	os << "all: $(OBJS)\n";
	os << "\t$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)\n\n";
	os << "main.o: " << GladeTemplate::getSrcFileName() << "\n"; 
	os << "\t$(CC) -c $(CCFLAGS) " << GladeTemplate::getSrcFileName() << " $(GTKLIB) -o main.o\n\n";
	os << "clean:\n";
	os << "\trm -f *.o $(TARGET)";
};

