
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//primary data structure
struct Enquiry {
    int enquiryID;
    int studentNo;
    long int studentContact;
    string studentName;
    string studentEmail;
    string enquiry;
    string date;

    struct Enquiry* nextPtr;

};

typedef struct Enquiry enquiry;
typedef enquiry* enquiryPtr;

//secondary data structure
struct removedEnquiries {
    enquiry* front, * rear;
    int enquiryID;
    int studentNo;
    long int studentContact;
    string studentName;
    string studentEmail;
    string enquiry;
    string date;
    struct removedEnquiries* nextPtr;
};
typedef struct removedEnquiries removedEnq;
typedef removedEnq* queuePtr;

//third data structure
struct enquiryStatus {
    enquiry* front, * rear;
    int enquiryID;
    string studentName;
    long int studentContact;
    string action;
    string status;
    struct enquiryStatus* nextPtr;
};
typedef struct enquiryStatus enqStatus;
typedef enqStatus* statusPtr;

// this is to check if an enquiry is already in the system.
bool checkID(enquiryPtr* startPtr, int enquiryID) {
    enquiryPtr tempPtr = *startPtr;
    if (tempPtr == NULL) { //check if the head is null
        return false;
    }

    else {
        enquiryPtr temp = new enquiry;
        temp = *startPtr;
        while (temp != NULL) {
            if (temp->enquiryID == enquiryID) {
                return true;
            }
            temp = temp->nextPtr;
        }


    }
    return false;
}
// this is to get user confirmation before exiting a function
void exitLoop() {
    char c;
    cout << "\tPress 'Y' to exit... ";

    do {
        cin >> c;
        c = toupper(c);
        if (c != 'Y') {
            cout << "\tInvalid entry. Please re-enter.";
        }
    } while (c != 'Y');

}
//this is to queue the removed enquiries to secondary data structure
void queueEnq(enquiryPtr enq, queuePtr* front, queuePtr* rear) {
    queuePtr newPtr = new removedEnq;

    if (newPtr != NULL) {
        newPtr->enquiryID = enq->enquiryID;
        newPtr->studentNo = enq->studentNo;
        newPtr->studentContact = enq->studentContact;
        newPtr->studentName = enq->studentName;
        newPtr->studentEmail = enq->studentEmail;
        newPtr->enquiry = enq->enquiry;
        newPtr->date = enq->date;


        if (*front == NULL) {
            *front = *rear = newPtr;
            (*rear)->nextPtr = NULL;

        }
        else {
            (*rear)->nextPtr = newPtr;
            *rear = newPtr;
            (*rear)->nextPtr = NULL;

        }
    }
    else {
        cout << "Could not save enquiry due to insufficient memory." << endl;
    }
    delete(enq);
    cout << "\tSuccessfully removed the enquiry. " << endl;


}
// this method displays all removed enquiries in queue
void viewRemovedEnq(queuePtr* front, queuePtr* rear) {
    queuePtr temp = *front;
    if (temp == NULL) {
        cout << "\tThere are no removed enquiries in the system." << endl;
    }
    else {
        while (temp != NULL) {
            cout << "\tEnquiry ID      :" << temp->enquiryID << endl;
            cout << "\tStudent No      :" << temp->studentNo << endl;
            cout << "\tStudent Contact :" << temp->studentContact << endl;
            cout << "\tStudent Name    :" << temp->studentName << endl;
            cout << "\tEmail           :" << temp->studentEmail << endl;
            cout << "\tEnquiry         :" << temp->enquiry << endl;
            cout << "\tDate            :" << temp->date << endl;
            cout << "\t\t  -------------------------------------" << endl;
            cout << endl;
            temp = temp->nextPtr;
        }
    }


}
// this method stores enquiry status in the queue (third data structure)
void queueEnqStatus(enquiryPtr* startPtr, statusPtr* front, statusPtr* rear, int enqId,
    string action, string status) {
    enquiryPtr currentPtr = NULL;

    statusPtr newPtr = new enqStatus;
    currentPtr = *startPtr;

    while (enqId != currentPtr->enquiryID) {

        currentPtr = currentPtr->nextPtr;
    }

    if (currentPtr != NULL) {
        newPtr->enquiryID = enqId;
        newPtr->studentName = currentPtr->studentName;
        newPtr->studentContact = currentPtr->studentContact;
        newPtr->action = action;
        newPtr->status = status;

        if (*front == NULL) {
            *front = *rear = newPtr;
            (*rear)->nextPtr = NULL;
        }
        else {
            (*rear)->nextPtr = newPtr;
            *rear = newPtr;
            (*rear)->nextPtr = NULL;
        }
        cout << "\tSuccessfully updated enquiry status" << endl;
    }

}
// this method displays all the enquiry statuses in the queue(third data structure)
void viewEnqStatus(statusPtr* front, statusPtr* rear) {

    statusPtr temp = *front;
    if (temp == NULL) {
        cout << "\tThere are no stored enquiry statuses in the system." << endl;
    }
    else {
        while (temp != NULL) {
            cout << "\tEnquiry ID      :" << temp->enquiryID << endl;
            cout << "\tStudent Name    :" << temp->studentName << endl;
            cout << "\tStudent Contact :" << temp->studentContact << endl;
            cout << "\tAction          :" << temp->action << endl;
            cout << "\tStatus          :" << temp->status << endl;
            cout << "\t\t  -------------------------------------" << endl;
            cout << endl;

            temp = temp->nextPtr;
        }
    }


}

