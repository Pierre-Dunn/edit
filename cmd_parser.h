#ifndef PARSER_H
#define PARSER_H

#define KEY_IN_CMD 0x00000080
#define VAL_IN_CMD 0x00000200

struct cmd_item
{
    char sng;
    char key;
    int mask;
    char *val;
    char *usg;
};

typedef struct cmd_item CMD_HLDR;

CMD_HLDR *cmd_parser(CMD_HLDR *itemList,int argc, char *argv[]);
void parse(int arc, char*arv[]);
int tstkey(char key);
int tstvalue(char key);
int val_is_default(char key);
char *get_key_val(char key);
void cmd_usage(const char* str);

#endif
