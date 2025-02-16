#include<iostream>
#include<fstream>
#include<string>
#include<random>
#include<cstdlib>
#include<chrono>
using namespace std;
ifstream f1, f2;
string path_f1, path_f2;
void Intro();
int endgame_input = 1;
int RNG(int min, int max);
void Difficulty(int& guess_limit, string& answer);
void Endgame(int guess_limit, int guess_count, int& endgame_input, string answer, bool victory);
void Game(int guess_limit, int& guess_count, string answer, bool& victory);
int main() {
    int guess_limit = 0, guess_count;
    string answer;
    bool victory;

    while (endgame_input != 0) {
        Intro();
        Game(guess_limit, guess_count, answer, victory);
    }

    f1.close();
    f2.close();
    return 0;
}
void Intro() {
    cout << "------------\n|WORDLE 1.0|\n------------\n";
    cout << "\nRules:\n";
    cout << "1. Lowercase letters only\n2. Guesses can only be made with existing english words\n3. You can only use the alphabet\n";
    cout << "4. Symbols: \n+ Matching letter in correct position(green)\n* Matching letter in different position(yellow)\n- Wrong letter(grey)\n";
}
int RNG(int min, int max) {
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937 gen(static_cast<unsigned>(seed));
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}
void Difficulty(int& guess_limit, string& answer) {
    int rng_max = -1, answer_index = -1;
    while (true) {
        cout << "\nChoose your difficulty:\n";
        cout << "Word size(from 2 to 12 letters): ";
        cin >> path_f1;
        path_f2 = path_f1;
        path_f1 = "Words/" + path_f1 + "_Letters.txt";
        path_f2 = "Words/A" + path_f2 + "_Letters.txt";
        f1.close();
        f2.close();
        f1.open(path_f1);
        f2.open(path_f2);
        if (!f1.is_open())
            cout << "Failed to open word database. Try again." << endl;
        else if (!f2.is_open())
            cout << "Failed to open answer database. Try again." << endl;
        else
            break;
    }
    while (!f2.eof()) {
        f2 >> answer;
        rng_max++;
    }
    f2.close();
    f2.open(path_f2);
    answer_index = RNG(0, rng_max);
    for (int i = 0; i < answer_index; i++)
        f2 >> answer;
    while (true) {
        cout << "Guess limit: ";
        cin >> guess_limit;
        if (cin.fail()) {
            cout << "Invalid input. Try again" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        else if (guess_limit < 1) {
            cout << "Invalid input. Try again" << endl;
            continue;
        }
        else
            break;
    }
}
void Endgame(int guess_limit, int guess_count, int& endgame_input, string answer, bool victory) {
    cout << "\n--------------------\n";
    if (victory == true)
        cout << "YOU STAND VICTORIOUS!" << endl;
    else
        cout << "YOU ARE A FAILURE!" << endl;
    cout << "Guess limit: " << guess_limit << endl;
    cout << "Guesses made: " << guess_count << endl;
    cout << "Answer: " << answer << endl;
    cout << "\n[1] Play again\n[0] Quit\n";
    while (true) {
        cin >> endgame_input;
        if (cin.fail()) {
            cout << endgame_input << endl;
            cout << "Invalid input. Try again" << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }
        else if (endgame_input == 0) {
            cout << "GOODBYE" << endl;
            break;
        }
        else if (endgame_input == 1) {
            cout << "RESTARTING" << endl;
            break;
        }
        else
            cout << "Invalid input. Try again." << endl;
    }
}
void Game(int guess_limit, int& guess_count, string answer, bool& victory) {
    Difficulty(guess_limit, answer);
    f2.close();
    f2.open(path_f2);
    string answer_2, guess, guess_2;
    char compare_char;
    bool cheat = false;
    guess_count = 0;
    cout << "\nThe game has begun.\n";
    while (true) {
        cout << "\nWrite your word: \n";
        if (cheat == false)
            cin >> guess;
        else {
            f2 >> guess;
            cout << guess << endl;
        }
        if (guess == "BRUTEFORCE") {
            cheat = true;
            guess_limit = 500000;
            cout << "\n------------------\nBRUTEFORCE ENABLED\n------------------\n";
        }
        else if (answer.length() != guess.length()) {
            cout << "Your guess is of a different lentgth. Try again." << endl;
            continue;
        }
        guess_2 = guess;
        answer_2 = answer;
        string legal_word;
        bool legal_word_status = false;
        f1.close();
        f1.open(path_f1);
        while (!f1.eof()) {
            f1 >> legal_word;
            if (guess == legal_word) {
                legal_word_status = true;
                break;
            }
        }
        if (legal_word_status == false) {
            cout << "Your guess was not found in the vocalbulary. Try again." << endl;
            continue;
        }

        for (int i = 0; i < answer.length(); i++)
            if (guess_2[i] == answer_2[i]) {
                guess_2[i] = '+';
                answer_2[i] = '+';
            }
        for (int i = 0; i < answer.length(); i++) {
            for (int j = 0; j < answer.length(); j++) {
                if (guess_2[i] == '+')
                    break;
                else if (guess_2[i] == answer_2[j]) {
                    guess_2[i] = '*';
                    answer_2[j] = '*';
                }
            }
        }
        for (int i = 0; i < answer.length(); i++) {
            if (guess_2[i] != '+' && guess_2[i] != '*') {
                guess_2[i] = '-';
            }
        }
        guess_count++;
        cout << guess_2 << endl;
        int temp = 0;
        for (int i = 0; i < answer.length(); i++) {
            if (guess_2[i] == '+')
                temp++;
        }
        if (temp == answer.length()) {
            victory = true;
            break;
        }
        if (guess_count == guess_limit) {
            victory = false;
            break;
        }
    }
    Endgame(guess_limit, guess_count, endgame_input, answer, victory);
}
