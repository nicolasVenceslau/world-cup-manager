#ifndef MANAGER_H
#define MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"

typedef struct {
    char username[50];
    char password[50];
    int isAdmin;
    int teamId;
    char coachName[50];
    char nationality[50];
} User;

typedef struct {
    int id;
    char name[50];
    int overallStrength;
    int gamesWon;
    int gamesDrawn;
    int gamesLost;
    int cupsWon;
} Team;

typedef struct {
    int id;
    int teamId;
    int originalTeamId;
    char name[50];
    int age;
    char position[20];
    int overall;
    int goals;
    int totalGoals;
    int assists;
    int totalAssists;
    int gamesPlayed;
    int isStarter;
} Player;

void clearBuffer();
void readValidField(char *destination, int size, const char *prompt, int minLen);
void showBanner();
int checkSession(User *loggedUser);
void saveSession(const char *username);
void endSession();
void updateUserInDatabase(User *u);
int usernameExists(const char *username);
int initialMenu(User *loggedUser);
int registerUser(User *loggedUser);
int doLogin(User *loggedUser);
void initializeDefaultData();
void loadTeams(Team *list, int *total);
void loadPlayers(Player *list, int *total);
void listPlayersFromTeam(Player *playerList, int totalPlayers, int teamId);
void chooseTeam(User *coach, Team *list, int total);
void listTeams(Team *list, int total);
void createTeam(Team *list, int *total);
void editTeam(Team *list, int total);
void saveTeams(Team *list, int total);
void savePlayers(Player *list, int total);
void sortPlayers(Player *list, int total, int criterion);
void showTeamStatistics(Team *list, int total);
void setStarters(Player *playerList, int totalPlayers, int teamId);
void editPlayer(Player *playerList, int totalPlayers, Team *teamList, int totalTeams);
void createPlayer(Player *playerList, int *totalPlayers, Team *teamList, int totalTeams);
int deleteTeam(Team *list, int *total, Player *playerList, int *totalPlayers, int teamId);
int deletePlayer(Player *playerList, int *totalPlayers, int playerId);

#endif