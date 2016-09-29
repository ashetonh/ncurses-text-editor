//HELLO????????????????
xc#include "Text.h"
#include <menu.h>


using namespace std;

WINDOW *textwin;
WINDOW *mywin;
WINDOW *menu;
WINDOW *openmenu;
WINDOW *opentextbox;

const char * textFile = nullptr;
int ch, t, ch2, ch3,j,r, i, x, y, rows, cols, menurows,menucols;
int length = 80;
char * buffer = new char[length];
int fd;
int size;
char * temp;
//char * temp2;
char textboxname [80];
int counter;
int numadd;
//newLength = length;
//char fileInput[256];
bool save = false;
bool run = true;



//open the main menu
void openMainMenu(){
  getmaxyx(textwin,rows,cols);
  menu = newwin(rows/3,cols/3,4,1);
  box(menu,ACS_VLINE,ACS_HLINE);
  getmaxyx(menu,menurows,menucols);
  mvwprintw(menu,1,(menucols/2)-3,"My Menu");
  mvwhline(menu,2,1,ACS_HLINE,menucols-2);
  mvwprintw(menu,4,3,"[1] Open ");
  mvwprintw(menu,5,3,"[2] Save");
  mvwprintw(menu,6,3,"[3] Save as");
  mvwprintw(menu,7,3,"[4] Exit");
  wrefresh(menu);
  refresh();
}


// open the textbox with a box border around it.
void openTextBox(){
  int a,b;
  a = rows/8;
  b = cols/4;
  openmenu = newwin(a,b,(rows/2),(cols/2)-(b/2));
  opentextbox = newwin(a-2,b-2,(rows/2)+1,(cols/2)-(b/2)+1);
  keypad(opentextbox,TRUE);
  wprintw(opentextbox,"Enter filename please: ");
  //wmove(opentextbox,1,0);
  
  // box(opentextbox,ACS_VLINE,ACS_HLINE);
  box(openmenu,ACS_VLINE,ACS_HLINE);
  wrefresh(textwin);
  wrefresh(openmenu);
  wrefresh(opentextbox);
}

//reallocating a bigger array
void newArrSize()
{ 
  length *=2;
  temp = new char[length];
  for (int f = 0;f<length;f++){
    temp[f] = buffer[f];
  }
  delete [] buffer;
  buffer = temp;
}
//save
void saveFile(){
  //i=0;
  if(textFile==nullptr){ // error msg
    openTextBox();
    wclear(opentextbox);
    wrefresh(opentextbox);
    wprintw(opentextbox,"You cannot save a file with no name. Open a file or use save as instead");
    wrefresh(opentextbox);
    ch3 = wgetch(opentextbox);
    wclear(opentextbox);
    wclear(openmenu);
    wrefresh(opentextbox);
    wrefresh(openmenu);
    save = true;
}
  else{ // actually saves.
    fd =  open(textFile,O_RDWR|O_TRUNC,0666);
    write(fd,buffer,strlen(buffer));
    buffer[strlen(buffer)] = '\0';
  }
}
//empty the buffer contents
void emptyBuffer(){
  for( int m = 0; m<strlen(buffer);m++){
    buffer[m] = 0;
  }
}

//save as
void saveAs(){  
  openTextBox();
  echo();
  wmove(opentextbox,1,0);
  wgetstr(opentextbox,textboxname);
  while(strcmp(textboxname+strlen(textboxname)-4,".txt")){//error msg
      wclear(opentextbox);
      wprintw(opentextbox,"Please enter a valid textfile suffix: ");
      wrefresh(opentextbox);
      wmove(opentextbox,1,0);
      wgetstr(opentextbox,textboxname);
      wmove(opentextbox,1,0);
    }
  // the actual save as
  textFile = textboxname;
  fd = open(textFile,O_RDWR|O_CREAT|O_TRUNC,0666);
  write(fd,buffer,strlen(buffer));
  buffer[strlen(buffer)] = '\0';
  wclear(opentextbox);
  wclear(openmenu);
  wrefresh(opentextbox);
  wrefresh(openmenu);
  refresh();
  save = true;
}

