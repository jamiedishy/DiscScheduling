  
/*
  Disk Scheduling Algorithms: FCFS, SCAN, C-SCSAN
*/

#include <stdio.h>
#include <stdlib.h>

#define HEADPOSITION 33

int requestsArray[25];

int indexLower = 0;
int indexLarger = 0;

FILE *input_file_pointer;
FILE *output_file_pointer;

void fcfs() {
    int headMovement = 0;
    int hPosition = HEADPOSITION;
    fprintf(output_file_pointer, "\nFCFS Algorithm\n");
    fprintf(output_file_pointer, "Initial head position = %d\n", HEADPOSITION);
    fprintf(output_file_pointer, "Seek Sequence is:\n");

    for (int i = 0; i < 25; i++) {
        fprintf(output_file_pointer, "%d\n", requestsArray[i]);
    }
    for(int i = 0; i < 25; i++) {
    	headMovement += abs(requestsArray[i] - hPosition);
        hPosition = requestsArray[i];
    }

    fprintf(output_file_pointer, "Total head movement for FCFS = %d\n", headMovement);
}

void scan() {
    int headMovement = 0;
    int hPosition = HEADPOSITION;

    fprintf(output_file_pointer, "\nSCAN Algorithm\n");
    fprintf(output_file_pointer, "Initial head position = %d\n", HEADPOSITION);
    fprintf(output_file_pointer, "Seek Sequence is:\n");
    
    for (int i = indexLower; i >= 0; i--) {
        fprintf(output_file_pointer, "%d\n", requestsArray[i]);
    }

    for (int i = indexLarger; i < 25; i++) {
        fprintf(output_file_pointer, "%d\n", requestsArray[i]);
    }    
    
    headMovement = abs(0 - HEADPOSITION) + abs(0 - requestsArray[24]);
    fprintf(output_file_pointer, "Total head movement for SCAN = %d\n", headMovement);
}

void cscan() {
    int headMovement = 0;
    int hPosition = HEADPOSITION;
    fprintf(output_file_pointer, "\nC_SCAN Algorithm\n");
    fprintf(output_file_pointer, "Initial head position = %d\n", HEADPOSITION);
    fprintf(output_file_pointer, "Seek Sequence is:\n");

    for (int i = indexLarger; i < 25; i++) {
        fprintf(output_file_pointer, "%d\n", requestsArray[i]);
    }   

    for (int i = 0; i <= indexLower; i++) {
        fprintf(output_file_pointer, "%d\n", requestsArray[i]);
    }    

    headMovement = abs(99-HEADPOSITION) + abs(99 - 0) + abs(requestsArray[indexLower] - 0);
    fprintf(output_file_pointer, "Total head movement for C_SCAN = %d", headMovement);
}

void sortArray() { // sorted in non-descending order 
    int temp;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            if (requestsArray[i] < requestsArray[j]) {
                temp =  requestsArray[i];
                requestsArray[i] = 	requestsArray[j];
                requestsArray[j] = temp;
            }
        }
    }
    findIndices();
}

void findIndices() {
    for (int i = 0; i < 25; i++) {
        if (requestsArray[i] > HEADPOSITION) {
            indexLarger = i;
            indexLower = i-1;
            break;     
        }
    }
}


int main()
{
    char input_read[10]; // to read values from input.txt
    int cylinder_request_value; // its the integer version of the input_read
    int index = 0; // to populate requestsArray

    input_file_pointer = fopen("input.txt", "r");
    if (input_file_pointer == NULL)
    {
        printf("Error no virtual file\n");
    }

    output_file_pointer = fopen("my_output.txt", "w");

    while (fgets(input_read, sizeof(input_read), input_file_pointer) != 0)
    {
        // total_counter++;
        cylinder_request_value = atoi(input_read);
        requestsArray[index] = cylinder_request_value;
        index++;
        //fprintf(output_file_pointer, "%d\n", cylinder_request_value);
    }

    fcfs();
    sortArray();
    scan();
    cscan();

    return 0;
}