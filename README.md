# GladeParrser
A tool that reads a Gtk Glade File and creates template C code that can be compiled to a GUI application. 
#Instructions
#Setup up the Development environment
Requires a Unix OS
Requires GCC for compiling C files. G++ is optional if you want to build GladeParser from source
1. Install Glade - a design tool for creating GUIs using GTK
sudo apt-get install glade
2. Install GTK
sudo apt-get install libgtk-3-dev

# Usage
1. Create a project folder that contains a "glade" folder to store glade files and a "src" folder to store c code.
2. Design your GUI layout in Glade and save it in the glade folder
3. Download the <a href="https://github.com/reaperofchaos/GladeParrser/blob/master/GladeTemplateParser">compiled binary</a>
(compiled using Ubuntu 18.10 "Cosmic Cuttlefish" G++ 8.3.0  and save to project folder
4. Type "./GladeTemplateParser glade/<name of glade file>
  This will create a main.c in the src folder and a makefile in the project directory
5.Type "make"
6. You will now have a compiled application that loads the GTK gui and has the on_window_destory function created, so the window can exit. In main.c, there is a struct with pointers to all GTK widgets and function headers with prebuilt parameters that can be editted to provide functionality for the various UI elements
 
# Build
1. Download source
