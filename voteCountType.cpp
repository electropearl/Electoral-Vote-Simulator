#include <iostream>
#include <fstream>
#include <string>
#include "voteCountType.h"
#include "binarySearchTree.h"

bool voteCountType::isDVDAvailable(std::string stateID)
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

void voteCountType::postDemocratUpdate(std::string stateID, int voteCount)
{
    bool found = false;
    nodeType<voteCountType> *location;

    searchDVDList(stateID, found, location);

    if (found)
        location->info.updatePopularVotesDemocrat(voteCount);
    else
        std::cout << "State not found " << stateID
                  << std::endl;
}

void voteCountType::postRepublicanUpdate(std::string stateID, int voteCount)
{
    bool found = false;
    nodeType<voteCountType> *location;

    searchDVDList(stateID, found, location);

    if (found)
        location->info.updatePopularVotesRepublican(voteCount);
    else{
        std::cout << "State not found " << stateID << std::endl;
    }
}

bool voteCountType::dvdSearch(std::string stateID)
{
    bool found = false;
    nodeType<voteCountType> *location;

    searchDVDList(stateID, found, location);


    return found;
}

void voteCountType::searchDVDList(std::string title,
                          bool& found,
                          nodeType<voteCountType>* &current) const
{
    found = false;

    voteCountType temp;


    temp.setStateInfo(title, "", 0, 0, 0);

    if (root == nullptr)  //tree is empty
        std::cout << "Cannot search an empty list. " << std::endl;
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


void voteCountType::inorderTitle(nodeType<voteCountType> *p, int &republican, int &democrat) const
{
    if (p != nullptr)
    {
        inorderTitle(p->lLink, republican, democrat);
        p->info.whosWinning(republican,democrat);
        inorderTitle(p->rLink, republican,democrat);
    }
}

void voteCountType::setStateInfo(std::string stateID, std::string stateName,
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
    std::cout << "State ID: " << stateID << std::endl;
}

void voteCountType::printInfo(std::string stateID) const
{
    bool found = false;
    nodeType<voteCountType> *location;

    searchDVDList(stateID, found, location);

    std::cout << "State ID: " << location->info.stateID << std::endl;
    std::cout << "State Name: " << location->info.stateName << std::endl;
    std::cout << "Electorial Votes Available: " << location->info.electorialVotes << std::endl;
    std::cout << "Popular vote count (Republican): " << location->info.popularVotesRepublican << std::endl;
    std::cout << "Popular vote count (Democrat): " << location->info.popularVotesDemocrat << std::endl;
}

bool voteCountType::checkTitle(std::string stateID)
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

std::string voteCountType::getTitle() const
{
    return stateID;
}

voteCountType::voteCountType(std::string stateID, std::string stateName, int eVotesAvailable, int voteCountRepublican, int voteCountDemocrat) {
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

std::ostream& operator<< (std::ostream& osObject, const voteCountType& dvd)
{
    osObject << std::endl;
    osObject << "  State ID: " << dvd.stateID << std::endl;
    osObject << "State Name: " << dvd.stateName << std::endl;
    osObject << "Electorial Votes Available: " << dvd.electorialVotes << std::endl;
    osObject << "Popular vote count (Republican): " << dvd.popularVotesRepublican << std::endl;
    osObject << "Popular vote count (Democrat): " << dvd.popularVotesDemocrat << std::endl;
    osObject << "_____________________________________" << std::endl;
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

void createDVDList(std::ifstream& infile, voteCountType& dvdList) {
    std::string stateID;
    std::string stateName;
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
    std::cout<<std::endl;
    std::cout << "Select one of the following:" << std::endl;
    std::cout << "1: Post new update message to database" << std::endl;
    std::cout << "2: Print status of a state" << std::endl;
    std::cout << "3: Print all states and current status" << std::endl;
    std::cout << "4: Determine who is winning" << std::endl;
    std::cout << "9: To exit" << std::endl;
}


int main()
{
    voteCountType dvdList;
    int choice,n,a;
    std::string title;
    //char p;

    std::ifstream infile;

    infile.open("states.txt");

    if (!infile) {
        std::cout << "The input file does not exist. "
             << "Program terminates!!" << std::endl;
        return 1;
    }

    createDVDList(infile, dvdList);
    infile.close();

    displayMenu();  // show the menu
    std::cout << "Enter your choice: ";
    std::cin >> choice;          // get the request
    std::cin.ignore(100, '\n');  // ignore the remainingclear
                            // characters in the line
    std::cout << std::endl;

    while (choice != 9) {
        switch (choice) {
             case 1:
                 std::cout << "Post new update to database. Type state ID (SS): ";
                 getline(std::cin, title);
                 //cin >> p;
                 //cin >>x;



                 std::cout << std::endl;

                 if (dvdList.dvdSearch(title))
                 {
                    std::cout << "Which Party would you like to update?" << std::endl;
                    std::cout << "1. Republican " << std::endl;
                    std::cout << "2. Democratic " << std::endl;
                    std::cout << "Enter your choice: ";
                    std::cin >> n;
                    std::cout << std::endl;
                    if(n == 1)
                    {
                        std::cout << "Enter the number to update Republican party: ";
                        std::cin >> a;
                        std::cout << std::endl;
                        dvdList.postRepublicanUpdate(title , a);
                        std::cout << title << " has been updated by " << a << std::endl;
                        std::cout << std::endl;
                    }
                    else if (n == 2)
                    {
                        std::cout << "Enter the number to update Democratic party: ";
                        std::cin >> a;
                        std::cout << std::endl;
                        dvdList.postDemocratUpdate(title, a);
                        std::cout << title << " has been updated by " << a <<std::endl;
                        std::cout << std::endl;
                    }
                    else
                    {
                        std::cout << "Sorry This choice is not an option."<< std::endl;
                    }
                    break;
                 }
                else
                {
                    std::cout << "This is not a State: " << title << std::endl;
                }
                break;

            case 2:
                std::cout << "Enter a state and to know its status (SS): ";
                std::getline(std::cin, title);
                std::cout << std::endl;
                 if (dvdList.dvdSearch(title)) {
                     dvdList.search(title);
                     dvdList.printInfo(title);

                 } else
                     std::cout << title << " does not exist." <<std::endl;
                break;

            case 3:
                dvdList.inorderTraversal();
                break;
            case 4:
            {
                int republican =0;
                int democrat = 0;
                dvdList.whosWinning(republican,democrat);
                std::cout << "Republican electorial votes: "<< republican<< std::endl;
                std::cout << "Democrat electorial votes: "<< democrat<< std::endl;
                std::cout << std::endl;
                break;
            }

            default:
                std::cout << "Invalid selection." << std::endl;
                break;
        }

        displayMenu();  // display the menu
        std::cout << "Enter your choice: ";
        std::cin >> choice;          // get the next request
        std::cin.ignore(100, '\n');  // ignore the remaining characters in the line
        std::cout << std::endl;
    }
    return 0;
}
