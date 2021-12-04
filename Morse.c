#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<time.h>
#include <sys/stat.h>

struct timeDone_t
{
	int hour;
	int min;
	int second;
	int day;
	int month;
	int year;
};

struct parsedBuff {
	char size_buff[10];
	char time_convert_buff[9];
	char num_of_word_input_buff[10];
	char num_of_word_converted_buff[10];
	char num_of_word_error_buff[10];
	char num_of_char_buff[10];
	char num_of_char_converted_buff[10];
	char num_of_char_not_converted_buff[10];
	char input_name_buff[20];
	char output_name_buff[20];
	char hour_buff[4];
	char min_buff[4];
	char second_buff[4];
	char day_buff[4];
	char month_buff[4];
	char year_buff[6];
};

struct conversion_statistics {
	struct timeDone_t time;
	int size;
	double time_convert;
	int num_of_word_input;
	int num_of_word_converted;
	int num_of_word_error;
	int num_of_char;
	int num_of_char_converted;
	int num_of_char_not_converted;
	char input_name[100];
	char output_name[100];
};

void parse_stat_file(char* buff, struct parsedBuff* pBuff)
{
	int index_of_comma[18];
	int index_of_dollar[2];
	int i = 0;
	int j = 0;
	int k = 0;

	for (i = 0, j = 0, k = 0; i < strlen(buff); i++) {
		if (buff[i] == '$') {
			index_of_dollar[j] = i;
			j++;
		}
		if (buff[i] == ',') {
			index_of_comma[k] = i;
			k++;
		}
	}

	//for (k = 0; k < 18; k++) {
	//	printf("%d\t", index_of_comma[k]);
	//}

	strncpy(pBuff->input_name_buff, buff + 1, index_of_comma[0] - index_of_dollar[0] - 1);
	pBuff->input_name_buff[index_of_comma[0] - index_of_dollar[0] - 1] = '\0';
	printf("Input file name: %s\n", pBuff->input_name_buff);

	strncpy(pBuff->output_name_buff, buff + index_of_comma[0] + 1, index_of_comma[1] - index_of_comma[0] - 1);
	pBuff->output_name_buff[index_of_comma[1] - index_of_comma[0] - 1] = '\0';
	printf("Output file name: %s\n", pBuff->output_name_buff);

	strncpy(pBuff->size_buff, buff + index_of_comma[1] + 1, index_of_comma[2] - index_of_comma[1] - 1);
	pBuff->size_buff[index_of_comma[2] - index_of_comma[1] - 1] = '\0';
	//printf("File size is %s\n", pBuff->size_buff);
	
	strncpy(pBuff->num_of_word_input_buff, buff + index_of_comma[2] + 1, index_of_comma[3] - index_of_comma[2] - 1);
	pBuff->num_of_word_input_buff[index_of_comma[3] - index_of_comma[2] - 1] = '\0';
	printf("Number of words input: %s\n", pBuff->num_of_word_input_buff);

	strncpy(pBuff->num_of_word_converted_buff, buff + index_of_comma[3] + 1, index_of_comma[4] - index_of_comma[3] - 1);
	pBuff->num_of_word_converted_buff[index_of_comma[4] - index_of_comma[3] - 1] = '\0';
	printf("Number of words converted: %s\n", pBuff->num_of_word_converted_buff);

	strncpy(pBuff->num_of_word_error_buff, buff + index_of_comma[4] + 1, index_of_comma[5] - index_of_comma[4] - 1);
	pBuff->num_of_word_error_buff[index_of_comma[5] - index_of_comma[4] - 1] = '\0';
	printf("Number of words with error: %s\n", pBuff->num_of_word_error_buff);

	strncpy(pBuff->num_of_char_buff, buff + index_of_comma[5] + 1, index_of_comma[6] - index_of_comma[5] - 1);
	pBuff->num_of_char_buff[index_of_comma[6] - index_of_comma[5] - 1] = '\0';
	printf("Number of characters: %s\n", pBuff->num_of_char_buff);

	strncpy(pBuff->num_of_char_converted_buff, buff + index_of_comma[6] + 1, index_of_comma[7] - index_of_comma[6] - 1);
	pBuff->num_of_char_converted_buff[index_of_comma[7] - index_of_comma[6] - 1] = '\0';
	printf("Number of characters converted: %s\n", pBuff->num_of_char_converted_buff);	

	strncpy(pBuff->num_of_char_not_converted_buff, buff + index_of_comma[7] + 1, index_of_comma[8] - index_of_comma[7] - 1);
	pBuff->num_of_char_not_converted_buff[index_of_comma[8] - index_of_comma[7] - 1] = '\0';
	printf("Number of characters not converted: %s\n", pBuff->num_of_char_not_converted_buff);	

	strncpy(pBuff->time_convert_buff, buff + index_of_comma[8] + 1, index_of_dollar[1] - index_of_comma[8] - 1);
	pBuff->time_convert_buff[index_of_dollar[1] - index_of_comma[8] - 1] = '\0';
	printf("Duration: %s seconds\n", pBuff->time_convert_buff);	

	strncpy(pBuff->hour_buff, buff + index_of_dollar[1] + 1, index_of_comma[9] - index_of_dollar[1] - 1);
	pBuff->hour_buff[index_of_comma[9] - index_of_dollar[1] - 1] = '\0';
	printf("Hour: %s\n", pBuff->hour_buff);		

	strncpy(pBuff->min_buff, buff + index_of_comma[9] + 1, index_of_comma[10] - index_of_comma[9] - 1);
	pBuff->min_buff[index_of_comma[10] - index_of_comma[9] - 1] = '\0';
	printf("Minute: %s\n", pBuff->min_buff);

	strncpy(pBuff->second_buff, buff + index_of_comma[10] + 1, index_of_comma[11] - index_of_comma[10] - 1);
	pBuff->second_buff[index_of_comma[11] - index_of_comma[10] - 1] = '\0';
	printf("Second: %s\n", pBuff->second_buff);

	strncpy(pBuff->day_buff, buff + index_of_comma[11] + 1, index_of_comma[12] - index_of_comma[11] - 1);
	pBuff->day_buff[index_of_comma[12] - index_of_comma[11] - 1] = '\0';
	printf("Day: %s\n", pBuff->day_buff);

	strncpy(pBuff->month_buff, buff + index_of_comma[12] + 1, index_of_comma[13] - index_of_comma[12] - 1);
	pBuff->month_buff[index_of_comma[13] - index_of_comma[12] - 1] = '\0';
	printf("Month: %s\n", pBuff->month_buff);

	strncpy(pBuff->year_buff, buff + index_of_comma[13] + 1, 4);
	pBuff->year_buff[4] = '\0';
	printf("Year: %s\n", pBuff->year_buff);

	printf("Time when the completion completed: %s:%s:%s  %s/%s/%s\n", pBuff->hour_buff, pBuff->min_buff, pBuff->second_buff, pBuff->day_buff, pBuff->month_buff, pBuff->year_buff);
}

