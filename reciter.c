#include <stdio.h>
#include <string.h>
int main(int argc,char **argv)
{
  if(argc != 2)
  {
    printf("使用方法: %s [单词表]\n",argv[0]);
    return 1;
  }
  unsigned long fileLen;
  FILE *fp=fopen(argv[1],"rb");

    if(fp==NULL){
	    puts("文件读取失败(1)");
    	return 1;
  }
  fseek(fp, 0, SEEK_END);
  fileLen = (unsigned long)ftell(fp);
  if(fileLen == 0)
  {
    puts("文件读取失败(2)");
    return 1;
  }
  char *text = (char *) malloc(sizeof(char) * (fileLen+1));
  fseek(fp, 0, SEEK_SET);
  fread(text, sizeof(char), fileLen, fp);
  fclose(fp);
  if(strlen(text) != fileLen)
  {
    puts("文件读取失败(3)");
    return 1;
  }
  char *line = strtok(text,"\n"),*word;
  char input[25],*tip;
  unsigned int lineLen = 0,wrongs = 0,i;
  while(line != NULL)
  {
    lineLen++;
    word = strstr(line,":");
    *word = '\0';
    printf("第%d个单词: %s\n",lineLen,line);
    word++;
    tip = word;
    while(1){
      scanf("%s",input);
      //printf("比较%s:%s",input,word);
      if(strcmp(word,input) == 0)
      {
        puts("答对了，你真棒!");
        wrongs = 0;
        break;
      }
      else
      {
        puts("答错了，你真笨!");
        if((wrongs+1)==strlen(word))
        {
          puts("你简直笨得要死啊!");
          printf("正确拼写: %s\n",word);
          wrongs = 0;
          break;
        }
        printf("提示: ");
        for(i=0;i<=wrongs;i++)
        {
          putchar(tip[i]);
        }
        putchar('\n');
        wrongs++;
      }
    }
    memset(input,0,25);
    line = strtok(NULL,"\n");
  }
  free(text);
}
