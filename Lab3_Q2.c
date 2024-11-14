// Q2
#include <stdio.h>
#include <string.h>

/* 
   NOTES/PLAN: 
    - Final transaction should be 400. Without the added transcation 
    - -200, the 6th element is not to be processed
    - Added transactions; {..., -400, 100, 200, 300}
    - Final balance is now zero, hence Message is triggered
*/

int main() {
    int balance = 1000; // Initial balance
    int transactions[] = {200, -150, -500, -400, -50, -200, 300, -400, 100, 200, 300}; // Transactions. Included added transactions to display if at any point the balance reaches 0
    int tobeprocessed[11]; // Unprocessed transactions. 11 because total number of transactions
    int processed[11]; // Processed transactions
    int tobeprocessedCount = 0; // Counter for unprocessed transactions. Initialized. For "for loop" where its incremented each time a transaction is unprocessed
    int processedCount = 0; // Counter for processed transactions. Same as above.
    int numTransactions = sizeof(transactions) / sizeof(transactions[0]); // Number of transactions = Total bytes of all transactions / over total bytes for a single transaction

    for (int i = 0; i < numTransactions; i++) {
        int transaction = transactions[i]; // Selects each transaction in order

        // If a withdrawal exceeds the current balance
        if (transaction < 0 && -transaction > balance) {
            printf("Transaction %d. Withdrawal of %d AED is invalid due to insufficient balance.\n\n", i + 1, -transaction);
            tobeprocessed[tobeprocessedCount] = transaction; // Store in tobeprocessed
            tobeprocessedCount++;  
            continue;  // Skip this transaction
        }

        // If at any point the balance reaches 0
        if (balance == 0) {
            printf("Balance has reached 0. No further transactions will be processed.\n\n"); // Message
            tobeprocessed[tobeprocessedCount] = transaction; // Store in tobeprocessed
            tobeprocessedCount++; // Increment count
            break;  // Stop further processing
        }

        // Update the balance for valid transactions
        balance += transaction;
        processed[processedCount] = transaction; // Store the processed transaction
        processedCount++;
    }

    // Print the final balance
    printf("Final balance: %d AED\n\n", balance);

    // Print the processed transactions
    printf("Processed transactions:\n");
    for (int i = 0; i < processedCount; i++) {
        printf("[%d] ", processed[i]);
    }
    printf("\n\n"); 

    // Print the unprocessed transactions
    printf("Unprocessed transactions:\n");
    for (int i = 0; i < tobeprocessedCount; i++) {
        printf("[%d] ", tobeprocessed[i]);
    }
    printf("\n");

    return 0;
}