int write_stat_file(struct conversion_statistics* stat)
{
	char buf[1000];
	FILE* fp;
	
	sprintf(buf, "$%s,%s,%d,%d,%d,%d,%d,%d,%d,%lf$%d,%d,%d,%d,%d,%d", stat->input_name, stat->output_name, 
	stat->size,stat->num_of_word_input,stat->num_of_word_converted,stat->num_of_word_error,stat->num_of_char,stat->num_of_char_converted,
	stat->num_of_char_not_converted,stat->time_convert,stat->time.hour,stat->time.min,stat->time.second,stat->time.day,stat->time.month,stat->time.year);

	printf("Stat buf: %s\n",buf);

	fp = fopen("stat.txt", "w+");
	if (!fp) {
		printf("Error opening statistic file\n");
		return -1;
	}

	fwrite(buf, strlen(buf), 1, fp);
	fclose(fp);
	
	return 0;
}

int get_statistics(struct conversion_statistics* stat)
{
	/* Implementing */
	time_t rawtime;
	struct tm *info;
	
	time(&rawtime);

	info = gmtime(&rawtime);
	stat->time.day = info->tm_mday;
	stat->time.hour = info->tm_hour;
	stat->time.min = info->tm_min;
	stat->time.second = info->tm_sec;
	stat->time.month = info->tm_mon + 1;
	stat->time.year = 2000 + info->tm_year - 100 ;
}

