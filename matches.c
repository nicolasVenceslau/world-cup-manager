#include "matches.h"

void calculateGoalsByStrength(int strength1, int strength2, int *goal1, int *goal2) {
    int diff = strength1 - strength2;

    int avgGoal1 = 14 + (diff * 5) / 10;
    int avgGoal2 = 14 - (diff * 5) / 10;

    if (avgGoal1 < 4) avgGoal1 = 4;
    if (avgGoal1 > 32) avgGoal1 = 32;
    if (avgGoal2 < 4) avgGoal2 = 4;
    if (avgGoal2 > 32) avgGoal2 = 32;

    int noise1 = (rand() % 25) - 12;
    int noise2 = (rand() % 25) - 12;

    int goals1 = (avgGoal1 + noise1) / 10;
    int goals2 = (avgGoal2 + noise2) / 10;

    if (goals1 < 0) goals1 = 0;
    if (goals2 < 0) goals2 = 0;

    *goal1 = goals1;
    *goal2 = goals2;
}

int chooseScorer(Player *players[], int qty) {
    if (qty <= 0) return 0;

    int weights[50];
    int totalWeights = 0;

    for (int i = 0; i < qty; i++) {
        int baseWeight = 0;

        if (strcmp(players[i]->position, "ATA") == 0) baseWeight = 10;
        else if (strcmp(players[i]->position, "MED") == 0) baseWeight = 4;
        else if (strcmp(players[i]->position, "DEF") == 0) baseWeight = 1;
        else if (strcmp(players[i]->position, "GK") == 0) baseWeight = 0;
        else baseWeight = 2;

        weights[i] = baseWeight * players[i]->overall;

        totalWeights += weights[i];
    }

    if (totalWeights == 0) return rand() % qty;

    int draw = rand() % totalWeights;
    int sum = 0;

    for (int i = 0; i < qty; i++) {
        sum += weights[i];
        if (draw < sum) {
            return i;
        }
    }

    return 0;
}

int chooseAssister(Player *players[], int qty, int scorerIdx) {

    if (rand() % 100 < 30) return -1;
    if (qty <= 1) return -1;

    int weights[50];
    int totalWeights = 0;

    for (int i = 0; i < qty; i++) {
        if (i == scorerIdx) { weights[i] = 0; continue; }
        if (strcmp(players[i]->position, "MED") == 0)      weights[i] = 8;
        else if (strcmp(players[i]->position, "ATA") == 0) weights[i] = 5;
        else if (strcmp(players[i]->position, "DEF") == 0) weights[i] = 2;
        else if (strcmp(players[i]->position, "GK") == 0) weights[i] = 0;
        else weights[i] = 3;
        totalWeights += weights[i];
    }

    if (totalWeights == 0) return -1;

    int draw = rand() % totalWeights;
    int sum = 0;
    for (int i = 0; i < qty; i++) {
        sum += weights[i];
        if (draw < sum) return i;
    }
    return -1;
}

void showWorldCupStandings(GroupTable tables[8][4], Team *teamList, int userTeamId) {
    printf(CYAN "\n==================================================\n" RESET);
    printf(CYAN "              CURRENT GROUP STANDINGS             \n" RESET);
    printf(CYAN "==================================================\n" RESET);

    for (int g = 0; g < 8; g++) {
        GroupTable groupCopy[4];
        for (int i = 0; i < 4; i++) {
            groupCopy[i] = tables[g][i];
        }

        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 4; j++) {
                int needsSwap = 0;
                if (groupCopy[j].points > groupCopy[i].points) needsSwap = 1;
                else if (groupCopy[j].points == groupCopy[i].points) {
                    if (groupCopy[j].goalDifference > groupCopy[i].goalDifference) needsSwap = 1;
                    else if (groupCopy[j].goalDifference == groupCopy[i].goalDifference && groupCopy[j].goalsFor > groupCopy[i].goalsFor) needsSwap = 1;
                }

                if (needsSwap) {
                    GroupTable temp = groupCopy[i];
                    groupCopy[i] = groupCopy[j];
                    groupCopy[j] = temp;
                }
            }
        }

        printf(BLUE "\n--- GROUP %c ---\n" RESET, 'A' + g);
        printf(BOLD "Pos | Team                | Pts | GF | GA | GD\n" RESET);
        for (int t = 0; t < 4; t++) {
            Team team = teamList[groupCopy[t].listIndex];

            if (t < 2) printf(GREEN); else printf(RED);
            if (team.id == userTeamId) printf("-> "); else printf("   ");

            printf("%d | %-19s | %3d | %2d | %2d | %2d\n" RESET,
                t + 1, team.name, groupCopy[t].points, groupCopy[t].goalsFor, groupCopy[t].goalsAgainst, groupCopy[t].goalDifference);
        }
        printf("------------------------------------------------\n");
    }
}

