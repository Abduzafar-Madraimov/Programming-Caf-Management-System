#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

// Function' Prototypes
void appendStudent(Student* studentPtr);
void displayAllStudents(void);
void updateStudent(Student* studentPtr, int index);

void appendTutor(Tutor* tutorPtr);
void displayAllTutors(void);

void appendSession(Sessions* sessionPtr);
void displayAllSessions(void);

void displayAllSessionsAndParticipants(void);

void displayTutorAssignedSessions(Tutor* tutorPtr);

void displayStudentAssignedSessions(Student* studentPtr);

int getStructCountInFile(const char* filename, int sizeOfStruct);

void removeNewline(char* str);
void printSession(Sessions* sessionPtr);
void enrollStudent(void);


// Defining adminMenu 
void adminMenu() {
	char line[256];
	int userCommand = 0;
	int shouldExit = 0;

	while (!shouldExit) {
		printf("Admin Mode: \n"); 
		printf("1. Display all students\n");
		printf("2. Display all tutors\n");
		printf("3. Display all sessions with participants\n");
		printf("4. Register a new student\n");
		printf("5. Register a new tutor\n");
		printf("6. Create a new session\n");
		printf("7. Enroll student to a session\n");
		printf("0. Exit\n");

		fgets(line, sizeof(line), stdin);
		sscanf(line, "%d", &userCommand);

		switch (userCommand) {
		case 0:
			printf("Exiting\n");
			shouldExit = 1;
			break;
		case 1:
			displayAllStudents();
			break;
		case 2:
			displayAllTutors();
			break;
		case 3:
			displayAllSessionsAndParticipants();
			break;
		case 4:
			// Initializing with sessions empty
			Student newStudent = { .sessions[0] = '\0', .sessions[1] = '\0', .sessions[2] = '\0' }; 

			printf("Enter name: ");
			fgets(newStudent.name, sizeof(newStudent.name), stdin);
			removeNewline(newStudent.name);

			printf("Enter tp: ");
			fgets(line, sizeof(line), stdin);
			sscanf(line, "%s", newStudent.tp);

			printf("Enter password: ");
			fgets(line, sizeof(line), stdin);
			sscanf(line, "%s", newStudent.password);

			printf("Student was successfully added!");
			appendStudent(&newStudent);

			break;
		case 5:
			// Initializing with sessions empty
			Tutor newTutor = { .sessionCode[0] = '\0'}; 

			printf("Enter name: ");
			fgets(newTutor.name, sizeof(newTutor.name), stdin);
			removeNewline(newTutor.name);

			printf("Enter title: ");
			fgets(newTutor.title, sizeof(newTutor.title), stdin);
			removeNewline(newTutor.title);

			printf("Enter tutor code: ");
			fgets(line, sizeof(line), stdin);
			sscanf(line, "%s", newTutor.tutorCode);

			printf("Enter password: ");
			fgets(line, sizeof(line), stdin);
			sscanf(line, "%s", newTutor.password);

			printf("Tutor was successfully added!");
			appendTutor(&newTutor);
			break;
		case 6:
			Sessions newSession = { .tutorCode[0] = '\0' };

			printf("Enter session code: ");
			fgets(line, sizeof(line), stdin);
			sscanf(line, "%s", newSession.sessionCode);

			printf("Enter title: ");
			fgets(newSession.title, sizeof(newSession.title), stdin);
			removeNewline(newSession.title);

			printf("Enter day: ");
			fgets(line, sizeof(line), stdin);
			sscanf(line, "%s", newSession.day);

			printf("Enter time: ");
			fgets(line, sizeof(line), stdin);
			sscanf(line, "%s", newSession.time);

			printf("Enter location: ");
			fgets(line, sizeof(line), stdin);
			sscanf(line, "%s", newSession.location);

			break;
		case 7:
			enrollStudent();
			break;
		default:
			printf("Choose something from the list!\n");
			break;
		}
	}
	return;
}

int loginStudent(Student* studentPtr) {
	char line[256];
	char inputLogin[32];
	char inputPassword[32];

	printf("Enter your login: ");
	fgets(line, sizeof(line), stdin);
	sscanf(line, "%s", &inputLogin);

	printf("Enter your password: ");
	fgets(line, sizeof(line), stdin);
	sscanf(line, "%s", &inputPassword); 

	Student tempStudent;

	FILE* file = fopen("students.dat", "r+b");

	int structCount = getStructCountInFile("students.dat", sizeof(Student));

	for (int i = 0; i < structCount; i++) {
		fread(&tempStudent, sizeof(Student), 1, file); 
		if ((strcmp(tempStudent.tp, inputLogin) == 0) && (strcmp(tempStudent.password, inputPassword) == 0)) {
			memcpy(studentPtr, &tempStudent, sizeof(Student));
			return 1;
		}
	}
	printf("Student with such login and password is not found!\n");
	return 0;
}

