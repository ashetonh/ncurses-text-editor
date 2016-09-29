#include "Text.h"
#include <ncurses.h>


// constructor

Text::Text(int textDesc){
  this->textDesc = textDesc;
}

void Text::print(){
  int x = read(textDesc, buffer2,256);
  // if there is a file then print the file contents
  if(textDesc != -1){
    while (x>0){
      if (x!=-1){ // make sure its not at the end.
	buffer2[x]='\0'; // null terminating to tell the buffer when to stop.
	printw(buffer2); // print
	x = read(textDesc, buffer2, 256);
      }
    }
  }
  // give error message if there is no file
  else {
    printw(strerror(errno)); 
    printw("\n");
  }
}

// close the textFile
void Text::closeText(){
  int textToClose;
  textToClose = close(textDesc);
  if(textToClose < 0){
      printw(strerror(errno)); 
  } // if there is no file then print error messsage
}
