/*
 * Single link list
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h> ( for sleep();)

//link list struct
typedef struct sv
{
	char ten[30];
	unsigned int tuoi;
	float diemTB;
	struct sv* next;
}
sv;

//prototype
void del(void);
void add(void);
void print_list(void);
//global variable
sv* first = NULL;
int main(void)
{
	int c;
	sv* ptr = NULL;
	do
	{
		printf("MENU\n\n");
		printf("1. add\n");
		printf("2. delete\n");
		printf("3. find\n");
		printf("4. print list\n");
		printf("0. quit\n");
		
		
		printf("COMAND :");
		scanf("%d", &c);
		
		
		//action
		switch 	(c)
		{
			case 1 : add(); break;
			case 2 : del(); break;
			case 4 : print_list(); break;
		}
	} while (c != 0);
	
	//free list after use
	while (ptr != NULL)
	{
		free(ptr);
		ptr = ptr->next;
	}
	return 0;
}

//add a sv
void add(void)
{
	//create newptr using malloc
	sv* newptr = malloc(sizeof(sv));
	newptr->next = NULL;
	printf("Ho ten : ");
	fflush(stdin);
	gets(newptr->ten);
	printf("Tuoi   : ");
	fflush(stdin);
	scanf("%d", &newptr->tuoi);
	printf("Diem TB: ");
	fflush(stdin);
	scanf("%f", &newptr->diemTB);
	
	//if list null
	if (first == NULL)
		first = newptr;
	//in the first
	else if(strcmpi(newptr->ten, first->ten) < 0)
	{
		newptr->next = first;
		first = newptr;
	}

	//if not null
	else
	{
		sv *preptr;
		preptr = first;
		while (1)
		{
			//check if duplicate
			if(strcmpi(preptr->ten, newptr->ten) == 0)
			{
				free(newptr);
				break;
			}
			//at tail
			else if (preptr->next == NULL)
			{
				preptr->next = newptr;
				break;
			}
			//in the middle
			else if(strcmpi(preptr->next->ten, newptr->ten) > 0)
			{
				newptr->next = preptr->next;
				preptr->next = newptr;
				break;
			}
			
			//update pointer
			preptr = preptr->next;
		}
		
	}
	print_list();
		
}

//Print list
void print_list(void)
{
	int i;
	sv* ptr = first;
	i = 1;
	printf("Danh sach sinh vien\n");
	printf("STT HOTEN              TUOI  DIEMTB\n");
	while (ptr!= NULL)
	{
		printf("%-4d%-20s%-6d%-6.2f\n", i, ptr->ten, ptr->tuoi, ptr->diemTB);
		ptr = ptr->next;
		i++;
	}
	
	// flush standard output since we haven't outputted any newlines yet
    fflush(stdout);

    // pause before continuing
    //sleep(1);
    printf("\n\n");
}

//delete a sv
void del(void)
{
	char s[30];
	sv* ptr, *preptr;
	ptr = first;
	preptr = NULL;

	printf("Nhap ten SV muon xoa : ");
	fflush(stdin);
	gets(s);
	while (ptr != NULL)
	{
		if (strcmpi(ptr->ten, s) == 0)
		{
			//delete at first of list
			if (first == ptr)
			{
				first =  ptr->next;
				free(ptr);
			}
			//delete at middle or tail
			else
			{
				preptr->next = ptr->next;
				free(ptr);
			}
			break;
		}
		//update pointer (preptr ->next = ptr)
		else
        	{
	            preptr = ptr;
	            ptr = ptr->next;
       		}
	}
	print_list();
}
