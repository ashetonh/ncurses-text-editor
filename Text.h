#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <ncurses.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

class Text {

 public:

  int textDesc; // file desciptor
  char buffer2[256]; // buffer for text
  Text(int textDesc); // constructor
  void print(); // print file contents
  void closeText(); // close File

};
#endif
