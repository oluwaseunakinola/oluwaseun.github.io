/*
    --------------------------------------------------------------
    Filename: numericOverflow.cpp
    Purpose: Demonstrates arithmetic operations with logging of overflows and underflows using SQLite3, considering various outcomes of a CS course.
    Author: Oluwaseun Akinola
    Date: 8/10/2023
    --------------------------------------------------------------
*/

#include <iostream>
#include <sqlite3.h>
#include <string>

// Collaborative environment setup (Course Outcome 1)
// Added error callback to facilitate collaborative debugging.
int error_callback(void* notUsed, int argc, char** argv, char** colName) {
    std::cerr << "Error logged for collaborative debugging: ";
    for (int i = 0; i < argc; i++) {
        std::cerr << colName[i] << " = " << argv[i] << "\n";
    }
    return 0;
}

// Enhanced the communication of the SQL execution function for clarity (Course Outcome 2)
/**
 * @brief Executes a given SQL command and returns the status.
 *
 * @param db Pointer to the SQLite3 database.
 * @param sql SQL command to be executed.
 * @return Returns true if successful, false otherwise.
 */
bool execute_sql(sqlite3* db, const std::string& sql) {
    char* errMsg;
    if (sqlite3_exec(db, sql.c_str(), error_callback, nullptr, &errMsg) != SQLITE_OK) {
        // For Course Outcome 2, we're adapting our error message to a technical audience.
        std::cerr << "SQL Execution Error: " << errMsg << "\n";
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

// Algorithmic enhancements (Course Outcome 3)
// Optimized algorithm to detect overflow without performing the addition.
bool is_overflow(int a, int b) {
    return (b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b);
}

bool is_underflow(int a, int b) {
    return is_overflow(a, -b);
}

// Using industry-accepted practices for database interaction (Course Outcome 4)
// The use of prepared statements and parameterized queries is a well-founded technique in database interactions.
void log_to_database(sqlite3* db, const std::string& type, const std::string& operation, const std::string& status) {
    const char* sql = "INSERT INTO logs (type, operation, status) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare SQL statement.\n";
        return;
    }

    sqlite3_bind_text(stmt, 1, type.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, operation.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, status.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to log data.\n";
    }

    sqlite3_finalize(stmt);
}

// Enhancing security and robustness (Course Outcome 5)
// Securely manage arithmetic operations.
void add_numbers(sqlite3* db, int a, int b) {
    if (is_overflow(a, b)) {
        log_to_database(db, "integer", "add", "overflow");
    }
}

void subtract_numbers(sqlite3* db, int a, int b) {
    if (is_underflow(a, b)) {
        log_to_database(db, "integer", "subtract", "underflow");
    }
}

int main() {
    sqlite3* db;

    // Connect to SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << "\n";
        return 1;
    }

    // Create a logs table in the database
    if (!execute_sql(db, "CREATE TABLE logs (id INTEGER PRIMARY KEY, type TEXT, operation TEXT, status TEXT);")) {
        std::cerr << "Failed to create table.\n";
        sqlite3_close(db);
        return 1;
    }

    add_numbers(db, INT_MAX, 1);
    subtract_numbers(db, INT_MIN, 1);

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, "SELECT * FROM logs;", -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Failed to prepare SQL statement.\n";
        sqlite3_close(db);
        return 1;
    }

    // Iterate over the rows in the result set
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string type(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string operation(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        std::string status(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));

        // Print the log entry
        std::cout << "ID: " << id << ", Type: " << type << ", Operation: " << operation << ", Status: " << status << "\n";
    }

    // Finalize the statement and close the database connection
    if (sqlite3_finalize(stmt) != SQLITE_OK) {
        std::cerr << "Failed to finalize statement.\n";
    }
    if (sqlite3_close(db) != SQLITE_OK) {
        std::cerr << "Failed to close database.\n";
    }

    return 0;
}
