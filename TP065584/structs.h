#pragma once
//Store a Programming Cafe Sessions
typedef struct {
    char sessionCode[8];
    char title[50];
    char day[16];
    char time[16];
    char location[16];
    char tutorCode[8];
} Sessions;


//Store student info
typedef struct {
    // Student card (tp card)
    char tp[32];
    char password[32];
    char name[50];
    char sessions[3][8];
} Student;

//Store tutor info
typedef struct {
    char tutorCode[32];
    char password[32];
    char name[50];
    char title[50];
    char sessionCode[8];
} Tutor;