void stat_display(struct conversion_statistics* stat)
{
	printf("Input file: %s\n", stat->input_name);
	printf("Output file: %s\n", stat->output_name);
	printf("Time when the completion completed: %d:%d:%d  %d/%d/%d\n", stat->time.hour, stat->time.min, stat->time.second, stat->time.day, stat->time.month, stat->time.year);
	printf("Duration of the conversion is %lf seconds\n",stat->time_convert);
	printf("Word count in input file: %d\n", stat->num_of_word_input);
	printf("Word converted: %d\n", stat->num_of_word_converted);
	printf("Word with errors: %d\n", stat->num_of_word_error);
	printf("Total number of characters: %d\n", stat->num_of_char);
	printf("Total number of characters coverted: %d\n", stat->num_of_char_converted);
	printf("Total number of characters not converted: %d\n", stat->num_of_char_not_converted);

}

/*Ham chuyen tu chu sang ma morse*/
void TexttoMorse(FILE *fp1, FILE *fp2, struct conversion_statistics* stat)
{
	int i,j,k=0;
	char sen[1000]={};
	int char_count = 0;
	int space_count = 0;
	int n;
	
	time_t begin = time(NULL);

	/*gan cac ma morse vao con tro*/
	char *mor[44]={".-","-...","-.-.","-..",".","..-.","--.",
                "....","..",".---","-.-",".-..","--","-.",
                "---",".--.","--.-",".-.","...","-","..-",
                "...-",".--","-..-","-.--","--..","-----",
                ".----","..---","...--","....-",".....",
                "-....","--...","---..","----.","/",
				".-.-.-","--..--","..--..","---...","-....-","........","..-..."};
	
	/*gan co chu in hoa va so vao mang*/
	char tex[44][2]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o",
               "p","q","r","s","t","u","v","w","x","y","z","0","1","2","3",
                "4","5","6","7","8","9"," ",".",",","?",":","-","#","*"};	
	
	while(!feof(fp1))
    {
        fgets(sen,200,fp1);
        
		n = strlen(sen);
        printf("%s\n", sen);
		
		for (i = 0; i < n; i++) {
			if (sen[i] == ' ')
				space_count++;
		}

		if(sen[n-1]=='\n')
        {
			sen[n-1]=' ';
			k=n-1;
		} 
    	
		for (i = 0; i < 200; i++)
    	{
    		//sen[i]= toupper(sen[i]);
    		for (j = 0; j < 43; j++)
    		{
				if (sen[i] == tex[36][0] && i==k)
				{
					fprintf(fp2, "\n");
					break;
				}
				if (sen[i] == tex[j][0])
    			{
					fprintf(fp2, "%s ", mor[j]);
					char_count++;
 				} 
			}
		}
	}

	printf("buf:%s\n",sen);

	time_t end = time(NULL);

	fseek(fp2, 0, SEEK_END);
	
	stat->size = ftell(fp2);
	stat->num_of_char = n;
	stat->num_of_char_converted = char_count;
	stat->num_of_char_not_converted = n - char_count;
	stat->time_convert = difftime(end, begin);
	stat->num_of_word_converted = space_count + 1;
	stat->num_of_word_input = space_count + 1;
	stat->num_of_word_error = stat->num_of_word_input - stat->num_of_word_converted;

	fclose(fp1);
	fclose(fp2);	
}

