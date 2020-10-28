//Program to understand API.
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define DATA_FILE_NAME "pincodedata.dat"
#define LENGTH_OF_COMPARABLE_STRING 40
#define PIN_CODE_LENGTH 7
#define CMD_LENGTH 100
#define PIN_CODE_INFO_LENGTH 1000
void main(int argc, char* argv[])
{
	char cmd[CMD_LENGTH];
	char pin_code_info[PIN_CODE_INFO_LENGTH];
	char pin_code[PIN_CODE_LENGTH];
	char *ptr_token_value;
	
	if(argv[1] == NULL)
	{
		printf("Enter a pin code: ");
		scanf("%s", pin_code);
		sprintf(cmd, "curl \"https://api.postalpincode.in/pincode/%s\" > pincodedata.dat -s", pin_code);
		system(cmd);
	}
	else
	{
		sprintf(cmd, "curl \"https://api.postalpincode.in/pincode/%s\" > pincodedata.dat -s", argv[1]);
		system(cmd);
	}

	FILE *fp_pin_code_info;
	fp_pin_code_info = fopen(DATA_FILE_NAME, "r");
	fread(pin_code_info, sizeof(pin_code_info), 1, fp_pin_code_info);
	fclose(fp_pin_code_info);
	

	char split_point1[2] = ",";
	char split_point2[2] = ":";
    char string_to_be_compared[LENGTH_OF_COMPARABLE_STRING] = "\"District\"";
	ptr_token_value = strtok(pin_code_info, split_point1);
	printf("Entered pin code belongs to: \n");
	while(ptr_token_value != NULL)
	{
		ptr_token_value = strtok(NULL, split_point2);
		if(strcmp(ptr_token_value, string_to_be_compared) == 0)
		{
			ptr_token_value = strtok(NULL,split_point1);
			printf("City: %s\n", ptr_token_value);
		}
		if(strcmp(ptr_token_value, "\"State\"") == 0)
		{
			ptr_token_value = strtok(NULL,split_point1);
			printf("State: %s\n", ptr_token_value);
			break;
		}
		ptr_token_value = strtok(NULL, split_point1);
	}
	return;
}
