﻿#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <ctime>
using namespace std;
int EnterIsInCorrect() {
    int players;
    bool isInCorrect;
    do {
        isInCorrect = false;
        cin >> players;
        if (cin.fail() || cin.peek() != '\n') {
            isInCorrect = true;
            cout << "ошибка, повторите попытку: " << endl;
            cin.clear();
            while (cin.get() != '\n');
        }
        if (!isInCorrect && players < 2 || players > 4) {
            isInCorrect = true;
            cout << "ошибка, количество игроков должно быть от 2 до 4, пересмотрите свой выбор, пожалуйста: " << endl;
            while (cin.get() != '\n');
        }
    } while (isInCorrect);
    return players;
}
int EnterPlayers() {
    int players = 0;
    cout << "Введите количество игроков //примечание: количество игроков варируется от 2 до 4. Удачной игры!!!" << endl;
    players = EnterIsInCorrect();
    return players;
}
string wordMapRandom() {
    int indexWord;
    string WordMap[3]{ "кинопанорама", "университет", "документация"};
    srand(static_cast<unsigned int>(time(0)));
    indexWord = rand() % 3;
    cout << WordMap[indexWord] << endl;
    return WordMap[indexWord];
}

/*int Points(const string& startWord, const string& move, vector<string>& enteredWords) {
    int points = 0;

    // Проверяем, было ли слово уже введено
    if (find(enteredWords.begin(), enteredWords.end(), move) != enteredWords.end()) {
        points -= move.size(); // Снимаем очки за повтор
    }
    else {
        bool wordIsCorrect = true;
        map<char, int> startWordLettersAmount;
        map<char, int> moveLettersAmount;

        // Подсчитываем количество букв в исходном слове
        for (char c : startWord) {
            startWordLettersAmount[c]++;
        }
        // Подсчитываем количество букв во введенном слове
        for (char c : move) {
            moveLettersAmount[c]++;
        }

        // Проверяем, есть ли достаточно букв в исходном слове
        for (auto& pair : moveLettersAmount) {
            if (pair.second > startWordLettersAmount[pair.first]) {
                wordIsCorrect = false; // Слово неверное, если букв больше, чем в исходном
                break;
            }
        }

        // Если слово правильно, добавляем очки
        if (wordIsCorrect) {
            points += move.size();
        }
        else {
            // Если слово неверно, вы можете добавить логику для штрафа, но пока просто ничего не делаем.
            // Или вы можете добавить все эти штрафы по вашему усмотрению
        }
    }
    return points;
}*/

int Points(const string& startWord, const string& move, vector<string>& enteredWords) {
    int points = 0;
    if (find(enteredWords.begin(), enteredWords.end(), move) != enteredWords.end()) {
        points -= move.size();
    }
    else {
        bool wordIsCorrect = true;
        map<char, int> startWordLettersAmount;
        map<char, int> moveLettersAmount;

        for (char c : startWord) {
            startWordLettersAmount[c]++;
        }
        for (char c : move) {
            moveLettersAmount[c]++;
        }

        for (char c : move) {
            if (moveLettersAmount[c] > startWordLettersAmount[c]) {
                wordIsCorrect = false;
                break;
            }
        }

        if (wordIsCorrect) {
            points += move.size();
        }
        else {
            for (auto it = moveLettersAmount.begin(); it != moveLettersAmount.end(); ++it) {
                char c = it->first;
                if (moveLettersAmount[c] > startWordLettersAmount[c]) {
                    points -= (moveLettersAmount[c] - startWordLettersAmount[c]);
                }
            }
        }
    }
    return points;
}

void Play(const int& players, const string& startWord) {
    vector <string> enteredWords = { startWord };
    vector <int> playersScore(5);

    int currentPlayer = 1, skipMoveCounter = 0;
    bool onGame = true;
    string move;
    getline(cin, move);

    while (onGame)
    {
        cout << "Ход " << currentPlayer << "-го игрока: ";
        getline(cin, move);
        if (move.empty())
        {
            skipMoveCounter++;
        }
        else
        {
            playersScore[currentPlayer] += Points(startWord, move, enteredWords);
            enteredWords.push_back(move);
            skipMoveCounter = 0;
        }

        cout << "Баллы " << currentPlayer << "-го игрока = " << playersScore[currentPlayer] << endl;
        if (currentPlayer == players)
        {
            currentPlayer = 1;
        }
        else
        {
            currentPlayer++;
        }
        if (skipMoveCounter == players) onGame = false;
    }

    int maxPoints = *max_element(playersScore.begin() + 1, playersScore.begin() + players + 1);
    vector<int> winners;

    for (int i = 1; i <= players; i++) {
        if (playersScore[i] == maxPoints) {
            winners.push_back(i);
        }
    }

    // Проверяем и выводим результат: ничья или победитель
    if (winners.size() > 1) {
        cout << "ИГРА ОКОНЧЕНА. НИЧЬЯ! Игроки: ";
        for (int winner : winners) {
            cout << winner << " ";
        }
        cout << "с " << maxPoints << " баллами!" << endl;
    }
    else {
        cout << "ИГРА ОКОНЧЕНА. ПОБЕДИЛ ИГРОК " << winners[0] << " с " << maxPoints << " баллами!" << endl;
    }
}

int main() {
    setlocale(0, "");
    int players;
    string startWord;
    cout << "Число игроков: ";
    players = EnterPlayers();
    cout << "\nИсходное слово: ";
    startWord = wordMapRandom();
    Play(players, startWord);
    return 0;
}