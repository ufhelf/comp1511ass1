// cs_submarine.c
// Written by Oliver Wen z567170 on <INSERT DATE>
//
// Description: <INSERT DESCRIPTION OF PROGRAM>

// Provided Libraries
#include <stdio.h>

// Add your own #include statements below this line
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

// Provided constants
#define ROWS 10
#define COLS 10

#define NO_SUBMARINE -1

// Add your own #define constants below this line


// Provided Enums
// Enum for features on the game board
enum entity {
    OCEAN,
    SEAWEED,
    TREASURE,
    EXIT_LOCKED,
    EXIT_UNLOCKED,
    AIR_POCKET,
    JELLYFISH,
    ANGLERFISH,
    MINE,
    HIDDEN,
    SEEKING_MINE,
    CURRENT_UP,
    CURRENT_DOWN,
    CURRENT_LEFT,
    CURRENT_RIGHT,
    TORPEDO
};

// Add your own enums below this line


// Represents a tile/cell on the game board
struct tile {
    enum entity entity;
};

// Add your own structs below this line
typedef struct Coord{
    int x;
    int y;
} Coord;


typedef struct GameState {
    Coord submarine_position;
} GameState;


// Provided Function Prototypes
void print_welcome(void);
void initialise_board(struct tile board[ROWS][COLS]);
void print_board(
    struct tile board[ROWS][COLS], 
    int submarine_row, 
    int submarine_col
);
void print_submarine_stats(
    int oxygen,
    int treasure_collected,
    int moves,
    int torpedoes
);
void print_map_statistics(
    int num_treasure,
    int num_air_pockets,
    int num_seaweed,
    int num_mines,
    int num_jellyfish,
    int num_anglerfish,
    int num_exits
);
void print_board_line(void);
void print_tile_spacer(void);
void print_board_header(void);
char *get_name_from_type(enum entity entity_type);
void print_win_message(void);
void print_loss_message(enum entity entity_type);
void print_oxygen_loss_message(void);

// Add your function prototypes below this line
char *entity_to_display(enum entity type);

//Restoring turns ()

// Provided sample main() function (you will need to modify this)
int main(void) {
    print_welcome();

    struct tile board[ROWS][COLS];
    initialise_board(board);

    //Main game loop
    while(true) {
        print_board(board, NO_SUBMARINE, NO_SUBMARINE);
        break;
    }

    return 0;
}

// Add your function definitions below this line

//This is stupid
//Ask if i can swap to switch statement
char *entity_to_display(enum entity type){
    if (type == SEAWEED) {
        return ")|(";
    } else if (type == TREASURE) {
        return "[$]";
    } else if (type == EXIT_LOCKED) {
        return "[X]";
    } else if (type == EXIT_UNLOCKED) {
        return "[^]";
    } else if (type == AIR_POCKET) {
        return "oOo";
    } else if (type == JELLYFISH) {
        return "(~)";
    } else if (type == ANGLERFISH) {
        return "><>";
    } else if (type == MINE) {
        return "(*)";
    } else if (type == HIDDEN) {
        return "###";
    } else if (type == SEEKING_MINE) {
        return "{*}";
    } else if (type == CURRENT_UP) {
        return "^^^";
    } else if (type == CURRENT_DOWN) {
        return "vvv";
    } else if (type == CURRENT_LEFT) {
        return "<<<";
    } else if (type == CURRENT_RIGHT) {
        return ">>>";
    } else if (type == TORPEDO) {
        return "-*-";
    } else {
        return "   ";
    }
}

// =============================================================================
// EDITABLE Provided Functions
// =============================================================================

// Given a 2D board array:
// Initialise all tile entities to OCEAN.
void initialise_board(struct tile board[ROWS][COLS]) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            board[row][col].entity = OCEAN;
        }
    }
}

// Prints the game board, showing the submarine's position and entities.
void print_board(struct tile board[ROWS][COLS], int submarine_row, int submarine_col) {
    print_board_line();
    print_board_header();
    print_board_line();

    //Seperate into its own function
    for (int row = 0; row < ROWS; row++) {
        print_tile_spacer();
        for (int col = 0; col < COLS; col++) {
            printf("|");
            struct tile _tile = board[row][col];

            if (row == submarine_row && col == submarine_col) {
                printf("[o>");
            } else {
                printf("%s", entity_to_display(_tile.entity));
            }
        }
        printf("|\n");
    }
    print_board_line();
    return;
}

