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

};