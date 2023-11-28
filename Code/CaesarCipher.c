//Computers Programming (2018/19) - Julius Caesar Cipher Algorithm
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHAR_PER_LINE 81 // Value defined by the prompt as the maximum number of characters per line
#define MAX_LINES 1000       // Value defined by the prompt as the maximum number of lines

// Function prototypes declared after the main function for usage within it
void encrypt(char table[MAX_LINES][MAX_CHAR_PER_LINE], char cipherLetter);
void decrypt(char table[MAX_LINES][MAX_CHAR_PER_LINE], char cipherLetter);
void saveEncryptedFile(char table[MAX_LINES][MAX_CHAR_PER_LINE]);
void saveDecryptedFile(char table[MAX_LINES][MAX_CHAR_PER_LINE]);
void readFromFile(char table[MAX_LINES][MAX_CHAR_PER_LINE]);

int main() {
    char table[MAX_LINES][MAX_CHAR_PER_LINE]; // Define the variable "table" as a 2D array with dimensions specified by MAX_LINES and MAX_CHAR_PER_LINE
    char choice, cipherLetter; // Define variables "choice" and "cipherLetter" as characters

    printf("\n[Ciphers in the style of Caesar]"); // Informative name for the program introduction
    printf("\n\nThis program allows you to encrypt and decrypt text. What operation do you want to perform?");

    do {
        printf("\nEncrypt - enter 'E'\nDecrypt - enter 'D'\n"); // Menu for choosing the operation, prompting the user for their intention
        scanf(" %c", &choice);
        if (choice != 'E' && choice != 'D')
            printf("The program only continues after choosing to encrypt or decrypt. '%c' is invalid!\n", choice); // Informative message when neither 'E' nor 'D' is entered
    } while (choice != 'E' && choice != 'D'); // This loop ensures that the program proceeds only after the user enters 'E' or 'D'

    switch (choice) {
        case 'E': // Functions performed by the program if the "choice" is 'E'
            printf("\nNow, choose a letter to be used as a cipher:");
            scanf(" %c", &cipherLetter);
            readFromFile(table); // Function call to "readFromFile"
            printf("\nYour encrypted text will be saved in Encrypted.txt.");
            encrypt(table, cipherLetter); // Function call to "encrypt"
            saveEncryptedFile(table); // Function call to "saveEncryptedFile"
            break;

        case 'D': // Functions performed by the program if the "choice" is 'D'
            printf("\nNow, choose a letter to be used as a cipher:");
            scanf(" %c", &cipherLetter);
            readFromFile(table); // Function call to "readFromFile"
            printf("\nYour decrypted text will be saved in Decrypted.txt..");
            decrypt(table, cipherLetter); // Function call to "decrypt"
            saveDecryptedFile(table); // Function call to "saveDecryptedFile"
            break;

        default:
            return 0; // In case neither of the previous options is selected, the program returns 0, leading to program termination
    }

    return 0; // The return value is 0, leading to program termination
}

void readFromFile(char table[MAX_LINES][MAX_CHAR_PER_LINE]) { // This function aims to read the file "Text.txt"
    FILE *filePointer = fopen("Text.txt", "r");
    if (filePointer == NULL) {
        perror("Error opening the file Text.txt");
        exit(EXIT_FAILURE);
    }
    printf("File opened...");
    for (int lineIndex = 0; lineIndex < MAX_LINES; lineIndex++) {
        fgets(table[lineIndex], MAX_CHAR_PER_LINE, filePointer); // With fgets, each element of each line from the opened file is "copied" and inserted into a table
        if (feof(filePointer) != 0)
            break; // When the function reads to the end of the file, the "break" statement causes the function to end
    }
    fclose(filePointer); // With fclose, we close the file, making the function no longer have access to it
}

void encrypt(char table[MAX_LINES][MAX_CHAR_PER_LINE], char cipherLetter) { // Function to replace letters in the table with encrypted letters
    int cipherCode = cipherLetter - 'A'; // "cipherCode" denotes the code of the letter we chose for encryption (e.g., cipherCode(A)=0, or cipherCode(M)=12), up to Z(25)

    for (int lineIndex = 0; strlen(table[lineIndex]) != 0; lineIndex++) {
        // Traverse the lines of the table until one is empty, i.e., its length (strlen(table[lineIndex])) is 0
        for (int charIndex = 0; charIndex < strlen(table[lineIndex]); charIndex++) {
            // Traverse each line of the table until its end
            if (table[lineIndex][charIndex] >= 'A' && table[lineIndex][charIndex] <= 'Z') {
                // If the element being traversed is a letter, it will be...
                table[lineIndex][charIndex] = (char)(table[lineIndex][charIndex] + cipherCode);
                // ...replaced by the code of the letter resulting from the encryption process
                if (table[lineIndex][charIndex] > 'Z') {
                    // If the encrypted letter has a code greater than that of 'Z', 26 units are subtracted from its...
                    table[lineIndex][charIndex] = (char)(table[lineIndex][charIndex] - 26);
                    // ...code to obtain the correct encrypted letter
                }
            }
        }
    }
}

void decrypt(char table[MAX_LINES][MAX_CHAR_PER_LINE], char cipherLetter) {
    int cipherCode = cipherLetter - 'A'; // Described in the function above

    for (int lineIndex = 0; strlen(table[lineIndex]) != 0; lineIndex++) {
        // Traverse the lines of the table until one is empty, i.e., its length (strlen(table[lineIndex])) is 0
        for (int charIndex = 0; charIndex < strlen(table[lineIndex]); charIndex++) {
            // Traverse each line of the table until its end
            if (table[lineIndex][charIndex] >= 'A' && table[lineIndex][charIndex] <= 'Z') {
                // If the element being traversed is a letter, it will be...
                table[lineIndex][charIndex] = (char)(table[lineIndex][charIndex] - cipherCode);
                // ...replaced by the code of the letter resulting from the decryption process
                if (table[lineIndex][charIndex] < 'A') {
                    // If the decrypted letter has a code less than that of 'A', 26 units are added to its...
                    table[lineIndex][charIndex] = (char)(table[lineIndex][charIndex] + 26);
                    // ...code to obtain the correct decrypted letter
                }
            }
        }
    }
}

void saveEncryptedFile(char table[MAX_LINES][MAX_CHAR_PER_LINE]) { // Function to create a file containing the encrypted text
    FILE *encryptedFile;
    encryptedFile = fopen("Encrypted.txt", "w"); // Create a file with the name "encrypted.txt" for writing
    for (int lineIndex = 0; strlen(table[lineIndex]) != 0; lineIndex++) {
        // In this loop, with the help of the fputs function, we write the text, after being encrypted, to the created file
        fputs(table[lineIndex], encryptedFile);
        // It is noteworthy to use the "strlen" function, which allows counting the number of characters in each line of the table
    }
    fclose(encryptedFile); // After the desired operations are performed, we close the file with the "fclose" function
}

void saveDecryptedFile(char table[MAX_LINES][MAX_CHAR_PER_LINE]) { // Function to create a file containing the decrypted text
    FILE *decryptedFile;
    decryptedFile = fopen("Decrypted.txt", "w"); // Create a file with the name "decrypted.txt" for writing
    for (int lineIndex = 0; strlen(table[lineIndex]) != 0; lineIndex++) {
        // In this loop, with the help of the fputs function, we write the text, after being decrypted, to the created file
        fputs(table[lineIndex], decryptedFile);
        // It is noteworthy to use the "strlen" function, which allows counting the number of characters in each line of the table
    }
    fclose(decryptedFile); // After the desired operations are performed, we close the file with the "fclose" function
}
