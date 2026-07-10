#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manager.c"
#include "matches.c"
#include "inicializate.c"

void initializeDefaultData();

int main()
{
    system("chcp 65001");
    system("cls");
    initializeDefaultData();

    showBanner();

    User currentUser;
    int loggedIn = 0;
    int playing = 1;

    Team teams[50];
    int totalTeams = 0;

    Player players[800];
    int totalPlayers = 0;

    loadTeams(teams, &totalTeams);
    loadPlayers(players, &totalPlayers);

    while (playing)
    {
        loggedIn = checkSession(&currentUser);

        while (!loggedIn)
        {
            loggedIn = initialMenu(&currentUser);
        }

        int menuOption = -1;

        if (currentUser.isAdmin == 1)
        {
            do
            {
                printf(GREEN "=========================================================================\n" RESET);
                printf(GREEN "                          [ADMINISTRATOR MENU]                           \n" RESET);
                printf(GREEN "=========================================================================\n" RESET);
                printf("\tAdmin: " BOLD "%s" RESET "\n", currentUser.username);
                printf("-------------------------------------------------------------------------\n");

                printf("\t1. " CYAN "Create Team" RESET "\n");
                printf("\t2. " CYAN "List Teams" RESET "\n");
                printf("\t3. " CYAN "Edit Team" RESET "\n");
                printf("\t7. " RED "Delete Team" RESET "\n");

                printf("\t4. " YELLOW "Create Player" RESET "\n");
                printf("\t5. " YELLOW "Edit Player" RESET "\n");
                printf("\t8. " RED "Delete Player" RESET "\n");

                printf("\t6. " GREEN "Save System Changes" RESET "\n");
                printf("\t9. " YELLOW "End Session (Logout)" RESET "\n");
                printf("\t0. " RED "Quit Game" RESET "\n");

                printf(GREEN "=========================================================================\n" RESET);
                printf("\t" BOLD "Choice: " RESET);

                if (scanf("%d", &menuOption) != 1)
                    menuOption = -1;
                clearBuffer();

                switch (menuOption)
                {
                case 1:
                    if (totalTeams < 32)
                        createTeam(teams, &totalTeams);
                    else
                        printf(RED "Limit reached!\n" RESET);
                    printf(YELLOW "\nPress Enter to continue..." RESET);
                    getchar();
                    system("cls");
                    break;

                case 2:
                    listTeams(teams, totalTeams);
                    printf(YELLOW "\nPress Enter to continue..." RESET);
                    getchar();
                    system("cls");
                    break;

                case 3:
                    editTeam(teams, totalTeams);
                    printf(YELLOW "\nPress Enter to continue..." RESET);
                    getchar();
                    system("cls");
                    break;

                case 4:
                    createPlayer(players, &totalPlayers, teams, totalTeams);
                    printf(YELLOW "\nPress Enter to continue..." RESET);
                    getchar();
                    system("cls");
                    break;

                case 5:
                    editPlayer(players, totalPlayers, teams, totalTeams);
                    printf(YELLOW "\nPress Enter to continue..." RESET);
                    getchar();
                    system("cls");
                    break;

                case 6:
                    saveTeams(teams, totalTeams);
                    savePlayers(players, totalPlayers);
                    printf(GREEN "System changes saved successfully!\n" RESET);
                    printf(YELLOW "\nPress Enter to continue..." RESET);
                    getchar();
                    system("cls");
                    break;

                case 7:
                {
                    listTeams(teams, totalTeams);
                    int teamIdToDelete;
                    printf(YELLOW "\nEnter the ID of the team to delete (0 to cancel): " RESET);
                    if (scanf("%d", &teamIdToDelete) != 1)
                    {
                        clearBuffer();
                        printf(RED "Invalid input.\n" RESET);
                    }
                    else
                    {
                        clearBuffer();
                        if (teamIdToDelete == 0)
                        {
                            printf(CYAN "Operation cancelled.\n" RESET);
                        }
                        else
                        {
                            printf(RED "\n[!] This will permanently delete the team and all its players. Are you sure? (1 = Yes, 0 = No): " RESET);
                            int confirmDelete;
                            if (scanf("%d", &confirmDelete) != 1)
                            {
                                clearBuffer();
                                confirmDelete = 0;
                            }
                            else
                            {
                                clearBuffer();
                            }

                            if (confirmDelete == 1)
                            {
                                if (deleteTeam(teams, &totalTeams, players, &totalPlayers, teamIdToDelete))
                                {
                                    saveTeams(teams, totalTeams);
                                    savePlayers(players, totalPlayers);
                                }
                                else
                                {
                                    printf(RED "[X] Invalid team ID.\n" RESET);
                                }
                            }
                            else
                            {
                                printf(CYAN "Operation cancelled.\n" RESET);
                            }
                        }
                    }
                    printf(YELLOW "\nPress Enter to continue..." RESET);
                    getchar();
                    system("cls");
                    break;
                }

                case 8:
                {
                    listPlayersFromTeam(players, totalPlayers, -1);
                    int playerIdToDelete;
                    printf(YELLOW "\nEnter the ID of the player to delete (0 to cancel): " RESET);
                    if (scanf("%d", &playerIdToDelete) != 1)
                    {
                        clearBuffer();
                        printf(RED "Invalid input.\n" RESET);
                    }
                    else
                    {
                        clearBuffer();
                        if (playerIdToDelete == 0)
                        {
                            printf(CYAN "Operation cancelled.\n" RESET);
                        }
                        else
                        {
                            printf(RED "\n[!] This will permanently delete the player. Are you sure? (1 = Yes, 0 = No): " RESET);
                            int confirmDelete;
                            if (scanf("%d", &confirmDelete) != 1)
                            {
                                clearBuffer();
                                confirmDelete = 0;
                            }
                            else
                            {
                                clearBuffer();
                            }

                            if (confirmDelete == 1)
                            {
                                if (deletePlayer(players, &totalPlayers, playerIdToDelete))
                                {
                                    savePlayers(players, totalPlayers);
                                }
                                else
                                {
                                    printf(RED "[X] Invalid player ID.\n" RESET);
                                }
                            }
                            else
                            {
                                printf(CYAN "Operation cancelled.\n" RESET);
                            }
                        }
                    }
                    printf(YELLOW "\nPress Enter to continue..." RESET);
                    getchar();
                    system("cls");
                    break;
                }

                case 9:
                    saveTeams(teams, totalTeams);
                    savePlayers(players, totalPlayers);
                    endSession();
                    loggedIn = 0;
                    menuOption = 0;
                    system("cls");
                    break;

                case 0:
                    saveTeams(teams, totalTeams);
                    savePlayers(players, totalPlayers);
                    printf(GREEN "Data saved. Exiting...\n" RESET);
                    playing = 0;
                    break;

                default:
                    printf(RED "Invalid option.\n" RESET);
                    printf(YELLOW "\nPress Enter to continue..." RESET);
                    getchar();
                    system("cls");
                }
            } while (menuOption != 0);
        }

        else
        {
            if (currentUser.teamId != 0)
            {
                int careerOption = -1;
                printf(CYAN "=========================================================================\n" RESET);
                printf(CYAN "                           CAREER OPTIONS                                \n" RESET);
                printf(CYAN "=========================================================================\n" RESET);
                printf("\tWelcome back, Coach %s (%s).\n", currentUser.coachName, currentUser.nationality);
                printf("\t1. Continue Current Career\n");
                printf("\t2. Start New Career (Deletes previous progress)\n");
                printf(CYAN "=========================================================================\n" RESET);
                printf("" BOLD "Choice: " RESET);
                if (scanf("%d", &careerOption) != 1)
                    careerOption = -1;
                clearBuffer();

                if (careerOption == 2)
                {
                    for (int i = 0; i < totalPlayers; i++)
                    {
                        players[i].teamId = 0;
                        players[i].isStarter = 0;
                        players[i].goals = 0;
                        players[i].totalGoals = 0;
                        players[i].assists = 0;
                        players[i].totalAssists = 0;
                        players[i].gamesPlayed = 0;
                    }
                    savePlayers(players, totalPlayers);

                    for (int i = 0; i < totalTeams; i++)
                    {
                        teams[i].gamesWon = 0;
                        teams[i].gamesDrawn = 0;
                        teams[i].gamesLost = 0;
                        teams[i].cupsWon = 0;
                    }
                    saveTeams(teams, totalTeams);

                    currentUser.teamId = 0;
                    updateUserInDatabase(&currentUser);
                }
                system("cls");
            }

            if (currentUser.teamId == 0)
            {
                printf(YELLOW "\nWe need to set up your coach profile before starting.\n" RESET);
                chooseTeam(&currentUser, teams, totalTeams);
                savePlayers(players, totalPlayers);
                system("cls");
                printf(CYAN "[!] Your squad is empty. Use 'Call Up Player' to build your team.\n" RESET);
            }

            do
            {
                char myTeamName[50] = "Unknown";
                for (int i = 0; i < totalTeams; i++)
                {
                    if (teams[i].id == currentUser.teamId)
                    {
                        strcpy(myTeamName, teams[i].name);
                        break;
                    }
                }

                int myTotalPlayers = 0;
                int starterGK = 0, starterDEF = 0;
                for (int i = 0; i < totalPlayers; i++)
                {
                    if (players[i].teamId == currentUser.teamId)
                    {
                        myTotalPlayers++;
                        if (players[i].isStarter == 1)
                        {
                            if (strcmp(players[i].position, "GK") == 0)
                                starterGK++;
                            else if (strcmp(players[i].position, "DEF") == 0)
                                starterDEF++;
                        }
                    }
                }

                printf(GREEN "=========================================================================\n" RESET);
                printf(GREEN "                       [CAREER MODE - COACH]                            \n" RESET);
                printf(GREEN "=========================================================================\n" RESET);
                printf("\tCoach:  " BOLD "%s (%s)" RESET "\n", currentUser.coachName, currentUser.nationality);
                printf("\tTeam:   " BOLD "%s" RESET "\n", myTeamName);
                const char *squadWarning;
                if (myTotalPlayers < 11)
                    squadWarning = RED " (minimum 11 to play!)" RESET;
                else
                    squadWarning = "";
                printf("\tSquad:  " BOLD "%d player(s)" RESET "%s\n", myTotalPlayers,
                       squadWarning);
                int lineupOk = (starterGK >= 1 && starterDEF >= 3);
                const char *lineupStatus;
                if (!lineupOk)
                    lineupStatus = RED " (min: 1 GK + 3 DEF as starters!)" RESET;
                else
                    lineupStatus = GREEN " [OK]" RESET;
                printf("\tLineup: " BOLD "GK: %d" RESET " | " BOLD "DEF: %d" RESET "%s\n",
                       starterGK, starterDEF,
                       lineupStatus);
                printf(CYAN "-------------------------------------------------------------------------\n" RESET);
                printf("\t1. View My Team (Squad & Stats)\n");
                printf("\t2. " YELLOW "Go to World Cup" RESET "\n");
                printf("\t3. Play Friendly Match\n");
                printf("\t4. Team Statistics (W/D/L and Cups)\n");
                printf("\t5. Sort All World Players\n");
                printf("\t6. Call Up Player\n");
                printf("\t7. Set Starters\n");
                printf("\t8. " GREEN "Save Career Progress" RESET "\n");
                printf("\t9. Exit Career (Back to career options)\n");
                printf("\t10. End Session (Logout)\n");
                printf("\t0. " RED "Quit Game" RESET "\n");
                printf(CYAN "=========================================================================\n" RESET);
                printf("\t" BOLD "Choice: " RESET);
                if (scanf("%d", &menuOption) != 1)
                    menuOption = -1;
                clearBuffer();

                switch (menuOption)
                {
                case 1:
                    listPlayersFromTeam(players, totalPlayers, currentUser.teamId);
                    printf(YELLOW "\nPress Enter to continue..." RESET);
                    getchar();
                    system("cls");
                    break;
                case 2:
                    if (myTotalPlayers < 11)
                    {
                        printf(RED "\n[X] You can't play the World Cup! Your team only has %d player(s). You need at least 11.\n" RESET, myTotalPlayers);
                        printf(YELLOW "\nPress Enter to continue..." RESET);
                        getchar();
                        system("cls");
                        break;
                    }
                    if (starterGK < 1 || starterDEF < 3)
                    {
                        printf(RED "\n[X] You can't play the World Cup! Your starters are not complete.\n" RESET);
                        printf(YELLOW "\nPress Enter to continue..." RESET);
                        getchar();
                        system("cls");
                        break;
                    }
                    resetTournamentStats(players, totalPlayers);
                    simulateWorldCup(teams, totalTeams, players, totalPlayers, currentUser.teamId);
                    saveTeams(teams, totalTeams);
                    savePlayers(players, totalPlayers);
                    printf(YELLOW "\nPress Enter to continue..." RESET);
                    getchar();
                    system("cls");
                    break;
                case 3:
                    if (myTotalPlayers < 11)
                    {
                        printf(RED "\n[X] You can't play! Your team only has %d player(s). You need at least 11.\n" RESET, myTotalPlayers);
                        printf(YELLOW "\nPress Enter to continue..." RESET);
                        getchar();
                        system("cls");
                        break;
                    }
                    if (starterGK < 1 || starterDEF < 3)
                    {
                        printf(RED "\n[X] You can't play! Your starters are not complete.\n" RESET);
                        printf(YELLOW "\nPress Enter to continue..." RESET);
                        getchar();
                        system("cls");
                        break;
                    }
                    simulateMatch(teams, totalTeams, players, totalPlayers, currentUser.teamId);
                    saveTeams(teams, totalTeams);
                    savePlayers(players, totalPlayers);
                    printf(YELLOW "\nPress Enter to continue..." RESET);
                    getchar();
                    system("cls");
                    break;
                case 5:
                {
                    int sortCriterion = -1;
                    printf(CYAN "=========================================================================\n" RESET);
                    printf(CYAN "                            [SORT PLAYERS]                               \n" RESET);
                    printf(CYAN "=========================================================================\n" RESET);
                    printf("\t1. Sort by Overall\n");
                    printf("\t2. Sort by Goals\n");
                    printf("\t3. Sort by Assists\n");
                    printf(CYAN "=========================================================================\n" RESET);
                    printf(BOLD "\tChoice: " RESET);
                    if (scanf("%d", &sortCriterion) != 1)
                        sortCriterion = 1;
                    clearBuffer();

                    if (sortCriterion != 1 && sortCriterion != 2 && sortCriterion != 3)
                    {
                        printf(RED "\tInvalid option, sorting by Overall by default.\n" RESET);
                        sortCriterion = 1;
                    }

                    sortPlayers(players, totalPlayers, sortCriterion);
                    listPlayersFromTeam(players, totalPlayers, -1);
                    printf(YELLOW "\nPress Enter to continue..." RESET);
                    getchar();
                    system("cls");
                    break;
                }
                case 6:
                {
                    int squadOption = -1;
                    while (squadOption != 0)
                    {
                        system("cls");
                        int calledUp = 0;
                        for (int i = 0; i < totalPlayers; i++)
                            if (players[i].teamId == currentUser.teamId)
                                calledUp++;

                        printf(CYAN "=========================================================================\n" RESET);
                        printf(CYAN "                       [SQUAD MANAGEMENT]                                \n" RESET);
                        printf(CYAN "=========================================================================\n" RESET);
                        printf("\tCurrent squad: " BOLD "%d/15\n" RESET, calledUp);
                        printf("-------------------------------------------------------------------------\n");
                        printf("\t1. " GREEN "Call Up Player" RESET "\n");
                        printf("\t2. " RED "Remove Player" RESET "\n");
                        printf("\t0. " YELLOW "Back to Main Menu" RESET "\n");
                        printf("=========================================================================\n");
                        printf("\t" BOLD "Choice: " RESET);
                        if (scanf("%d", &squadOption) != 1)
                        {
                            clearBuffer();
                            squadOption = -1;
                            continue;
                        }
                        clearBuffer();

                        if (squadOption == 1)
                        {
                            if (calledUp >= 15)
                            {
                                system("cls");
                                printf(CYAN "=========================================================================\n" RESET);
                                printf(CYAN "                          [CALL UP PLAYER]                               \n" RESET);
                                printf(CYAN "=========================================================================\n" RESET);
                                printf(RED "\t[X] You already have 15 players! Remove one before calling up another.\n" RESET);
                                printf(YELLOW "\n\tPress Enter to continue..." RESET);
                                getchar();
                                continue;
                            }
                            while (1)
                            {
                                system("cls");
                                calledUp = 0;
                                for (int i = 0; i < totalPlayers; i++)
                                    if (players[i].teamId == currentUser.teamId)
                                        calledUp++;

                                printf(CYAN "=========================================================================\n" RESET);
                                printf(CYAN "                          [CALL UP PLAYER]                               \n" RESET);
                                printf(CYAN "=========================================================================\n" RESET);
                                printf("\tCurrent squad: " BOLD "%d/15\n" RESET, calledUp);
                                printf(YELLOW "-------------------------------------------------------------------------\n" RESET);
                                printf(YELLOW "\t\t   [AVAILABLE PLAYERS (%s)]\n" RESET, myTeamName);
                                printf(YELLOW "=========================================================================\n" RESET);
                                printf(BOLD "\tID\t%-22s POS\tOVR\n" RESET, "NAME");
                                printf("-------------------------------------------------------------------------\n");
                                int hasAvailable = 0;
                                for (int i = 0; i < totalPlayers; i++)
                                {
                                    if (players[i].originalTeamId == currentUser.teamId && players[i].teamId == 0)
                                    {
                                        printf("\t%d\t%-22s %s\t%d\n", players[i].id, players[i].name, players[i].position, players[i].overall);
                                        hasAvailable = 1;
                                    }
                                }
                                if (!hasAvailable)
                                {
                                    printf(RED "\tNo players available to call up.\n" RESET);
                                    printf(YELLOW "\n\tPress Enter to continue..." RESET);
                                    getchar();
                                    break;
                                }
                                if (calledUp >= 15)
                                {
                                    printf(RED "\t[X] Squad limit of 15 reached!\n" RESET);
                                    printf(YELLOW "\n\tPress Enter to continue..." RESET);
                                    getchar();
                                    break;
                                }
                                int callId;
                                printf(YELLOW "\n\tEnter player ID to call up (0 to go back): " RESET);
                                if (scanf("%d", &callId) != 1)
                                {
                                    clearBuffer();
                                    continue;
                                }
                                clearBuffer();
                                if (callId == 0)
                                    break;

                                int found = 0;
                                for (int i = 0; i < totalPlayers; i++)
                                {
                                    if (players[i].id == callId && players[i].originalTeamId == currentUser.teamId && players[i].teamId == 0)
                                    {
                                        players[i].teamId = currentUser.teamId;
                                        players[i].isStarter = 0;
                                        players[i].gamesPlayed = 0;
                                        printf(GREEN "\t[!] %s called up! (%d/15)\n" RESET, players[i].name, calledUp + 1);
                                        savePlayers(players, totalPlayers);
                                        found = 1;
                                        break;
                                    }
                                }
                                if (!found)
                                    printf(RED "\t[X] Invalid ID or player not available.\n" RESET);
                                printf(YELLOW "\n\tPress Enter to continue..." RESET);
                                getchar();
                            }
                        }

                        else if (squadOption == 2)
                        {
                            while (1)
                            {
                                system("cls");
                                calledUp = 0;
                                for (int i = 0; i < totalPlayers; i++)
                                    if (players[i].teamId == currentUser.teamId)
                                        calledUp++;

                                printf(CYAN "=========================================================================\n" RESET);
                                printf(CYAN "                         [REMOVE PLAYER]                                 \n" RESET);
                                printf(CYAN "=========================================================================\n" RESET);
                                printf("\tCurrent squad: " BOLD "%d/15\n" RESET, calledUp);
                                printf(YELLOW "=========================================================================\n" RESET);
                                printf(BOLD "\tID\t%-22s POS\tOVR\tSTARTER\n" RESET, "NAME");
                                printf("-------------------------------------------------------------------------\n");
                                int hasPlayer = 0;
                                for (int i = 0; i < totalPlayers; i++)
                                {
                                    if (players[i].teamId == currentUser.teamId)
                                    {
                                        const char *starterLabel;
                                        if (players[i].isStarter)
                                            starterLabel = GREEN "Yes" RESET;
                                        else
                                            starterLabel = "No";
                                        printf("\t%d\t%-22s %s\t%d\t%s\n",
                                               players[i].id, players[i].name, players[i].position,
                                               players[i].overall,
                                               starterLabel);
                                        hasPlayer = 1;
                                    }
                                }
                                if (!hasPlayer)
                                {
                                    printf(RED "\tYou have no players in your squad.\n" RESET);
                                    printf(YELLOW "\n\tPress Enter to continue..." RESET);
                                    getchar();
                                    break;
                                }
                                int removeId;
                                printf(YELLOW "\n\tEnter player ID to remove (0 to go back): " RESET);
                                if (scanf("%d", &removeId) != 1)
                                {
                                    clearBuffer();
                                    continue;
                                }
                                clearBuffer();
                                if (removeId == 0)
                                    break;

                                int found = 0;
                                for (int i = 0; i < totalPlayers; i++)
                                {
                                    if (players[i].id == removeId && players[i].teamId == currentUser.teamId)
                                    {
                                        char removedName[50];
                                        strcpy(removedName, players[i].name);
                                        players[i].teamId = 0;
                                        players[i].isStarter = 0;
                                        savePlayers(players, totalPlayers);
                                        printf(YELLOW "\t[!] %s was removed. (%d/15)\n" RESET, removedName, calledUp - 1);
                                        found = 1;
                                        break;
                                    }
                                }
                                if (!found)
                                    printf(RED "\t[X] Invalid ID or player not in squad.\n" RESET);
                                printf(YELLOW "\n\tPress Enter to continue..." RESET);
                                getchar();
                            }
                        }
                    }
                    system("cls");
                    break;
                }
                case 7:
                {
                    setStarters(players, totalPlayers, currentUser.teamId);
                    break;
                }
                case 8:
                    saveTeams(teams, totalTeams);
                    savePlayers(players, totalPlayers);
                    updateUserInDatabase(&currentUser);
                    printf(GREEN "[!] Your career has been saved successfully!\n" RESET);
                    printf(YELLOW "\nPress Enter to continue..." RESET);
                    getchar();
                    system("cls");
                    break;
                case 9:
                    saveTeams(teams, totalTeams);
                    savePlayers(players, totalPlayers);
                    updateUserInDatabase(&currentUser);
                    printf(CYAN "Returning to career options...\n" RESET);
                    menuOption = 0;
                    system("cls");
                    break;
                case 4:
                    showTeamStatistics(teams, totalTeams);
                    printf(YELLOW "\nPress Enter to continue..." RESET);
                    getchar();
                    system("cls");
                    break;
                case 10:
                    saveTeams(teams, totalTeams);
                    savePlayers(players, totalPlayers);
                    updateUserInDatabase(&currentUser);
                    endSession();
                    loggedIn = 0;
                    menuOption = 0;
                    system("cls");
                    break;
                case 0:
                    saveTeams(teams, totalTeams);
                    savePlayers(players, totalPlayers);
                    printf(GREEN "Data saved. Goodbye, Coach!\n" RESET);
                    playing = 0;
                    break;
                default:
                    printf(RED "Invalid option.\n" RESET);
                    printf(YELLOW "\nPress Enter to continue..." RESET);
                    getchar();
                    system("cls");
                }
            } while (menuOption != 0);
        }
    }

    return 0;
}