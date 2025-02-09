#pragma once
#include <bits/stdc++.h>

using namespace std;


class Book{
    private:
        string isbn;
        int copiesAvailable;
        int totalCopies;

    public:
        string title;
        string author;


    Book(){
        title = "UnknownTitle";
        author = "UnknownAuthor";
        isbn = "ISBN";
        copiesAvailable = 0;
        totalCopies = 5;    
    }

    Book(string inptitle, string inpauthor, string inpisbn, int inpcopiesAvailable, int inptotalCopies){
        title = inptitle;
        author = inpauthor;
        isbn = inpisbn;
        copiesAvailable = inpcopiesAvailable;
        totalCopies = inptotalCopies;
    }

    Book(Book& copybook, string newisbn){
        title = copybook.title;
        author = copybook.author;
        isbn = newisbn;
        copiesAvailable = copybook.copiesAvailable;
        totalCopies = copybook.totalCopies;
    }

    string get_isbn(){
        return isbn;
    }

    int get_copiesAvailable(){
        return copiesAvailable;
    }

    int get_totalCopies(){
        return totalCopies;
    }

    void updateCopies(int count){
        if((copiesAvailable + count) < 0 or (totalCopies + count) < 0){
            cout << "Invalid request! Count becomes negative" << endl;
        }
        else{   
            copiesAvailable += count;
            totalCopies += count;
        }
    }

    bool borrowBook(){
        if(copiesAvailable > 0){
            copiesAvailable -= 1;
            return true;
        }
        else{
            cout << "Invalid request! Copy of book not available" << endl;
            return false;
        }
    }

    bool returnBook(){
        if(copiesAvailable < totalCopies){
            copiesAvailable += 1;
            return true;
        }
        else{
            cout << "Invalid request! Copy of book exceeds total copies" << endl;
            return false;
        }
    }

    void printDetails(){
        cout << title << " " << author << endl;
    }

};