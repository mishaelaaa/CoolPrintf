#pragma region Prototypes
/*@ brief printed text in the console, adding the variable values and formatted the */
int coolPrintf(char str[], ...);

/*@ brief Converts a number to a number system with a given basis and converts the result to string */
char* prepNum(unsigned long num, int base, int* size);

/*@ brief converts (adds/removes symbols) the number relative to the string format and returns the finished number as a string */
char* coolPrintInteger(char format[], int formatSize, long num);

/*@ brief converts (adds/removes symbols) the number relative to the string format and returns the finished number as a string */
char* coolPrintFloat(char format[], int formatSize, double num);

/*@ brief converts (adds/removes symbols) from string to string format and returns the transformed string*/
char* coolPrintString(char format[], int formatSize, char* str);

/*@ brief checks whether a symbol has it in a string */
short contains(char str[], int strSize, char sym);
#pragma endregion 