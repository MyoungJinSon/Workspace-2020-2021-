#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_NUM 200
#define BUFFER_SIZE 256
typedef struct {
		char name[30];
		char phone1[20];
		char phone2[20];
		char memo[40];
}Phonebook, temp;
int Save(Phonebook* ptr, int* num);
int Open(Phonebook* ptr, int* num);
void Add(Phonebook* ptr,int* num,char* s1);
int Delete(Phonebook* ptr, int* num);
void List(Phonebook* ptr, int *num);
void Search(Phonebook* ptr, int*num,char *s1);
void print_menu();
int main(int argc, char*argv[]){
		Phonebook user[MAX_NUM];
		int count = 0;
		int i;
		char Input;
		Open(user, &count);
		printf("자료수 :%d\n",(count/4));
		if(strcmp(argv[1], "-a")==0){   //add 완료
				printf("add? [Y/N]: Y(Enter)\n");
				scanf("%c", &Input);
				if(Input=='Y'){
						Add(user, &count,argv[2]);
						count = count +4;
						printf("몇줄 :%d \n",(count/4));
				}
				else
						exit(0);
		}
		else if(strcmp(argv[1], "-d")==0){
				//Delete(user, &count);
				printf("delete\n");
		}
		else if (strcmp(argv[1], "-l")==0){
				List(user, &count);
				
		}
		else if(argc==1)  {
			print_menu();
		}
		else if (strcmp(argv[1],"-s")==0){
				Save(user, &count);
				printf("Saving\n");
		}
		
		else {  //이부분 고쳐야됨
                printf("serching\n");
                Search(user, &count, argv[2]);
		}

		return 0;
}

void Add(Phonebook* ptr, int* num,char* s1){
		char BUF[BUFFER_SIZE];
		char *sArr[200] = {NULL,};
		int i=0;
		char data_count = 0;
		int offset  = 0;
		int chars = strlen(s1)+1;
		char delimeter = ':';
		FILE*fp1 = NULL;
		char Input;
        fp1 = fopen("data.txt","a");
		
		if(*num <MAX_NUM){
				while(data_count<4){
						BUF[0] ='\0';
						for(i= offset; i<chars; i++){
								if(s1[i]== ':'){
										BUF[i-offset]= '\0';
										break;
								}
								BUF[i-offset] = s1[i];
						}
						offset = i+1;
						if(data_count ==0){
								memcpy(ptr[(*num/4)].name,BUF,sizeof(ptr->name));
								fprintf(fp1,("%s",BUF));
								fprintf(fp1,":");
						}
						else if(data_count ==1){
								memcpy(ptr[(*num/4)].phone1,BUF,sizeof(ptr->phone1));
								fprintf(fp1,("%s",BUF));
								fprintf(fp1,":");
						}
						else if(data_count ==2){
								memcpy(ptr[(*num/4)].phone2,BUF,sizeof(ptr->phone2));
								fprintf(fp1,("%s",BUF));
								fprintf(fp1,":");
						}
						else if(data_count ==3){
								memcpy(ptr[(*num/4)].memo,BUF,sizeof(ptr->memo));
								fprintf(fp1,("%s",BUF));
								fprintf(fp1,"\n");
						}
						data_count++;
				}
		}
		else{
				printf("data FULL\n");
		}
		fclose(fp1);
		printf("Data Added");
		
}

