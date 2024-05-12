#define _CRT_SECURE_NO_WARNINGS

#include "structs.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assumption that system has only one admin
#define ADMIN_LOGIN "admin"
#define ADMIN_PASSWORD "admin"

#define ADMIN 1
#define TUTOR 2
#define STUDENT 3

int main() {
	// Declaring variables that may be used later in code for condition statmenst or as functions attributes 
	int shouldExit = 0;
	char line[256];
	int userType = 0;
	char userLogin[256];
	char userPassword[256];
	Student currentStudent;
	Tutor currentTutor;

	printf("Welcome to the APU Programming Cafe!\n");
	// Only when user has decided to exit the programm, it will stop running 
	while (!shouldExit) {

		printf("Choose your user type:\n");
		printf("0. Exit\n");
		printf("1. Admin\n");
		printf("2. Student\n");
		printf("3. Tutor\n");
		
		fgets(line, sizeof(line), stdin);
		sscanf(line, "%d", &userType);

		switch (userType) {
		case 0:
			shouldExit = 1;
			break;
		case 1:
			printf("Admin login: ");
			fgets(line, sizeof(line), stdin);
			sscanf(line, "%s", &userLogin);

			printf("Admin password: ");
			fgets(line, sizeof(line), stdin);
			sscanf(line, "%s", &userPassword);

			// If valid credentials
			if ((strcmp(userLogin, ADMIN_LOGIN) == 0) && (strcmp(userPassword, ADMIN_PASSWORD) == 0)) {
				printf("Correct admin credentials!\n");
				adminMenu();
			}
			else {
				printf("Wrong admin credentials!\n");
			}

			break;
		case 2:
			if (loginStudent(&currentStudent) == 1) {
				studentMenu(&currentStudent);
			}

			break;
		case 3:
			if (loginTutor(&currentTutor) == 1) {
				tutorMenu(&currentTutor);
			}

			break;
		default:
			printf("Invalid credentials!\n");
			break;
		}
	}

	return 0;
}