#include <stdio.h>
#include <stdbool.h>

// Function to print the flag
void flag() {
  printf("Congratulations! You've found the secret stash flag!\n");
  printf("FLAG{C4ndy_Cr4sh_0verfl0w_D3l1ght}");
}

// VIP function
void VIP() {
  printf("Welcome, Candy VIP user!\n");
  flag();
}

// Candy stash struct. Tracks the user's candy count.
struct candy_stash {
  int candy_count;
};

// Get the user's candy count
int get_candy_count(struct candy_stash *stash) {
  return stash->candy_count;
}

// Update the stash when candy is removed or added
int update_candy_count(int amount, struct candy_stash *stash) {
  stash->candy_count = stash->candy_count + amount; // Adding here allows for negative inputs
  return stash->candy_count;
}

// Handle removing candy
void remove_candy(struct candy_stash *stash) {
  int candy_to_remove;

  printf("How much candy would you like to remove?\n> ");
  scanf("%d", &candy_to_remove);

  // Ensure the user has enough candy to complete the removal
  if (candy_to_remove > get_candy_count(stash)) {
    printf("Sorry, you do not have enough candy to remove that amount.\n");
    return;
  }

  printf("Removing %d pieces of candy...\n", candy_to_remove);
  update_candy_count(-candy_to_remove, stash);
  printf("You now have %d pieces of candy in your stash.\n", get_candy_count(stash));
}

// Handle adding candy
void add_candy(struct candy_stash *stash) {
  int candy_to_add;

  printf("How much candy would you like to add?\n> ");
  scanf("%d", &candy_to_add);

  if (candy_to_add < 0) {
    printf("You can't add a negative amount of candy!\n");
    return;
  }

  printf("Adding %d pieces of candy to your stash...\n", candy_to_add);
  update_candy_count(candy_to_add, stash);
  printf("You now have %d pieces of candy in your stash.\n", get_candy_count(stash));
}

int main() {
  struct candy_stash stash;
  int choice_num;

  // Set up the user's stash with a default amount
  stash.candy_count = 100;

  // Greeting the user
  printf("Welcome to your Secret Candy Stash!\n");
  printf("You currently have %d pieces of candy.\n\n", get_candy_count(&stash));

  // Main game loop
  while (true) {
    // Display options
    printf("\nWhat would you like to do?\n");
    printf("[1] Remove candy\n");
    printf("[2] Add candy\n");
    printf("[3] Quit\n");
    printf("> ");

    // Get the user's choice
    if (scanf("%d", &choice_num) != 1) {
      // Clear invalid input
      while (getchar() != '\n');
      printf("Invalid input. Please enter a valid choice.\n");
      continue;
    }

    // Process the user's choice
    if (choice_num == 1) {
      remove_candy(&stash);
    } else if (choice_num == 2) {
      add_candy(&stash);
    } else if (choice_num == 3) {
      printf("Thank you for using your Candy Stash. Have a sweet day!\n");
      break;
    } else {
      printf("Invalid choice. Please select 1, 2, or 3.\n");
    }

    // Check for VIP status (stash overflow vulnerability)
    if (get_candy_count(&stash) > 1000000) {
      VIP();
    }
  }

  return 0;
}
