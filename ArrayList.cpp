#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int listMaxSize;
int * list;
int length;


void initializeList()
{
	listMaxSize = LIST_INIT_SIZE;
	list = (int*)malloc(sizeof(int)*listMaxSize) ;
	length = 0 ;
}

void shrink()
{
    //if(length==LIST_INIT_SIZE) return NULL_VALUE;
    if(length==listMaxSize/2)
    {
        int *temp;
        listMaxSize=listMaxSize/2;
        temp=(int*)malloc(listMaxSize*sizeof(int));
        int i;
        for(i=0;i<length;i++) temp[i]=list[i];
        free(list);
        list=temp;
    }
}

int searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

int insertItem(int newitem)
{
    if(list==0) initializeList();
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
	return SUCCESS_VALUE ;
}


int deleteItemAt(int position) //version 2, do not preserve order of items
{
	if ( position >= length ) return NULL_VALUE;
	list[position] = list[length-1] ;
	length-- ;
	shrink();
	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return NULL_VALUE;
	deleteItemAt(position) ;
	return SUCCESS_VALUE ;
}

void printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}





int getLength()
{
    return length;
}

int insertItemAt(int pos, int item)
{
    if(pos>=length) return NULL_VALUE;
    if(length==listMaxSize)
    {
        int *temp;
        listMaxSize=2*listMaxSize;
        temp=(int*)malloc(listMaxSize*sizeof(int));
        int i;
        for(i=0;i<length;i++) temp[i]=list[i];
        free(list);
        list=temp;
    }
    list[length]=list[pos];
    list[pos]=item;
    length++;
    return SUCCESS_VALUE;
}



int deleteLast()
{
    int c;
    c=list[length-1];
    length--;
    shrink();
    return c;
}

void clear()
{
    free(list);
    length=0;
}

void deleteAll()
{
    initializeList();
}


int main()
{
    char str[50];
    gets(str);
    //printf("%s",str);
    int flag=0;
    initializeList();
    char *p=str;
    while(*p!='\0')
    {
        if(*p=='(' || *p=='{' || *p=='[')
            {
                insertItem(*p);
            }
        else if(*p==')' || *p=='}' || *p==']')
        {
            if(getLength()==0)  {flag=1; break;}
            else
            {

                int c=deleteLast();
                if(*p==')') if(c!='(') {flag=1; break;}
                if(*p=='}') if(c!='{') {flag=1;break;}
                if(*p==']') if(c!='[') {flag=1;break;}
            }
        }
        p++;
    }
    if(getLength()!=0) flag=1;
    if(flag==0) printf("Balanced\n");
    else printf("Not Balanced\n");
    return 0;
}


/*int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item at. 3. Delete item.\n");
        printf("4. Get Length. 5. Insert Item at. 6. Clear List. \n7.Delete All. 8. Delete Last.\n 9. Print. 10. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==4)
        {
            printf("Length is: %d",getLength());
        }
        else if(ch==5)
        {
            int pos,item;
            printf("position and item:");
            scanf("%d %d",&pos,&item);
            insertItemAt(pos,item);
        }
        else if(ch==6)
        {
            clear();
        }
        else if(ch==7)
        {
            deleteAll();
        }
        else if(ch==8)
        {
            deleteLast();
        }

        else if(ch==9)
        {
            printList();
        }
        else if(ch==10)
        {
            break;
        }
    }
    return 0;

}*/