// Print out the submarine's stats
void print_submarine_stats(
    int oxygen, 
    int treasure_collected, 
    int moves, 
    int torpedoes
) {
    printf("+=======================================+\n");
    printf("|        >> SUBMARINE STATUS <<         |\n");
    printf("+=======================================+\n");
    printf("|  Oxygen     : %-23d |\n", oxygen);
    printf("|  Treasure   : %-23d |\n", treasure_collected);
    printf("|  Moves      : %-23d |\n", moves);
    printf("|  Torpedoes  : %-23d |\n", torpedoes);
    printf("+=======================================+\n");
    return;
}

// Prints how much of each entity type is left on the board
void print_map_statistics(
    int num_treasure, 
    int num_air_pockets, 
    int num_seaweed, 
    int num_mines, 
    int num_jellyfish, 
    int num_anglerfish, 
    int num_exits
) {
    printf("+=======================================+\n");
    printf("|         >> MAP STATISTICS <<          |\n");
    printf("+=======================================+\n");
    printf("|  Treasure     : %-21d |\n", num_treasure);
    printf("|  Air Pockets  : %-21d |\n", num_air_pockets);
    printf("|  Seaweed      : %-21d |\n", num_seaweed);
    printf("+---------------------------------------+\n");
    printf("|  Mines        : %-21d |\n", num_mines);
    printf("|  Jellyfish    : %-21d |\n", num_jellyfish);
    printf("|  Anglerfish   : %-21d |\n", num_anglerfish);
    printf("+---------------------------------------+\n");
    printf("|  Exits        : %-21d |\n", num_exits);
    printf("+=======================================+\n");
    return;
}

// =============================================================================
// NON-EDITABLE Provided Functions
// (Recommended to NOT EDIT the functions below this line!!)
// =============================================================================

// Prints the game win message
void print_win_message(void) {
    printf("+=======================================+\n");
    printf("|  *** ESCAPED WITH THE TREASURE! ***   |\n");
    printf("+=======================================+\n");
}

// Prints the game loss message given an entity type
void print_loss_message(enum entity entity_type) {
    printf("+=======================================+\n");
    printf("        >> Sunk by a %s! <<\n"
        , get_name_from_type(entity_type));
    printf("+=======================================+\n");
}

// Prints the game loss message for running out of oxygen
void print_oxygen_loss_message(void) {
    printf("+=======================================+\n");
    printf("        >> Out of oxygen! <<\n");
    printf("+=======================================+\n");
}

// Prints the welcome banner.
void print_welcome(void) {
    printf("=========================================\n");
    printf("    o                               o    \n");
    printf("   o o    |===================|    o o   \n");
    printf("  o   o   |    Welcome to     |   o   o  \n");
    printf("   o o    |   CS SUBMARINE    |    o o   \n");
    printf("    o     |===================|     o    \n");
    printf("  ~~~~~                           ~~~~~  \n");
    printf("=========================================\n\n");
}

// Helper function for print_board().
void print_board_header(void) {
    printf("|***  >> C S   S U B M A R I N E <<  ***|\n");
}

// Helper function for print_board().
void print_board_line(void) {
    printf("+");
    for (int col = 0; col < COLS; col++) {
        printf("===+");
    }
    printf("\n");
}

// Helper function for print_board().
void print_tile_spacer(void) {
    printf("+");
    for (int col = 0; col < COLS; col++) {
        printf("---+");
    }
    printf("\n");
}

// Returns the name of an entity given its type
char *get_name_from_type(enum entity entity_type) {
    if (entity_type == JELLYFISH) {
        return "Jellyfish";
    } else if (entity_type == ANGLERFISH) {
        return "Anglerfish";
    } else if (entity_type == MINE) {
        return "Mine";
    } else if (entity_type == SEEKING_MINE) {
        return "Seeking Mine";
    } else if (entity_type == TORPEDO) {
        return "Torpedo";
    } else {
        return "Invalid";
    }
}