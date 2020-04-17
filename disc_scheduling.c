  
/*
  Disk Scheduling Algorithms: FCFS, SCAN, C-SCSAN
*/

#include <stdio.h>
#include <stdlib.h>

#define HEADPOSITION 33

int requestsArray[25];

FILE *input_file_pointer;
FILE *output_file_pointer;

void fcfs(int * rArray) {
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

    fcfs(requestsArray);

    // printf("FCFS head movements: %d\n", fcfs(ran_array));
	// printf("SCAN head movements: %d\n", scan(ran_array));
	// printf("CSCAN head movements: %d\n", cscan(ran_array));

    return 0;
}