/* this method gets the user's choice to confirm before updating, inserting or deleting from
data structures*/
char getUserChoice() {
    char choice;
    bool valid = false;

    do {
        cin >> choice;
        choice = toupper(choice);

        switch (choice) {
        case 'Y':
            valid = true;
            break;

        case 'N':
            valid = true;
            break;

        default:
            cout << "\tPlease enter a valid choice." << endl;

        }
    } while (!valid);
    return choice;
}

// this method displays the data from the node its parameter points at.
void displayData(enquiryPtr currentPtr) {
    if (currentPtr != NULL) {
        cout << "\tEnquiry ID      :" << currentPtr->enquiryID << endl;
        cout << "\tStudent No      :" << currentPtr->studentNo << endl;
        cout << "\tStudent Contact :" << currentPtr->studentContact << endl;
        cout << "\tStudent Name    :" << currentPtr->studentName << endl;
        cout << "\tEmail           :" << currentPtr->studentEmail << endl;
        cout << "\tEnquiry         :" << currentPtr->enquiry << endl;
        cout << "\tDate            :" << currentPtr->date << endl;
    }

}
// this method inserts enquiry to main data structure
void insertEnquiry(enquiryPtr* startPtr, int enquiryID, int studentNo, long int studentContact,
    string studentName, string studentEmail, string enquiryTxt, string date) {

    enquiryPtr newPtr = NULL;
    enquiryPtr previousPtr = NULL;
    enquiryPtr currentPtr = NULL;

    newPtr = new enquiry; //create a new node
    if (newPtr != NULL) { //check if node is created
        newPtr->enquiryID = enquiryID;
        newPtr->studentNo = studentNo;
        newPtr->studentContact = studentContact;
        newPtr->studentName = studentName;
        newPtr->studentEmail = studentEmail;
        newPtr->enquiry = enquiryTxt;
        newPtr->date = date;
        newPtr->nextPtr = NULL;

        currentPtr = *startPtr;

        if (currentPtr == NULL || currentPtr->enquiryID > enquiryID) {
            newPtr->nextPtr = currentPtr;
            *startPtr = newPtr;
        }
        else {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
            while (currentPtr != NULL && enquiryID > currentPtr->enquiryID) {
                previousPtr = currentPtr;
                currentPtr = currentPtr->nextPtr;
            }
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;

        }
        cout << "\tSuccessfully created the enquiry." << endl;
    }
    else {
        cout << "Error! Could not create node." << endl;
    }
}
// this method helps remove enquiry from main data structure
enquiryPtr deleteEnquiry(enquiryPtr* startPtr, int enquiryID) {
    enquiryPtr tempPtr = NULL;
    enquiryPtr previousPtr = NULL;
    enquiryPtr currentPtr = NULL;

    currentPtr = *startPtr;

    if (enquiryID == currentPtr->enquiryID) {
        displayData(currentPtr);
        cout << "\tAre you sure you want to delete this enquiry (Y/N)?";
        char choice = getUserChoice();
        if (choice == 'Y') {
            tempPtr = *startPtr;
            *startPtr = (*startPtr)->nextPtr;
            //delete(tempPtr);
        }
        else {
            tempPtr = NULL;
        }

    }
    else {
        previousPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
        while (enquiryID != currentPtr->enquiryID) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }
        displayData(currentPtr);
        cout << "\tAre you sure you want to delete this enquiry (Y/N)?";
        char choice = getUserChoice();
        if (choice == 'Y') {
            tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            //delete(tempPtr);
        }
        else {
            tempPtr = NULL;
        }
    }
    return tempPtr;
}
/* this method searches for an enquiry and displays it by sending pointer
to displayData method.*/
void searchEnquiry(enquiryPtr* startPtr, int enquiryID) {

    enquiryPtr currentPtr = NULL;

    currentPtr = *startPtr;

    while (enquiryID != currentPtr->enquiryID) {

        currentPtr = currentPtr->nextPtr;
    }

    displayData(currentPtr);

}
//this method updates the enquiry in main data structure