void viewTopScorers(Player *playerList, int totalPlayers, Team *teamList, int totalTeams) {
    printf(CYAN "\n==================================================\n" RESET);
    printf(CYAN "             TOP 30 WORLD CUP SCORERS              \n" RESET);
    printf(CYAN "==================================================\n" RESET);

    Player *scorers[100];
    int scorerCount = 0;

    for (int i = 0; i < totalPlayers; i++) {
        if (playerList[i].goals > 0) {
            if (scorerCount < 100) {
                scorers[scorerCount++] = &playerList[i];
            } else {
                break;
            }
        }
    }

    if (scorerCount == 0) {
        printf(YELLOW "\nNo goals have been scored in the tournament yet!\n" RESET);
        printf("--------------------------------------------------\n");
        return;
    }

    for (int i = 0; i < scorerCount - 1; i++) {
        for (int j = i + 1; j < scorerCount; j++) {
            if (scorers[j]->goals > scorers[i]->goals) {
                Player *temp = scorers[i];
                scorers[i] = scorers[j];
                scorers[j] = temp;
            }
        }
    }

    printf(BOLD "%-4s | %-20s | %-15s | %-5s \n" RESET, "Pos", "Player", "Team", "Goals");
    printf("--------------------------------------------------\n");

    int displayLimit;
    if (scorerCount > 30)
        displayLimit = 30;
    else
        displayLimit = scorerCount;

    for (int i = 0; i < displayLimit; i++) {
        char teamName[50] = "Unknown";
        int searchTeamId;
        if (scorers[i]->teamId != 0)
            searchTeamId = scorers[i]->teamId;
        else
            searchTeamId = scorers[i]->originalTeamId;
        for (int s = 0; s < totalTeams; s++) {
            if (teamList[s].id == searchTeamId) {
                strcpy(teamName, teamList[s].name);
                break;
            }
        }

        if (i == 0) printf(GREEN);
        else if (i < 3) printf(YELLOW);
        else printf(RESET);

        printf("%-4d | %-20s | %-15s | %-5d\n" RESET,
               i + 1, scorers[i]->name, teamName, scorers[i]->goals);
    }
    printf("--------------------------------------------------\n");
}

void resetTournamentStats(Player *playerList, int totalPlayers) {
    for (int i = 0; i < totalPlayers; i++) {
        playerList[i].goals = 0;
        playerList[i].assists = 0;

    }
}

void viewTopAssisters(Player *playerList, int totalPlayers, Team *teamList, int totalTeams) {
    printf(CYAN "\n==================================================\n" RESET);
    printf(CYAN "            TOP 30 WORLD CUP ASSISTERS             \n" RESET);
    printf(CYAN "==================================================\n" RESET);

    Player *assisters[100];
    int assisterCount = 0;

    for (int i = 0; i < totalPlayers; i++) {
        if (playerList[i].assists > 0) {
            if (assisterCount < 100) {
                assisters[assisterCount++] = &playerList[i];
            } else {
                break;
            }
        }
    }

    if (assisterCount == 0) {
        printf(YELLOW "\nNo assists have been recorded in the tournament yet!\n" RESET);
        printf("--------------------------------------------------\n");
        return;
    }

    for (int i = 0; i < assisterCount - 1; i++) {
        for (int j = i + 1; j < assisterCount; j++) {
            if (assisters[j]->assists > assisters[i]->assists) {
                Player *temp = assisters[i];
                assisters[i] = assisters[j];
                assisters[j] = temp;
            }
        }
    }

    printf(BOLD "%-4s | %-20s | %-15s | %-5s \n" RESET, "Pos", "Player", "Team", "Assists");
    printf("--------------------------------------------------\n");

    int displayLimit;
    if (assisterCount > 30)
        displayLimit = 30;
    else
        displayLimit = assisterCount;

    for (int i = 0; i < displayLimit; i++) {
        char teamName[50] = "Unknown";
        int searchTeamId;
        if (assisters[i]->teamId != 0)
            searchTeamId = assisters[i]->teamId;
        else
            searchTeamId = assisters[i]->originalTeamId;
        for (int s = 0; s < totalTeams; s++) {
            if (teamList[s].id == searchTeamId) {
                strcpy(teamName, teamList[s].name);
                break;
            }
        }

        if (i == 0) printf(GREEN);
        else if (i < 3) printf(YELLOW);
        else printf(RESET);

        printf("%-4d | %-20s | %-15s | %-5d \n" RESET,
               i + 1, assisters[i]->name, teamName, assisters[i]->assists);
    }
    printf("--------------------------------------------------\n");
}

