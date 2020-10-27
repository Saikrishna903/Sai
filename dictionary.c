//Program to understand API.
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define DATA_FILE_NAME "dictionarywordinfo.dat"
#define LENGTH_OF_COMPARABLE_STRING 100
#define DICTIONARY_WORD_LENGTH 30
#define LENGTH 100
#define WORD_INFO_LENGTH 1000

void call_system_function_cmd_line_input(char **);
void call_system_function_run_time();
void load_dictionary_word_info();
void show_defination();	
void play_dictionary_word();

char dictionary_word_info[WORD_INFO_LENGTH];
char audio_url[LENGTH], cmd[LENGTH], *ptr_token_value;

void main(int argc, char* argv[])
{
	if(argc == 2)
	{
 		call_system_function_cmd_line_input(argv);
	}
	else
	{
		call_system_function_run_time();
	}
	load_dictionary_word_info();
	show_defination();	
	play_dictionary_word();
}

void call_system_function_cmd_line_input(char **arg_list)
{
	sprintf(cmd, "curl \"https://api.dictionaryapi.dev/api/v2/entries/en/%s\" > dictionarywordinfo.dat -s", arg_list[1]);
	system(cmd);	
}

void call_system_function_run_time()
{
	char dictionary_word[DICTIONARY_WORD_LENGTH];
	printf("Enter a word: ");
	scanf("%s", dictionary_word);
	sprintf(cmd, "curl \"https://api.dictionaryapi.dev/api/v2/entries/en/%s\" > dictionarywordinfo.dat -s", dictionary_word);
	system(cmd);
}

void load_dictionary_word_info()
{
	FILE *fp_dictionary_word;
	fp_dictionary_word = fopen(DATA_FILE_NAME, "r");
	fread(dictionary_word_info, WORD_INFO_LENGTH, 1, fp_dictionary_word);
	fclose(fp_dictionary_word);
	return;
}

void show_defination()
{
	char split_point1[2] = " ";
	char split_point2[2] = ".";
	char string_to_be_compared[LENGTH_OF_COMPARABLE_STRING] = "\"definition\":";
	ptr_token_value = strtok(dictionary_word_info, split_point1);
	while(ptr_token_value != NULL)
	{
	
		if(strcmp(ptr_token_value, "\"audio\":") == 0)
		{
			ptr_token_value = strtok(NULL, split_point1);
			strcpy(audio_url, ptr_token_value);
		}

		if(strcmp(ptr_token_value, string_to_be_compared) == 0)
		{
			ptr_token_value = strtok(NULL,split_point2);
			printf("\nDefination of given word: %s\".\n", ptr_token_value);
			break;
		}
		ptr_token_value = strtok(NULL, split_point1);
	}
}

void play_dictionary_word()
{
	sprintf(cmd, "vlc -I null --play-and-exit %s -s", audio_url);
	system(cmd);
}

