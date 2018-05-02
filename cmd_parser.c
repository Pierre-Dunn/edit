#include<stdio.h>
#include"cmd_parser.h"
#include<string.h>
#include"cmd_config.h"
CMD_HLDR *cmd_ptr = NULL;
CMD_HLDR *cmd_parser(CMD_HLDR *itemList,int argc, char *argv[])
{  
   cmd_ptr = itemList;     
   int itemNum = 0;
   int parsedNum = 1;
   while(itemList[itemNum].key != 0){
    int argNum;
    int flag = 0;
    for(argNum = 1; argNum < argc; argNum++){
	char *arg = argv[argNum];
 	if(arg[0]=='-'){
		if(arg[0]==itemList[itemNum].sng && arg[1] == itemList[itemNum].key && strlen(arg) == 2) {
	 	 itemList[itemNum].mask = KEY_IN_CMD;
	         parsedNum++;
                 flag=1;
                 continue;
          	}
        }

        
        if(arg[0]!='-' && flag == 1){
            flag = 0;
            if(cmd_ptr[itemNum].mask == KEY_IN_CMD){
               cmd_ptr[itemNum].val = arg;
               cmd_ptr[itemNum].mask |= VAL_IN_CMD;
               parsedNum++;
            }
            else return NULL;
        }
        flag=0;

   

   }
       itemNum++;
   
  }
    if(parsedNum != argc) return NULL;
    return itemList;
}
void parse(int argc,char*argv[])
{   
    cmd_parser(CmditemsList,argc,argv);
}
void cmd_usage(const char *str)
{  
    if(str != NULL) 
       printf("%s\n",str);
    int itemNum = 0;
    if(cmd_ptr != NULL)
    while(cmd_ptr[itemNum].key != 0){
         printf("+++++++++++++++\n");
         printf("+key: %c\n+description: %s\n",cmd_ptr[itemNum].key,cmd_ptr[itemNum].usg);
         itemNum++;
    }
    else printf("%s","parse() doesn't exist\n");
}
int tstkey(char key)
{
    int itemNum=0;
    while(cmd_ptr[itemNum].key != 0){
     if(cmd_ptr[itemNum].key == key && cmd_ptr[itemNum].mask != 0)
         return 1;
     itemNum++;
    }
    return-1;
}
int tstvalue(char key)
{
    int itemNum=0;	
    while(cmd_ptr[itemNum].key != 0){
      if((cmd_ptr[itemNum].val != NULL) !=0  && cmd_ptr[itemNum].key == key) 
           return 1;
      itemNum++;
    } 
    return -1;
}
int val_is_default(char key)
{
    int itemNum=0;
    while(cmd_ptr[itemNum].key != 0){
      if(cmd_ptr[itemNum].key == key && (cmd_ptr[itemNum].mask&VAL_IN_CMD) != 0)
      return 0;
      itemNum++;
    }
    return 1;
}   
char *get_key_val(char key)
{
   if(cmd_ptr==NULL) return NULL;
   int itemNum=0;
   while(cmd_ptr[itemNum].key != 0){
    if(cmd_ptr[itemNum].key==key && cmd_ptr[itemNum].val != NULL)
	return cmd_ptr[itemNum].val;
    itemNum++;
   }
   return NULL;
}
	
