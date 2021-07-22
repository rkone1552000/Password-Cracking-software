#include<iostream>
#include<fstream>
#include <thread>
#include <fcntl.h>
#include <string.h>

using namespace std;

bool match_found=false;

void tryPass(FILE* input_file_stream,int offset,int no_of_bytes,char* destination_buffer,char* target_hashed_password)
{
	char* hashed_password=(char*)malloc(100*1+1);
	int delta=0;		//stores the extra bytes we need to travers in order to get to the starting of the next password
	if(offset!=0)
	{	fseek(input_file_stream,offset-1,SEEK_SET);
		char *temp=(char*)malloc(1);
		*temp=' ';
		while(*temp!='\n')
		{	fread(temp,1,1,input_file_stream);
			delta++;
		}
	}
	offset+=delta;	//updated offset marking the starting of the password from which checking is to be done
	for(int i=0;i<no_of_bytes;i++)
	{
		if(match_found==true)
			return;
		char* temp=(char*)malloc(1);
		*temp=' ';
		int j=0;
		while(true)
		{	fread(temp,1,1,input_file_stream);
			if(*temp=='\n')	
			{	hashed_password[j]='\0';
				break;
			}	
			hashed_password[j]=*temp;
			j++;
		}
		i+=j;
		if(strcmp(hashed_password,target_hashed_password)==0)
		{
			cout<<"****************************Match found*****************************"<<endl;
			match_found=true;
			return;
		}
	cout<<hashed_password<<endl;
	}
				
}	
	
void gen(char* dictionary_path,char* target_hashed_password)		// dictionary [input file path]
{
	
	char* destination_buffer1=(char*)malloc(100*1+1);
	char* destination_buffer2=(char*)malloc(100*1+1);
	char* destination_buffer3=(char*)malloc(100*1+1);
	char* destination_buffer4=(char*)malloc(100*1+1);
	char* size_in_string;
	int fd_input1,fd_input2,fd_input3,fd_input4;
	int size,interval;
	int fd_size_file=open("temp.txt",0);
	
	FILE *input_file_stream1,*input_file_stream2,*input_file_stream3,*input_file_stream4;
	FILE *fstr;
	cout<<"hello"<<endl;
	cout<<dictionary_path<<endl;
	fd_input1=open(dictionary_path,0);
	fd_input2=open(dictionary_path,0);
	fd_input3=open(dictionary_path,0);
	fd_input4=open(dictionary_path,0);
	
	fstr=fdopen(fd_size_file,"r");
	
	input_file_stream1=fdopen(fd_input1,"r");
	input_file_stream2=fdopen(fd_input2,"r");
	input_file_stream3=fdopen(fd_input3,"r");
	input_file_stream4=fdopen(fd_input4,"r");
	
	cout<<"Echo1"<<endl;
	size_in_string=(char*)malloc(100*1);
	int i=0;
	for(i=0;i<100;i++)
	{
		fread(size_in_string+i,1,1,fstr);
		cout<<size_in_string[i];
		if(size_in_string[i]==':')
		{	size_in_string[i]='\0';
			break;
		}
	}	
	if(i==100)
	{	cout<<"Sorry file size is larger than permissible"<<endl;
		return ;
	}
	cout<<endl;
	cout<<size_in_string<<endl;	
	
	size=stoi(size_in_string);	
	
	string s;
	cin>>s;
	
	interval=size/4;
	cout<<"Echo2"<<endl;	
	thread th1(tryPass,input_file_stream1,0,interval,destination_buffer1,target_hashed_password);
	thread th2(tryPass,input_file_stream2,1*interval,interval,destination_buffer2,target_hashed_password);
	thread th3(tryPass,input_file_stream3,2*interval,interval,destination_buffer3,target_hashed_password);
	thread th4(tryPass,input_file_stream4,3*interval,interval,destination_buffer4,target_hashed_password);
	
	th1.join();th2.join();th3.join();th4.join();
	
	free(destination_buffer1);free(destination_buffer2);free(destination_buffer3);free(destination_buffer4);
	fclose(input_file_stream1);fclose(input_file_stream2);fclose(input_file_stream3);fclose(input_file_stream4);
	fclose(fstr);
	free(size_in_string);	
		
}
int main()
{
	char* target_hashed_password=(char*)malloc(200);
	char* path=(char*)malloc(200);
	char* dict_name=(char*)malloc(100);
	char* cmd=(char*)malloc(200);

	cout<<"Enter the hashed password whose plaintext is to be found"<<endl;
	cin>>target_hashed_password;
	cout<<"Enter the dictionay name: ";
	cin>>dict_name;
	sprintf(path,"/home/shayaksarkar/Desktop/PROJECT-ON-PASSWORD-CRACKING-TOOL-supermaster/PROJECT-ON-PASSWORD-CRACKING-TOOL-master/data/dictionary/%s",dict_name);
	cout<<"Path is \n"<<path<<endl<<endl;
	sprintf(cmd,"python3 /home/shayaksarkar/Desktop/PROJECT-ON-PASSWORD-CRACKING-TOOL-supermaster/PROJECT-ON-PASSWORD-CRACKING-TOOL-master/headers/GetFileInfo.py %s",path);
	system(cmd);
	gen(path,target_hashed_password);
	free(path);free(dict_name);free(cmd);
	if(!match_found)
		cout<<"Sorry match not found"<<endl;
}
