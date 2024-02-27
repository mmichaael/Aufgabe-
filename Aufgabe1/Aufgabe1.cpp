#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>


using namespace std;

// Генератор випадкових чисел в межах від min до max
int getRandomNumber(int min, int max) {
    static const double fraction = 1.0 / (RAND_MAX + 1.0);
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

// Функція для генерації пароля
string generatePassword(int length, bool useUppercase, bool useDigits, bool useSpecialChars) {
    string passwordChars = "";
    string uppercaseChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lowercaseChars = "abcdefghijklmnopqrstuvwxyz";
    string digitChars = "0123456789";
    string specialChars = "!@#$%^&*()_+-=[]{}|;:,.<>?";

    if (useUppercase)
        passwordChars += uppercaseChars;
    else
        passwordChars += lowercaseChars;

    if (useDigits)
        passwordChars += digitChars;

    if (useSpecialChars)
        passwordChars += specialChars;

    string password = "";

    // Послідовно додаємо символи до пароля
    for (int i = 0; i < length; ++i) {
        int randomIndex = getRandomNumber(0, passwordChars.length() - 1);
        password += passwordChars[randomIndex];
    }

    return password;
}

int main() {

    srand(static_cast<unsigned int>(time(0))); // Ініціалізація генератора випадкових чисел

    int length;
    bool useUppercase, useDigits, useSpecialChars;

    // Зчитування вхідних даних
    cout << "Enter the length of the password: ";
    cin >> length;

    cout << "Use uppercase letters? (Yes/No): ";
    string uppercaseInput;
    cin >> uppercaseInput;
    useUppercase = (uppercaseInput == "Yes" || uppercaseInput == "yes");

    cout << "Use special characters? (Yes/No): ";
    string digitsInput;
    cin >> digitsInput;
    useDigits = (digitsInput == "Yes" || digitsInput == "yes");

    cout << "Use digits? (Yes/No): ";
    string specialCharsInput;
    cin >> specialCharsInput;
    useSpecialChars = (specialCharsInput == "Yes" || specialCharsInput == "yes");

    // Генерація пароля
    string password = generatePassword(length, useUppercase, useDigits, useSpecialChars);

    // Виведення пароля на екран
    cout << "Generated Password: " << password << endl;

    // Запис пароля у файл (за бажанням користувача)
    cout << "Do you want to save the password to a file? (Yes/No): ";
    string saveToFileInput;
    cin >> saveToFileInput;
    if (saveToFileInput == "Yes" || saveToFileInput == "yes") {
        ofstream outputFile("password.txt");
        if (outputFile.is_open()) {
            outputFile << "Generated Password: " << password << endl;
            outputFile.close();
            cout << "Password saved to password.txt" << endl;
        }
        else {
            cout << "Unable to open file for writing." << endl;
        }
    }

    return 0;
}

