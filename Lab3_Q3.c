// Q3
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define NUM_TEAMS 5 
#define SQUAD_SIZE 23 
#define MAX_NAME 26 
#define MAX_CLUB_NAME 21  
#define MAX_POSITION 15

// Structure for date of birth
typedef struct {
    int day;
    int month;
    int year;
} age_t;

// Structure for player information
typedef struct {
    char name[MAX_NAME];
    int kitNumber;
    char club[MAX_CLUB_NAME];
    age_t dob; // Date of birth
    char position[MAX_POSITION];
} player_t;

// Structure for team information
typedef struct {
    char name[MAX_CLUB_NAME];
    player_t players[SQUAD_SIZE];
    int activeSize;
} team_t;

// Function prototypes
void display_menu();
void enroll_club(team_t teams[], int *numTeams);
void add_player(team_t teams[], int numTeams);
void search_update(team_t teams[], int numTeams);
void display_club_statistics(team_t teams[], int numTeams);
void handle_error(const char *message);
bool is_kit_number_valid(int kit);
bool is_date_valid(int day, int month, int year);
int calculate_age(age_t dob);
bool is_name_duplicate(team_t teams[], int numTeams, const char *name);
bool is_kit_duplicate(team_t teams[], int teamIndex, int kit);

int main() {
    team_t teams[NUM_TEAMS];
    int numofTeams = 0;
    int options;

    // Initialize teams
    for (int i = 0; i < NUM_TEAMS; i++) {
        teams[i].activeSize = 0;
    }

    do {
        display_menu();
        scanf("%d", &options);
        getchar(); // For clearing inputs. Basically, clear input buffer

        switch (options) {
            case 1:
                enroll_club(teams, &numofTeams);
                break;
            case 2:
                add_player(teams, numofTeams);
                break;
            case 3:
                search_update(teams, numofTeams);
                break;
            case 4:
                display_club_statistics(teams, numofTeams);
                break;
            case 5:
                printf("Exited manager.\n"); 
                return 0;
            default:
                handle_error("Invalid choice. Choose from options 1-5");
        }
    } while (1);

    return 0;
}

