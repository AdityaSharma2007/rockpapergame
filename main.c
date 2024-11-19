#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

const char* choices[] = {"Rock", "Paper", "Scissors"};

int get_computer_choice() {
    return rand() % 3; // Returns 0, 1, or 2
}

int get_user_choice() {
    int choice;
    printf("\nEnter your choice:\n");
    printf("0: Rock\n");
    printf("1: Paper\n");
    printf("2: Scissors\n");
    printf("3: Exit Game\n");
    printf("Your choice: ");
    scanf("%d", &choice);
    
    while (choice < 0 || choice > 3) {
        printf(RED "Invalid choice. Please try again (0: Rock, 1: Paper, 2: Scissors, 3: Exit): " RESET);
        scanf("%d", &choice);
    }
    
    return choice;
}

void determine_winner(int user_choice, int computer_choice, int* user_score, int* computer_score) {
    printf("\n" YELLOW "You chose: %s\n" RESET, choices[user_choice]);
    printf(CYAN "Computer chose: %s\n" RESET, choices[computer_choice]);
    
    if (user_choice == computer_choice) {
        printf(MAGENTA "It's a tie!\n" RESET);
    } else if ((user_choice == 0 && computer_choice == 2) ||
               (user_choice == 1 && computer_choice == 0) ||
               (user_choice == 2 && computer_choice == 1)) {
        printf(GREEN "You win this round!\n" RESET);
        (*user_score)++;
    } else {
        printf(RED "You lose this round!\n" RESET);
        (*computer_score)++;
    }
}

void display_score(int user_score, int computer_score, int rounds_played) {
    printf("\n" BLUE "==================== Scoreboard ====================\n" RESET);
    printf("Rounds Played: %d\n", rounds_played);
    printf("You:         %d\n", user_score);
    printf("Computer:    %d\n", computer_score);
    
    if (rounds_played > 0) {
        float win_ratio = (float)user_score / rounds_played * 100;
        printf("Win Ratio:   %.2f%%\n", win_ratio);
    }
    
    printf("====================================================\n" RESET);
}

void print_welcome_message() {
    printf("====================================\n");
    printf("      Welcome to Rock, Paper, Scissors!\n");
    printf("====================================\n");
    printf("Instructions:\n");
    printf("Choose 0 for Rock, 1 for Paper, 2 for Scissors.\n");
    printf("Choose 3 to exit the game at any time.\n");
    printf("====================================\n");
}

int main() {
    srand(time(NULL)); // Seed the random number generator
    int user_score = 0, computer_score = 0;
    int rounds_played = 0;
    char play_again;

    print_welcome_message();

    while (1) {
        int user_choice = get_user_choice();
        
        if (user_choice == 3) {
            printf("\nThank you for playing! Final Score:\n");
            printf("You:         %d\n", user_score);
            printf("Computer:    %d\n", computer_score);
            printf("Total Rounds Played: %d\n", rounds_played);
            printf("====================================\n");
            break;
        }

        int computer_choice = get_computer_choice();
        
        determine_winner(user_choice, computer_choice, &user_score, &computer_score);
        rounds_played++;
        
        display_score(user_score, computer_score, rounds_played);
        
                printf("\nDo you want to play another round? (y/n): ");
        scanf(" %c", &play_again); // The space before %c ignores any whitespace

        // If the user chooses 'n' or 'N', break the loop
        if (play_again == 'n' || play_again == 'N') {
            printf("\nThank you for playing! Final Score:\n");
            printf("You:         %d\n", user_score);
            printf("Computer:    %d\n", computer_score);
            printf("Total Rounds Played: %d\n", rounds_played);
            printf("====================================\n");
            break;
        }
    }

    return 0;
}
