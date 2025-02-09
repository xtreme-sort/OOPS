#pragma once
#include <bits/stdc++.h>

using namespace std;

class Member{
    private:
        string memberID;
        map<string,int> borrowedBooks;
        int borrowLimit;
        int NoofBorrowedbooks;

    public:
        string name;
        
        Member(){}

        Member(string inpmemberID, string inpname, int inpborrowLimit){
            memberID = inpmemberID;
            name = inpname;
            borrowLimit = inpborrowLimit;
            NoofBorrowedbooks = 0;
        }

        Member(string inpmemberID, string inpname){
            memberID = inpmemberID;
            name = inpname;
            borrowLimit = 3;
            NoofBorrowedbooks = 0;
        }


        string get_memberID(){
            return memberID;
        }

        int get_borrowLimit(){
            return borrowLimit;
        }

        int get_NoofBorrowedBooks(){
            return NoofBorrowedbooks;
        }

        bool has_borrowed(string isbn){
            if(borrowedBooks[isbn] > 0) return true;
            else return false;
        }


        bool borrowBook(string isbn){
            if(NoofBorrowedbooks < borrowLimit){
                borrowedBooks[isbn] += 1;
                NoofBorrowedbooks += 1;
                return true;
            }
            else{
                cout << "Invalid request! Borrow limit exceeded" << endl;
                return false;
            }
        }

        bool returnBook(string isbn){
            if(borrowedBooks[isbn] > 0){
                borrowedBooks[isbn] -= 1;
                NoofBorrowedbooks -= 1;
                return true;
            }
            else{
                cout << "Invalid request! Book not borrowed" << endl;
                return false;
            }
        }

        void printDetails(){
            for(auto x : borrowedBooks){
                if(x.second == 0) continue;
                cout << memberID << " " << name << " " << x.first << " " << x.second << endl;
            }
        }

};