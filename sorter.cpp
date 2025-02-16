#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main()
{
    int letter_count;
    cout << "Input letter count: ";
    cin >> letter_count;
    string digit = to_string(letter_count);
    string path_w2, path_a2;
    path_w2 = "Words/" + digit + "_Letters.txt";
    path_a2 = "Words/A" + digit + "_Letters.txt";
    ifstream w1, a1;
    w1.open("Words/Words.txt");
    a1.open("Words/Answers.txt");
    ofstream w2, a2;
    w2.open(path_w2);
    a2.open(path_a2);

    string line;
    int illegal_char;
    char alphabet_small[] = "abcdefghijklmnopqrstuvwxyz", alphabet_big[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    cout << "\n-----\nWORDS: \n-----\n\n";
    while(!w1.eof()) {
        getline(w1, line);
        if(line.length() == letter_count) {
            illegal_char = 0;
            for(char &i : line) {
                for(int j = 0; j < 26; j++) {
                    if(i == alphabet_big[j]) {
                        illegal_char++;
                        i = alphabet_small[j];
                        break;
                    }
                    else if(i == alphabet_small[j]) {
                        illegal_char++;
                        break;
                    }
                }
            }
            if(illegal_char == letter_count) {
                cout << line << endl;
                w2 << line << endl;
            }
        }
    }
    cout << "\n-----\nANSWERS: \n-----\n\n";
    while(!a1.eof()) {
        getline(a1, line);
        if(line.length() == letter_count) {
            illegal_char = 0;
            for(char &i : line) {
                for(int j = 0; j < 26; j++) {
                    if(i == alphabet_big[j]) {
                        illegal_char++;
                        i = alphabet_small[j];
                        break;
                    }
                    else if(i == alphabet_small[j]) {
                        illegal_char++;
                        break;
                    }
                }
            }
            if(illegal_char == letter_count) {
                cout << line << endl;
                a2 << line << endl;
            }
        }
    }
    w1.close();
    w2.close();
    a1.close();
    a1.close();
    return 0;
}
