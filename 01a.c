# include <stdio.h>
# include <time.h>

void clearCurrentNumber(char * currentNumber);


int main(){

    clock_t begin = clock();

    FILE* fp = fopen("./Input.txt", "r");
    if(fp == NULL)
    {
        printf("cannot open file\n");
        return 1;
    }


    char c = fgetc(fp);

    char currentNumber[5] = {32}; //char array which contains digits in current line
    int number; //number in current line, converted from currentNumber array
    int i = 0; //current location in currentNumber array
    int lineBreakCounter = 0; //checks if there are two linebreaks in a row

    int currentMax = 0; //current biggest amount of calories
    int currentSum = 0; //added up sum of calories of current elf

    while(c != EOF)
    {
        //end of block
        if (c == '\n' && lineBreakCounter == 1)
        {
            lineBreakCounter = 0;
            i = 0;

            currentMax = (currentMax >= currentSum) ? currentMax : currentSum;

            currentSum = 0;
        }
        //end of line
        else if(c == '\n')
        {
            i = 0;
            lineBreakCounter++;
            sscanf(currentNumber, "%d", &number);
            currentSum += number;

            clearCurrentNumber(currentNumber);
            
        }
        else
        {
            lineBreakCounter = 0;
            currentNumber[i++] = c;
        }


        c = fgetc(fp);
    }
    
    if (ferror(fp)) 
    {
        printf("There appears to be an error. Stay calm\n");
        return 1;
    }

    fclose(fp);


    sscanf(currentNumber, "%d", &number);
    currentSum += number;
    currentMax = (currentMax >= currentSum) ? currentMax : currentSum;


    clock_t end = clock();


    printf("Solution: %d in time: %f sec\n", currentMax, (double)(end - begin)/CLOCKS_PER_SEC);


    return 0;
}

void clearCurrentNumber(char * currentNumber){
    for (int i = 0; i < 5; i++){
        currentNumber[i] = 32;
    }
}