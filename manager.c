#include "manager.h"

void clearBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int isEmptyOrSpaces(const char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] != ' ' && s[i] != '\t')
            return 0;
        i++;
    }
    return 1;
}

void readValidField(char *destination, int size, const char *prompt, int minLen)
{
    while (1)
    {
        printf("%s", prompt);
        fgets(destination, size, stdin);
        destination[strcspn(destination, "\n")] = 0;

        if (isEmptyOrSpaces(destination))
        {
            printf(RED "This field cannot be empty or contain only spaces.\n" RESET);
            continue;
        }

        if (minLen > 0 && (int)strlen(destination) < minLen)
        {
            printf(RED "Must have at least %d characters.\n" RESET, minLen);
            continue;
        }

        break;
    }
}

void showBanner()
{
    printf(CYAN BOLD);
    printf("███████  ██████   ██████  ████████ ██████   █████  ██      ██            ██████  ██████  ██  ██████  ██ ███    ██ \n");
    printf("██      ██    ██ ██    ██    ██    ██   ██ ██   ██ ██      ██           ██    ██ ██   ██ ██ ██       ██ ████   ██ \n");
    printf("█████   ██    ██ ██    ██    ██    ██████  ███████ ██      ██           ██    ██ ██████  ██ ██   ███ ██ ██ ██  ██ \n");
    printf("██      ██    ██ ██    ██    ██    ██   ██ ██   ██ ██      ██           ██    ██ ██   ██ ██ ██    ██ ██ ██  ██ ██ \n");
    printf("██       ██████   ██████     ██    ██████  ██   ██ ███████ ███████       ██████  ██   ██ ██  ██████  ██ ██   ████ \n\n");
    printf(RESET);
}

void saveSession(const char *username)
{
    FILE *f = fopen("../database/session.txt", "w");
    if (f)
    {
        fprintf(f, "%s\n", username);
        fclose(f);
    }
}

void endSession()
{
    remove("../database/session.txt");
    printf(YELLOW "\n[!] Session ended successfully.\n" RESET);
}

void updateUserInDatabase(User *u)
{
    FILE *fIn = fopen("../database/users.txt", "r");
    FILE *fOut = fopen("../database/temp.txt", "w");
    if (!fIn || !fOut)
        return;

    char line[250];
    while (fgets(line, sizeof(line), fIn))
    {
        char lineCopy[250];
        strcpy(lineCopy, line);
        lineCopy[strcspn(lineCopy, "\n")] = 0;

        char *user = strtok(lineCopy, ",");

        if (user && strcmp(user, u->username) == 0)
        {
            fprintf(fOut, "%s,%s,%d,%d,%s,%s\n", u->username, u->password, u->isAdmin, u->teamId, u->coachName, u->nationality);
        }
        else
        {
            fputs(line, fOut);
        }
    }
    fclose(fIn);
    fclose(fOut);

    remove("../database/users.txt");
    rename("../database/temp.txt", "../database/users.txt");
}