void studentMenu(Student* currentStudentPtr) {
	char line[256];
	int userCommand = 0;
	int shouldExit = 0;

	while (!shouldExit) {
		printf("Student Mode: \n"); //
		printf("1. Display all sessions\n");
		printf("2. Display assigned session\n");
		printf("0. Exit\n");

		fgets(line, sizeof(line), stdin);
		sscanf(line, "%d", &userCommand);

		switch (userCommand) {
		case 0:
			printf("Exiting\n");
			shouldExit = 1;

			break;
		case 1:
			displayAllSessions();

			break;
		case 2:
			displayStudentAssignedSessions(currentStudentPtr);

			break;
		}
	}
}

void printStudent(Student* studentPtr) {
	printf("%s %s %s %s %s %s\n", studentPtr->tp, studentPtr->password, studentPtr->name, studentPtr->sessions[0], studentPtr->sessions[1], studentPtr->sessions[2]);
	return;
}

void appendStudent(Student* studentPtr) {
	FILE* file = fopen("students.dat", "a+b");
	fwrite(studentPtr, sizeof(Student), 1, file);
	fclose(file);
	return;
}


void updateStudent(Student* studentPtr, int index) {
	FILE* file = fopen("students.dat", "r+b");
	fseek(file, sizeof(Student) * index, SEEK_SET);
	fwrite(studentPtr, sizeof(Student), 1, file);
	fclose(file);
	return;
}


void enrollStudent(void) {
	int studentFound = 0;
	int sessionFound = 0;
	char line[256];
	Student tempStudent;
	int studentIndex = 0;
	Sessions tempSession;
	char inputTp[32];
	char inputSessionCode[32];
	
	displayAllStudents();
	printf("Choose TP of the student that you want to enroll\n");
	fgets(line, sizeof(line), stdin);
	sscanf(line, "%s", inputTp);

	FILE* studentFilePtr = fopen("students.dat", "r+b");

	while (fread(&tempStudent, sizeof(tempStudent), 1, studentFilePtr) > 0) {
		if (strcmp(tempStudent.tp, inputTp) == 0) {
			studentFound = 1;
			displayAllSessions();

			printf("Enter session code to enroll student: \n");
			fgets(line, sizeof(line), stdin);
			sscanf(line, "%s", inputSessionCode);

			FILE* sessionFilePtr = fopen("sessions.dat", "r+b");
			while (fread(&tempSession, sizeof(tempSession), 1, sessionFilePtr) > 0) {
				if (strcmp(tempSession.sessionCode, inputSessionCode) == 0) {
					sessionFound = 1;
					
					if (tempStudent.sessions[0][0] == '\0') {  
						strcpy(tempStudent.sessions[0], inputSessionCode);
						updateStudent(&tempStudent, studentIndex);
						break;
					}
					else if (tempStudent.sessions[1][0] == '\0') { 
						strcpy(tempStudent.sessions[1], inputSessionCode);
						updateStudent(&tempStudent, studentIndex);
						break;
					}
					else if (tempStudent.sessions[2][0] == '\0') { 
						strcpy(tempStudent.sessions[2], inputSessionCode);
						updateStudent(&tempStudent, studentIndex);
						break;
					}
					else { 
						printf("Student already has 3 sessions");
						return;
					}
				}
			}
			printf("Successfully enrolled\n");
		}
		studentIndex++;
	}
}

void displayAllStudents(void) {
	Student tempStudent;
	FILE* file = fopen("students.dat", "r+b");
	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	rewind(file);
	// If file is not empty
	if (fileSize != 0){ 
		for (int i = 0; i < getStructCountInFile("students.dat", sizeof(Student)); i++) {
			fread(&tempStudent, sizeof(Student), 1, file);
			printStudent(&tempStudent);
		}
	}
	else {
		printf("Student' records are empty.\n");
	}
	return;
}


void displayStudentAssignedSessions(Student* studentPtr) {
	Sessions tempSession;
	FILE* file = fopen("sessions.dat", "r+b");
	fseek(file, 0, SEEK_END);
	int count = ftell(file) / sizeof(Sessions);
	rewind(file);
	for (int i = 0; i < count; i++) {
		fread(&tempSession, sizeof(Sessions), 1, file);
		for(int i = 0; i < 3; i++){
			if (strcmp(studentPtr->sessions[i], tempSession.sessionCode) == 0) {
				printSession(&tempSession);
			}
		}
	}
	return;
}

void printTutor(Tutor* tutorPtr) {
	printf("%s %s %s %s %s\n", tutorPtr->tutorCode, tutorPtr->name, tutorPtr->title, tutorPtr->sessionCode, tutorPtr->password);
	return;
}

void appendTutor(Tutor* tutorPtr) {
	FILE* file = fopen("tutors.dat", "a+b");
	fwrite(tutorPtr, sizeof(Tutor), 1, file);
	fclose(file);
	return;
}

void displayAllTutors(void) {
	Tutor tempTutor;
	FILE* file = fopen("tutors.dat", "r+b");
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	rewind(file);
	if (fileSize != 0) {
		printf("%s %s %s %s %s\n", "Tutor Code", "Name", "Title", "Session Code", "Password\n");
		for (int i = 0; i < getStructCountInFile("tutors.dat", sizeof(Tutor)); i++) {
			fread(&tempTutor, sizeof(Tutor), 1, file);
			printTutor(&tempTutor);
		}
	}
	else {
		printf("Tutor' records are empty.\n");
	}
	return;
}

