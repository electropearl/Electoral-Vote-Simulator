#include <iostream>
#include <fstream>
#include <string>
#include "voteCountType.h"
#include "binarySearchTree.h"

using namespace std;
//A
bool voteCountType::isDVDAvailable(string stateID) 
{
    bool found;
    nodeType<voteCountType> *location;

    searchDVDList(stateID, found, location);

    if (found)
        found = (location->info.getNoOfCopiesInStock() > 0);
    else  
        found = false;

    return found;
}

void voteCountType::postDemocratUpdate(string stateID, int voteCount)
{
    bool found = false;
    nodeType<voteCountType> *location;

    searchDVDList(stateID, found, location);

    if (found)
        location->info.updatePopularVotesDemocrat(voteCount);
    else
        cout << "State not found " << stateID
            << endl;
}

void voteCountType::postRepublicanUpdate(string stateID, int voteCount)
{
    bool found = false;
    nodeType<voteCountType> *location;

    searchDVDList(stateID, found, location);

    if (found)
        location->info.updatePopularVotesRepublican(voteCount);
    else{
        cout << "State not found " << stateID<< endl;
    }
}

bool voteCountType::dvdSearch(string stateID)
{
    bool found = false;
    nodeType<voteCountType> *location;

    searchDVDList(stateID, found, location);


    return found;
}

void voteCountType::searchDVDList(string title, 
                          bool& found,
                          nodeType<voteCountType>* &current) const
{
    found = false;   
   
    voteCountType temp;

    
    temp.setStateInfo(title, "", 0, 0, 0);            

    if (root == nullptr)  //tree is empty
        cout << "Cannot search an empty list. " << endl;
    else
    {
        current = root; //set current point to the root node 
                        //of the binary tree
        found = false;  //set found to false

        while (current != nullptr && !found) //search the tree
            if (current->info == temp)    //item is found
                found = true;
            else if (current->info > temp)
                current = current->lLink;
            else
                current = current->rLink;
    }
} //end searchDVDList


void voteCountType::inorderTitle
                          (nodeType<voteCountType> *p, int &republican, int &democrat) const
{
    if (p != nullptr)
    { 
        inorderTitle(p->lLink, republican, democrat);
        p->info.whosWinning(republican,democrat);
        inorderTitle(p->rLink, republican,democrat);
    }
}
//B
void voteCountType::setStateInfo(string stateID, string stateName,
                    int eVoteAvailable, int voteCountRepublican, int voteCountDemocrat) {
    this->stateID = stateID;
    this->stateName = stateName;
    this->electorialVotes = eVoteAvailable;
    this->popularVotesRepublican = voteCountRepublican;
    this->popularVotesDemocrat = voteCountDemocrat;
}

int voteCountType::getNoOfCopiesInStock() const
{
    return this->electorialVotes;
}

int voteCountType::getPopularVoteRepublican() const {
    return this->popularVotesRepublican;
}

int voteCountType::getPopularVoteDemocrat() const {
    return this->popularVotesDemocrat;
}

void voteCountType::printTitle() const
{
    cout << "State ID: " << stateID << endl;
}

void voteCountType::printInfo(string stateID) const
{  
    bool found = false;
    nodeType<voteCountType> *location;

    searchDVDList(stateID, found, location);

    
    cout << "State ID: " << location->info.stateID << endl;
    cout << "State Name: " << location->info.stateName << endl;
    cout << "Electorial Votes Available: " << location->info.electorialVotes << endl;
    cout << "Popular vote count (Republican): " << location->info.popularVotesRepublican << endl;
    cout << "Popular vote count (Democrat): " << location->info.popularVotesDemocrat << endl;

}

bool voteCountType::checkTitle(string stateID)
{
    return(this->stateID == stateID);
}

bool voteCountType::updatePopularVotesDemocrat(int thisVoteCount)
{
    bool result = false;
    if (popularVotesDemocrat <= thisVoteCount){
        popularVotesDemocrat = thisVoteCount;
        result = true;
    }
    return result;
}

bool voteCountType::updatePopularVotesRepublican(int thisVoteCount)
{
    bool result = false;
    if (popularVotesRepublican <= thisVoteCount){
        popularVotesRepublican = thisVoteCount;
        result = true;
    }
    return result;
}

void voteCountType::setCopiesInStock(int num) 
{
    electorialVotes = num;
}

string voteCountType::getTitle() const
{
    return stateID;
}

voteCountType::voteCountType(string stateID, string stateName, int eVotesAvailable, int voteCountRepublican, int voteCountDemocrat) {
    setStateInfo(stateID, stateName, eVotesAvailable, voteCountRepublican, voteCountDemocrat);
}

//Overload the relational operators
bool voteCountType::operator==(const voteCountType& right) const
{
    return (this->stateID == right.stateID);
}

bool voteCountType::operator!=(const voteCountType& right) const
{
    return (this->stateID != right.stateID);
}

bool voteCountType::operator<(const voteCountType& right) const
{
    return (this->stateID < right.stateID);
}