void simulateMatch(Team *teamList, int totalTeams, Player *playerList, int totalPlayers, int userTeamId) {
    if (totalTeams < 2) {
        printf(RED "Not enough teams to play.\n" RESET);
        return;
    }

    printf(CYAN "\n--- CHALLENGE AN OPPONENT ---\n" RESET);
    listTeams(teamList, totalTeams);
    printf(YELLOW "\nEnter the ID of the team you want to play against: " RESET);

    int opponentId;
    if (scanf("%d", &opponentId) != 1) {
        clearBuffer();
        printf(RED "Invalid option.\n" RESET);
        return;
    }
    clearBuffer();

    if (opponentId == userTeamId) {
        printf(RED "Mister, you can't play against your own team!\n" RESET);
        return;
    }

    int opponentIdx = -1;
    int userIdx = -1;
    for(int i = 0; i < totalTeams; i++) {
        if(teamList[i].id == opponentId) opponentIdx = i;
        if(teamList[i].id == userTeamId) userIdx = i;
    }

    if (opponentIdx == -1) {
        printf(RED "That team doesn't exist!\n" RESET);
        return;
    }

    Team user = teamList[userIdx];
    Team opponent = teamList[opponentIdx];

    int acceptChance = rand() % 100;
    if (acceptChance < 30) {
        printf(RED "\n[X] %s's federation rejected your friendly match invitation.\n" RESET, opponent.name);
        return;
    }

    printf(GREEN "\n[!] %s's team accepted the challenge!\n" RESET, opponent.name);

    printf(BLUE "\n--- MATCH DAY ---\n" RESET);
    printf(BOLD "%s (Strength %d)" RESET " VS " BOLD "%s (Strength %d)\n" RESET, user.name, user.overallStrength, opponent.name, opponent.overallStrength);

    int userGoals, opponentGoals;
    calculateGoalsByStrength(user.overallStrength, opponent.overallStrength, &userGoals, &opponentGoals);

    Player *userPlayers[50]; int userCount = 0;
    Player *opponentPlayers[50]; int opponentCount = 0;

    for(int i = 0; i < totalPlayers; i++) {
        if(playerList[i].teamId == userTeamId) {
            if (playerList[i].isStarter == 1) {
                userPlayers[userCount++] = &playerList[i];
                playerList[i].gamesPlayed++;
            }
        }
        else if(playerList[i].originalTeamId == opponentId) {
            opponentPlayers[opponentCount++] = &playerList[i];
            playerList[i].gamesPlayed++;
        }
    }

    if (userCount == 0) {
        for(int i = 0; i < totalPlayers; i++) {
            if(playerList[i].teamId == userTeamId) {
                userPlayers[userCount++] = &playerList[i];
                playerList[i].gamesPlayed++;
            }
        }
    }

    printf(YELLOW "\n[ MATCH EVENTS ]\n" RESET);

    for(int g = 0; g < userGoals; g++) {
        if(userCount > 0) {
            int scorerIdx = chooseScorer(userPlayers, userCount);
            int assisterIdx = chooseAssister(userPlayers, userCount, scorerIdx);
            userPlayers[scorerIdx]->goals++;
            userPlayers[scorerIdx]->totalGoals++;
            if (assisterIdx >= 0) {
                userPlayers[assisterIdx]->assists++;
                userPlayers[assisterIdx]->totalAssists++;
                printf(GREEN "⚽ GOAL BY %s! (%s) [Assist: %s]\n" RESET, userPlayers[scorerIdx]->name, user.name, userPlayers[assisterIdx]->name);
            } else {
                printf(GREEN "⚽ GOAL BY %s! (%s)\n" RESET, userPlayers[scorerIdx]->name, user.name);
            }
        } else {
            printf(GREEN "⚽ GOAL by %s! (Unknown Player)\n" RESET, user.name);
        }
    }

    for(int g = 0; g < opponentGoals; g++) {
        if(opponentCount > 0) {
            int scorerIdx = chooseScorer(opponentPlayers, opponentCount);
            int assisterIdx = chooseAssister(opponentPlayers, opponentCount, scorerIdx);
            opponentPlayers[scorerIdx]->goals++;
            opponentPlayers[scorerIdx]->totalGoals++;
            if (assisterIdx >= 0) {
                opponentPlayers[assisterIdx]->assists++;
                opponentPlayers[assisterIdx]->totalAssists++;
                printf(RED "⚽ GOAL BY %s! (%s) [Assist: %s]\n" RESET, opponentPlayers[scorerIdx]->name, opponent.name, opponentPlayers[assisterIdx]->name);
            } else {
                printf(RED "⚽ GOAL BY %s! (%s)\n" RESET, opponentPlayers[scorerIdx]->name, opponent.name);
            }
        } else {
            printf(RED "⚽ GOAL by %s! (Unknown Player)\n" RESET, opponent.name);
        }
    }

    printf(YELLOW "\n[!!!] FULL TIME [!!!]\n" RESET);
    printf("Result: " BOLD "%s %d x %d %s\n" RESET, user.name, userGoals, opponentGoals, opponent.name);

    if (userGoals > opponentGoals) {
        printf(GREEN "Great Victory, Mister!\n" RESET);
        teamList[userIdx].gamesWon++;
        teamList[opponentIdx].gamesLost++;
    }
    else if (userGoals < opponentGoals) {
        printf(RED "Defeat... The board is not happy.\n" RESET);
        teamList[userIdx].gamesLost++;
        teamList[opponentIdx].gamesWon++;
    }
    else {
        printf(YELLOW "Draw. A very tight match.\n" RESET);
        teamList[userIdx].gamesDrawn++;
        teamList[opponentIdx].gamesDrawn++;
    }
}

