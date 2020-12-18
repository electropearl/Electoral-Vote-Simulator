#ifndef H_voteCountType
#define H_voteCountType

#include <iostream>
#include <string>

#include "binarySearchTree.h"


using namespace std;

class voteCountType : public bSearchTreeType<voteCountType> {
    friend ostream& operator<<(ostream&, const voteCountType&);

   public:

    void setStateInfo(string stateID, string stateName, int eVoteAvailable,
                    int voteCountRepublican, int voteCountDemocrat);

    int getNoOfCopiesInStock() const;
    int getPopularVoteRepublican() const;
    int getPopularVoteDemocrat() const;
    bool dvdSearch(string title);
    bool isDVDAvailable(string title);

    void printTitle() const;
    void printInfo(string stateID) const;
    bool checkTitle(string title);
    bool updatePopularVotesDemocrat(int thisVoteCount);
    bool updatePopularVotesRepublican(int thisVoteCount);
    string getTitle() const;
    void setCopiesInStock(int num);
    void postDemocratUpdate(string stateID, int voteCount);
    void postRepublicanUpdate(string stateID, int voteCount);
    void whosWinning(int &republican, int &democrat);
    

    voteCountType(string stateID = "", string stateName = "", int setInStock = 0,
            int voteCountRepublican = 0, int voteCountDemocrat = 0);

    // Overload relational operators
    bool operator==(const voteCountType&) const;
    bool operator!=(const voteCountType&) const;
    bool operator<(const voteCountType&) const;
    bool operator<=(const voteCountType&) const;
    bool operator>(const voteCountType&) const;
    bool operator>=(const voteCountType&) const;

   private:
    string stateID;
    string stateName;
    int electorialVotes;         // todo : unsigned
    int popularVotesRepublican;  // todo : unsigned
    int popularVotesDemocrat;    // todo : unsigned
    void searchDVDList(string title, bool& found, nodeType<voteCountType>*& current) const;
    void inorderTitle(nodeType<voteCountType> *p, int &republican, int &democrat) const;
    
   
};

#endif