bool voteCountType::operator<=(const voteCountType& right) const
{
    return (this->stateID <= right.stateID);
}

bool voteCountType::operator>(const voteCountType& right) const
{
    return (this->stateID > right.stateID);
}

bool voteCountType::operator>=(const voteCountType& right) const
{
    return (this->stateID >= right.stateID);
}

ostream& operator<< (ostream& osObject, const voteCountType& dvd)
{
    osObject << endl;
    osObject << "  State ID: " << dvd.stateID << endl; 
    osObject << "State Name: " << dvd.stateName << endl;
    osObject << "Electorial Votes Available: " << dvd.electorialVotes << endl;
    osObject << "Popular vote count (Republican): " << dvd.popularVotesRepublican << endl;
    osObject << "Popular vote count (Democrat): " << dvd.popularVotesDemocrat << endl;
    osObject << "_____________________________________" << endl;
    return osObject;
}

void voteCountType:: whosWinning(int &republican, int &democrat){
    inorderTitle(root,republican,democrat);
    if(this->getPopularVoteRepublican() > 0 || this->getPopularVoteDemocrat() > 0){
        if(this->getPopularVoteRepublican() > this->getPopularVoteDemocrat()){
            republican += this->getNoOfCopiesInStock();
        } else {
            democrat += this->getNoOfCopiesInStock();
        }
    }

}

void createDVDList(ifstream& infile, voteCountType& dvdList) {
    string stateID;
    string stateName;
    int electorialVotes;

    voteCountType newState;

    getline(infile, stateID);

    while (infile) {
        getline(infile, stateName);
        infile >> electorialVotes;
        infile.ignore(100, '\n');
        newState.setStateInfo(stateID, stateName, electorialVotes, 0, 0);
        dvdList.insert(newState);

        getline(infile, stateID);
    }
}

void displayMenu() {
    cout<<endl;
    cout << "Select one of the following:" << endl;
    cout << "1: Post new update message to database" << endl;
    cout << "2: Print status of a state" << endl;
    cout << "3: Print all states and current status" << endl;
    cout << "4: Determine who is winning" << endl;
    cout << "9: To exit" << endl;
}


int main()
{
    voteCountType dvdList;
    
    

    int choice,n,a;
    string title;
    //char p;

    ifstream infile;

    infile.open("/Users/nick/Downloads/lab09Transition/states.txt");

    if (!infile) {
        cout << "The input file does not exist. "
             << "Program terminates!!" << endl;
        return 1;
    }

    createDVDList(infile, dvdList);
    infile.close();

    displayMenu();  // show the menu
    cout << "Enter your choice: ";
    cin >> choice;          // get the request
    cin.ignore(100, '\n');  // ignore the remainingclear
                            // characters in the line
    cout << endl;

    while (choice != 9) {
        switch (choice) {
             case 1:
                 cout << "Post new update to database. Type state ID (SS): ";
                 getline(cin, title);
                 //cin >> p;
                 //cin >>x;


                 
                 cout << endl;

                 if (dvdList.dvdSearch(title))
                 {
                    cout << "Which Party would you like to update?" << endl;
                    cout << "1. Republican " << endl;
                    cout << "2. Democratic " << endl;
                    cout<< "Enter your choice: ";
                    cin >> n;
                    cout << endl;
                    if(n == 1)
                    {   cout << "Enter the number to update Republican party: ";
                        cin >> a;
                        cout<<endl;
                        dvdList.postRepublicanUpdate(title , a);
                        cout << title << " has been updated by "<< a <<endl;
                        cout<<endl;
                    }
                    else if (n == 2)
                    {
                        cout << "Enter the number to update Democratic party: ";
                        cin >> a;
                        cout<<endl;
                        dvdList.postDemocratUpdate(title, a);
                        cout << title << " has been updated by "<< a <<endl;
                        cout<<endl;
                    }
                    else
                    {
                        cout << "Sorry This choice is not an option."<<endl;
                    }
                    break;
                 }
                else
                {
                    cout << "This is not a State: " << title << endl;
                }
                break;

            case 2:
                cout << "Enter a state and to know its status (SS): ";
                getline(cin, title);
                cout << endl;
                 if (dvdList.dvdSearch(title)) {
                     dvdList.search(title);
                     dvdList.printInfo(title);

                 } else
                     cout << title << " does not exist." <<endl;
                break;

            case 3:
                dvdList.inorderTraversal();
                break;

            case 4:
            {
                int republican =0;
                int democrat = 0;
                dvdList.whosWinning(republican,democrat);
                cout << "Republican electorial votes: "<< republican<< endl;
                cout << "Democrat electorial votes: "<< democrat<< endl;
                cout << endl;
                break;
            }

            default:
                cout << "Invalid selection." << endl;
                break;
        }

        displayMenu();  // display the menu
        cout << "Enter your choice: ";
        cin >> choice;          // get the next request
        cin.ignore(100, '\n');  // ignore the remaining characters in the line
        cout << endl;
    }

    return 0;
}