/*Ham chuyen tu ma morse ve chu*/
void MorsetoText(FILE *fp1, FILE *fp2, struct conversion_statistics* stat)
{
	int i = 0, j = 0, k = 0, n = 0, a[100];
	char *mor[44]={".-","-...","-.-.","-..",".","..-.","--.",
                "....","..",".---","-.-",".-..","--","-.",
                "---",".--.","--.-",".-.","...","-","..-",
                "...-",".--","-..-","-.--","--..","-----",
                ".----","..---","...--","....-",".....",
                "-....","--...","---..","----.","/",
				".-.-.-","--..--","..--..","---...","-....-","........","..-..."};
	char tex[44][2]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o",
               "p","q","r","s","t","u","v","w","x","y","z","0","1","2","3",
                "4","5","6","7","8","9"," ",".",",","?",":","-","#","*"};
    char morse[1000]={ }, substr[1000][100]={ };
	int char_count = 0;
	int word_count = 0;
	long file_size;

	time_t begin = time(NULL);
    
	/*Dich ma morse*/
	while (!feof(fp1))
	{
		while(fgets (morse, 1000, fp1) != NULL)
    	{
			while(morse[k] != '\0')     /*xac dinh va loai bo (\n)*/
			{
				if (morse[k] == '\n')
				{
					morse[k] = '/';
					a[n] = k;
					n++;
					k = 0;
					break;
				}
				j=0; 

				if (morse[k] == '/') 
					word_count++;

				while(morse[k] != ' ' && morse[k] != '\0')   /*dich ma morse ve chu tuong ung*/
        		{
            		substr[i][j] = morse[k];
            		k++;
            		j++;
        		}
       			substr[i][j] = '\0';
        		i++;
        		if (morse[k] != '\0') {
            		k++;
       			}
			}
		}
	}
	
	/* Dua phan da dich vao file out*/
    int len=i;
 	for(i=0;i<len;i++)
 	{
  		for(j=0;j<44;j++)
  	 	{
			if(!strcmp(mor[j],substr[i]))
   			{
    			printf("%s",tex[j]);
    			fprintf(fp2, "%s",tex[j]);
				char_count++;
				break;	
    		}
		}
  	}

	time_t end = time(NULL);

	fseek(fp2, 0, SEEK_END);

	stat->size = ftell(fp2);
	stat->num_of_char = len;
	stat->num_of_char_converted = char_count;
	stat->num_of_char_not_converted = len - char_count;
	stat->num_of_word_input = word_count + 1;
	stat->num_of_word_converted = word_count + 1;
	stat->num_of_word_error = stat->num_of_word_input - stat->num_of_word_converted;
	stat->time_convert = difftime(end, begin);

  	fclose(fp1);
  	fclose(fp2);
}

/*Ham check file input, file output co ton tai khong?*/
int Checkfile(FILE *fp1, FILE *fp2,char fname1[], char fname2[], int cf)
{
	/*nhap dia chi cua file*/
    printf("Nhap file in: ");       
    gets(fname1);
	printf("Nhap file out: ");
    gets(fname2);
    
	/*check 2 file co ton tai khong*/
	fp1 = fopen(fname1, "r");
   	if (fp1 == NULL) 
	{
    	printf("Khong co file input\n");
		printf("Ket thuc chuong trinh");
      	cf = 0;
      	exit (1);
   	}
   	if (fp1 != NULL)
   	{
   		
		cf = 1;
	}
 	fp2 = fopen(fname2, "r");
   	if (fp2 == NULL) 
	{
      	printf("Khong co file output");
      	cf = 2;
		fclose(fp1);
    }
    if (fp2 != NULL)
    {
    	cf = 3;
    	fclose(fp1);
	}
   	return cf;  /*tra ve bang 1,2,3 hoac dung chuong trinh*/
}

/*Ham check file input la file morse hay file text*/
int Check(FILE *fp1, FILE *fp2,char fname1[], int c)
{
	/*so sanh cac phan tu voi cac chu, so, ky hieu ma khong phai ".""-"" ""/" */
	char str[1000]={ };
	int i,j;
	char tex[45][2]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o",
               "p","q","r","s","t","u","v","w","x","y","z","0","1","2","3",
                "4","5","6","7","8","9",",","?",":","#","*",".","-"," ","/"};
	fp1 = fopen(fname1, "r");
	while(!feof(fp1))
    {
        fgets(str,200,fp1);
        int n = strlen(str);
        if(str[n-1]=='\n')
        {
			str[n-1]='\0';
		}
		for (i=0;i<n;i++)
    	{
    		str[i]= toupper(str[i]);
    		for (j = 0; j < 40; j++)
    		{
				if (str[i] == tex[j][0])
    			{
					c=1; 
					break;
 				} 
			}
		}
	}
	fclose(fp1);
	
	return c; /*tra ve 1 hoac 0*/
}

