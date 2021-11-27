#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

struct timeDone_t
{
	int hour;
	int min;
	int second;
	int day;
	int month;
	int year;
};

struct conversion_statistics {
	struct timeDone_t time;
	int size;
	int num_of_word_input;
	int num_of_word_converted;
	int num_of_word_error;
	int num_of_char;
	int num_of_char_converted;
	int num_of_char_not_cponverted;
	char input_name[100];
	char output_name[100];
};

int get_statistics(struct conversion_statistics* stat)
{
	/* Implementing */
	;
}

void stat_display(struct conversion_statistics* stat)
{
	printf("Input file: %s\n", stat->input_name);
	printf("Output file: %s\n", stat->output_name);
	printf("Time when the completion completed: ");
}

/*Ham chuyen tu chu sang ma morse*/
void TexttoMorse(FILE *fp1, FILE *fp2)
{
	int i,j,k=0;
	char sen[1000]={};
	
	/*gan cac ma morse vao con tro*/
	char *mor[44]={".-","-...","-.-.","-..",".","..-.","--.",
                "....","..",".---","-.-",".-..","--","-.",
                "---",".--.","--.-",".-.","...","-","..-",
                "...-",".--","-..-","-.--","--..","-----",
                ".----","..---","...--","....-",".....",
                "-....","--...","---..","----.","/",
				".-.-.-","--..--","..--..","---...","-....-","........","..-..."};
	
	/*gan co chu in hoa va so vao mang*/
	char tex[44][2]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O",
               "P","Q","R","S","T","U","V","W","X","Y","Z","0","1","2","3",
                "4","5","6","7","8","9"," ",".",",","?",":","-","#","*"};	
	
	/*dich tu cac chu ra ma morse va dua vao file out*/
	do
    {
        int n = strlen(sen);      /*loai cac o chua (\n) thay bang (whitespace)*/
		if(sen[n-1]=='\n')
        {
			sen[n-1]=' ';
			k=n-1; 
		}
		
    	for (i=0;i<1000;i++)
    	{
			if (i==k)
			{
				if(sen[i] == tex[36][0])
				{	
					fprintf(fp2, "\n"); 	/*xuong dong o nhung cho tuong ung (\n)*/
					break; 
				}
			}
   			if(i<k)
   			{
				sen[i]= toupper(sen[i]);  /*chuyen chu thuong thanh chu in hoa*/
   				for (j=0;j<43;j++)		  /*so sanh voi tung mang va in ra ma morse tuong ung*/
   				{
					if (sen[i] == tex[j][0])
    				{
						fprintf(fp2, "%s ", mor[j]);
						printf("%s\n",mor[j]);
						break;
 					} 
 				}
			}
		}
	}
	while(fgets(sen,1000,fp1)!= NULL);
	fclose(fp1);
	fclose(fp2);	
}

/*Ham chuyen tu ma morse ve chu*/
void MorsetoText(FILE *fp1, FILE *fp2)
{
	int i=0,j=0,k=0,n=0,a[100];
	char *mor[44]={".-","-...","-.-.","-..",".","..-.","--.",
                "....","..",".---","-.-",".-..","--","-.",
                "---",".--.","--.-",".-.","...","-","..-",
                "...-",".--","-..-","-.--","--..","-----",
                ".----","..---","...--","....-",".....",
                "-....","--...","---..","----.","/",
				".-.-.-","--..--","..--..","---...","-....-","........","..-..."};
	char tex[44][2]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O",
               "P","Q","R","S","T","U","V","W","X","Y","Z","0","1","2","3",
                "4","5","6","7","8","9"," ",".",",","?",":","-","#","*"};
    char morse[1000]={ }, substr[1000][100]={ };
    
	/*Dich ma morse*/
	while (!feof(fp1))
	{
		while(fgets (morse, 1000, fp1)!=NULL)
    	{
			while(morse[k]!='\0')     /*xac dinh va loai bo (\n)*/
			{
				if (morse[k]=='\n')
				{
					morse[k]='/';
					a[n]=k;
					n++;
					k=0;
					break;
				}
				j=0; 
				while(morse[k]!=' '&& morse[k]!='\0')   /*dich ma morse ve chu tuong ung*/
        		{
            		substr[i][j]=morse[k];
            		k++;
            		j++;
        		}
       			substr[i][j]='\0';
        		i++;
        		if(morse[k]!='\0')
        		{
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
				break;	
    		}
		}
  	}
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
	char tex[45][2]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O",
               "P","Q","R","S","T","U","V","W","X","Y","Z","0","1","2","3",
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
    		for (j=0;j<40;j++)
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
	FILE *fp1, *fp2;
    char fname1[40], fname2[40];
    int cf=0, c=0, mofile=0;
	char buffDebug[1000];
	struct conversion_statistics stat1;

    if (strcmp(argv[1],"-h") == 0) {
        printf("!!!!!USER GUIDE OF THE PROGRAM!!!!!!\n");
        printf("Steps 1: \n1. Open the command line and type the argument:\n\tIf you want to convert text to morse, type '-t'");
        printf("\n\tIf you want to convert morse to text, type '-m'\n\tIf you want to show the statistic, type '-c'");
        
        return 0;
    } else if (strcmp(argv[1],"-c") == 0) {
        printf("Showing statistics of the program\n");
		get_statistics(&stat1);
		printf("");
        return 0;
    } else if (strcmp(argv[3],"-t") == 0) {
		fp1 = fopen(argv[1], "r");
		fp2 = fopen(argv[2], "w");

		printf("Change text to morse\n");

		if ((!fp1) || (!fp2)) {
			printf("Error opening file\n");

			return -1;	
		}

		fread(buffDebug, sizeof(buffDebug), 1, fp1);

		printf("%s\n", buffDebug);

		TexttoMorse(fp1, fp2);

		return 0;
	} else if (strcmp(argv[3],"-h") == 0) {
		fp1 = fopen(argv[1], "r");
		fp2 = fopen(argv[2], "w");

		printf("Change morse to text\n");
		if ((!fp1) || (!fp2)) {
			printf("Error opening file\n");

			return -1;	
		}

		MorsetoText(fp1, fp2);

		fclose(fp1);
		fclose(fp2);

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
			TexttoMorse(fp1,fp2);
		}
		if (c==0)
		{
			printf("File input la file morse\n");
			fp1 = fopen(fname1, "r+");
			fp2 = fopen(fname2, "w+");
			MorsetoText(fp1,fp2);
		}
	}
	return (0);
}