void updateEnquiry(enquiryPtr* startPtr, int enquiryID) {
    string email;
    long int contact;
    char userChoice;
    enquiryPtr currentPtr = NULL;

    currentPtr = *startPtr;

    while (enquiryID != currentPtr->enquiryID) {

        currentPtr = currentPtr->nextPtr;
    }

    if (currentPtr != NULL) {
        displayData(currentPtr);

        cout << "\tEnter new student contact(10 digits) : ";
        cin >> contact;
        cout << "\tEnter new student email : ";
        cin >> email;
        cout << "\tAre you sure you want to update (Y/N)? : " << endl;
        userChoice = getUserChoice();
        if (userChoice == 'Y') {
            currentPtr->studentContact = contact;
            currentPtr->studentEmail = email;
            cout << "\tSuccessfully updated the enquiry" << endl;
        }
        else {
            cout << "\tOperation terminated." << endl;
        }

    }
    else {
        cout << "Could not retrieve the data." << endl;
    }

}
// this method displays all data in main data structure
void displayAllEnquiries(enquiryPtr* startPtr) {
    enquiryPtr currentPtr = NULL;
    currentPtr = *startPtr;
    if (currentPtr == NULL) {
        cout << "\tNo enquiries in the system." << endl;
    }
    else {
        while (currentPtr != NULL) {
            cout << "\tEnquiry ID      :" << currentPtr->enquiryID << endl;
            cout << "\tStudent No      :" << currentPtr->studentNo << endl;
            cout << "\tStudent Contact :" << currentPtr->studentContact << endl;
            cout << "\tStudent Name    :" << currentPtr->studentName << endl;
            cout << "\tEmail           :" << currentPtr->studentEmail << endl;
            cout << "\tEnquiry         :" << currentPtr->enquiry << endl;
            cout << "\tDate            :" << currentPtr->date << endl;
            cout << "\t\t  -------------------------------------" << endl;
            cout << endl;
            currentPtr = currentPtr->nextPtr;
        }

    }


}
// this method gets the status of enquiry based on character input
string checkStatus() {
    string status;
    char c;
    bool valid = false;

    do {
        cin >> c;
        c = toupper(c);

        switch (c) {
        case 'C':
            status = "Closed";
            valid = true;
            break;

        case 'O':
            status = "Open";
            valid = true;
            break;

        case 'A':
            status = "Cannot Address";
            valid = true;
            break;

        default:
            cout << "\tPlease enter a valid choice. ";

        }
    } while (!valid);
    return status;
}