int main(int argc, char* argv[])
{
	FILE *fp1, *fp2, *fpstat;
    char fname1[40], fname2[40];
    int cf=0, c=0, mofile=0;
	char buffDebug[1000];
	char buffStat[1000];
	struct conversion_statistics stat1;
	struct parsedBuff parseString;

    if (strcmp(argv[1],"-h") == 0) {
        printf("!!!!!USER GUIDE OF THE PROGRAM!!!!!!\n");
        printf("Steps 1: \n1. Open the command line and type the argument:\n\tIf you want to convert text to morse, type '-t'");
        printf("\n\tIf you want to convert morse to text, type '-m'\n\tIf you want to show the statistic, type '-c'\n");
        
        return 0;
    } else if (strcmp(argv[1],"-c") == 0) {
        printf("Showing statistics of the program\n");
		fpstat = fopen("stat.txt", "r+");
		if (!fpstat) {
			printf("Error opening statistic file\n");
			return -1;
		}
		
		fread(buffStat, sizeof(buffStat), 1, fpstat);

		printf("buff readed: %s\n", buffStat);

		parse_stat_file(buffStat, &parseString);

		fclose(fpstat);
		//get_statistics(&stat1, fp1, fp2);
		//stat_display(&stat1);
        return 0;
    } else if (strcmp(argv[3],"-t") == 0) {
		fp1 = fopen(argv[1], "r+");
		fp2 = fopen(argv[2], "w+");
		
		strcpy(stat1.input_name, argv[1]);
		strcpy(stat1.output_name, argv[2]);
		
		printf("Change text to morse\n");

		if ((!fp1) || (!fp2)) {
			printf("Error opening file\n");

			return -1;	
		}

		//fread(buffDebug, sizeof(buffDebug), 1, fp1);

		printf("%s\n", buffDebug);

		TexttoMorse(fp1, fp2, &stat1);

		get_statistics(&stat1);

		stat_display(&stat1);

		write_stat_file(&stat1);

		return 0;
	} else if (strcmp(argv[3],"-h") == 0) {
		fp1 = fopen(argv[1], "r+");
		fp2 = fopen(argv[2], "w+");

		strcpy(stat1.input_name, argv[1]);
		strcpy(stat1.output_name, argv[2]);

		printf("Change morse to text\n");
		if ((!fp1) || (!fp2)) {
			printf("Error opening file\n");

			return -1;	
		}

		MorsetoText(fp1, fp2, &stat1);

		get_statistics(&stat1);

		stat_display(&stat1);

		write_stat_file(&stat1);

		return 0;
	} else {
        printf("Unknown command. Types ""morse -h"" for help\n");

        return -1;
    }

	/* Lay gia tri 1,2,3 hoac chuong trinh dung */
    cf = Checkfile(fp1,fp2,fname1,fname2,cf);
    
	/*co file input, khong co file output*/
	if (cf==2)
    {
    	printf("\nTao file output?? Y(1) N(2):");
    	scanf("%d",&mofile);
    	if (mofile ==1)
    	{
    		cf = 3;
		}
		if (mofile ==2)
		{
			printf("Ket thuc chuong trinh");
			exit(1);
		}
	}
	/*co file output va input*/
   	if (cf==3)
	{	
		/*lay gia tri 0 hoac 1*/
		c= Check(fp1,fp2,fname1,c);		
   		if (c==1)
		{
			printf("File input la file text\n");
			fp1 = fopen(fname1, "r+");
			fp2 = fopen(fname2, "w+");
			TexttoMorse(fp1,fp2, &stat1);
		}
		if (c==0)
		{
			printf("File input la file morse\n");
			fp1 = fopen(fname1, "r+");
			fp2 = fopen(fname2, "w+");
			MorsetoText(fp1,fp2, &stat1);
		}
	}
	return (0);
}