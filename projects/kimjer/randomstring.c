INSTRUCTIONS: ./runnit.sh

inputchar() produces random number from 0 to 9. inputString() produces random number from 0 to 4. inputchar() sets as the index the random number, called num, for the global array containing the chars to be tested for in testme(). inputString() does the same with chars2() before terminating the string with a null character, and then returns a pointer to memory address of the first char in the string. In order to produce the error message, the conditions of the last if statement in testme() must be met, which is that the state is equal to 9, the first char of the string is equal to 'r', etc. It can be determined that the state can never descend in value, so it will reach the value of 9 quite quickly. This only leaves for the string to spell out 'reset\0' in order for the error message to be activated, which will eventually happen since the loop is forever-going.  
