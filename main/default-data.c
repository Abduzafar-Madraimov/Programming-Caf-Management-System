#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "structs.h"

int main() {

	Sessions session1 = {"PYP101", "Python Programming", "Saturday", "9.00am", "C - 01 - 01", "T01" };
	Sessions session2 = {"JAV102", "Java Programming", "Sunday", "9.00am", "C-01-02", "T02" };
	Sessions session3 = {"CPL103", "C Programming", "Saturday", "2.00pm", "C-01-03", "T03" };
	Sessions session4 = {"WEB104", "Web Development", "Sunday", "2.00pm", "C-01-04", "T04"};
	Sessions session5 = {"CSP105", "C Sharp Programming", "Monday", "7.00pm", "C-01-05", "T05"};
	appendSession(&session1);
	appendSession(&session2);
	appendSession(&session3);
	appendSession(&session4);
	appendSession(&session5);

	Tutor tutor1 = {"T01","T1", "Albert", "Python Programming"};
	Tutor tutor2 = {"T02","T2", "Amad", "Java Programming"};
	Tutor tutor3 = {"T03","T3", "Steve", "C Programming"};
	appendTutor(&tutor1);
	appendTutor(&tutor2);
	appendTutor(&tutor3);

	Student student1 = { "TP123456", "S1", "Arina" };
	strcpy(student1.sessions[0], "PYP101");
	strcpy(student1.sessions[1], "JAV101");
	strcpy(student1.sessions[2], "CPL103");

	appendStudent(&student1);



	return 0;
}