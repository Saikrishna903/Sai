//Program to understand API.
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define WEATHER_REPORT_DATA_FILE_NAME "weatherReport.dat"
#define LENGTH_OF_COMPARABLE_STRING 10
#define LOCATION_NAME_LENGTH 20
#define CMD_LENGTH 200
#define WEATHER_REPORT_LENGTH 500
void show_temperature();
void run_system_funtion();
void load_weather_report();
char weatherReport[WEATHER_REPORT_LENGTH];
char location[LOCATION_NAME_LENGTH];
int main()
{
	run_system_funtion();
	load_weather_report();
	show_temperature();
	return 0;
}
void run_system_funtion()
{
	char cmd[CMD_LENGTH];
	printf("Enter city name to find temperature: ");
	scanf("%s", location);
	sprintf(cmd, "curl \"http://api.openweathermap.org/data/2.5/find?q=%s&appid=d12cf8c5c3c40febafd1dca5750f7eb1&units=metric\" > WEATHER_REPORT_DATA_FILE_NAME -s", location);
	system(cmd);
}
void load_weather_report()
{
	FILE *fp_weather_report;
	fp_weather_report = fopen(WEATHER_REPORT_DATA_FILE_NAME, "r");
	fread(weatherReport, WEATHER_REPORT_LENGTH, 1, fp_weather_report);
	fclose(fp_weather_report);
	return;
}
void show_temperature()
{
	char string_to_be_compared[LENGTH_OF_COMPARABLE_STRING] = "{\"temp\"";
	char split_point1[2] = ":";
	char split_point2[2] = ",";
	char degree_symbol = 248; 
	char *ptr_token_value;
	ptr_token_value = strtok(weatherReport, split_point1);
	while(ptr_token_value != NULL)
	{
		if(strcmp(ptr_token_value, string_to_be_compared) == 0)
		{
			ptr_token_value = strtok(NULL,split_point2);
			break;
		}
		ptr_token_value = strtok(NULL, split_point1);
	}
	printf("\nTemperature in '%s' is %s%cC.\n", location, ptr_token_value, degree_symbol);
	return;
}