int playKnockoutMatch(Team *team1, Team *team2, Player *playerList, int totalPlayers,
                                   int userTeamId, const char *stageName) {
    int isUserMatch = (team1->id == userTeamId || team2->id == userTeamId);

    int goal1, goal2;
    calculateGoalsByStrength(team1->overallStrength, team2->overallStrength, &goal1, &goal2);

    Player *players1[50]; int count1 = 0;
    Player *players2[50]; int count2 = 0;

    for (int i = 0; i < totalPlayers; i++) {
        if (team1->id == userTeamId && playerList[i].teamId == team1->id) {
            if (playerList[i].isStarter == 1) { players1[count1++] = &playerList[i]; playerList[i].gamesPlayed++; }
        } else if (team1->id != userTeamId && playerList[i].originalTeamId == team1->id) {
            players1[count1++] = &playerList[i]; playerList[i].gamesPlayed++;
        } else if (team2->id == userTeamId && playerList[i].teamId == team2->id) {
            if (playerList[i].isStarter == 1) { players2[count2++] = &playerList[i]; playerList[i].gamesPlayed++; }
        } else if (team2->id != userTeamId && playerList[i].originalTeamId == team2->id) {
            players2[count2++] = &playerList[i]; playerList[i].gamesPlayed++;
        }
    }

    if (team1->id == userTeamId && count1 == 0) {
        for (int i = 0; i < totalPlayers; i++) if (playerList[i].teamId == userTeamId) { players1[count1++] = &playerList[i]; playerList[i].gamesPlayed++; }
    }
    if (team2->id == userTeamId && count2 == 0) {
        for (int i = 0; i < totalPlayers; i++) if (playerList[i].teamId == userTeamId) { players2[count2++] = &playerList[i]; playerList[i].gamesPlayed++; }
    }

    if (isUserMatch) {
        printf(BLUE "\n--- %s ---\n" RESET, stageName);
        printf(BOLD "%s (Strength %d)" RESET " VS " BOLD "%s (Strength %d)\n" RESET, team1->name, team1->overallStrength, team2->name, team2->overallStrength);
        printf(YELLOW "\n[ MATCH EVENTS ]\n" RESET);
    }

    for (int g = 0; g < goal1; g++) {
        if (count1 > 0) {
            int scorerIdx = chooseScorer(players1, count1);
            int assisterIdx = chooseAssister(players1, count1, scorerIdx);
            players1[scorerIdx]->goals++;
            players1[scorerIdx]->totalGoals++;
            if (assisterIdx >= 0) { players1[assisterIdx]->assists++; players1[assisterIdx]->totalAssists++; }
            if (isUserMatch) {
                if (assisterIdx >= 0)
                    printf(GREEN "⚽ GOAL BY %s! (%s) [Assist: %s]\n" RESET, players1[scorerIdx]->name, team1->name, players1[assisterIdx]->name);
                else
                    printf(GREEN "⚽ GOAL BY %s! (%s)\n" RESET, players1[scorerIdx]->name, team1->name);
            }
        } else if (isUserMatch) printf(GREEN "⚽ GOAL by %s! (Unknown Player)\n" RESET, team1->name);
    }

    for (int g = 0; g < goal2; g++) {
        if (count2 > 0) {
            int scorerIdx = chooseScorer(players2, count2);
            int assisterIdx = chooseAssister(players2, count2, scorerIdx);
            players2[scorerIdx]->goals++;
            players2[scorerIdx]->totalGoals++;
            if (assisterIdx >= 0) { players2[assisterIdx]->assists++; players2[assisterIdx]->totalAssists++; }
            if (isUserMatch) {
                if (assisterIdx >= 0)
                    printf(RED "⚽ GOAL BY %s! (%s) [Assist: %s]\n" RESET, players2[scorerIdx]->name, team2->name, players2[assisterIdx]->name);
                else
                    printf(RED "⚽ GOAL BY %s! (%s)\n" RESET, players2[scorerIdx]->name, team2->name);
            }
        } else if (isUserMatch) printf(RED "⚽ GOAL by %s! (Unknown Player)\n" RESET, team2->name);
    }

    int penalties1 = -1, penalties2 = -1;
    int winner;

    if (goal1 > goal2) winner = 0;
    else if (goal2 > goal1) winner = 1;
    else {

        do {
            penalties1 = 3 + rand() % 4;
            penalties2 = 3 + rand() % 4;
        } while (penalties1 == penalties2);
        if (penalties1 > penalties2)
            winner = 0;
        else
            winner = 1;
    }

    if (winner == 0) {
        team1->gamesWon++;
        team2->gamesLost++;
    } else {
        team2->gamesWon++;
        team1->gamesLost++;
    }

    if (isUserMatch) {
        printf(YELLOW "\n[!!!] FULL TIME [!!!]\n" RESET);
        printf("Result: " BOLD "%s %d x %d %s\n" RESET, team1->name, goal1, goal2, team2->name);
        if (penalties1 >= 0) {
            printf(YELLOW "It went to penalties: " BOLD "%s %d x %d %s\n" RESET, team1->name, penalties1, penalties2, team2->name);
        }
        Team *winningTeam;
        if (winner == 0)
            winningTeam = team1;
        else
            winningTeam = team2;
        if (winningTeam->id == userTeamId) printf(GREEN "Victory, Mister! The journey continues!\n" RESET);
        else printf(RED "Eliminated! The World Cup adventure ends here...\n" RESET);
        printf("\n");
    } else {
        Team *winningTeam;
        if (winner == 0)
            winningTeam = team1;
        else
            winningTeam = team2;
        if (penalties1 >= 0)
            printf("[%s] %-16s %d(%d) x (%d)%d %s -> advances: %s\n", stageName, team1->name, goal1, penalties1, penalties2, goal2, team2->name, winningTeam->name);
        else
            printf("[%s] %-16s %d x %d %s -> advances: %s\n", stageName, team1->name, goal1, goal2, team2->name, winningTeam->name);
    }

    return winner;
}

void showMatchups(Team *participants[], int totalParticipants, const char *stageName) {
    printf(BOLD "\n--- %s MATCHUPS ---\n" RESET, stageName);
    for (int i = 0; i < totalParticipants; i += 2) {
        printf("%-20s x %s\n", participants[i]->name, participants[i + 1]->name);
    }
}

void simulateKnockoutStage(Team *participants[], int totalParticipants,
                                     Team *winners[], Player *playerList, int totalPlayers,
                                     int userTeamId, const char *stageName) {
    system("cls");
    printf(CYAN "\n==================================================\n" RESET);
    printf(CYAN "  %-46s\n" RESET, stageName);
    printf(CYAN "==================================================\n" RESET);

    for (int i = 0; i < totalParticipants; i += 2) {
        Team *team1 = participants[i];
        Team *team2 = participants[i + 1];

        int result = playKnockoutMatch(team1, team2, playerList, totalPlayers, userTeamId, stageName);
        if (result == 0)
            winners[i / 2] = team1;
        else
            winners[i / 2] = team2;
    }
}

