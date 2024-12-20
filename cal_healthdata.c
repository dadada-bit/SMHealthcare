//
//  cal_healthdata.c
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


/*
    description : enter the exercise and diet history in "health_data.txt" 
    input parameters : health_data - data object in which the selected exercise and diet is stored
    return value : No
    
    operation : 1. save the chosen exercise and total calories burned 
    			2. save the chosen diet and total calories intake 
    			3. save the total remaining calrories
*/

void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
	int exercise_index;
	int diet_index;
	int remaining_calories;
	
    FILE* file = fopen(HEALTHFILEPATH, "w");
    //If opening the file fails, print an error message and exit the function
    if (file == NULL) {
        printf("There is no file for health data.\n"); //Error message when the file cannot be opened
        return;
    }

    // ToCode: to save the chosen exercise and total calories burned 
    fprintf(file, "[Exercises] \n");
    for (exercise_index = 0; exercise_index < health_data->exercise_count; exercise_index++) {
        // Print the name of the exercise and its calories burned
		fprintf(file, "%s- %d kcal \n", health_data->exercises[exercise_index].exercise_name, health_data->exercises[exercise_index].calories_burned_per_minute);
    }
    fprintf(file, "Total calories burned: %d kcal\n", health_data->total_calories_burned); 
    
    
    // ToCode: to save the chosen diet and total calories intake 
	fprintf(file, "\n[Diets] \n");
    for (diet_index = 0; diet_index < health_data->diet_count; diet_index++) {
        // Print the food name and its calories intake
		fprintf(file, "%s- %d kcal \n", health_data->diet[diet_index].food_name, health_data->diet[diet_index].calories_intake);
    }
    fprintf(file, "Total calories intake: %d kcal\n", health_data->total_calories_intake);


    // ToCode: to save the total remaining calrories
    remaining_calories = (health_data->total_calories_intake - health_data->total_calories_burned - BASAL_METABOLIC_RATE);
   
    fprintf(file, "\n[Total] \n");
    fprintf(file, "Basal metabolic rate - %d kcal\n", BASAL_METABOLIC_RATE);
    fprintf(file, "The remaining calories: %d kcal\n", remaining_calories);
    
    fclose(file); // Close the file after writing the data
} 

/*
    description : print the history of exercised and diets
    input parameters : health_data - data object in which the history of the exercise and diet is to be printed
    return value : No
    
    operation : 1. print out the saved history of exercises
    			2. print out the saved history of diets
    			3. print out the saved history of calories
*/

void printHealthData(const HealthData* health_data) {
	int exercise_index;
	int diet_index;
	int remaining_calories = health_data->total_calories_intake - health_data->total_calories_burned - BASAL_METABOLIC_RATE;
	
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
	if (health_data->exercise_count == 0) {
		printf("No exercise data print available.\n");
		} else {
			for (exercise_index = 0; exercise_index < health_data->exercise_count; exercise_index++) {
                // Print each exercise's name and the calories burned per minute
				printf("Exercise: %s kcal, Calories burned per minute: %d kcal\n", health_data->exercises[exercise_index].exercise_name, health_data->exercises[exercise_index].calories_burned_per_minute);
					   }
				}
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    printf("============================= History of Diet =========================\n");
    if (health_data->diet_count == 0) {
    	printf("No diet data available.\n");
    	} else {
		for (diet_index = 0; diet_index < health_data->diet_count; diet_index++) {
            // Print each food item's name and its calories intake
			printf("Food: %s kcal, Calories intake: %d kcal\n", health_data->diet[diet_index].food_name, health_data->diet[diet_index].calories_intake);
              }
        }
    printf("=======================================================================\n");

	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	printf("============================== Total Calories =========================\n");
	printf("Basal metabolic rate: %d kcal\n", BASAL_METABOLIC_RATE);
    printf("Total calories burned: %d kcal\n", health_data->total_calories_burned);
    printf("Total calories intake: %d kcal\n", health_data->total_calories_intake);
    printf("Remaining calories: %d kcal\n", remaining_calories);
    printf("=======================================================================\n \n"); 
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
	if (remaining_calories == 0) {		
        printf("You have consumed all your calories for today!\n");
    } else if (remaining_calories < 0) { 	
        printf("[Warning] Too few calories!\n");
        if (health_data->total_calories_intake == DAILY_CALORIE_GOAL) {
            printf("Your total calorie intake for today has reached your goal!\n");
        } else if (health_data->total_calories_intake < DAILY_CALORIE_GOAL) {
            printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n");
        } else {
            printf("You have eaten more calories than planned today, but you have exercised too much!\n");
    }   
    } else {
        printf("Please exercise for your health!\n");
        if (health_data->total_calories_intake == DAILY_CALORIE_GOAL) {
            printf("Your total calorie intake for today has reached your goal!\n");
        } else if (health_data->total_calories_intake < DAILY_CALORIE_GOAL) {
            printf("Your total calorie intake for today has not reached your goal, remember to eat more!!\n");
        }
    }
    printf("=======================================================================\n");
}