int main(const int argc, const char *argv[]) {
  
  
  // messing with window
 
  initscr(); // start up the window
  keypad(stdscr, TRUE);
  start_color();
  init_pair(1,COLOR_RED,COLOR_GREEN);
  wbkgd(stdscr,COLOR_PAIR(1));
  
  //TITLE SCREEN
  printw("F1: Menu"); 
  const char * ex = "CSCI 1730 Editor!!";
  mvprintw(0,(COLS-(strlen(ex)))/2,ex);
  

  // NEW WINDOW FOR THE BORDER AND TEXT EDITITITNINIGNIGNIGNGNI
  mywin = newwin(LINES-2,COLS,0,0); // border window
  textwin = newwin(LINES-4,COLS-2,0,0); // text window
  init_pair(2,COLOR_RED,COLOR_GREEN);
  wbkgd(textwin,COLOR_PAIR(2));
  scrollok(textwin,TRUE);
   // refresh the stdscr so the window shows
  refresh();
  // MOVE WINDOWS
  mvwin(mywin,LINES-(LINES-1),0); // move the border window
  mvwin(textwin,LINES-(LINES-2),1); // move text window
  box(mywin,ACS_VLINE,ACS_HLINE); // create box inside the border window
  wrefresh(mywin);
  
  //ENABLE KEYPAD FOR TEXTWIN
  keypad(textwin,TRUE);
 
  refresh();



  //CREATING VARIABLES FOR TEXTWIN TRAVERSAL

  i=0, x=0,y=0;
  getmaxyx(textwin,rows,cols);
 
  wmove(textwin,0,0);
  wrefresh(textwin);
 
 
  // OPEN THE COMMAND LINE ARGUMENT 
  if (argc==2)
    { 
      
      textFile = argv[1];
      if (strcmp(textFile+strlen(textFile)-4,".txt")){//error message
	openTextBox();
	wclear(opentextbox);
	wrefresh(opentextbox);
	wprintw(opentextbox,"Did not end in .txt. Exiting now");
	wrefresh(opentextbox);
	ch3 = wgetch(opentextbox);
	wclear(opentextbox);
	wclear(openmenu);
	wrefresh(opentextbox);
	wrefresh(openmenu);
	//refresh();
	endwin();
	return EXIT_SUCCESS;
      }
      //WRITE FILENAME AT BOTTOM OF SCREEN
      move(LINES-1,0);
      clrtoeol();
      mvprintw(LINES-1,0,textFile,0);
      refresh();
      //SEEK FOR END OF FILE
      fd = open(textFile, O_RDWR,0666); 
      size = lseek(fd,0,SEEK_END);
      if(size>80){
	numadd = size/80;
	for(int g =0;g<numadd;g++){
	  newArrSize();	  
	}
      }
      t= read(fd,buffer,length); // almost like truncating the buffer
      fd = open(textFile,O_RDWR);
      if (fd!=-1)
	{
	  i = size;
	}
      refresh();
      //WRITE TO BUFFER AND PUT IN WINDOW.
      while((t=read(fd,buffer,length))>0){
	if(t!=-1){
	  wprintw(textwin,buffer);
	  buffer[t]='\0';
	}	  
      }
      y=0; x=strlen(buffer);
      wmove(textwin,y,x);
    }
        
  //the buffer filler and menu
  while((ch=wgetch(textwin)) != KEY_F(5)){ // SET TO WHILE(RUN) WHEN DONE TESTING    
    if(i == length-1){
      newArrSize();
    }
    save=false;
    switch (ch){
    case KEY_F(1):
      //create menu.
      openMainMenu();
      noecho();
      ch2 = getch();
      if (ch2  == 49){ // KEY-PRESS 1
	
	//case 49: //open option
	wclear(menu);
	wrefresh(menu);
	refresh();	
	//open text box	
	openTextBox();
	if(save==false&&textFile!=nullptr){
	  wclear(opentextbox);
	  wprintw(opentextbox,"Would you like to save the current file? Press 'y' if so.");
	  ch3 = wgetch(opentextbox);
	  if(ch3 == 'y'){
	    saveFile();
	    wrefresh(opentextbox);
	    wclear(opentextbox);
	    openTextBox();
	  }
	}
	
	//see the stuff you are typing
	echo();
	//get string of the stuff you are typying
	
	wgetstr(opentextbox,textboxname);
	while(strcmp(textboxname+strlen(textboxname)-4,".txt")){//error msg
	  wclear(opentextbox);
	  wprintw(opentextbox,"Please enter a valid textfile suffix: ");
	  wrefresh(opentextbox);
	  wmove(opentextbox,1,0);
	  wgetstr(opentextbox,textboxname);
	  wmove(opentextbox,1,0);
	}
	
	emptyBuffer(); // empty the buffer since we are opening a different file
	werase(textwin); //claer text window
	wrefresh(textwin);
	textFile = textboxname;
	move(LINES-1,0);
	clrtoeol();
	mvprintw(LINES-1,0,textboxname,0);
	wrefresh(textwin);
	refresh();

	fd = open(textFile, O_RDWR,0666); // open time
	size = lseek(fd,0,SEEK_END);
	if(size>80){ // reallocate array
	  numadd = size/80;
	  for(int g =0;g<numadd;g++){
	    newArrSize();
	  }
	}
	t= read(fd,buffer,length);
	fd = open(textFile,O_RDWR);
	if (fd!=-1) // change i value of buffer to the end of tthe read function.
	  {
	    i = size;
	  }
	refresh();
	while((t=read(fd,buffer,length))>0){ // print the buffer contents
	  if(t!=-1){
	    wprintw(textwin,buffer);
	    buffer[t]='\0';
	  }
	}
	y=0; x=strlen(buffer);
	wmove(textwin,y,x);
      }
      if(ch2 == 50){//save KEY PRESS 2
	echo();
	wclear(menu);
	wrefresh(menu);
	wrefresh(textwin);
	saveFile();
	
      }   
      if(ch2==51){ // save as KEY PRESS 3
	echo();
	wclear(menu);
	wrefresh(menu);
	wrefresh(textwin);
	saveAs();
	
	
      }
      if(ch2 == 52){ // exit KEY PRESS 4
	if(strlen(buffer)!=0){ // if file size is not 0 then ask if you want to save. if so then give name of file you want to save as.
	  openTextBox();
	  wclear(opentextbox);
	  wprintw(opentextbox,"Would you like to save? (y) or (n)");
	 
	  ch3 = wgetch(opentextbox);
	  if((char)ch3 == 'y'){
	    saveAs();
	  }
	  else if((char)ch3 == 'n'){
	    endwin();
	    return EXIT_SUCCESS;
	  }
	}
	  endwin();
	  return EXIT_SUCCESS;
      }
      break;
    case KEY_BACKSPACE:
      wdelch(textwin);
      if(i!=0){
	i--;
	x--;
      }
      buffer[i] ='\0';
      break;
    case KEY_LEFT:
      if(x!=0){
	--x;
      }
      break;
    case KEY_RIGHT:
      if(x!=cols){
	x++;
      }
      break;
    case KEY_UP:
      if(y!=0){
	y--;
      }
      break;
    case KEY_DOWN:
      if(y!=rows)
	{
	  y++;
	}
      break;
    case '\n':
      x=0;
      y++;
      buffer[i] = '\n';
      i++;
      break;
   
    default:
      buffer[i] = (char)ch;
      i++;
      x++;
      break;
    }
    wmove(textwin,y,x);
  }
  endwin();
  
  //THIS WAS USED FOR TESTING PURPOSES TO SEE IF BUFFER WAS HOLDING EVERYTHING PROPERLY. 
  for (int q =0;q<strlen(buffer);q++){
    cout<<buffer[q];
  }
  cout<<endl;
  cout<<strlen(buffer)<<endl;
  // delete buffer;
  
  return EXIT_SUCCESS;
  
}

