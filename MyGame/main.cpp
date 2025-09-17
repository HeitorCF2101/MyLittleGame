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
#include "Character.cpp"

using namespace std;

// Character class to hold character properties and methods
/*class Character{
    public:
        string name;
        string sprite;
        int health;

        // Nested Attack structure to hold attack properties and methods
        struct Attack{
            Character* attacker;
            string name;
            int damage;
            string type;

            // Method to initialize an attack
            void init(Character* attacker, const string &attackName, int attackDamage, const string &attackType){
                this->attacker = attacker;
                name = attackName;
                damage = attackDamage;
                type = attackType;
            }

            // Method to execute the attack on a target character
            void attackTarget(Character &target){
                cout << "\n" << name << " hit " << target.name << "!\n" << "and deals " << damage << " " << type << " damage" << "!\n";
                target.health -= damage;
                this_thread::sleep_for(chrono::seconds(5)); // Pause for dramatic effect
            }
        };

        Attack attacks[4]; // Array to hold up to 4 attacks

        // Method to initialize a character
        void init(const string &characterName, const string &characterSprite, int characterHealth){
            name = characterName;
            sprite = characterSprite;
            health = characterHealth;
            
        }

        // Method to render character with its current health
        void renderCharacter(){
            cout << name << "\t" << "Health: " << health << "\n";
            cout << sprite << "\n";
        }

        // Method to check if the character is alive
        bool isAlive() const {
            return health > 0;
        }

};*/

// Function to update and render all characters in the scene
void update(Character &character1, Character &character2){
    system("cls"); // Use "cls" for windows and "clear" for Linux/MacOS
    cout << "Hero vs Enemy\n";
    character1.renderCharacter();
    cout << "\n";
    character2.renderCharacter();
}

void combatTurn(Character &attacker, Character &target){
    cout << "\nChoose an attack:\n";
    for(int i = 0; i < 4; i++){
        cout << i+1 << ". " << attacker.attacks[i].name << " (Damage: " << attacker.attacks[i].damage << ", Type: " << attacker.attacks[i].type << ")\n";
    }
    int attackChoice;
    cin >> attackChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    if(attackChoice >= 1 && attackChoice <= 4){
        this_thread::sleep_for(chrono::seconds(1)); // Pause for a moment before attacks
        attacker.attacks[attackChoice - 1].attackTarget(target);
    }
}

int main(){
    // loop variable
    bool running = true;

    // create characters
    Character player1, player2;
    player1.init("Player 1", "(._.)", 100);
    player2.init("Player 2", "(._.)", 100);

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
        cout << "Enter 'a' to attack or 'q' to quit: ";
        cin >> playerInput;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        
        if(playerInput == "a"){
            // Player1's turn if it's still alive
            if(player1Ref.isAlive()) combatTurn(player1Ref, player2Ref);

            update(player1Ref, player2Ref);

            // Player2's turn if it's still alive
            if(player2Ref.isAlive()) combatTurn(player2Ref, player1Ref);
            
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