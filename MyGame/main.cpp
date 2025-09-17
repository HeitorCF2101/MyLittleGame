/* Simple Turn-Based Combat System in C++
    This code demonstrates a basic turn-based combat system between two players.
    The players can choose from multiple attacks.
    The game continues until one of the players is defeated, or one of the players chooses to quit.
    The code uses C++23 features and standard libraries for input/output and threading.
*/


#include <iostream>
#include <string>
#include <thread>
#include <limits>
#include "GameResources.cpp"

using namespace std;

int main(){
    // loop variable
    bool running = true;

    // create characters
    Character player1, player2;
    player1.init("Player 1", "(._.)1", 100);
    player2.init("Player 2", "(._.)2", 100);

    //create player input variable
    string playerInput;
    
    //create references to characters
    Character &player1Ref = player1;
    Character &player2Ref = player2;

    // create player1's attacks
    player1Ref.attacks[0].init(nullptr, "magical slash", 20, "raw magic");
    player1Ref.attacks[1].init(nullptr, "thunderbolt", 20, "electric");
    player1Ref.attacks[2].init(nullptr, "fireball", 20, "fire");
    player1Ref.attacks[3].init(nullptr, "ice gauntled", 20, "ice");

    // create player2's attacks
    player2Ref.attacks[0].init(nullptr, "gas bomb", 20, "toxic");
    player2Ref.attacks[1].init(nullptr, "hakai", 20, "godlike");
    player2Ref.attacks[2].init(nullptr, "shadow blast", 20, "dark");
    player2Ref.attacks[3].init(nullptr, "magma punch", 20, "fire");


    // Initial render
    update(player1Ref, player2Ref);

    // main game loop
    while(running == true){
        cout << "Enter 'a' to begin the fight or 'q' to quit: ";
        cin >> playerInput;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        
        if(playerInput == "a"){
            // Player1's turn if it's still alive
            if(player1Ref.isAlive()) combatTurn(player1Ref, player2Ref);
            
            if(player1.health <= 0 || player2.health <= 0){
                running = false;
                break;
            }
            else {
                cout << "Invalid attack choice. Please try again.\n";
                this_thread::sleep_for(chrono::seconds(1)); // Pause for a moment before re-rendering
            }
        //function to update the scene in the loop
        update(player1Ref, player2Ref);
    }
    if(playerInput == "q" || player1.health <= 0 || player2.health <= 0){
            running = false;
            break;
        }
    }

    update(player1Ref, player2Ref);

    // Announce the result of the battle
    if(player1Ref.health <= 0){
        cout << player1Ref.name << " has been defeated!\n";
    }
    if(player2Ref.health <= 0){
        cout << player2Ref.name << " has been defeated!\n";
    }
    
    return 0;
}