// Display menu function
void display_menu(void) {
    printf("\nLeague Team Application:\n"); // Title
    printf("1. Enroll Clubs\n"); // for void enroll_club(…)
    printf("2. Add Players\n"); // for void add_player(…)
    printf("3. Search and Edit Player\n"); // for void search_update(…)
    printf("4. Display Club Statistics\n"); // for void display_club_statistics(…)
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

// Enroll club function: Registers club name and puts in teams[] array. Notes current count of teams. As long as teams counts doesnt exceed 5, it will register
void enroll_club(team_t teams[], int *numTeams) {
    if (*numTeams >= NUM_TEAMS) {
        handle_error("Maximum number of clubs reached, register is closed for any further clubs.");
        return;
    }

    printf("Enter club name: ");
    fgets(teams[*numTeams].name, MAX_CLUB_NAME, stdin);
    teams[*numTeams].name[strcspn(teams[*numTeams].name, "\n")] = 0;
    teams[*numTeams].activeSize = 0;
    (*numTeams)++;
    printf("Club enrolled.\n");
}

// Add Player function: Adds a player to a selected club
void add_player(team_t teams[], int numTeams) {
    if (numTeams == 0) {
        handle_error("No clubs available");
        return;
    }

    // Display available clubs
    printf("\nAvailable clubs:\n");
    for (int i = 0; i < numTeams; i++) {
        printf("%d. %s\n", i + 1, teams[i].name); // i + 1 because numTeams is from 0-4
    }

    int clubChoice;
    printf("Select club (1-%d): ", numTeams); // Shows total of avialble clubs as options to choose from
    scanf("%d", &clubChoice);
    getchar(); // For clearing input buffer

    // ensure that the choice is valid
    if (clubChoice < 1 || clubChoice > numTeams) {
        handle_error("Invalid club selection");
        return;
    }

    // if choice is 1, teamIndex option would be 0 as it is from 0-4 which is 5 in total
    int teamIndex = clubChoice - 1;

    // Ensure squad size doesn't exceed valid limit
    if (teams[teamIndex].activeSize >= SQUAD_SIZE) {
        handle_error("Squad is full");
        return;
    }

    player_t newPlayer;
    printf("Enter player name (First Last): ");
    fgets(newPlayer.name, MAX_NAME, stdin);
    newPlayer.name[strcspn(newPlayer.name, "\n")] = 0;

    if (is_name_duplicate(teams, numTeams, newPlayer.name)) {
        handle_error("Player name already exists");
        return;
    }

    printf("Enter kit number (1-99): ");
    scanf("%d", &newPlayer.kitNumber);
    getchar(); // For clearing inputs

    if (is_kit_number_valid(newPlayer.kitNumber) == false || is_kit_duplicate(teams, teamIndex, newPlayer.kitNumber)) {
        handle_error("Invalid or duplicate kit number");
        return;
    }

    printf("Enter position: ");
    fgets(newPlayer.position, MAX_POSITION, stdin);
    newPlayer.position[strcspn(newPlayer.position, "\n")] = 0;

    printf("Enter date of birth (DD MM YYYY): ");
    scanf("%d %d %d", &newPlayer.dob.day, &newPlayer.dob.month, &newPlayer.dob.year);
    getchar(); // For clearing inputs

    if (is_date_valid(newPlayer.dob.day, newPlayer.dob.month, newPlayer.dob.year)==false) {
        handle_error("Invalid date");
        return;
    }

    strcpy(newPlayer.club, teams[teamIndex].name);
    teams[teamIndex].players[teams[teamIndex].activeSize] = newPlayer;
    teams[teamIndex].activeSize++;

    printf("Player added to Club.\n");
}

// search_update function: Allows searching for players by name or kit number
void search_update(team_t teams[], int numTeams) {
    if (numTeams == 0) {
        handle_error("No clubs enrolled yet");
        return;
    }

    printf("Search by:\n1. Name\n2. Kit Number\nChoice: ");
    int searchChoice;
    scanf("%d", &searchChoice);
    getchar(); // For clearing inputs
    bool found = false;
    int foundTeamIndex = -1, foundPlayerIndex = -1;

    if (searchChoice == 1) {
        char searchName[MAX_NAME];
        printf("Enter player name: ");
        fgets(searchName, MAX_NAME, stdin);
        searchName[strcspn(searchName, "\n")] = 0;

        for (int i = 0; i < numTeams && found == false; i++) {
            for (int j = 0; j < teams[i].activeSize; j++) {
                if (strcasecmp(teams[i].players[j].name, searchName) == 0) {
                    foundTeamIndex = i;
                    foundPlayerIndex = j;
                    found = true;
                    break;
                }
            }
        }
    } else if (searchChoice == 2) {
        int searchKit;
        printf("Enter kit number: ");
        scanf("%d", &searchKit);
        getchar(); // For clearing inputs

        for (int i = 0; i < numTeams && found == false; i++) {
            for (int j = 0; j < teams[i].activeSize; j++) {
                if (teams[i].players[j].kitNumber == searchKit) {
                    foundTeamIndex = i;
                    foundPlayerIndex = j;
                    found = true;
                    break;
                }
            }
        }
    } else {
        handle_error("Invalid search choice");
        return;
    }

    if (found== false) {
        handle_error("Player not found");
        return;
    }

    // Display current player details
    player_t *player = &teams[foundTeamIndex].players[foundPlayerIndex];
    printf("\nPlayer found:\n");
    printf("Name: %s\nKit Number: %d\nPosition: %s\n", 
           player->name, player->kitNumber, player->position); // -> operator is used to access members of a structure
    printf("DOB: %d/%d/%d\n", 
           player->dob.day, player->dob.month, player->dob.year);

    // Update menu
    printf("\nWhat would you like to update?\n");
    printf("1. Name\n2. Kit Number\n3. Position\n4. Date of Birth\n5. Cancel\n");
    printf("Choice: ");
    
    int updateChoice;
    scanf("%d", &updateChoice);
    getchar(); // For clearing inputs

    // Switch Statement for updating player info menu
    switch (updateChoice) {
        case 1: {
            printf("Enter new name: ");
            char newName[MAX_NAME];
            fgets(newName, MAX_NAME, stdin);
            newName[strcspn(newName, "\n")] = 0;
            if (is_name_duplicate(teams, numTeams, newName) == false) {
                strcpy(player->name, newName);
                printf("Name updated successfully!\n");
            } else {
                handle_error("Name already exists");
            }
            break;
        }   
        case 2: {
            printf("Enter new kit number: ");
            int newKit;
            scanf("%d", &newKit);
            getchar(); // For clearing inputs
            if (is_kit_number_valid(newKit) && is_kit_duplicate(teams, foundTeamIndex, newKit) == false) {
                player->kitNumber = newKit;
                printf("Kit number updated successfully!\n");
            } else {
                handle_error("Invalid or duplicate kit number");
            }
            break;
        }
        case 3: {
            printf("Enter new position: ");
            fgets(player->position, MAX_POSITION, stdin);
            player->position[strcspn(player->position, "\n")] = 0;
            printf("Position updated successfully!\n");
            break;
        }
        case 4: {
            printf("Enter new date of birth (DD MM YYYY): ");
            int day, month, year;
            scanf("%d %d %d", &day, &month, &year);
            getchar(); // For clearing inputs
            if (is_date_valid(day, month, year)) {
                player->dob.day = day; // -> operator is used to access members of a structure
                player->dob.month = month;
                player->dob.year = year;
                printf("Date of birth updated successfully!\n");
            } else {
                handle_error("Invalid date");
            }
            break;
        }
        case 5:
            printf("Update cancelled.\n");
            break;
        default:
            handle_error("Invalid choice");
    }
}

// display_club_statistics function: Shows the number of players in each club, ages, and details of each player
void display_club_statistics(team_t teams[], int numTeams) {
    if (numTeams == 0) {
        handle_error("No clubs enrolled yet");
        return;
    }

    for (int i = 0; i < numTeams; i++) {
        printf("\n%s\n", teams[i].name);
        printf("Number of players: %d\n", teams[i].activeSize);

        if (teams[i].activeSize > 0) {
            // Calculate average age
            int totalAge = 0;
            for (int j = 0; j < teams[i].activeSize; j++) {
                totalAge += calculate_age(teams[i].players[j].dob);
            }
            float avgAge = (float)totalAge / teams[i].activeSize;
            printf("Average age: %.1f years\n\n", avgAge);

            // Display player details
            printf("Player Details:\n");
            printf("%-25s %-10s %-15s %-10s\n", "Name", "Kit", "Position", "Age"); // Positioning titles in proper places directly above there data
            for (int j = 0; j < teams[i].activeSize; j++) {
                printf("%-25s %-10d %-15s %-10d\n", teams[i].players[j].name, teams[i].players[j].kitNumber, teams[i].players[j].position, calculate_age(teams[i].players[j].dob));
            }
        }
    }
}

// handle_error function: for printing error messages
void handle_error(const char *message) {
    printf("Error: %s\n", message);
}

// is_kit_number_valid function: To ensure kit numbers are within range of 1-99
bool is_kit_number_valid(int kit) {
    if (kit >= 1 && kit <= 99) {
        return true;
    } else {
        return false;
    }
}

// Ensure age is correct. Prevents user from entering an unrealsitic birth date
bool is_date_valid(int day, int month, int year) {
    if (month < 1 || month > 12) {
        return false;
    }
    if (day < 1) { 
        return false;
    }

    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        daysInMonth[1] = 29;
        
    return day <= daysInMonth[month-1] && year >= 1900 && year <= 2024;
}

int calculate_age(age_t dob) {
    // Using 2024 as the current year for simplicity
    int age = 2024 - dob.year;
    if (dob.month > 11 || (dob.month == 11 && dob.day > 10))
        age--;
    return age;
}

// For avoidinng duplicate names from being inputed. If strcasecmp(s1, s2) where s1 == s2, it returns 0. If name is a duplicate it will return true.
bool is_name_duplicate(team_t teams[], int numTeams, const char *name) {
    for (int i = 0; i < numTeams; i++) {
        for (int j = 0; j < teams[i].activeSize; j++) {
            if (strcasecmp(teams[i].players[j].name, name) == 0) {
                return true;
            }
        }
    }
    return false;
}

// Similar to function above but for kit numbers
bool is_kit_duplicate(team_t teams[], int teamIndex, int kit) {
    for (int i = 0; i < teams[teamIndex].activeSize; i++) {
        if (teams[teamIndex].players[i].kitNumber == kit) {
            return true;
        }
    }
    return false;
}