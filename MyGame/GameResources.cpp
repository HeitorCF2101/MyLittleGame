#include <iostream>
#include <string>
#include <thread>

using namespace std;

// Character class to hold character properties and methods
class Character{
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
                this_thread::sleep_for(chrono::seconds(2)); // Pause for dramatic effect
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
        
        //Method to heal the character if he chooses to do it
        void heal(){
            cout << "\n" << name << " decided to heal itself and recieve +10 health\n"; 
            health += 10;
        }

};

// Function to update and render all characters in the scene
void update(Character &character1, Character &character2){
    system("clear"); // Use "cls" for windows and "clear" for Linux/MacOS
    cout << "The Players Battle\n";
    character1.renderCharacter();
    cout << "\n";
    character2.renderCharacter();
}

// Function to make a combat turn
void combatTurn(Character &attacker, Character &target){
    cout << "\n" << attacker.name << " Choose an action:\n" << "attacks:\n";
    for(int i = 0; i < 4; i++){
        cout << i+1 << ". " << attacker.attacks[i].name << " (Damage: " << attacker.attacks[i].damage << ", Type: " << attacker.attacks[i].type << ")\n";
    }
    cout << "\n" << "5. use heal power\n";
    int actionChoice;
    cin >> actionChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    if(actionChoice >= 1 && actionChoice <= 4){
        this_thread::sleep_for(chrono::seconds(1)); // Pause for a moment before attacks
        attacker.attacks[actionChoice - 1].attackTarget(target);
    }
    else if(actionChoice == 5){
        attacker.heal();
    }

    update(attacker, target);

    if(target.isAlive()) combatTurn(target, attacker);

}