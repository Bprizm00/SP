#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct _StackeElement;
typedef struct _StackElement* Position;
typedef struct _StackElement{
    double number;
    Position next;
}StackElement;

Position CreateElement(double number);
int InsertAfter(Position position, Position newElement);
int Push(Position head, double number);
int DeleteAfter(Position position);
int Pop(double* result, Position head);
int PerformOperation(Position head, char operation);
int CalculatePostfixFromFile(double* result, char* fileName);
int DeleteAll(Position head);

int main(){
    StackElement head = {.number = 0, .next = NULL};
    Position p = &head;



    return 0;
}

Position CreateElement(double number)
{
    Position newElement = NULL;

    newElement = (Position)malloc(sizeof(StackElement));

    if(!newElement)
    {
        perror("Can't allocate memory!\n");
    }

    newElement->number = number;
    newElement->next = NULL;

    return newElement;
}

int InsertAfter(Position position, Position newElement)
{
    newElement->next = position->next;
    position->next = newElement;

    return 0;
}

int Push(Position head, double number)
{
    Position newElement = NULL;

    newElement = CreateElement(number);

    if(!newElement)
    {
        return -1;
    }

    InsertAfter(head, newElement);

    return EXIT_SUCCESS;
}

int DeleteAfter(Position position)
{
    Position temp = position->next;

    if(!temp)
    {
        return EXIT_SUCCESS;
    }

    position->next = temp->next;
    free(temp);

    return EXIT_SUCCESS;
}

int DeleteAll(Position head)
{
    
    Position position = head;
	Position temp = NULL;

	while (position->next != NULL)
	{
		temp = position->next;
		position->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}


int Pop(double* result, Position head)
{
    Position first = head->next;

    if(!first)
    {
        perror("Postfix not valid! Please check your file!\n");
        return -1;
    }

    *result = first->number;
    DeleteAfter(head);

    return EXIT_SUCCESS;
}

int PerformOperation(Position head, char operation)
{
    double operand1 = 0;
    double operand2 = 0;
    int status1 = EXIT_SUCCESS;
    int status2 = EXIT_SUCCESS;
    double result = 0.0;

    status2 = Pop(&operand2, head);
    if(status2 != EXIT_SUCCESS)
    {
        return -1;
    }

    status1 = Pop(&operand1, head);
    if(status1 != EXIT_SUCCESS)
    {
        return -2;
    }

    switch(operation)
    {
        case '+':
            result = operand1 + operand2;
            break;

        case '-':
            result = operand1 - operand2;
            break;

        case '*':
            result = operand1 * operand2;
            break;    

        case '/':
            if(operand2 == 0)
            {
                printf("Can not divide with zero!\n");
                return -3;
            }
            result = operand1/operand2;
            break;

        default:
            printf("This operation is not supported yet!\n");
            return -4;    
    }

    Push(head, result);

    return EXIT_SUCCESS;
}

int CalculatePostfixFromFile(double* result, char* fileName)
{
    FILE* file = NULL;
    file = fopen(fileName, "rb");
    int fileLength = 0;
    int status = 0;
    char* buffer = NULL;
    char* currentBuffer = NULL;
    int numBytes = 0;
    int number = 0;
    char operation = {0};
    StackElement head = { .number = 0, .next = NULL};
    
    if(!file)
    {
        perror("Can't open file!\n");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);

    buffer = (char*)calloc(fileLength + 1, sizeof(char));
    if(!buffer)
    {
        printf("Can't allocate memory!\n");
        return -2;
    }

    rewind(file);

    fread(buffer, sizeof(char), fileLength, file);
    printf("|%s|\n",buffer);
    fclose(file);
    currentBuffer = buffer;

    while(strlen(currentBuffer) > 0)
    {
        status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);
        if(status == 1)
        {
            Push(&head, number);
            if(status != EXIT_SUCCESS){
                free(buffer);
                DeleteAll(&head);
                return -3;
            }
            currentBuffer += numBytes;
        }  
        else
        {
            sscanf(currentBuffer, " %c %n", &operation, &numBytes);
            status = PerformOperation(&head, operation);
            if(status != EXIT_SUCCESS){
                free(buffer);
                DeleteAll(&head);
                return -4;
            }
            currentBuffer += numBytes;
   
        }
            free(buffer);
            status = Pop(result, &head);
        if(status != EXIT_SUCCESS){
                DeleteAll(&head);
                return -5;
            }
        if(head.next)
            {
            printf("Please check your file!\n");
            DeleteAll(&head);
            return -6;
            }       
    

    return EXIT_SUCCESS; 

}
}



