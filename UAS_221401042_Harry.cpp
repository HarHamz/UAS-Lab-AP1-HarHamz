#include <ctime>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// class for notes
class notes
{
    public:
    string title;
    string content;
    time_t creationDate;
};

// prevents inputs other than integers
int inputInt(int index)
{
    if (cin.fail()) {
        cout << "Invalid input. Please enter a number." << endl;
        cin.clear();
        cin.ignore();
        index = 0;
    }
    return index;
}

// prevents inputs other than the size of array
int inputSpecifier(int index, int size)
{
    do
    {
        cout << "Select a file by inputting the index (Starts at 1): ";
        cin >> index;
        cin.ignore();

        index = inputInt(index);
    }
    while(index < 1 || index > size);
    return index;
}

// function to view all notes
void viewAll(vector<notes>& notesVec)
{
    int i = 1, size = notesVec.size();
    cout << "You are viewing all notes." << endl;
    if(size == 0)
    {
        cout << "There are no notes." << endl;
    }
    else
    {
        for(auto index: notesVec) // loops through every note
        { 
            cout << "\033[48;5;22m" << i << ":" << "\033[0m" << endl; // makes the index's bg color to dark green, to make it easier for the user to view each note
            cout << "Title: " << index.title << endl;
            cout << "Created at: " << asctime(localtime(&index.creationDate)) << endl;
            i++;
        }
    }
}

// function to create a new note
void createNew(vector<notes>& notesVec)
{
    string title, content;

    cout << "You are about to create a new note." << endl;
    cout << "Title of the new note: ";
    getline(cin >> ws , title);
    cout << "Contents of the new note: ";
    getline(cin >> ws , content);

    notes newNotes; // makes a class named newNotes
    newNotes.title = title;
    newNotes.content = content;
    newNotes.creationDate = time(nullptr);

    notesVec.push_back(newNotes); // adds newNotes to the back of notesVec

    cout << "Note created successfully." << endl;
}

// function to view a specific note
void viewOne(vector<notes>& notesVec)
{
    int index, size = notesVec.size();
    char yorn;
    viewOneAgain:
    viewAll(notesVec);
    
    if(size > 0)
    {
        index = inputSpecifier(index, size);

        auto note = notesVec[index - 1];
        cout << note.title << endl;
        cout << note.content << endl;

        do
        {
        cout << "Want to continue viewing individual notes? (y/n): ";
        cin >> yorn;
        cin.ignore();
        }
        while (yorn != 'y' && yorn != 'n');

        if (yorn == 'y')
        {
            goto viewOneAgain;
        }
    }
}

// function to edit a note
void editNote(vector<notes>& notesVec)
{
    int index, size = notesVec.size();
    string title, content;
    viewAll(notesVec);

    if(size > 0)
    {
        index = inputSpecifier(index, size);

        cout << "You are about to edit this note." << endl;
        cout << "Contents of the note: ";
        getline(cin >> ws , content);

        notesVec[index - 1].content = content; // overwrites the content with the edited one

        cout << "Note edited successfully." << endl;
    }
}

// function to delete a note
void deleteNote(vector<notes>& notesVec)
{
    int index, size = notesVec.size();
    char yorn;
    string title, content;
    viewAll(notesVec);

    if(size > 0)
    {
        index = inputSpecifier(index, size);

        do
        {
            cout << "You are about to delete this note." << endl;
            cout << "Confirm? (y/n): ";
            cin >> yorn;
            cin.ignore();
        }
        while (yorn != 'y' && yorn != 'n');

        if (yorn == 'y')
        {
            notesVec.erase(notesVec.begin() + index - 1);
        }

        cout << "Note deleted successfully." << endl;
    }
}

int main(void)
{
    vector<notes> notesVec;
    
    int choice;
    loop: // start of the loop after using a choice
    system("cls"); // clears the screen
    cout << "\033[48;5;22m"; // makes the title's bg color to dark green, to make it pretty :)
    cout << "--- HarHamz's Note Taking CLI Program ---" << endl;
    cout << "\033[0m"; // resets the bg color

    do {
        cout << "1. View All Notes.\n2. Create New Note.\n3. View Specific Note.\n4. Edit Note.\n5. Delete Note.\n6. Exit." << endl;
        cout << "Input a number according to your choice below: ";
        cin >> choice;
        cin.ignore(); //ignores whitespace
        choice = inputInt(choice); // go to the inputInt function
    }
    while(choice < 1 || choice > 6); // prevents other integers

    switch(choice)
    {
        case 1:
        {
            viewAll(notesVec);
            break;
        }
        case 2:
        {
            createNew(notesVec);
            break;
        }
        case 3:
        {
            viewOne(notesVec);
            break;
        }
        case 4:
        {
            editNote(notesVec);
            break;
        }
        case 5:
        {
            deleteNote(notesVec);
            break;
        }
        case 6:
        {
            cout << "Thanks for using this program :)" << endl;
            cout << "        HarHamz, 2023" << endl;
            return 0;
        }
        default:
        {
            break;
        }
    }
    cout << "Press Enter to continue.";
    cin.get();
    
    goto loop; // goes to loop to go back to the main menu
}