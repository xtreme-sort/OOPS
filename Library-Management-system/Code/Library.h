#pragma once
#include <bits/stdc++.h>
#include "Books.h"
#include "Member.h"

using namespace std;


class Library{

    private:
        vector<Book> books;
        vector<Member> members;


    public:

        bool addBook(Book& newbook){
            bool canAdd = true;
            string newisbn = newbook.get_isbn();

            for(auto &x : books){
                if(x.get_isbn() == newisbn){
                    canAdd = false;
                    break;
                }
            }

            if(canAdd) books.push_back(newbook);
            else{
                cout << "Invalid request! Book with same isbn already exists" << endl;
            }

            return canAdd;
        }


        bool addMember(Member& newmember){
            bool canAdd = true;
            string newmemberID = newmember.get_memberID();

            for(auto &x : members){
                if(x.get_memberID() == newmemberID){
                    canAdd = false;
                    break;
                }
            }

            if(canAdd) members.push_back(newmember);
            else{
                cout << "Invalid request! Member with same id already exists" << endl;
            }

            return canAdd;
        } 


        bool borrowBook(string memberID, string isbn){

            for(auto &x : books){
                if(x.get_isbn() == isbn){
                        if(x.get_copiesAvailable() > 0){
                            for(auto &y : members){
                                if(y.get_memberID() == memberID){
                                    if(y.borrowBook(isbn)){
                                        x.borrowBook();
                                        return true;
                                    }
                                }
                            }    
                        
                        }
                        else{
                            cout << "Invalid request! Copy of book not available" << endl;
                        }
                    
                }
            }

            return false;
        }


        bool returnBook(string memberID, string isbn){

            for(auto &x : books){
                if(x.get_isbn() == isbn){
                    bool yes = x.returnBook();
                    if(yes){
                        for(auto &y : members){
                            if(y.get_memberID() == memberID){
                                if(y.has_borrowed(isbn)){
                                    y.returnBook(isbn);
                                    return true;
                                }
                            }
                        }
                        cout << "Invalid request! Book not borrowed" << endl;
                        x.borrowBook();
                        return false;
                    }
                    
                }
            }

            return false;

        }

        Member get_member(string memberID){
            Member member;
            for(auto &x : members){
                if(x.get_memberID() == memberID){
                    return x;
                }
            }

            return member;
        }

        Book get_book(string isbn){
            Book book;
            for(auto &x : books){
                if(x.get_isbn() == isbn){
                    return x;
                }
            }

            return book;
        }

        void update_count(int count,string isbn){
            for(auto &x : books){
                if(x.get_isbn() == isbn){
                    x.updateCopies(count);
                }
            }
        }

        void printLibrarydetails(){
            for(auto x : books){
                cout << x.title << " " << x.author << " " << x.get_copiesAvailable() << endl;
            }

            for(auto x : members){
                cout << x.get_memberID() << " " << x.name << endl;
            }
        }

};