// this method displays the menu
void displayMenu() {

    cout << endl;
    cout << "\t\t\t =================================" << endl;
    cout << "\t\t\t STUDENT ENQUIRY MANAGEMENT SYSTEM" << endl;
    cout << "\t\t\t =========XYZ UNIVERSITY=========" << endl;
    cout << "\t\t  ===================================================" << endl;
    cout << endl;

    cout << "\t\t\tINPUT  (1)  TO ADD AN ENQUIRY                    \t" << endl;
    cout << "\t\t  ---------------------------------------------------" << endl;
    cout << "\t\t\tINPUT  (2)  TO REMOVE AN ENQUIRY                 \t" << endl;
    cout << "\t\t  ---------------------------------------------------" << endl;
    cout << "\t\t\tINPUT  (3)  TO UPDATE AN ENQUIRY                 \t" << endl;
    cout << "\t\t  ---------------------------------------------------" << endl;
    cout << "\t\t\tINPUT  (4)  TO VIEW SINGLE ENQUIRY DETAILS       \t" << endl;
    cout << "\t\t  ---------------------------------------------------" << endl;
    cout << "\t\t\tINPUT  (5)  TO VIEW ALL ENQUIRIES                \t" << endl;
    cout << "\t\t  ---------------------------------------------------" << endl;
    cout << "\t\t\tINPUT  (6)  TO STORE STATUS OF ENQUIRY           \t" << endl;
    cout << "\t\t  ---------------------------------------------------" << endl;
    cout << "\t\t\tINPUT  (7)  TO VIEW ALL CLOSED ENQUIRIES         \t" << endl;
    cout << "\t\t  ---------------------------------------------------" << endl;
    cout << "\t\t\tINPUT  (8)  TO VIEW ALL REMOVED ENQUIRIES        \t" << endl;
    cout << "\t\t  ---------------------------------------------------" << endl;
    cout << "\t\t\tINPUT  (9)  EXIT                                 \t" << endl;
    cout << "\t\t  ---------------------------------------------------" << endl;

    cout << endl;

    cout << "\t\t\t\tEnter your choice:";
}

