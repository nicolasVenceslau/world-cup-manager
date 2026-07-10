#ifndef MATCHES_H
#define MATCHES_H

#include "manager.h"

typedef struct {
    int teamId;
    int listIndex;
    int points;
    int goalsFor;
    int goalsAgainst;
    int goalDifference;
} GroupTable;

void simulateMatch(Team *teamList, int totalTeams, Player *playerList, int totalPlayers, int myTeamId);

void simulateWorldCup(Team *teamList, int totalTeams, Player *playerList, int totalPlayers, int userTeamId);

void calculateGoalsByStrength(int strength1, int strength2, int *goals1, int *goals2);

void viewTopScorers(Player *playerList, int totalPlayers, Team *teamList, int totalTeams);

void showWorldCupStandings(GroupTable tables[8][4], Team *teamList, int userTeamId);

void resetTournamentStats(Player *playerList, int totalPlayers);

int chooseScorer(Player *players[], int count);

int chooseAssist(Player *players[], int count, int scorerId);

#endif