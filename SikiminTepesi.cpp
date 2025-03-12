#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Function to handle user authentication
bool authenticateUser(string& storedUser, string& storedPass) {
    string user, pass, choice;

    cout << "Welcome! Do you want to Log in or Sign up? (Enter 'login' or 'signup'): ";
    cin >> choice;

    if (choice == "login") {
        cout << "Please log in!" << endl;
        cout << "Username: ";
        cin >> user;
        cout << "Password: ";
        cin >> pass;

        if (user != storedUser || pass != storedPass) {
            cout << "Invalid username or password." << endl;
            return false;
        }
        else {
            cout << "Login successful!" << endl;
            return true;
        }
    }
    else if (choice == "signup") {
        cout << "Please sign up!" << endl;
        cout << "Enter a new username: ";
        cin >> user;
        cout << "Enter a new password: ";
        cin >> pass;

        ofstream outFile("credentials.txt", ios::trunc);
        if (outFile) {
            outFile << user << endl;
            outFile << pass << endl;
            outFile.close();
            cout << "Sign-up successful! Your credentials have been saved." << endl;
            storedUser = user;
            storedPass = pass;
            return true;
        }
        else {
            cout << "Error: Could not save credentials!" << endl;
            return false;
        }
    }
    else {
        cout << "Invalid option! Please restart the program and enter either 'login' or 'signup'." << endl;
        return false;
    }
}

// Function to perform currency exchange
void currencyExchange(int& balance) {
    vector<string> currencies = { "USD", "EUR", "CNY" };
    string currency;
    double coefficient = 0;

    cout << "What currency do you use (USD, EUR, CNY): ";
    cin >> currency;

    if (find(currencies.begin(), currencies.end(), currency) == currencies.end()) {
        cout << "Invalid currency. Exiting program.\n";
        return;
    }

    if (currency == "USD") {
        coefficient = 1;
    }
    else if (currency == "EUR") {
        coefficient = 0.93;
    }
    else if (currency == "CNY") {
        coefficient = 0.72;
    }

    cout << "For " << currency << ", the coefficient is " << coefficient << " chips per unit.\n";

    double value;
    cout << "Enter the value of your currency: ";
    cin >> value;

    if (value >= coefficient) {
        int wholeChips = floor(value / coefficient);
        double remainingCurrency = value - (wholeChips * coefficient);

        cout << "This would be " << wholeChips << " chips.\n";
        cout << "Remaining currency: " << remainingCurrency << " " << currency << ".\n";

        balance += wholeChips;
        cout << "Your new balance is: " << balance << " chips.\n";
    }
    else {
        cout << "Dear client, please add more money.\n";
    }
}

// Function to display Blackjack instructions
void displayBlackjackInstructions() {
    cout << "\n----- Blackjack Instructions -----\n";
    cout << "1. In Blackjack, you and the dealer are dealt two cards each.\n";
    cout << "2. The goal is to get as close to 21 as possible without going over.\n";
    cout << "3. You can choose to 'Hit' (draw another card) or 'Stand' (keep your current cards).\n";
    cout << "4. If your cards total over 21, you 'bust' and lose the game.\n";
    cout << "5. If the dealer's cards total over 21, you win.\n";
    cout << "6. If you have a higher total than the dealer, you win.\n";
    cout << "7. If you have the same total as the dealer, it's a tie.\n";
    cout << "Good luck!\n";
}

// Function to play Blackjack
void blackjack(int& balance, int& gamesPlayed, int& gamesWon, int& gamesLost, int& bonusMultiplier) {
    srand(time(0));

    int bet;
    int dealerCard = 2 + (rand() % 9);
    int playerCard = 4 + (rand() % 18);
    int newCard = 2 + (rand() % 9);
    int option;

    // Apply bonus multiplier if any
    bet *= bonusMultiplier;
    cout << "Your game is Blackjack. Type 1 to start the game: ";
    cin >> option;

    if (option == 1) {
        cout << "Enter the bet amount: ";
        cin >> bet;

        if (bet > balance) {
            cout << "Insufficient balance.\n";
            return;
        }

        balance -= bet;
        cout << "Your bet is: " << bet << " chips.\n";
        cout << "Dealer's card: " << dealerCard << endl;
        cout << "Your card: " << playerCard << endl;

        if (playerCard != 21) {
            cout << "Not Blackjack! Hit or Stand? (1 for Hit, 0 for Stand): ";
            cin >> option;

            if (option == 1) {
                playerCard += newCard;
                cout << "Your new card: " << newCard << endl;
                cout << "Your total: " << playerCard << endl;
            }
        }

        // Dealer logic: Dealer stands on 17 or higher
        while (dealerCard < 17) {
            dealerCard += newCard;
        }

        cout << "Dealer's total: " << dealerCard << endl;

        if (playerCard > 21) {
            cout << "You busted! You lost.\n";
            gamesLost++;
        }
        else if (dealerCard > 21 || playerCard > dealerCard) {
            cout << "You win!\n";
            balance += 2 * bet;  // Double the bet for a win
            gamesWon++;
        }
        else if (playerCard == dealerCard) {
            cout << "It's a tie!\n";
            balance += bet;  // Return the bet amount for a tie
        }
        else {
            cout << "Dealer wins!\n";
            gamesLost++;
        }

        gamesPlayed++;
    }
}

