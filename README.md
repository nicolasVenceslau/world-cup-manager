# World Cup Manager

A football (soccer) team and player management system written in C, featuring match simulation and a full World Cup tournament. Built to run in the Windows terminal.

## How to compile and run

> ⚠️ This project was built for **Windows** (uses commands like `cls` and `chcp`).

In your terminal (Command Prompt, PowerShell, or Git Bash), inside the project folder:

```bash
gcc main.c -o world-cup-manager
```

Then run it:

```bash
./world-cup-manager
```

## Features

### User system
- User registration and login
- Persistent session (no need to log in every time)
- **Administrator** and **Coach** profiles

### Administrator
- Create, list, edit, and delete teams
- Create, edit, and delete players
- Save system changes

### Coach
- Choose a team to manage
- Build the squad: call up and release players (15-player limit per team)
- Set starting lineup
- View team statistics
- Simulate matches
- Compete in the World Cup (group stage + knockout stage)
- Track player goals and assists

### Matches
- Match results simulated based on team strength (`overallStrength`)
- Goal scorers and assists drawn randomly
- Group standings tables

## Project structure

| File | Description |
|---|---|
| `main.c` | Main menu and game loop |
| `manager.c` / `manager.h` | User, team, and player management |
| `matches.c` / `matches.h` | Match simulation and World Cup logic |
| `inicializate.c` | Default system data initialization |

## Author

Nicolas Venceslau
