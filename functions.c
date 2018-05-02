#include"functions.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<curses.h>
#include"cmd_parser.h"
#define CTRL(c) ((c) & 037)
    int lin=1, col=0;
    int line = 0; 
    int number_of_lines=1;  
    void set_coordinates()
    { 
         char*value = get_key_val('M');
         lin = value[0]-'0'; col = (value[2]-'0'-1);
    }
    void back_del_ch()
    {
    	if (col > 0) {
    		move(lin, --col);
    		delch();
    	}
    }
     
    void Enter()
    {
        if(lineLength(LINES-2) != 0) { beep();  return;}
    	char ch;
    	int len = col; //Длина строки слева от курсора
    	int lineLen = lineLength(lin); //Длина всей строки 
            if(lin == LINES-2) return;
    	insertln();
    	while (len-- != 0) {
    		ch = mvinch(++lin, col - 1); //Возвращает код символа в позиции y,x
    		back_del_ch();
    		mvinsch(--lin, 0, ch);// Вставляет символ в позицию y,x
    	}
    	move(++lin, 0);
            number_of_lines++;
    }
    char*  copyln()
    {
    	int size = lineLength(lin);
    	char*buff = (char*)malloc(sizeof(char)*size);
    	int i;
    	char tmp;
    	for (i = 0; i < size; i++) {
    		tmp = mvinch(lin, i);
    		buff[i] = tmp;
    	}
    	return buff;
     
    }
    void Backspace()
    {
        
    	int tmpCol, i;
    	char *line = copyln();
    	int lineLen = lineLength(lin);
        if(lin-1 == 0 && col == 0) { beep(); return; } 
    	if (col > 0) back_del_ch();
    	else if (col == 0 && lin > 1) { 
    		deleteln();
    		tmpCol = lineLength(--lin);
    		for (i = 0; i < lineLen; i++)
    			mvinsch(lin, tmpCol + i, line[i]);
    		col = tmpCol;
                 number_of_lines--;
    	}
    	free(line);
            
    }
    int lineLength(int lines)
    {
    	int lineLen = COLS - 1;
    	while (lineLen >= 0 && mvinch(lines, lineLen) == ' ')
    		lineLen--;
    	return lineLen + 1;
    }
    void edit(WINDOW* dialog,WINDOW* title_bar,WINDOW*hot_keys,int max_x,char* savepath,char*savefile)
    {
    	int key;

    	for (;;) {
                refresh();
                draw_title_bar(title_bar, max_x, savepath, savefile);
                draw_hot_keys(hot_keys,max_x);
    		move(lin, col);
    		noecho();
    		key = getch();
    		echo();
    		switch (key) {
     
    		case KEY_LEFT:
    			if (col > 0) col--;
                        else beep();
    			break;
     
    		case KEY_RIGHT:
    			if (col < COLS - 1 && col < lineLength(lin)) col++;
                        else beep();
    			break;
     
    		case KEY_UP:
    			if (lin > 1) { lin--;
    			col = lineLength(lin); } 
                        else beep();
    			break;
     
    		case KEY_DOWN:
    			if(lin < LINES-2  && lin != number_of_lines ){
    				lin++;
    			    col = lineLength(lin);
    			}
                        else beep();
    			break;
     
    		case '\r': //  KEY_ENTER
    			Enter();
                      

    			break;
              
                case '\t': //TAB
                        { 		
                          int i; 
                          char* tab = get_key_val('T') ;
                         for(i = 0; i < atoi(tab); i++){
                          if(mvinch(lin,max_x-1) != ' ') { beep(); continue; }
                            mvinsch(lin,col++,' ');                                                                                             
                         }
                        }
                        break;
    		case KEY_BACKSPACE:
    			Backspace();
    			break;
     
    		case KEY_DC: 
    			delch();
    			break;
      
    		case CTRL('x'):{
                            if(tstkey('t') != 1){
                              noecho();
                              wmove(dialog, 0, 0);
                              draw_dialog_win(dialog,max_x,savefile);
                              char answ = wgetch(dialog);
                              if(answ == 'n' ||  answ == 'N'){   endwin(); exit(3); }
                              else if(answ == CTRL('w')){  touchwin(stdscr);   continue;}
                              else return;
         
                            }
                          return; 
                } 
    			break;
     
    		default:  
                     if(mvinch(lin,max_x-1) == ' '){ 
                       move(lin,col); 
                      if(col < max_x-1) { 
                      	insch(key);
    			col++;
                     }
                   else continue;
                  } 
                 else  beep();
                        break;
                   
    		}
     
    	}
    }
    void draw_dialog_win(WINDOW* window,int max_x,char *savefile)
    {
    	wclear(window);
    	wstandout(window);
    	mvwhline(window, 0, 0, ' ', max_x);
    	wprintw(window, "Save as \"%s\"?",savefile);
            mvwaddstr(window,1,0,"Y");
            mvwaddstr(window,2,0,"N");
            mvwaddstr(window,1,10,"^W");
    	wstandend(window);
            mvwaddstr(window,1,2,"YES");
            mvwaddstr(window,2,2,"NO");
            mvwaddstr(window,1,13,"Cancel");
            wmove(window,0,25);
            wrefresh(window);        
    }
    void draw_title_bar(WINDOW *window, int max_x, char *savepath, char *savefile) {
    	wclear(window);
    	wstandout(window);
    	mvwhline(window, 0, 0, ' ', max_x);
    	mvwprintw(window, 0, 4, "edit: %s/%s", savepath, savefile);
    	wstandend(window);
    	wnoutrefresh(window);
    }
    void draw_hot_keys(WINDOW *window, int max_x)
    { 
            wclear(window);
            wstandout(window);
            mvwaddstr(window,0,0,"^X");
            wstandend(window);
            mvwaddstr(window,0,3,"Exit");
            mvwprintw(window,0,max_x-15,"%d,%d",lin,col+1);
            wrefresh(window);
    }
     
    void read_file(FILE* file)
    {
        move(lin,col);
            int k;
           int c;
        if(file == NULL) return;
    while ((c = getc(file)) != EOF){
    	 	if (c == '\n')
                          { line++; number_of_lines++; } 
                	if (line > LINES - 2) break;
    		addch(c);
     	}
    }
    void write_file(FILE* file)
    {
    	int l, n, i;
    	for (l = 1; l <  number_of_lines; l++) {
    		n = lineLength(l);
    		for (i = 0; i < n; i++)
    			putc(mvinch(l, i) & A_CHARTEXT, file);
    		putc('\n', file);
    	}
    }
