/***********************************
 * Автор: Захаров Никита           *
 * Вариант: в задании не требуется *
 ***********************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Проверка, является ли символ буквой
bool letterConfirmation(char symbol) {
  return (symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z');
}

// Приведение символа к нижнему регистру
char toLowerCase(char symbol) {
  if (symbol >= 'A' && symbol <= 'Z') {
    return symbol + ('a' - 'A');
  }
  
  return symbol;
}

int main() {
    
  const string inputFileName = "text.txt";
  const string outputFileName = "result.txt";

  ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        cout << "Не удалось открыть файл " << inputFileName << endl;
        return 1;
    }

  ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
      cout << "Не удалось открыть файл " << outputFileName << endl;
      return 1;
    }

  int numberOfLettersInTheAlphabet = 26;
  int letterFrequency[numberOfLettersInTheAlphabet] = {0}; // Массив для подсчета количества каждой буквы
  int bigramFrequency[numberOfLettersInTheAlphabet][numberOfLettersInTheAlphabet] = {{0}}; // Матрица для подсчета частоты двухбуквенных сочетаний

  char previousChar = 0; // Предыдущая буква для формирования биграмм
  char currentChar;

  while (inputFile.get(currentChar)) {
    currentChar = toLowerCase(currentChar);
    if (letterConfirmation(currentChar)) {
      // Увеличиваем счетчик для текущей буквы
      ++letterFrequency[currentChar - 'a'];

      // Увеличиваем счетчик для биграммы (предыдущая и текущая буквы)
      if (previousChar != 0) {
        ++bigramFrequency[previousChar - 'a'][currentChar - 'a'];
      }
      
      previousChar = currentChar; // Обновляем предыдущую букву
      
    } else {
      previousChar = 0; // Сброс, если символ не буква
    }
  }

  inputFile.close();

  // Вывод частот букв
  cout << "Частота букв:\n";
  outputFile << "Частота букв:\n";
  for (int indexOfALetterInTheAlphabet = 0; indexOfALetterInTheAlphabet < numberOfLettersInTheAlphabet; ++indexOfALetterInTheAlphabet) {
    if (letterFrequency[indexOfALetterInTheAlphabet] > 0) {
      string line = string(1, 'a' + indexOfALetterInTheAlphabet) + ": " + to_strin (letterFrequency[indexOfALetterInTheAlphabet]) + "\n";
      cout << line;
      outputFile << line;
    }
  }

  // Вывод частот двубуквенных сочетаний
  cout << "\nЧастота двубуквенных сочетаний:\n";
  outputFile << "\nЧастота двубуквенных сочетаний:\n";
  for (int indexOfALetterInTheAlphabet1 = 0; indexOfALetterInTheAlphabet1 < numberOfLettersInTheAlphabet; ++indexOfALetterInTheAlphabet1) {
    for (int indexOfALetterInTheAlphabet2 = 0; indexOfALetterInTheAlphabet2 < numberOfLettersInTheAlphabet; ++indexOfALetterInTheAlphabet2) {
      if (bigramFrequency[indexOfALetterInTheAlphabet1][indexOfALetterInTheAlphabet2] > 0) {
        string line = "" + string(1, 'a' + indexOfALetterInTheAlphabet1) + string(1, 'a' + indexOfALetterInTheAlphabet2) + ": " + to_string(bigramFrequency[indexOfALetterInTheAlphabet1][indexOfALetterInTheAlphabet2]) + "\n";
        cout << line;
        outputFile << line;
      }
    }
  }

  outputFile.close();

  return 0;
}