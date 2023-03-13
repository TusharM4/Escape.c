#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>

int key = 0;

//Outputs key data to window
char keydata(void)
{
  mvaddch(1, 99, '|');
  mvaddch(2, 99, '|');
  mvaddch(1, 117, '|');
  mvaddch(2, 117, '|');
  mvprintw(0, 99, "/-----------------\\");
  mvprintw(3, 99, "\\-----------------/");
  mvprintw(1, 100, "Key's obtained: %i", key);
  mvprintw(2, 100, "Key's required: 2");
  move(4, 0);
  curs_set(0);
}

int main(void)
{
  initscr();			//Initializes curses library
  cbreak();			//Will take input chars one at a time
  timeout(1);		//Waits 1ms for keypress,otherwise continues
  noecho();

  char move = 0;
  int mainroom = 0;
  int Instuctions = 0;
  int keycounterone = 0;
  int keycountertwo = 0;
  //Game loop
  while(1)
  {
    move = getch();	//Takes input

    //Starting room
    if (mainroom == 0)
    {
      clear();
      if (Instuctions == 0)
      {
        printw("LOADING GAME...");
        sleep(1);
        clear();
        printw("Welcome To \'The Room Of Doom\' \n");
        printw("It is an online simulation of a mystery game where\n"); 
        printw("your goal is to escape with the keys you will collect.\n");
        printw("Press w,a,s,d to move from room to room\n");
        Instuctions ++;
      }

      printw(" W = north\n A = west\n S = south\n D = east\n");
      printw("You are in the starting room. You can travel in all 4 directions\n");
      keydata();
      refresh();
      mainroom ++;
      sleep(1);
    }

    //North room 1
    if (move == 'w')
    {
      clear();
      printw("You've entered north room.\n");
      printw("Press q to investigate room.\n");
      printw("You can go north or south from here.\n");
      keydata();
      refresh();
      while(1)
      {
        move = getch();
        if (move == 'q')
        {
          printw("There is no key in this room\n");
          refresh();
        }
        
        //North 2 room
        if (move == 'w')
        {
          clear();
          printw("You've entered north2 room\n");
          printw("Press q to investigate room\n");
          printw("You can only go south from here.\n");
          keydata();
          refresh();
          while(1)
          {
            move = getch();
            if (move == 'q')
            {
              if (key == 2)
              {
                printw("You now have the key and attempt to open the gate...\n");
                refresh();
                sleep(2);
                printw("You escaped!");
                sleep(3);
                refresh();
                endwin();
                return 0;	
              }
              else
              {
                printw("You have found the gate! Return here when you have all the key parts to escape.\n");
                refresh();
              }
            }
            
            //Returns to North 1 room
            if (move == 's' )
            {
              clear();
              printw("You've entered north room\n");
              printw("Press q to investigate room\n");
              printw("You can go north or south from here.\n");
              keydata();
              refresh();
              move = 0;
              break;
            }
          }
        }
        
        //Returns to Starting room
        if (move == 's')
        {
          move = 0;
          mainroom --;
          break;
        }
      }
    }

    //West room
    if (move == 'a')
    {
      clear();
      printw("You've entered west room\n");
      printw("Press q to investigate room\n");
      printw("You can only go east from here\n");
      keydata();
      refresh();
      while(1)
      {
        move = getch();
        if (move == 'q')
        {
          printw("There is no key in this room\n");
          refresh();
        }
        //Returns to Starting room        
        if (move == 'd')
        {
          move = 0;
          mainroom --;
          break;
        }
      }
    }

    //South room
    if (move == 's')
    {
      clear();
      printw("You've entered south room\n");
      printw("Press q to investigate room\n");
      printw("You can only go north from here\n");
      keydata();
      refresh();
      while(1)
      {
        move = getch();
        if (move == 'q')
        {
          if (keycounterone == 0)
          {
            keycounterone ++;
            key ++;
            printw("You have a found a key part!\n");
            keydata();
            refresh();
          }
          else
          {
            printw("You have already found the key part in this room\n");
          }
        }

        //Returns to Starting room
        if (move == 'w')
        {
          move = 0;
          mainroom --;
          break;
        }
      }
    }

    //East room
    if (move == 'd')
    {
      clear();
      printw("You've entered east room\n");
      printw("Press q to investigate room\n");
      printw("You can only go west from here\n");
      keydata();
      refresh();
      while(1)
      {
        move = getch();
        if (move == 'q')
        {
          if (keycountertwo == 0)
          {
            keycountertwo ++;
            key ++;
            printw("You have a found a key part!\n");
            keydata();
            refresh();
          }
          else
          {
            printw("You have already found the key part in this room\n");
          }
        }
        
        //Returns to Starting room
        if (move == 'a')
        {
          move = 0;
          mainroom --;
          break;
        }
      }
    }
  }
  endwin();
  return 0;
}










