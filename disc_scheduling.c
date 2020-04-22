  
/*
  Disk Scheduling Algorithms: FCFS, SCAN, C-SCSAN
*/

#include <stdio.h>
#include <stdlib.h>

#define HEADPOSITION 33
#define CYLINDERREQUESTS 25
#define INITIALINDEX 24

int requestsArray[CYLINDERREQUESTS];

int indexLower = INITIALINDEX;
int indexLarger = INITIALINDEX ;

FILE *input_file_pointer;
FILE *output_file_pointer;

void fcfs() {
    int headMovement = 0;
    int hPosition = HEADPOSITION;
    fprintf(output_file_pointer, "\nFCFS Algorithm\n");
    fprintf(output_file_pointer, "Initial head position = %d\n", HEADPOSITION);
    fprintf(output_file_pointer, "Seek Sequence is:\n");

    for (int i = 0; i < CYLINDERREQUESTS; i++) {
        fprintf(output_file_pointer, "%d\n", requestsArray[i]);
    }
    for(int i = 0; i < CYLINDERREQUESTS; i++) {
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
    
    if (indexLarger == INITIALINDEX && indexLower == INITIALINDEX) { // strictly smaller
        for (int i = indexLower; i >= 0; i--) {
            fprintf(output_file_pointer, "%d\n", requestsArray[i]);
        }

        headMovement = abs(HEADPOSITION - requestsArray[0]);
    }
    else if (indexLarger != INITIALINDEX && indexLower == INITIALINDEX) { // strictly larger
        for (int i = indexLarger; i < CYLINDERREQUESTS; i++) {
            fprintf(output_file_pointer, "%d\n", requestsArray[i]);
        } 
        headMovement = abs(0 - HEADPOSITION) + abs(0 - requestsArray[INITIALINDEX]);
    }
    else { // both smaller and larger than init
        for (int i = indexLower; i >= 0; i--) {
            fprintf(output_file_pointer, "%d\n", requestsArray[i]);
        }
        for (int i = indexLarger; i < 25; i++) {
            fprintf(output_file_pointer, "%d\n", requestsArray[i]);
        }    
        headMovement = abs(0 - HEADPOSITION) + abs(0 - requestsArray[INITIALINDEX]);
    }

    fprintf(output_file_pointer, "Total head movement for SCAN = %d\n", headMovement);
}

void cscan() {
    int headMovement = 0;
    int hPosition = HEADPOSITION;
    fprintf(output_file_pointer, "\nC_SCAN Algorithm\n");
    fprintf(output_file_pointer, "Initial head position = %d\n", HEADPOSITION);
    fprintf(output_file_pointer, "Seek Sequence is:\n");

    if (indexLarger == INITIALINDEX && indexLower == INITIALINDEX) { // strictly smaller
        for (int i = 0; i <= indexLower; i++) {
            fprintf(output_file_pointer, "%d\n", requestsArray[i]);
        }
        if (requestsArray[INITIALINDEX] == 33) {
            headMovement = abs(99-HEADPOSITION) + abs(99 - 0) + abs(requestsArray[indexLower - 1] - 0);
        }
        else {
            headMovement = abs(99-HEADPOSITION) + abs(99 - 0) + abs(requestsArray[indexLower] - 0);
        }
    }
    else if (indexLarger != INITIALINDEX && indexLower == INITIALINDEX) { // strictly larger
        for (int i = indexLarger; i < CYLINDERREQUESTS; i++) {
            fprintf(output_file_pointer, "%d\n", requestsArray[i]);
        } 
        headMovement = abs(HEADPOSITION - requestsArray[INITIALINDEX]);
    }
    else { // both smaller and larger than init
        for (int i = indexLarger; i < 25; i++) {
            fprintf(output_file_pointer, "%d\n", requestsArray[i]);
        }   
        for (int i = 0; i <= indexLower; i++) {
            fprintf(output_file_pointer, "%d\n", requestsArray[i]);
        }    
        if (indexLower == 0) {
            headMovement = abs(99-HEADPOSITION);
        }
        else {
        headMovement = abs(99-HEADPOSITION) + abs(99 - 0) + abs(requestsArray[indexLower] - 0);
        }
    }

    fprintf(output_file_pointer, "Total head movement for C_SCAN = %d", headMovement);
}

void sortArray() { // sorted in non-descending order 
    int temp;
    for (int i = 0; i < CYLINDERREQUESTS; i++) {
        for (int j = 0; j < CYLINDERREQUESTS; j++) {
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
    for (int i = 0; i < CYLINDERREQUESTS; i++) {
        if (requestsArray[i] > HEADPOSITION) {
            indexLarger = i;
            if (i != 0) {
            indexLower = i-1;
            }
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

    output_file_pointer = fopen("output.txt", "w");

    while (fgets(input_read, sizeof(input_read), input_file_pointer) != 0)
    {
        cylinder_request_value = atoi(input_read);
        requestsArray[index] = cylinder_request_value;
        index++;
    }

    fcfs();
    sortArray();
    scan();
    cscan();

    return 0;
}