int usernameExists(const char *username)
{
    FILE *f = fopen("../database/users.txt", "r");
    if (!f)
        return 0;

    char line[250];
    while (fgets(line, sizeof(line), f))
    {
        char lineCopy[250];
        strcpy(lineCopy, line);
        lineCopy[strcspn(lineCopy, "\n")] = 0;

        char *user = strtok(lineCopy, ",");

        if (user && strcmp(user, username) == 0)
        {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int checkSession(User *loggedUser)
{
    FILE *f = fopen("../database/session.txt", "r");
    if (!f)
        return 0;

    char savedUsername[50];
    if (fgets(savedUsername, 50, f) != NULL)
    {
        savedUsername[strcspn(savedUsername, "\n")] = 0;
        fclose(f);

        FILE *fUsers = fopen("../database/users.txt", "r");
        if (!fUsers)
            return 0;

        char line[250];
        while (fgets(line, sizeof(line), fUsers))
        {
            line[strcspn(line, "\n")] = 0;
            char *user = strtok(line, ",");
            char *pass = strtok(NULL, ",");
            char *adminStr = strtok(NULL, ",");
            char *teamStr = strtok(NULL, ",");
            char *coachName = strtok(NULL, ",");
            char *nat = strtok(NULL, ",");

            if (user && strcmp(savedUsername, user) == 0)
            {
                strcpy(loggedUser->username, user);
                strcpy(loggedUser->password, pass);
                loggedUser->isAdmin = atoi(adminStr);
                loggedUser->teamId = atoi(teamStr);
                if (coachName)
                    strcpy(loggedUser->coachName, coachName);
                if (nat)
                    strcpy(loggedUser->nationality, nat);
                fclose(fUsers);

                return 1;
            }
        }
        fclose(fUsers);
    }
    else
    {
        fclose(f);
    }
    return 0;
}

int initialMenu(User *loggedUser)
{
    int option;
    printf(CYAN "=========================================================================\n" RESET);
    printf(CYAN "                            [GAME ACCESS]                                \n" RESET);
    printf(CYAN "=========================================================================\n" RESET);
    printf("\t1. Log In\n");
    printf("\t2. Register Account\n");
    printf("\t0. Exit Game\n");
    printf(CYAN "=========================================================================\n" RESET);
    printf("\t" BOLD "Choice: " RESET);
    if (scanf("%d", &option) != 1)
    {
        clearBuffer();
        printf(RED "Invalid option.\n" RESET);
        return 0;
    }
    clearBuffer();
    system("cls");

    if (option == 1)
        return doLogin(loggedUser);
    else if (option == 2)
        return registerUser(loggedUser);
    else if (option == 0)
        exit(0);

    return 0;
}

int registerUser(User *loggedUser)
{
    User newUser;
    printf(YELLOW "=========================================================================\n" RESET);
    printf(YELLOW "                          [ACCOUNT REGISTRATION]                         \n" RESET);
    printf(YELLOW "=========================================================================\n" RESET);

    while (1)
    {
        readValidField(newUser.username, 50, "\tUsername: ", 3);

        if (usernameExists(newUser.username))
        {
            printf(RED "\tThis username is already taken. Choose another one.\n" RESET);
            continue;
        }

        break;
    }

    readValidField(newUser.password, 50, "\tPassword (minimum 8 characters): ", 8);

    FILE *file = fopen("../database/users.txt", "a");
    if (!file)
    {
        printf(RED "Error accessing the users database.\n" RESET);
        return 0;
    }

    if (strcmp(newUser.username, "admin") == 0)
        newUser.isAdmin = 1;
    else
        newUser.isAdmin = 0;
    newUser.teamId = 0;
    strcpy(newUser.coachName, "Pending");
    strcpy(newUser.nationality, "Pending");

    fprintf(file, "%s,%s,%d,%d,%s,%s\n", newUser.username, newUser.password, newUser.isAdmin, newUser.teamId, newUser.coachName, newUser.nationality);
    fclose(file);

    strcpy(loggedUser->username, newUser.username);
    strcpy(loggedUser->password, newUser.password);
    loggedUser->isAdmin = newUser.isAdmin;
    loggedUser->teamId = newUser.teamId;
    strcpy(loggedUser->coachName, newUser.coachName);
    strcpy(loggedUser->nationality, newUser.nationality);
    saveSession(newUser.username);

    printf(GREEN "\n\t[>] Account created!\n" RESET);
    return 1;
}

int doLogin(User *loggedUser)
{
    FILE *file = fopen("../database/users.txt", "r");
    if (!file)
    {
        printf(RED "No users registered yet. Create an account first.\n" RESET);
        return 0;
    }

    char inputUser[50], inputPass[50];
    printf(YELLOW "=========================================================================\n" RESET);
    printf(YELLOW "                                 [LOGIN]                                 \n" RESET);
    printf(YELLOW "=========================================================================\n" RESET);
    printf("\tUsername: ");
    fgets(inputUser, 50, stdin);
    inputUser[strcspn(inputUser, "\n")] = 0;

    printf("\tPassword: ");
    fgets(inputPass, 50, stdin);
    inputPass[strcspn(inputPass, "\n")] = 0;

    char line[250];
    int success = 0;

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0;
        char *user = strtok(line, ",");
        char *pass = strtok(NULL, ",");
        char *adminStr = strtok(NULL, ",");
        char *teamStr = strtok(NULL, ",");
        char *coachName = strtok(NULL, ",");
        char *nat = strtok(NULL, ",");

        if (user && pass && adminStr && teamStr && coachName && nat)
        {
            if (strcmp(inputUser, user) == 0 && strcmp(inputPass, pass) == 0)
            {
                strcpy(loggedUser->username, user);
                strcpy(loggedUser->password, pass);
                loggedUser->isAdmin = atoi(adminStr);
                loggedUser->teamId = atoi(teamStr);
                strcpy(loggedUser->coachName, coachName);
                strcpy(loggedUser->nationality, nat);
                success = 1;
                break;
            }
        }
    }
    fclose(file);

    if (success)
    {
        saveSession(loggedUser->username);
        printf(GREEN "\n[>] Login successful! Welcome, %s.\n" RESET, loggedUser->username);
        return 1;
    }
    else
    {
        printf(RED "\n[X] Wrong credentials.\n" RESET);
        return 0;
    }
}

void loadTeams(Team *list, int *total)
{
    FILE *f = fopen("../database/teams.txt", "r");
    *total = 0;
    if (!f)
        return;

    char line[250];
    while (fgets(line, sizeof(line), f))
    {
        line[strcspn(line, "\n")] = 0;
        if (isEmptyOrSpaces(line))
            continue;

        Team *t = &list[*total];
        t->gamesWon = 0;
        t->gamesDrawn = 0;
        t->gamesLost = 0;
        t->cupsWon = 0;

        int fieldsRead = sscanf(line, "%d,%49[^,],%d,%d,%d,%d,%d",
                            &t->id, t->name, &t->overallStrength,
                            &t->gamesWon, &t->gamesDrawn, &t->gamesLost, &t->cupsWon);

        if (fieldsRead < 3)
            continue;

        (*total)++;
    }
    fclose(f);
}

void saveTeams(Team *list, int total)
{
    FILE *f = fopen("../database/teams.txt", "w");
    if (!f)
        return;
    for (int i = 0; i < total; i++)
    {
        fprintf(f, "%d,%s,%d,%d,%d,%d,%d\n", list[i].id, list[i].name, list[i].overallStrength,
                list[i].gamesWon, list[i].gamesDrawn, list[i].gamesLost, list[i].cupsWon);
    }
    fclose(f);
}

void createTeam(Team *list, int *total)
{
    Team newTeam;
    if (*total > 0)
        newTeam.id = list[*total - 1].id + 1;
    else
        newTeam.id = 1;

    printf("\nTeam Name: ");
    fgets(newTeam.name, 50, stdin);
    newTeam.name[strcspn(newTeam.name, "\n")] = 0;

    printf("Overall Strength (0-100): ");
    if (scanf("%d", &newTeam.overallStrength) != 1)
    {
        clearBuffer();
        newTeam.overallStrength = 70;
        printf(YELLOW "Invalid value, using 70 by default.\n" RESET);
    }
    else
    {
        clearBuffer();
    }

    list[*total] = newTeam;
    list[*total].gamesWon = 0;
    list[*total].gamesDrawn = 0;
    list[*total].gamesLost = 0;
    list[*total].cupsWon = 0;
    (*total)++;
    printf(GREEN "Team %s added to the tournament!\n" RESET, newTeam.name);
}

void listTeams(Team *list, int total)
{
    printf(YELLOW "=========================================================================\n" RESET);
    printf(YELLOW "                            [REGISTERED TEAMS]                           \n" RESET);
    printf(YELLOW "=========================================================================\n" RESET);
    printf(BOLD "\tID\tNAME\t\tSTRENGTH\n" RESET);
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < total; i++)
    {
        printf("\t%d\t%-15s\t%d\n", list[i].id, list[i].name, list[i].overallStrength);
    }
}

void showTeamStatistics(Team *list, int total)
{
    if (total == 0)
    {
        printf(RED "No teams registered.\n" RESET);
        return;
    }

    Team *sorted[200];
    for (int i = 0; i < total; i++)
        sorted[i] = &list[i];

    for (int i = 0; i < total - 1; i++)
    {
        for (int j = i + 1; j < total; j++)
        {
            int shouldSwap = 0;
            if (sorted[j]->cupsWon > sorted[i]->cupsWon)
                shouldSwap = 1;
            else if (sorted[j]->cupsWon == sorted[i]->cupsWon &&
                     sorted[j]->gamesWon > sorted[i]->gamesWon)
                shouldSwap = 1;

            if (shouldSwap)
            {
                Team *temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }

    printf(CYAN "=========================================================================\n" RESET);
    printf(CYAN "                            [TEAM STATISTICS]                            \n" RESET);
    printf(CYAN "=========================================================================\n" RESET);
    printf(BOLD "\tID\tNAME\t\t\tW\tD\tL\tCUPS\n" RESET);
    printf("-------------------------------------------------------------------------\n");

    for (int i = 0; i < total; i++)
    {
        Team *t = sorted[i];
        if (t->cupsWon > 0)
            printf(YELLOW);
        printf("\t%d\t%-20s\t%d\t%d\t%d\t%d\n" RESET,
               t->id, t->name, t->gamesWon, t->gamesDrawn, t->gamesLost, t->cupsWon);
    }
    printf(CYAN "=========================================================================\n" RESET);
}

void editTeam(Team *list, int total)
{
    if (total == 0)
    {
        printf(RED "No teams registered to edit.\n" RESET);
        return;
    }

    listTeams(list, total);

    int chosenId;
    printf(YELLOW "\nEnter the ID of the team to edit (0 to cancel): " RESET);
    if (scanf("%d", &chosenId) != 1)
    {
        clearBuffer();
        printf(RED "Invalid input.\n" RESET);
        return;
    }
    clearBuffer();

    if (chosenId == 0)
    {
        printf(CYAN "Operation cancelled.\n" RESET);
        return;
    }

    int index = -1;
    for (int i = 0; i < total; i++)
    {
        if (list[i].id == chosenId)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf(RED "[X] Invalid ID.\n" RESET);
        return;
    }

    char newName[50];
    printf("Current name: %s\n", list[index].name);
    printf("New name (Enter to keep): ");
    fgets(newName, 50, stdin);
    newName[strcspn(newName, "\n")] = 0;
    if (!isEmptyOrSpaces(newName) && strlen(newName) > 0)
    {
        strcpy(list[index].name, newName);
    }

    char strengthBuffer[20];
    printf("Current strength: %d\n", list[index].overallStrength);
    printf("New strength 0-100 (Enter to keep): ");
    fgets(strengthBuffer, sizeof(strengthBuffer), stdin);
    strengthBuffer[strcspn(strengthBuffer, "\n")] = 0;
    if (strlen(strengthBuffer) > 0)
    {
        int newStrength = atoi(strengthBuffer);
        if (newStrength >= 0 && newStrength <= 100)
        {
            list[index].overallStrength = newStrength;
        }
        else
        {
            printf(YELLOW "Value out of range, strength kept.\n" RESET);
        }
    }

    printf(GREEN "Team updated successfully!\n" RESET);
}

int deleteTeam(Team *list, int *total, Player *playerList, int *totalPlayers, int teamId)
{
    int index = -1;
    for (int i = 0; i < *total; i++)
    {
        if (list[i].id == teamId)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
        return 0;

    char deletedName[50];
    strcpy(deletedName, list[index].name);

    for (int i = index; i < *total - 1; i++)
    {
        list[i] = list[i + 1];
    }
    (*total)--;

    int i = 0;
    while (i < *totalPlayers)
    {
        if (playerList[i].originalTeamId == teamId)
        {
            for (int j = i; j < *totalPlayers - 1; j++)
            {
                playerList[j] = playerList[j + 1];
            }
            (*totalPlayers)--;
        }
        else
        {
            i++;
        }
    }

    printf(GREEN "[V] Team '%s' and all its players were permanently deleted.\n" RESET, deletedName);
    return 1;
}

void setStarters(Player *playerList, int totalPlayers, int teamId)
{

    const char *formationNames[5] = {"4-4-2", "4-3-3", "3-5-2", "5-3-2", "3-4-3"};
    int formationDef[5] = {4, 4, 3, 5, 3};
    int formationMed[5] = {4, 3, 5, 3, 4};
    int formationAtt[5] = {2, 3, 2, 2, 3};

    int formationChoice = -1;
    system("cls");
    printf(CYAN "=========================================================================\n" RESET);
    printf(CYAN "                          [CHOOSE FORMATION]                             \n" RESET);
    printf(CYAN "=========================================================================\n" RESET);
    for (int i = 0; i < 5; i++)
        printf("\t%d. %s  (GK 1 | DEF %d | MED %d | ATA %d)\n", i + 1, formationNames[i], formationDef[i], formationMed[i], formationAtt[i]);
    printf("\t0. " YELLOW "No Formation (free, only the 11-player limit applies)" RESET "\n");
    printf("-------------------------------------------------------------------------\n");
    printf(YELLOW "\tChoice (Enter for 4-4-2 by default): " RESET);
    if (scanf("%d", &formationChoice) != 1)
    {
        clearBuffer();
        formationChoice = 1;
    }
    else
    {
        clearBuffer();
    }
    if (formationChoice < 0 || formationChoice > 5)
        formationChoice = 1;

    int freeMode = (formationChoice == 0);
    int idx = freeMode ? 0 : (formationChoice - 1);
    int reqGK = freeMode ? 99 : 1;
    int reqDEF = freeMode ? 99 : formationDef[idx];
    int reqMED = freeMode ? 99 : formationMed[idx];
    int reqATA = freeMode ? 99 : formationAtt[idx];
    const char *formationLabel = freeMode ? "FREE" : formationNames[idx];

    printf(GREEN "\n\t[!] %s%s selected.\n" RESET, freeMode ? "No formation " : "Formation ", formationLabel);
    printf(YELLOW "\tPress Enter to continue..." RESET);
    getchar();

    while (1)
    {
        system("cls");
        int totalStarters = 0;
        int starterGK = 0, starterDEF = 0, starterMED = 0, starterATA = 0;
        for (int i = 0; i < totalPlayers; i++)
        {
            if (playerList[i].teamId == teamId && playerList[i].isStarter == 1)
            {
                totalStarters++;
                if (strcmp(playerList[i].position, "GK") == 0) starterGK++;
                else if (strcmp(playerList[i].position, "DEF") == 0) starterDEF++;
                else if (strcmp(playerList[i].position, "MED") == 0) starterMED++;
                else if (strcmp(playerList[i].position, "ATA") == 0) starterATA++;
            }
        }

        printf(CYAN "=========================================================================\n" RESET);
        printf(CYAN "                  [SET STARTERS - FORMATION %s]\n" RESET, formationLabel);
        printf(CYAN "=========================================================================\n" RESET);
        printf("\tStarters set: " BOLD "%d/11\n" RESET, totalStarters);
        if (!freeMode)
            printf("\tGK: %d/%d   DEF: %d/%d   MED: %d/%d   ATA: %d/%d\n",
                   starterGK, reqGK, starterDEF, reqDEF, starterMED, reqMED, starterATA, reqATA);
        printf(YELLOW "=========================================================================\n" RESET);
        printf(BOLD "\tID\t%-22s POS\tOVR\tSTARTER\n" RESET, "NAME");
        printf("-------------------------------------------------------------------------\n");
        int hasCalled = 0;
        for (int i = 0; i < totalPlayers; i++)
        {
            if (playerList[i].teamId == teamId)
            {
                const char *starterLabel;
                if (playerList[i].isStarter)
                    starterLabel = GREEN "Yes" RESET;
                else
                    starterLabel = "No";
                printf("\t%d\t%-22s %s\t%d\t%s\n",
                       playerList[i].id, playerList[i].name, playerList[i].position,
                       playerList[i].overall,
                       starterLabel);
                hasCalled = 1;
            }
        }
        if (!hasCalled)
        {
            printf(RED "\tYou have no players called up to set as starters.\n" RESET);
            printf(YELLOW "\n\tPress Enter to continue..." RESET);
            getchar();
            break;
        }

        int chosenId;
        printf(YELLOW "\n\tEnter the player ID to mark/unmark as starter (0 to go back): " RESET);
        if (scanf("%d", &chosenId) != 1)
        {
            clearBuffer();
            continue;
        }
        clearBuffer();
        if (chosenId == 0)
            break;

        int found = 0;
        for (int i = 0; i < totalPlayers; i++)
        {
            if (playerList[i].id == chosenId && playerList[i].teamId == teamId)
            {
                found = 1;
                if (playerList[i].isStarter == 1)
                {
                    playerList[i].isStarter = 0;
                    printf(YELLOW "\t[!] %s is no longer a starter.\n" RESET, playerList[i].name);
                }
                else
                {
                    int posLimit = -1;
                    int posCurrent = -1;
                    if (strcmp(playerList[i].position, "GK") == 0) { posLimit = reqGK; posCurrent = starterGK; }
                    else if (strcmp(playerList[i].position, "DEF") == 0) { posLimit = reqDEF; posCurrent = starterDEF; }
                    else if (strcmp(playerList[i].position, "MED") == 0) { posLimit = reqMED; posCurrent = starterMED; }
                    else if (strcmp(playerList[i].position, "ATA") == 0) { posLimit = reqATA; posCurrent = starterATA; }

                    if (totalStarters >= 11)
                    {
                        printf(RED "\t[X] You already have 11 starters set! Unmark one before setting another.\n" RESET);
                    }
                    else if (!freeMode && posLimit != -1 && posCurrent >= posLimit)
                    {
                        printf(RED "\t[X] The %s formation already has %d/%d players for the %s position!\n" RESET,
                               formationLabel, posCurrent, posLimit, playerList[i].position);
                    }
                    else
                    {
                        playerList[i].isStarter = 1;
                        printf(GREEN "\t[!] %s set as starter! (%d/11)\n" RESET, playerList[i].name, totalStarters + 1);
                    }
                }
                savePlayers(playerList, totalPlayers);
                break;
            }
        }
        if (!found)
            printf(RED "\t[X] Invalid ID or player not called up.\n" RESET);
        printf(YELLOW "\n\tPress Enter to continue..." RESET);
        getchar();
    }
    system("cls");
}

void editPlayer(Player *playerList, int totalPlayers, Team *teamList, int totalTeams)
{
    if (totalTeams == 0)
    {
        printf(RED "No teams registered to look up players.\n" RESET);
        return;
    }
    if (totalPlayers == 0)
    {
        printf(RED "No players registered in the system.\n" RESET);
        return;
    }

    printf(YELLOW "=========================================================================\n" RESET);
    printf(YELLOW "                            [REGISTERED TEAMS]                           \n" RESET);
    printf(YELLOW "=========================================================================\n" RESET);
    printf(BOLD "\tID\tSTRENGTH\tNAME\n" RESET);
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < totalTeams; i++)
    {
        printf("\t%d\t%d%%\t%s\n",
               teamList[i].id, teamList[i].overallStrength, teamList[i].name);
    }
    printf("-------------------------------------------------------------------------\n");

    int chosenTeamId;
    printf(YELLOW "\nEnter the team ID of the player you want to edit (0 to cancel): " RESET);
    if (scanf("%d", &chosenTeamId) != 1)
    {
        clearBuffer();
        printf(RED "Invalid input.\n" RESET);
        return;
    }
    clearBuffer();

    if (chosenTeamId == 0)
    {
        printf(CYAN "Operation cancelled.\n" RESET);
        return;
    }

    int teamExists = 0;
    for (int i = 0; i < totalTeams; i++)
    {
        if (teamList[i].id == chosenTeamId)
        {
            teamExists = 1;
            break;
        }
    }

    if (!teamExists)
    {
        printf(RED "[X] Invalid team ID.\n" RESET);
        return;
    }

    system("cls");
    printf(YELLOW "=========================================================================\n" RESET);
    printf(YELLOW "                            [TEAM PLAYERS]                               \n" RESET);
    printf(YELLOW "=========================================================================\n" RESET);
    printf(BOLD "\tID\tOVERALL\tPOSITION\t\tNAME\n" RESET);
    printf("-------------------------------------------------------------------------\n");

    int teamPlayerCount = 0;
    for (int i = 0; i < totalPlayers; i++)
    {
        if (playerList[i].originalTeamId == chosenTeamId)
        {
            printf("\t%d\t%d\t%-15s\t%s\n",
                   playerList[i].id, playerList[i].overall, playerList[i].position, playerList[i].name);
            teamPlayerCount++;
        }
    }
    printf("-------------------------------------------------------------------------\n");

    if (teamPlayerCount == 0)
    {
        printf(YELLOW "This team doesn't have any registered players yet.\n" RESET);
        return;
    }

    int chosenPlayerId;
    printf(YELLOW "\nEnter the player ID to edit (0 to cancel): " RESET);
    if (scanf("%d", &chosenPlayerId) != 1)
    {
        clearBuffer();
        printf(RED "Invalid input.\n" RESET);
        return;
    }
    clearBuffer();

    if (chosenPlayerId == 0)
    {
        printf(CYAN "Operation cancelled.\n" RESET);
        return;
    }

    int index = -1;
    for (int i = 0; i < totalPlayers; i++)
    {
        if (playerList[i].id == chosenPlayerId && playerList[i].originalTeamId == chosenTeamId)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf(RED "[X] Invalid ID or the player does not originally belong to this team.\n" RESET);
        return;
    }

    system("cls");
    printf(CYAN "=========================================================================\n" RESET);
    printf(CYAN "                          [EDITING PLAYER DATA]                          \n" RESET);
    printf(CYAN "=========================================================================\n" RESET);

    char newName[50];
    printf(BOLD " Current name:" RESET " %s\n", playerList[index].name);
    printf(" -> New name (Enter to keep): ");
    fgets(newName, 50, stdin);
    newName[strcspn(newName, "\n")] = 0;
    if (!isEmptyOrSpaces(newName) && strlen(newName) > 0)
    {
        strcpy(playerList[index].name, newName);
    }
    printf("-------------------------------------------------------------------------\n");

    char ageBuffer[20];
    printf(BOLD " Current age:" RESET " %d years\n", playerList[index].age);
    printf(" -> New age (Enter to keep): ");
    fgets(ageBuffer, sizeof(ageBuffer), stdin);
    ageBuffer[strcspn(ageBuffer, "\n")] = 0;
    if (strlen(ageBuffer) > 0)
    {
        int newAge = atoi(ageBuffer);
        if (newAge > 0)
        {
            playerList[index].age = newAge;
        }
    }
    printf("-------------------------------------------------------------------------\n");

    char newPosition[20];
    printf(BOLD " Current position:" RESET " %s\n", playerList[index].position);
    printf(" -> New position (Enter to keep): ");
    fgets(newPosition, 20, stdin);
    newPosition[strcspn(newPosition, "\n")] = 0;
    if (!isEmptyOrSpaces(newPosition) && strlen(newPosition) > 0)
    {
        strcpy(playerList[index].position, newPosition);
    }
    printf("-------------------------------------------------------------------------\n");

    char overallBuffer[20];
    printf(BOLD " Current overall:" RESET " %d\n", playerList[index].overall);
    printf(" -> New Overall 0-100 (Enter to keep): ");
    fgets(overallBuffer, sizeof(overallBuffer), stdin);
    overallBuffer[strcspn(overallBuffer, "\n")] = 0;
    if (strlen(overallBuffer) > 0)
    {
        int newOverall = atoi(overallBuffer);
        if (newOverall >= 0 && newOverall <= 100)
        {
            playerList[index].overall = newOverall;
        }
        else
        {
            printf(YELLOW " Value out of range (0-100), kept unchanged.\n" RESET);
        }
    }
    printf(CYAN "=========================================================================\n" RESET);

    printf(GREEN "\n[V] Player updated successfully!\n" RESET);
}

int deletePlayer(Player *playerList, int *totalPlayers, int playerId)
{
    int index = -1;
    for (int i = 0; i < *totalPlayers; i++)
    {
        if (playerList[i].id == playerId)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
        return 0;

    char deletedName[50];
    strcpy(deletedName, playerList[index].name);

    for (int i = index; i < *totalPlayers - 1; i++)
    {
        playerList[i] = playerList[i + 1];
    }
    (*totalPlayers)--;

    printf(GREEN "[V] Player '%s' was permanently deleted.\n" RESET, deletedName);
    return 1;
}

void createPlayer(Player *playerList, int *totalPlayers, Team *teamList, int totalTeams)
{
    if (totalTeams == 0)
    {
        printf(RED "No teams registered. Create a team before adding players.\n" RESET);
        return;
    }

    printf(YELLOW "=========================================================================\n" RESET);
    printf(YELLOW "                        [CHOOSE THE PLAYER'S TEAM]                       \n" RESET);
    printf(YELLOW "=========================================================================\n" RESET);
    printf(BOLD "\tID\tSTRENGTH\tNAME\n" RESET);
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < totalTeams; i++)
    {
        printf("\t%d\t%d%%\t%s\n",
               teamList[i].id, teamList[i].overallStrength, teamList[i].name);
    }
    printf("-------------------------------------------------------------------------\n");

    int chosenTeamId;
    printf(YELLOW "\nEnter the team ID for the new player (0 to cancel): " RESET);
    if (scanf("%d", &chosenTeamId) != 1)
    {
        clearBuffer();
        printf(RED "Invalid input.\n" RESET);
        return;
    }
    clearBuffer();

    if (chosenTeamId == 0)
    {
        printf(CYAN "Operation cancelled.\n" RESET);
        return;
    }

    int teamIndex = -1;
    for (int i = 0; i < totalTeams; i++)
    {
        if (teamList[i].id == chosenTeamId)
        {
            teamIndex = i;
            break;
        }
    }

    if (teamIndex == -1)
    {
        printf(RED "[X] Invalid team ID.\n" RESET);
        return;
    }

    system("cls");
    printf(YELLOW "=========================================================================\n" RESET);
    printf(YELLOW "                            [REGISTER PLAYER]                            \n" RESET);
    printf(YELLOW "=========================================================================\n" RESET);
    printf(BOLD " Destination Team:" RESET " %s\n", teamList[teamIndex].name);
    printf("-------------------------------------------------------------------------\n");

    Player newPlayer;

    newPlayer.id = (*totalPlayers) + 1;
    newPlayer.teamId = 0;
    newPlayer.originalTeamId = chosenTeamId;

    do {
        printf(" -> Player Name: ");
        fgets(newPlayer.name, 50, stdin);
        newPlayer.name[strcspn(newPlayer.name, "\n")] = 0;
        if (isEmptyOrSpaces(newPlayer.name) || strlen(newPlayer.name) == 0) {
            printf(RED " Name cannot be empty.\n" RESET);
        }
    } while (isEmptyOrSpaces(newPlayer.name) || strlen(newPlayer.name) == 0);
    printf("-------------------------------------------------------------------------\n");

    char ageBuffer[20];
    do {
        printf(" -> Age: ");
        fgets(ageBuffer, sizeof(ageBuffer), stdin);
        ageBuffer[strcspn(ageBuffer, "\n")] = 0;
        newPlayer.age = atoi(ageBuffer);
        if (newPlayer.age <= 0 || newPlayer.age > 100) {
            printf(RED " Invalid age. Enter a real value.\n" RESET);
        }
    } while (newPlayer.age <= 0 || newPlayer.age > 100);
    printf("-------------------------------------------------------------------------\n");

    do {
        printf(" -> Position (e.g. Forward, Midfielder, Defender, Goalkeeper): ");
        fgets(newPlayer.position, 20, stdin);
        newPlayer.position[strcspn(newPlayer.position, "\n")] = 0;
        if (isEmptyOrSpaces(newPlayer.position) || strlen(newPlayer.position) == 0) {
            printf(RED " Position cannot be empty.\n" RESET);
        }
    } while (isEmptyOrSpaces(newPlayer.position) || strlen(newPlayer.position) == 0);
    printf("-------------------------------------------------------------------------\n");

    char overallBuffer[20];
    do {
        printf(" -> Overall (0 - 100): ");
        fgets(overallBuffer, sizeof(overallBuffer), stdin);
        overallBuffer[strcspn(overallBuffer, "\n")] = 0;
        newPlayer.overall = atoi(overallBuffer);
        if (newPlayer.overall < 0 || newPlayer.overall > 100) {
            printf(RED " Invalid value! Overall must be between 0 and 100.\n" RESET);
        }
    } while (newPlayer.overall < 0 || newPlayer.overall > 100);
    printf("-------------------------------------------------------------------------\n");

    newPlayer.goals = 0;
    newPlayer.totalGoals = 0;
    newPlayer.assists = 0;
    newPlayer.totalAssists = 0;
    newPlayer.gamesPlayed = 0;
    newPlayer.isStarter = 0;

    playerList[*totalPlayers] = newPlayer;
    (*totalPlayers)++;

    printf(YELLOW "=========================================================================\n" RESET);
    printf(GREEN "\n[V] Player '%s' registered successfully! (ID: %d | Original: %d | Current: 0)\n" RESET,
           newPlayer.name, newPlayer.id, newPlayer.originalTeamId);
}

void loadPlayers(Player *list, int *total)
{
    FILE *f = fopen("../database/players.txt", "r");

    *total = 0;

    if (!f)
        return;

    while (fscanf(f, "%d,%d,%d,%49[^,],%d,%19[^,],%d,%d,%d,%d,%d,%d,%d\n",
                  &list[*total].id, &list[*total].teamId, &list[*total].originalTeamId,
                  list[*total].name, &list[*total].age, list[*total].position,
                  &list[*total].overall, &list[*total].goals, &list[*total].totalGoals,
                  &list[*total].assists, &list[*total].totalAssists,
                  &list[*total].gamesPlayed, &list[*total].isStarter) != EOF)
    {
        (*total)++;
    }

    fclose(f);
}

void savePlayers(Player *list, int total)
{
    FILE *f = fopen("../database/players.txt", "w");
    if (!f)
        return;
    for (int i = 0; i < total; i++)
    {
        fprintf(f, "%d,%d,%d,%s,%d,%s,%d,%d,%d,%d,%d,%d,%d\n",
                list[i].id, list[i].teamId, list[i].originalTeamId,
                list[i].name, list[i].age, list[i].position,
                list[i].overall, list[i].goals, list[i].totalGoals,
                list[i].assists, list[i].totalAssists,
                list[i].gamesPlayed, list[i].isStarter);
    }
    fclose(f);
}

void listPlayersFromTeam(Player *playerList, int totalPlayers, int teamId)
{
    printf(CYAN "=========================================================================\n" RESET);
    printf(CYAN "                              [TEAM SQUAD]                               \n" RESET);
    printf(CYAN "=========================================================================\n" RESET);
    printf(BOLD "\tID\tNAME\t\t\tPOS\tOVR\tGOALS\tAST\tGAMES\n" RESET);
    printf("-------------------------------------------------------------------------\n");

    int found = 0;

    for (int i = 0; i < totalPlayers; i++)
    {
        if (playerList[i].teamId == teamId || teamId == -1)
        {
            printf("\t%d\t%-20s\t%s\t%d\t%d\t%d\t%d\n",
                   playerList[i].id,
                   playerList[i].name,
                   playerList[i].position,
                   playerList[i].overall,
                   playerList[i].totalGoals,
                   playerList[i].totalAssists,
                   playerList[i].gamesPlayed);
            found = 1;
        }
    }

    if (!found)
    {
        printf("\tNo players found for this team.\n");
    }

    printf(CYAN "=========================================================================\n" RESET);
}

void sortPlayers(Player *list, int total, int criterion)
{
    for (int i = 0; i < total - 1; i++)
    {
        for (int j = 0; j < total - i - 1; j++)
        {
            int currentValue, nextValue;

            switch (criterion)
            {
            case 2:
                currentValue = list[j].totalGoals;
                nextValue = list[j + 1].totalGoals;
                break;
            case 3:
                currentValue = list[j].totalAssists;
                nextValue = list[j + 1].totalAssists;
                break;
            default:
                currentValue = list[j].overall;
                nextValue = list[j + 1].overall;
                break;
            }

            if (currentValue < nextValue)
            {
                Player temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }

    switch (criterion)
    {
    case 2:
        printf(GREEN "\nPlayers sorted by Goals successfully!\n" RESET);
        break;
    case 3:
        printf(GREEN "\nPlayers sorted by Assists successfully!\n" RESET);
        break;
    default:
        printf(GREEN "\nPlayers sorted by Overall successfully!\n" RESET);
        break;
    }
}

void chooseTeam(User *coach, Team *list, int total)
{
    printf(YELLOW "=========================================================================\n" RESET);
    printf(YELLOW "                            [START NEW CAREER]                           \n" RESET);
    printf(YELLOW "=========================================================================\n" RESET);
    readValidField(coach->coachName, 50, "\tCoach Name: ", 3);
    readValidField(coach->nationality, 50, "\tNationality: ", 3);

    printf("\n\tExcellent, Mister %s. Now choose your team:\n", coach->coachName);

    listTeams(list, total);
    printf(YELLOW "\n\tEnter the ID of the team you want to manage: " RESET);
    if (scanf("%d", &coach->teamId) != 1)
    {
        clearBuffer();
        if (total > 0)
            coach->teamId = list[0].id;
        else
            coach->teamId = 1;
        printf(YELLOW "\tInvalid value, default team selected.\n" RESET);
    }
    else
    {
        clearBuffer();
    }

    updateUserInDatabase(coach);
    printf(GREEN "\tContract signed and saved! Good luck in the tournament.\n" RESET);
}