// Function to handle bonuses
void handleBonuses(int gamesPlayed, int& balance, int& bonusMultiplier) {
    int bonusChoice;
    cout << "\nAvailable bonuses:\n";
    cout << "1. Extra 30 chips for 50 chips.\n";
    cout << "2. Double the bet for 100 chips (Next round only).\n";
    cout << "3. Extra card in Blackjack for 150 chips.\n";
    cout << "4. Refund half your lost bet for 200 chips.\n";
    cout << "Your balance: " << balance << " chips.\n";
    cout << "Choose a bonus (1-4), or 0 to cancel: ";
    cin >> bonusChoice;

    if (bonusChoice == 1) {
        if (balance >= 50) {
            balance -= 50;
            balance += 30;
            cout << "You bought 30 extra chips for 50 chips! New balance: " << balance << endl;
        }
        else {
            cout << "Not enough chips for this bonus.\n";
        }
    }
    else if (bonusChoice == 2) {
        if (balance >= 100) {
            balance -= 100;
            bonusMultiplier = 2;
            cout << "You bought the double bet bonus! Your next bet will be doubled.\n";
        }
        else {
            cout << "Not enough chips for this bonus.\n";
        }
    }
    else if (bonusChoice == 3) {
        if (balance >= 150) {
            balance -= 150;
            cout << "You bought the extra card bonus! You will get one more card in your next Blackjack game.\n";
        }
        else {
            cout << "Not enough chips for this bonus.\n";
        }
    }
    else if (bonusChoice == 4) {
        if (balance >= 200) {
            balance -= 200;
            cout << "You bought the refund bonus! You will get half your lost bet refunded after the next loss.\n";
        }
        else {
            cout << "Not enough chips for this bonus.\n";
        }
    }
}

// Function to display game statistics
void displayStats(int gamesPlayed, int gamesWon, int gamesLost, int balance) {
    cout << "\nGame Statistics:\n";
    cout << "Games Played: " << gamesPlayed << endl;
    cout << "Games Won: " << gamesWon << endl;
    cout << "Games Lost: " << gamesLost << endl;
    cout << "Balance: " << balance << " chips\n";
}

int main() {
    string storedUser, storedPass;
    storedPass = "2315";  // Default password

    ifstream inFile("credentials.txt");

    // Load user credentials from file if available
    if (inFile) {
        getline(inFile, storedUser);
        getline(inFile, storedPass);
        inFile.close();
    }
    else {
        storedUser = "joe";  // Default user
    }
    // Authenticate user
    if (!authenticateUser(storedUser, storedPass)) {
        return 1;  // Exit if authentication fails
    }

    // Initialize game variables
    int balance = 100;  // Starting balance
    int gamesPlayed = 0, gamesWon = 0, gamesLost = 0;
    int bonusMultiplier = 1;  // Default no bonus multiplier
    int choice;

    while (true) {
        // Display main menu
        cout << "\nGame Menu:\n";
        cout << "1. Start a new game\n";
        cout << "2. View statistics\n";
        cout << "3. Currency exchange\n";
        cout << "4. Buy bonus\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayBlackjackInstructions();  // Show instructions before starting the game
            blackjack(balance, gamesPlayed, gamesWon, gamesLost, bonusMultiplier);
            break;
        case 2:
            displayStats(gamesPlayed, gamesWon, gamesLost, balance);
            break;
        case 3:
            currencyExchange(balance);
            break;
        case 4:
            handleBonuses(gamesPlayed, balance, bonusMultiplier);
            break;


        case 5:
            cout << "Exiting the game. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}