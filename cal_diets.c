//
//  cal_diets.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// Diets list 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

     // ToCode: to read a list of the diets from the given file
    while (fscanf(file, "%s %d", diet_list[diet_list_size].food_name, &diet_list[diet_list_size].calories_intake) == 2) {
    	diet_list_size++;
    	
        if (diet_list_size >= MAX_DIETS){
        	break;
		}
    }
    fclose(file);
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice;
    int intake = 0;
    int diet_index;
    
    //limit to 3 meals a day for healthy calorie intake.
    if (health_data->diet_count >= 3) {
    	printf("You can only intake up to 3 meals today.");
    	return;
    }
    
    // ToCode: to provide the options for the diets to be selected
    printf("The list of diets:\n");
    for (diet_index = 0; diet_index < diet_list_size; diet_index++) {
        printf("%d. %s\n", diet_index + 1, diet_list[diet_index].food_name);
    }
    
	// ToCode: to enter the diet to be chosen with exit option
    printf("Enter the number of the food you want to intake: ");
    scanf("%d", &choice);
    
    if (choice < 1 || choice > diet_list_size) {
        printf("Invalid choice. Please try again.\n");
        return;
    }

    // ToCode: to enter the selected diet in the health data
    printf("Enter the number of intake: ");
    scanf("%d", &intake);
    
    // Calculate total calories intaken
    int total_calories_intake = diet_list[choice - 1].calories_intake * intake;
    
    // ToCode: to enter the total calories intake in the health data
    strncpy(health_data->diet[health_data->diet_count].food_name, diet_list[choice - 1].food_name, MAX_FOOD_NAME_LEN - 1);
    health_data->diet[health_data->diet_count].calories_intake = total_calories_intake;
    health_data->diet_count++;
    health_data->total_calories_intake += total_calories_intake;
    
    printf("You have intaken %d calories by eating %s (%d intake).\n", total_calories_intake, diet_list[choice - 1].food_name, intake);
}