void displayTutorAssignedSessions(Tutor* tutorPtr) {
	Sessions tempSession;
	FILE* file = fopen("sessions.dat", "r+b");
	fseek(file,0, SEEK_END);
	int count = ftell(file) / sizeof(Sessions);
	rewind(file);
	for (int i = 0; i < count; i++) {
		fread(&tempSession, sizeof(Sessions), 1, file);
		if (strcmp(tutorPtr->tutorCode, tempSession.tutorCode) == 0) {
			printSession(&tempSession);
		}
	}
	return;
}


void printSession(Sessions* sessionPtr) {
	printf("%s %s %s %s %s %s\n", sessionPtr->sessionCode, sessionPtr->title, sessionPtr->day, sessionPtr->time, sessionPtr->location, sessionPtr->tutorCode);
	return;
}

void appendSession(Sessions* sessionPtr) {
	FILE* file = fopen("sessions.dat", "a+b");
	fwrite(sessionPtr, sizeof(Sessions), 1, file);
	fclose(file);
	return;
}

void displayAllSessions(void) {
	Sessions tempSession;
	FILE* file = fopen("sessions.dat", "r+b");

	for (int i = 0; i < getStructCountInFile("sessions.dat", sizeof(Sessions)); i++) {
		fread(&tempSession, sizeof(Sessions), 1, file);
		printSession(&tempSession);
	}
	return;
}

void displayAllSessionsAndParticipants(void) {
	Sessions tempSession;
	FILE* sessionFilePtr = fopen("sessions.dat", "r+b");
	for (int i = 0; i < getStructCountInFile("sessions.dat", sizeof(Sessions)); i++) {
		fread(&tempSession, sizeof(Sessions), 1, sessionFilePtr);
		printSession(&tempSession);
		Student tempStudent;
		FILE* studentFilePtr = fopen("students.dat", "r+b");
		int numStudents = getStructCountInFile("students.dat", sizeof(Student));
		for (int i = 0; i < numStudents; i++) {
			fread(&tempStudent, sizeof(Student), 1, studentFilePtr);
			if ( (strcmp(tempStudent.sessions[0], tempSession.sessionCode) == 0) || (strcmp(tempStudent.sessions[1], tempSession.sessionCode) == 0) || (strcmp(tempStudent.sessions[2], tempSession.sessionCode) == 0) ){
				printf("%s %s\n", tempStudent.tp, tempStudent.name);
			}
		}
	}
}

int loginTutor(Tutor* tutorPtr) {
	char line[256];
	char inputLogin[32];
	char inputPassword[32];

	printf("Enter your login: ");
	fgets(line, sizeof(line), stdin);
	sscanf(line, "%s", &inputLogin);

	printf("Enter your password: ");
	fgets(line, sizeof(line), stdin);
	sscanf(line, "%s", &inputPassword);

	Tutor tempTutor;

	FILE* file = fopen("tutors.dat", "r+b");

	int structCount = getStructCountInFile("tutors.dat", sizeof(Tutor));

	for (int i = 0; i < structCount; i++) {
		fread(&tempTutor, sizeof(Tutor), 1, file);
		if ((strcmp(tempTutor.tutorCode, inputLogin) == 0) && (strcmp(tempTutor.password, inputPassword) == 0)) {
			memcpy(tutorPtr, &tempTutor, sizeof(Tutor));
			return 1;
		}
	}
	printf("Tutor with such login and password is not found!\n");
	return 0;
}

void tutorMenu(Tutor* currentTutorPtr) {
	char line[256];
	int userCommand = 0;
	int shouldExit = 0;

	while (!shouldExit) {
		printf("Tutor Mode: \n"); //
		printf("1. Display all sessions\n");
		printf("2. Display assigned session\n");
		printf("0. Exit\n");

		fgets(line, sizeof(line), stdin);
		sscanf(line, "%d", &userCommand);

		switch (userCommand) {
		case 0:
			printf("Exiting\n");
			shouldExit = 1;
			
			break;
		case 1:
			displayAllSessions();
			
			break;
		case 2:
			displayTutorAssignedSessions(currentTutorPtr);

			break;
		}
	}
}

// Defining removeNewline function to use it for formating later
void removeNewline(char* str) {
	char* ch = str;
	while (1) {
		if (*ch == '\n') {
			*ch = '\0';
			break;
		}
		else {
			ch++;
		}
	}
	return;
}

// Defining getStructCountInFile to count amount of structs in a file 
int getStructCountInFile(const char* filename, int sizeOfStruct) {
	FILE* file = fopen(filename, "r+b");
	fseek(file, 0, SEEK_END);
	// Divide file memory size by struct memory size
	int structCount = ftell(file) / sizeOfStruct; 
	fclose(file);
	return structCount;
}
