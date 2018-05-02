#include<stdio.h>
#include<stdlib.h>
#include"functions.h"
#include<curses.h>
#include<unistd.h>
#include<string.h>
#include"cmd_parser.h"

    int main(int argc, char* argv[])
    {

         parse(argc,argv);
            if(tstkey('h') == 1)   { system("cat help.txt"); exit(5); }
        else  if(argc == 1  ||  argv[1][0]=='-') {
            fprintf (stderr, "Invalid arguments! Run: \"edit -h\"\n");
            exit(1);
        }
        int max_y=0,max_x=0;
        char *savefile = argv[1];
        char savepath[1024];
        getcwd(savepath, 1024);
        initscr();
        keypad (stdscr, TRUE);
        nonl();
        if(tstkey('b') == 1) attrset(A_BOLD);
        getmaxyx(stdscr,max_y,max_x);
        WINDOW* dialog = newwin(3, max_x, LINES - 3, 0);
        WINDOW* hot_keys = newwin(1,max_x,LINES-1,0);
        WINDOW* title_bar = newwin(1, max_x, 0, 0);
        FILE *file;
        file = fopen (argv [1], "r");

        read_file(file);
        set_coordinates();
        refresh();
        edit(dialog,title_bar,hot_keys,max_x,savepath,savefile);
        if(file != NULL) fclose(file);


        file = fopen(argv[1],"w");
        write_file(file);
        fclose(file);
        endwin();
        return 0;


    }