int Open(Phonebook* ptr, int *num){
		char *sArr[200]={NULL,};
		char inputfile[256];
		FILE *fp;
		int i=0;
		int count = -1;
		char delimeter =':';
		
		fp= fopen("data.txt","rt");
		int linecount = 1;
		char BUF[BUFFER_SIZE];
		
		if (fp !=NULL){
				char buffer[256];
				while(1){
						fgets(buffer,sizeof(buffer), fp);
						if(feof(fp))
										break;
						linecount++;
						int chars = strlen(buffer)+1;
						int data_count =0;
						int offset = 0;
						
						//printf("saving \n");
						while(data_count<4){
								BUF[0] ='\0';
								
								for(i= offset; i<chars; i++){
										if(buffer[i]== ':'){
												BUF[i-offset]= '\0';
												break;
										}
										BUF[i-offset] = buffer[i];
								}
								offset = i+1;
								if(data_count ==0){
										memcpy(ptr[(*num)/4].name,BUF,sizeof(ptr->name));
										printf("몇번째 자료:%d, %s",(*num/4),ptr[(*num)/4].name);
										data_count++;
								}
								else if(data_count ==1){
										memcpy(ptr[(*num)/4].phone1,BUF,sizeof(ptr->phone1));
										printf("%s",ptr[(*num)/4].phone1);
										data_count++;
								}
								else if(data_count ==2){
										memcpy(ptr[(*num)/4].phone2,BUF,sizeof(ptr->phone2));
										printf("%s",ptr[(*num)/4].phone2);
										data_count++;
								}
								else if(data_count ==3){

										memcpy(ptr[(*num)/4].memo,BUF,sizeof(ptr->memo));
										printf("%s\n",ptr[(*num)/4].memo);
										data_count++;
								}
								//data_count++;
								(*num)++;
										
						}
						
					
				}
		}
		else{
				printf("Failed to open file");
				return 1;
		}

		
		fclose(fp);
		return 0;
}
int Save(Phonebook* ptr, int *num){
		int i;
		if(*num>0){
				FILE *fp = fopen("data.txt","wt");
				if(fp = NULL){
						printf("failed");
						return 1;
				}
				for (i=0; i<*num; i++){
						fprintf(fp,"%s %s %s %s",ptr[i].name,ptr[i].phone1,ptr[i].phone2,ptr[i].memo);
						fputc('\n',fp);
				}
				fclose(fp);
				printf("saved\n");
				return 0;
		}
		else{
				printf(" closeing...\n");
				return 0;
		}
}

	
void print_menu(){
	printf("it is menu\n");
}

void Search(Phonebook* ptr, int*num,char *s1){
		int i;
		FILE *fp;
		fp =fopen("data.txt","r");
		int count = (*num)/4;	
		char arr[30];
		arr[0]='\0';
		int ct=0;
		char buffer[256];
		int linecount =0;
		//char *ptr2= strchr(ptr[i].name,s1);
		//printf("*ptr2 :%c , ptr : %d\n",*ptr2, ptr2);
		if(fp != NULL){
				while(1){
						fgets(buffer, sizeof(buffer), fp);
						if(feof(fp))
								break;
						linecount++;
						char *ptr2 = strchr(buffer,s1);
						printf("%s \n",buffer);
						while(ptr2 !='\0'){
								printf("%d %s %s\n",linecount,ptr[linecount].name,ptr[linecount].phone1);
						}
						
						//if ((*(strchr(ptr[i].name,s1))==NULL)&&(*(strchr(ptr[i].phone1,s1))==NULL)&&(*(strchr(ptr[i].phone2,s1))==NULL)&&(*(strchr(ptr[i].memo,s1))==NULL)){
						//		printf("%d %s %s %s %s",i, ptr[i].name, ptr[i].phone1,ptr[i].phone2,ptr[i].memo);
						//		printf("matchfound \n");
						//}
						
				}
		}
		else{
				printf("no data\n");
		}
		fclose(fp);
}

void List(Phonebook* ptr, int *num){
		int i, j;
		Phonebook tmp;
		int count = (*num)/4;
		for (i=1; i<count; i++)
				for(j=0; j<count-i; j++){
						if(strcmp(ptr[j].name, ptr[j+1].name)>0){
								tmp = ptr[j];
								ptr[j] = ptr[j+1];
								ptr[j+1] = tmp;
						}
				}

		for (i=0; i<count;i++){
				printf("%s %s %s %s",(ptr[i].name),(ptr[i].phone1),(ptr[i].phone2),(ptr[i].memo));
		}
}
						
				