void simulateWorldCup(Team *teamList, int totalTeams, Player *playerList, int totalPlayers, int userTeamId) {
    if (totalTeams != 32) {
        printf(RED "Error: The World Cup needs exactly 32 registered teams.\n" RESET);
        return;
    }

    printf(CYAN "\n==================================================\n" RESET);
    printf(CYAN "              STARTING THE WORLD CUP              \n" RESET);
    printf(CYAN "==================================================\n\n" RESET);

    srand(time(NULL));

    int indices[32];
    for (int i = 0; i < 32; i++) indices[i] = i;

    for (int i = 31; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    int groups[8][4];
    for (int i = 0; i < 32; i++) {
        groups[i / 4][i % 4] = indices[i];
    }

    GroupTable tables[8][4];
    for (int g = 0; g < 8; g++) {
        for (int t = 0; t < 4; t++) {
            tables[g][t].teamId = teamList[groups[g][t]].id;
            tables[g][t].listIndex = groups[g][t];
            tables[g][t].points = 0;
            tables[g][t].goalsFor = 0;
            tables[g][t].goalsAgainst = 0;
            tables[g][t].goalDifference = 0;
        }
    }

    printf(YELLOW "[!] The draw has been made! Here are the groups set for the World Cup:\n" RESET);
    showWorldCupStandings(tables, teamList, userTeamId);

    int menuOption = 0;
    do {
        printf(YELLOW "\n--- TOURNAMENT PREPARATION ---\n" RESET);
        printf("1 - Review World Cup Groups\n");
        printf("2 - Start Round 1!\n");
        printf("Choose an option: ");
        if (scanf("%d", &menuOption) != 1) { clearBuffer(); menuOption = 0; }
        clearBuffer();

        if (menuOption == 1) {
            showWorldCupStandings(tables, teamList, userTeamId);
        }
    } while (menuOption != 2);

    int roundMatches[3][2][2] = {
        {{0, 1}, {2, 3}},
        {{0, 2}, {1, 3}},
        {{0, 3}, {1, 2}}
    };

    for (int r = 0; r < 3; r++) {
        system("cls");
        printf(CYAN "\n==============================================\n" RESET);
        printf(CYAN "             WORLD CUP - ROUND %d/3            \n" RESET, r + 1);
        printf(CYAN "==============================================\n" RESET);

        for (int g = 0; g < 8; g++) {
            for (int j = 0; j < 2; j++) {
                int tableIdx1 = roundMatches[r][j][0];
                int tableIdx2 = roundMatches[r][j][1];

                Team *team1 = &teamList[tables[g][tableIdx1].listIndex];
                Team *team2 = &teamList[tables[g][tableIdx2].listIndex];

                int isUserMatch = (team1->id == userTeamId || team2->id == userTeamId);

                int goal1, goal2;
                calculateGoalsByStrength(team1->overallStrength, team2->overallStrength, &goal1, &goal2);

                Player *players1[50]; int count1 = 0;
                Player *players2[50]; int count2 = 0;

                for (int i = 0; i < totalPlayers; i++) {
                    if (team1->id == userTeamId && playerList[i].teamId == team1->id) {
                        if (playerList[i].isStarter == 1) { players1[count1++] = &playerList[i]; playerList[i].gamesPlayed++; }
                    } else if (team1->id != userTeamId && playerList[i].originalTeamId == team1->id) {
                        players1[count1++] = &playerList[i]; playerList[i].gamesPlayed++;
                    } else if (team2->id == userTeamId && playerList[i].teamId == team2->id) {
                        if (playerList[i].isStarter == 1) { players2[count2++] = &playerList[i]; playerList[i].gamesPlayed++; }
                    } else if (team2->id != userTeamId && playerList[i].originalTeamId == team2->id) {
                        players2[count2++] = &playerList[i]; playerList[i].gamesPlayed++;
                    }
                }

                if (team1->id == userTeamId && count1 == 0) {
                    for (int i = 0; i < totalPlayers; i++) if (playerList[i].teamId == userTeamId) { players1[count1++] = &playerList[i]; playerList[i].gamesPlayed++; }
                }
                if (team2->id == userTeamId && count2 == 0) {
                    for (int i = 0; i < totalPlayers; i++) if (playerList[i].teamId == userTeamId) { players2[count2++] = &playerList[i]; playerList[i].gamesPlayed++; }
                }

                if (isUserMatch) {
                    printf(BLUE "\n--- WORLD CUP MATCH DAY ---\n" RESET);
                    printf(BOLD "%s (Strength %d)" RESET " VS " BOLD "%s (Strength %d)\n" RESET, team1->name, team1->overallStrength, team2->name, team2->overallStrength);
                    printf(YELLOW "\n[ MATCH EVENTS ]\n" RESET);
                }

                for (int gGoal = 0; gGoal < goal1; gGoal++) {
                    if (count1 > 0) {
                        int scorerIdx = chooseScorer(players1, count1);
                        int assisterIdx = chooseAssister(players1, count1, scorerIdx);
                        players1[scorerIdx]->goals++;
                        players1[scorerIdx]->totalGoals++;
                        if (assisterIdx >= 0) { players1[assisterIdx]->assists++; players1[assisterIdx]->totalAssists++; }
                        if (isUserMatch) {
                            if (assisterIdx >= 0)
                                printf(GREEN "⚽ GOAL BY %s! (%s) [Assist: %s]\n" RESET, players1[scorerIdx]->name, team1->name, players1[assisterIdx]->name);
                            else
                                printf(GREEN "⚽ GOAL BY %s! (%s)\n" RESET, players1[scorerIdx]->name, team1->name);
                        }
                    } else if (isUserMatch) printf(GREEN "⚽ GOAL by %s! (Unknown Player)\n" RESET, team1->name);
                }

                for (int gGoal = 0; gGoal < goal2; gGoal++) {
                    if (count2 > 0) {
                        int scorerIdx = chooseScorer(players2, count2);
                        int assisterIdx = chooseAssister(players2, count2, scorerIdx);
                        players2[scorerIdx]->goals++;
                        players2[scorerIdx]->totalGoals++;
                        if (assisterIdx >= 0) { players2[assisterIdx]->assists++; players2[assisterIdx]->totalAssists++; }
                        if (isUserMatch) {
                            if (assisterIdx >= 0)
                                printf(RED "⚽ GOAL BY %s! (%s) [Assist: %s]\n" RESET, players2[scorerIdx]->name, team2->name, players2[assisterIdx]->name);
                            else
                                printf(RED "⚽ GOAL BY %s! (%s)\n" RESET, players2[scorerIdx]->name, team2->name);
                        }
                    } else if (isUserMatch) printf(RED "⚽ GOAL by %s! (Unknown Player)\n" RESET, team2->name);
                }

                if (isUserMatch) {
                    printf(YELLOW "\n[!!!] FULL TIME [!!!]\n" RESET);
                    printf("Result: " BOLD "%s %d x %d %s\n" RESET, team1->name, goal1, goal2, team2->name);

                    if (team1->id == userTeamId) {
                        if (goal1 > goal2) printf(GREEN "Great Victory in the World Cup, Mister!\n" RESET);
                        else if (goal1 < goal2) printf(RED "Defeat... It complicates the group standings.\n" RESET);
                        else printf(YELLOW "Draw. A very tense match.\n" RESET);
                    } else {
                        if (goal2 > goal1) printf(GREEN "Great Victory in the World Cup, Mister!\n" RESET);
                        else if (goal2 < goal1) printf(RED "Defeat... It complicates the group standings.\n" RESET);
                        else printf(YELLOW "Draw. A very tense match.\n" RESET);
                    }
                    printf("\n");
                } else {
                    printf("[Group %c] %-16s %d x %d %s\n", 'A' + g, team1->name, goal1, goal2, team2->name);
                }

                tables[g][tableIdx1].goalsFor += goal1;
                tables[g][tableIdx1].goalsAgainst += goal2;
                tables[g][tableIdx1].goalDifference = tables[g][tableIdx1].goalsFor - tables[g][tableIdx1].goalsAgainst;

                tables[g][tableIdx2].goalsFor += goal2;
                tables[g][tableIdx2].goalsAgainst += goal1;
                tables[g][tableIdx2].goalDifference = tables[g][tableIdx2].goalsFor - tables[g][tableIdx2].goalsAgainst;

                if (goal1 > goal2) {
                    tables[g][tableIdx1].points += 3;
                    teamList[team1 - teamList].gamesWon++;
                    teamList[team2 - teamList].gamesLost++;
                }
                else if (goal2 > goal1) {
                    tables[g][tableIdx2].points += 3;
                    teamList[team2 - teamList].gamesWon++;
                    teamList[team1 - teamList].gamesLost++;
                }
                else {
                    tables[g][tableIdx1].points += 1; tables[g][tableIdx2].points += 1;
                    teamList[team1 - teamList].gamesDrawn++;
                    teamList[team2 - teamList].gamesDrawn++;
                }
            }
        }

        int roundOption = 0;
        do {
            printf(YELLOW "\n--- END OF ROUND %d ---" RESET, r + 1);
            printf("\n1 - View Updated Group Standings\n");
            printf("2 - View World Cup Top Scorers\n");
            printf("3 - View World Cup Top Assisters\n");
            printf("4 - Change Starters\n");
            printf("5 - Advance to the next round\n");
            printf("Choose an option: ");
            if (scanf("%d", &roundOption) != 1) { clearBuffer(); roundOption = 0; }
            clearBuffer();

            if (roundOption == 1) {
                showWorldCupStandings(tables, teamList, userTeamId);
            }
            else if (roundOption == 2) {
                viewTopScorers(playerList, totalPlayers, teamList, totalTeams);
            }
            else if (roundOption == 3) {
                viewTopAssisters(playerList, totalPlayers, teamList, totalTeams);
            }
            else if (roundOption == 4) {
                setStarters(playerList, totalPlayers, userTeamId);
            }
        } while (roundOption != 5);
    }

    printf(CYAN "\n==================================================\n" RESET);
    printf(CYAN "             FINAL GROUP STAGE STANDINGS           \n" RESET);
    printf(CYAN "==================================================\n" RESET);
    showWorldCupStandings(tables, teamList, userTeamId);

    printf(GREEN "\n[!] Group Stage finished successfully!\n" RESET);

    Team *firstPlace[8];
    Team *secondPlace[8];

    for (int g = 0; g < 8; g++) {
        GroupTable groupCopy[4];
        for (int i = 0; i < 4; i++) groupCopy[i] = tables[g][i];

        for (int i = 0; i < 3; i++) {
            for (int j = i + 1; j < 4; j++) {
                int needsSwap = 0;
                if (groupCopy[j].points > groupCopy[i].points) needsSwap = 1;
                else if (groupCopy[j].points == groupCopy[i].points) {
                    if (groupCopy[j].goalDifference > groupCopy[i].goalDifference) needsSwap = 1;
                    else if (groupCopy[j].goalDifference == groupCopy[i].goalDifference && groupCopy[j].goalsFor > groupCopy[i].goalsFor) needsSwap = 1;
                }
                if (needsSwap) {
                    GroupTable temp = groupCopy[i];
                    groupCopy[i] = groupCopy[j];
                    groupCopy[j] = temp;
                }
            }
        }

        firstPlace[g] = &teamList[groupCopy[0].listIndex];
        secondPlace[g] = &teamList[groupCopy[1].listIndex];
    }

    Team *roundOf16[16] = {
        firstPlace[0], secondPlace[1],
        firstPlace[2], secondPlace[3],
        firstPlace[4], secondPlace[5],
        firstPlace[6], secondPlace[7],
        firstPlace[1], secondPlace[0],
        firstPlace[3], secondPlace[2],
        firstPlace[5], secondPlace[4],
        firstPlace[7], secondPlace[6]
    };

    printf(YELLOW "\n[!] The 16 teams qualified for the Round of 16 are set!\n" RESET);
    showMatchups(roundOf16, 16, "ROUND OF 16");

    int knockoutOption = 0;
    do {
        printf(YELLOW "\n--- GROUP STAGE COMPLETE ---\n" RESET);
        printf("1 - View World Cup Top Scorers\n");
        printf("2 - View World Cup Top Assisters\n");
        printf("3 - Change Starters\n");
        printf("4 - Advance to the Knockout Stage (Round of 16)\n");
        printf("Choose an option: ");
        if (scanf("%d", &knockoutOption) != 1) { clearBuffer(); knockoutOption = 0; }
        clearBuffer();

        if (knockoutOption == 1) {
            viewTopScorers(playerList, totalPlayers, teamList, totalTeams);
        }
        else if (knockoutOption == 2) {
            viewTopAssisters(playerList, totalPlayers, teamList, totalTeams);
        }
        else if (knockoutOption == 3) {
            setStarters(playerList, totalPlayers, userTeamId);
        }
    } while (knockoutOption != 4);

    Team *quarterfinalists[8];
    simulateKnockoutStage(roundOf16, 16, quarterfinalists, playerList, totalPlayers, userTeamId, "ROUND OF 16");

    printf(BOLD "\n--- QUALIFIED FOR THE QUARTERFINALS ---\n" RESET);
    showMatchups(quarterfinalists, 8, "QUARTERFINALS");

    int postRoundOf16Option = 0;
    do {
        printf(YELLOW "\n1 - Change Starters\n" RESET);
        printf("2 - Advance to the Quarterfinals\n");
        printf("Choose an option: ");
        if (scanf("%d", &postRoundOf16Option) != 1) { clearBuffer(); postRoundOf16Option = 0; }
        clearBuffer();

        if (postRoundOf16Option == 1) {
            setStarters(playerList, totalPlayers, userTeamId);
        }
    } while (postRoundOf16Option != 2);

    Team *semifinalists[4];
    simulateKnockoutStage(quarterfinalists, 8, semifinalists, playerList, totalPlayers, userTeamId, "QUARTERFINALS");

    printf(BOLD "\n--- QUALIFIED FOR THE SEMIFINALS ---\n" RESET);
    showMatchups(semifinalists, 4, "SEMIFINALS");

    int postQuarterfinalsOption = 0;
    do {
        printf(YELLOW "\n1 - Change Starters\n" RESET);
        printf("2 - Advance to the Semifinals\n");
        printf("Choose an option: ");
        if (scanf("%d", &postQuarterfinalsOption) != 1) { clearBuffer(); postQuarterfinalsOption = 0; }
        clearBuffer();

        if (postQuarterfinalsOption == 1) {
            setStarters(playerList, totalPlayers, userTeamId);
        }
    } while (postQuarterfinalsOption != 2);

    system("cls");
    printf(CYAN "\n==================================================\n" RESET);
    printf(CYAN "  %-46s\n" RESET, "SEMIFINALS");
    printf(CYAN "==================================================\n" RESET);

    Team *finalists[2];
    Team *semifinalLosers[2];

    for (int i = 0; i < 2; i++) {
        Team *team1 = semifinalists[i * 2];
        Team *team2 = semifinalists[i * 2 + 1];
        int result = playKnockoutMatch(team1, team2, playerList, totalPlayers, userTeamId, "SEMIFINAL");
        if (result == 0) {
            finalists[i] = team1;
            semifinalLosers[i] = team2;
        } else {
            finalists[i] = team2;
            semifinalLosers[i] = team1;
        }
    }

    int postSemifinalsOption = 0;
    do {
        printf(YELLOW "\n1 - Change Starters\n" RESET);
        printf("2 - Advance to the 3rd Place Match and the Final\n");
        printf("Choose an option: ");
        if (scanf("%d", &postSemifinalsOption) != 1) { clearBuffer(); postSemifinalsOption = 0; }
        clearBuffer();

        if (postSemifinalsOption == 1) {
            setStarters(playerList, totalPlayers, userTeamId);
        }
    } while (postSemifinalsOption != 2);

    system("cls");
    printf(BOLD "\n--- THIRD PLACE PLAYOFF MATCH ---\n" RESET);
    printf("%-20s x %s\n", semifinalLosers[0]->name, semifinalLosers[1]->name);
    int thirdPlaceResult = playKnockoutMatch(semifinalLosers[0], semifinalLosers[1], playerList, totalPlayers, userTeamId, "THIRD PLACE PLAYOFF");
    Team *thirdPlace;
    Team *fourthPlace;
    if (thirdPlaceResult == 0) {
        thirdPlace = semifinalLosers[0];
        fourthPlace = semifinalLosers[1];
    } else {
        thirdPlace = semifinalLosers[1];
        fourthPlace = semifinalLosers[0];
    }

    int postThirdPlaceOption = 0;
    do {
        printf(YELLOW "\n1 - Change Starters\n" RESET);
        printf("2 - Advance to the GRAND FINAL\n");
        printf("Choose an option: ");
        if (scanf("%d", &postThirdPlaceOption) != 1) { clearBuffer(); postThirdPlaceOption = 0; }
        clearBuffer();

        if (postThirdPlaceOption == 1) {
            setStarters(playerList, totalPlayers, userTeamId);
        }
    } while (postThirdPlaceOption != 2);
    system("cls");

    printf(BOLD "\n--- GRAND FINAL MATCH ---\n" RESET);
    printf("%-20s x %s\n", finalists[0]->name, finalists[1]->name);
    int finalResult = playKnockoutMatch(finalists[0], finalists[1], playerList, totalPlayers, userTeamId, "GRAND FINAL");
    Team *champion;
    Team *runnerUp;
    if (finalResult == 0) {
        champion = finalists[0];
        runnerUp = finalists[1];
    } else {
        champion = finalists[1];
        runnerUp = finalists[0];
    }

    champion->cupsWon++;

    if (champion->cupsWon % 5 == 0) {
        for (int i = 0; i < totalPlayers; i++) {
            if (playerList[i].originalTeamId == champion->id && playerList[i].overall < 100) {
                playerList[i].overall++;
            }
        }
        printf(YELLOW "\n[!] %s have reached %d cups won! The overall of the entire squad went up by 1 point!\n" RESET,
               champion->name, champion->cupsWon);
    }

    printf(GREEN "\n==================================================\n" RESET);
    printf(GREEN "               FINAL WORLD CUP PODIUM              \n" RESET);
    printf(GREEN "==================================================\n" RESET);
    printf(BOLD "🥇 Champion:   " RESET GREEN "%s\n" RESET, champion->name);
    printf(BOLD "🥈 Runner-up:  " RESET "%s\n", runnerUp->name);
    printf(BOLD "🥉 3rd Place:  " RESET "%s\n", thirdPlace->name);
    printf(BOLD "4th Place:  " RESET "%s\n", fourthPlace->name);
    printf(GREEN "==================================================\n" RESET);

    printf(CYAN "\n==================================================\n" RESET);
    printf(CYAN "             WORLD CUP INDIVIDUAL AWARDS           \n" RESET);
    printf(CYAN "==================================================\n" RESET);

    Player *bootWinner = NULL;
    for (int i = 0; i < totalPlayers; i++)
    {
        if (playerList[i].goals > 0 && (bootWinner == NULL || playerList[i].goals > bootWinner->goals))
            bootWinner = &playerList[i];
    }

    Player *assistWinner = NULL;
    for (int i = 0; i < totalPlayers; i++)
    {
        if (playerList[i].assists > 0 && (assistWinner == NULL || playerList[i].assists > assistWinner->assists))
            assistWinner = &playerList[i];
    }

    Player *mvp = NULL;
    int mvpScore = 0;
    for (int i = 0; i < totalPlayers; i++)
    {
        int score = playerList[i].goals * 2 + playerList[i].assists;
        if (score > 0 && (mvp == NULL || score > mvpScore ||
            (score == mvpScore && playerList[i].overall > mvp->overall)))
        {
            mvp = &playerList[i];
            mvpScore = score;
        }
    }

    int bestGoalsAgainst = -1;
    int bestDefenseTeamId = -1;
    for (int g = 0; g < 8; g++)
    {
        for (int t = 0; t < 4; t++)
        {
            int currentTeamId = teamList[tables[g][t].listIndex].id;
            int currentGoalsAgainst = tables[g][t].goalsAgainst;
            if (bestGoalsAgainst == -1 || currentGoalsAgainst < bestGoalsAgainst)
            {
                bestGoalsAgainst = currentGoalsAgainst;
                bestDefenseTeamId = currentTeamId;
            }
        }
    }
    char bestDefenseTeamName[50] = "Unknown";
    if (bestDefenseTeamId != -1)
    {
        for (int s = 0; s < totalTeams; s++)
            if (teamList[s].id == bestDefenseTeamId) { strcpy(bestDefenseTeamName, teamList[s].name); break; }
    }
    Player *goldenGlove = NULL;
    if (bestDefenseTeamId != -1)
    {
        for (int i = 0; i < totalPlayers; i++)
        {
            if (strcmp(playerList[i].position, "GK") != 0)
                continue;
            int playerTeamId = (playerList[i].teamId != 0) ? playerList[i].teamId : playerList[i].originalTeamId;
            if (playerTeamId != bestDefenseTeamId)
                continue;
            if (goldenGlove == NULL || playerList[i].isStarter > goldenGlove->isStarter ||
                (playerList[i].isStarter == goldenGlove->isStarter && playerList[i].overall > goldenGlove->overall))
                goldenGlove = &playerList[i];
        }
    }

    char awardTeamName[50];

    if (mvp != NULL)
    {
        strcpy(awardTeamName, "Unknown");
        int searchTeamId = (mvp->teamId != 0) ? mvp->teamId : mvp->originalTeamId;
        for (int s = 0; s < totalTeams; s++)
            if (teamList[s].id == searchTeamId) { strcpy(awardTeamName, teamList[s].name); break; }
        printf(BOLD "🏅 MVP of the Tournament: " RESET GREEN "%s" RESET " (%s) - %d goals, %d assists\n",
               mvp->name, awardTeamName, mvp->goals, mvp->assists);
    }

    if (bootWinner != NULL)
    {
        strcpy(awardTeamName, "Unknown");
        int searchTeamId = (bootWinner->teamId != 0) ? bootWinner->teamId : bootWinner->originalTeamId;
        for (int s = 0; s < totalTeams; s++)
            if (teamList[s].id == searchTeamId) { strcpy(awardTeamName, teamList[s].name); break; }
        printf(BOLD "👟 Golden Boot (Top Scorer): " RESET YELLOW "%s" RESET " (%s) - %d goals\n",
               bootWinner->name, awardTeamName, bootWinner->goals);
    }

    if (assistWinner != NULL)
    {
        strcpy(awardTeamName, "Unknown");
        int searchTeamId = (assistWinner->teamId != 0) ? assistWinner->teamId : assistWinner->originalTeamId;
        for (int s = 0; s < totalTeams; s++)
            if (teamList[s].id == searchTeamId) { strcpy(awardTeamName, teamList[s].name); break; }
        printf(BOLD "🎯 Best Assister: " RESET YELLOW "%s" RESET " (%s) - %d assists\n",
               assistWinner->name, awardTeamName, assistWinner->assists);
    }

    if (goldenGlove != NULL)
    {
        printf(BOLD "🧤 Golden Glove (Best Defense): " RESET CYAN "%s" RESET " (%s) - %d goals conceded in the group stage\n",
               goldenGlove->name, bestDefenseTeamName, bestGoalsAgainst);
    }
    else
    {
        printf(YELLOW "🧤 Golden Glove: not awarded (no goalkeeper found for the best defense).\n" RESET);
    }

    printf(CYAN "==================================================\n" RESET);

    if (champion->id == userTeamId) {
        printf(GREEN "\n🏆 CONGRATULATIONS, MISTER! You won the World Cup with %s! 🏆\n" RESET, champion->name);
    } else if (runnerUp->id == userTeamId) {
        printf(YELLOW "\nYou finished 2nd with %s. So close to the title, Mister!\n" RESET, runnerUp->name);
    } else if (thirdPlace->id == userTeamId) {
        printf(YELLOW "\nYou finished 3rd with %s. A good campaign!\n" RESET, thirdPlace->name);
    } else if (fourthPlace->id == userTeamId) {
        printf(YELLOW "\nYou finished 4th with %s. So close to the podium!\n" RESET, fourthPlace->name);
    }
}