#pragma once
#include<stdio.h>
#include<curses.h>
void back_del_ch();
void set_coordinates();
void Enter();
char*  copyln();
void Backspace();
int lineLength(int lines);
void edit(WINDOW*dialog,WINDOW*title_bar,WINDOW*hot_keys,int max_x,char*savepath,char*savefile);
void write_file(FILE* file);
void read_file(FILE* file);
void draw_dialog_win(WINDOW* window,int max_x,char* savefile);
void draw_title_bar(WINDOW* title_bar,int max_x, char *savepath, char *savefile);
void draw_hot_keys(WINDOW* window,int max_x);
