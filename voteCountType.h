#ifndef H_voteCountType
#define H_voteCountType

#include <iostream>
#include <string>

#include "binarySearchTree.h"

class voteCountType : public bSearchTreeType<voteCountType> {
    friend std::ostream& operator<<(std::ostream&, const voteCountType&);

   public:

    void setStateInfo(std::string stateID, std::string stateName, int eVoteAvailable,
                    int voteCountRepublican, int voteCountDemocrat);

    int getNoOfCopiesInStock() const;
    int getPopularVoteRepublican() const;
    int getPopularVoteDemocrat() const;
    bool dvdSearch(std::string title);
    bool isDVDAvailable(std::string title);

    void printTitle() const;
    void printInfo(std::string stateID) const;
    bool checkTitle(std::string title);
    bool updatePopularVotesDemocrat(int thisVoteCount);
    bool updatePopularVotesRepublican(int thisVoteCount);
    std::string getTitle() const;
    void setCopiesInStock(int num);
    void postDemocratUpdate(std::string stateID, int voteCount);
    void postRepublicanUpdate(std::string stateID, int voteCount);
    void whosWinning(int &republican, int &democrat);


    voteCountType(std::string stateID = "", std::string stateName = "", int setInStock = 0,
            int voteCountRepublican = 0, int voteCountDemocrat = 0);

    // Overload relational operators
    bool operator==(const voteCountType&) const;
    bool operator!=(const voteCountType&) const;
    bool operator<(const voteCountType&) const;
    bool operator<=(const voteCountType&) const;
    bool operator>(const voteCountType&) const;
    bool operator>=(const voteCountType&) const;

   private:
    std::string stateID;
    std::string stateName;
    int electorialVotes;         // todo : unsigned
    int popularVotesRepublican;  // todo : unsigned
    int popularVotesDemocrat;    // todo : unsigned
    void searchDVDList(std::string title, bool& found, nodeType<voteCountType>*& current) const;
    void inorderTitle(nodeType<voteCountType> *p, int &republican, int &democrat) const;


};

#endif