// this method validates integer inputs
int validateInput() {
    int menuChoice;
    cin >> menuChoice;

    while (!cin.good()) {

        cin.clear();
        cin.ignore(INT_MAX, '\n');

        cout << "\tPlease enter a valid number: ";
        cin >> menuChoice;
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    return menuChoice;
}



int main()
{
    enquiryPtr startPtr = NULL;
    enquiryPtr tempPtr = NULL;
    queuePtr frontPtr = NULL;
    queuePtr rearPtr = NULL;
    statusPtr statusPtrFront = NULL;
    statusPtr statusPtrRear = NULL;

    int enquiryID, studentNo, menuChoice;
    long int contact;
    string name, email, enquiry, date, action, status;
    bool isAvailable, exit = false;
    char userChoice;
    do {
        displayMenu();
        //cin >> menuChoice;
        menuChoice = validateInput();
        switch (menuChoice) {
        case 1:
            cout << endl;
            cout << "\t\t\t==========================================" << endl;
            cout << "\t\t\t              ADD AN ENQUIRY              " << endl;
            cout << "\t\t\t==========================================" << endl;

            cout << endl;
            cout << "\tEnter Enquiry ID : ";
            do {
                enquiryID = validateInput();

                isAvailable = checkID(&startPtr, enquiryID);
                if (isAvailable) {
                    cout << "\tThe entered ID already exists. Please re-enter: ";
                }
            } while (isAvailable);

            cout << "\tEnter Student No. : ";
            studentNo = validateInput();
            cout << "\tEnter Student Name : ";
            getline(cin >> ws, name);
            cout << "\tEnter Student Contact : ";
            cin >> contact;
            cout << "\tEnter Student Email : ";
            cin >> email;
            cout << "\tEnter Enquiry : ";
            getline(cin >> ws, enquiry);
            cout << "\tEnter Date : ";
            cin >> date;
            cout << "\tAre you sure you want to add this enquiry (Y/N)?";
            userChoice = getUserChoice();
            if (userChoice == 'Y') {
                insertEnquiry(&startPtr, enquiryID, studentNo, contact, name, email, enquiry, date);

            }
            else {
                cout << "\tOperation terminated." << endl;
            }
            exitLoop();

            break;

        case 2:
            cout << endl;
            cout << "\t\t\t==========================================" << endl;
            cout << "\t\t\t            REMOVE AN ENQUIRY             " << endl;
            cout << "\t\t\t==========================================" << endl;

            cout << endl;
            cout << "\tEnter Enquiry ID : ";
            enquiryID = validateInput();

            isAvailable = checkID(&startPtr, enquiryID);
            if (isAvailable) {
                tempPtr = deleteEnquiry(&startPtr, enquiryID);
                if (tempPtr != NULL) {
                    queueEnq(tempPtr, &frontPtr, &rearPtr);
                }
                else {
                    cout << "\tOperation terminated." << endl;
                }
            }
            else {
                cout << "\tEnquiryID does not exist." << endl;
            }
            exitLoop();

            break;

        case 3:
            cout << endl;
            cout << "\t\t\t==========================================" << endl;
            cout << "\t\t\t            UPDATE AN ENQUIRY             " << endl;
            cout << "\t\t\t==========================================" << endl;

            cout << endl;
            cout << "\tEnter Enquiry ID : ";
            enquiryID = validateInput();
            isAvailable = checkID(&startPtr, enquiryID);

            if (isAvailable) {
                updateEnquiry(&startPtr, enquiryID);

            }
            else {
                cout << "\tEnquiryID does not exist." << endl;
            }

            exitLoop();
            break;



        case 4:
            cout << endl;
            cout << "\t\t\t==========================================" << endl;
            cout << "\t\t\t       VIEW SINGLE ENQUIRY DETAILS        " << endl;
            cout << "\t\t\t==========================================" << endl;

            cout << endl;
            cout << "\tEnter Enquiry ID : ";
            enquiryID = validateInput();
            isAvailable = checkID(&startPtr, enquiryID);

            if (isAvailable) {
                searchEnquiry(&startPtr, enquiryID);

            }
            else {
                cout << "\tEnquiryID does not exist." << endl;
            }
            exitLoop();
            break;

        case 5:
            cout << endl;
            cout << "\t\t\t==========================================" << endl;
            cout << "\t\t\t            VIEW ALL ENQUIRIES            " << endl;
            cout << "\t\t\t==========================================" << endl;

            cout << endl;
            displayAllEnquiries(&startPtr);
            exitLoop();
            break;

        case 6:
            cout << endl;
            cout << "\t\t\t==========================================" << endl;
            cout << "\t\t\t          STORE STATUS OF ENQUIRY         " << endl;
            cout << "\t\t\t==========================================" << endl;

            cout << endl;
            cout << "\tEnter Enquiry ID : ";
            enquiryID = validateInput();
            isAvailable = checkID(&startPtr, enquiryID);

            if (isAvailable) {
                cout << "\tEnter the action taken : ";
                getline(cin >> ws, action);
                cout << "\tEnter the status Closed/Open/Cannot Address(C/O/A) : ";
                status = checkStatus();
                queueEnqStatus(&startPtr, &statusPtrFront, &statusPtrRear, enquiryID, action, status);
            }
            else {
                cout << "\tEnquiryID does not exist." << endl;
            }
            exitLoop();
            break;


        case 7:
            cout << endl;
            cout << "\t\t\t==========================================" << endl;
            cout << "\t\t\t         VIEW ALL CLOSED ENQUIRIES        " << endl;
            cout << "\t\t\t==========================================" << endl;

            cout << endl;
            viewEnqStatus(&statusPtrFront, &statusPtrRear);
            exitLoop();
            break;

        case 8:
            cout << endl;
            cout << "\t\t\t==========================================" << endl;
            cout << "\t\t\t        VIEW ALL REMOVED ENQUIRIES        " << endl;
            cout << "\t\t\t==========================================" << endl;

            cout << endl;
            viewRemovedEnq(&frontPtr, &rearPtr);
            exitLoop();
            break;

        case 9:
            exit = true;
            break;

        default:
            cout << "Please enter the value of a function." << endl;

        }

    } while (!exit);

    return(0);

}

