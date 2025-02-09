#include <bits/stdc++.h>
#include "Books.h"
#include "Member.h"
#include "Library.h"

using namespace std;

#define endl '\n'

int main(){

    Library lib;

    while(true){
        string word;
        cin >> word;

        if(word == "Book"){
            string cases;
            cin >> cases;

            if(cases == "None"){
                Book newbook;
                lib.addBook(newbook);
            }

            else if(cases == "ExistingBook"){
                string oldisbn , newisbn;
                cin >> oldisbn >> newisbn;
                Book exisitingbook = lib.get_book(oldisbn);
                Book newbook = Book(exisitingbook, newisbn);
                lib.addBook(newbook);                
            }

            else{
                string title = cases;
                string author,isbn;
                cin >> author >> isbn;

                int copiesAvailable, totalCopies;
                cin >> copiesAvailable >> totalCopies;

                Book newbook(title, author, isbn, copiesAvailable, totalCopies);
                lib.addBook(newbook);
            }
        }

        else if(word == "Member"){
            string cases;
            cin >> cases;

            if(cases == "NoBorrowLimit"){
                string id,name;
                cin >> id >> name;  

                Member newmember(id,name);
                lib.addMember(newmember);
            }

            else{
                string id = cases;
                string name;
                int borrowlimit;
                cin >> name >> borrowlimit;

                Member newmember(id, name, borrowlimit);
                lib.addMember(newmember);
            }
        }

        else if(word == "UpdateCopiesCount"){
            string isbn;
            cin >> isbn;
            int count;
            cin >> count;
            lib.update_count(count,isbn);
            
        }

        else if(word == "Borrow"){
            string id;
            string isbn;
            cin >> id >> isbn;

            lib.borrowBook(id,isbn);
        }

        else if(word == "Return"){
            string id;
            string isbn;
            cin>>id>>isbn;

            lib.returnBook(id,isbn);
        }

        else if(word == "PrintBook"){
            string isbn;
            cin >> isbn;

            Book book = lib.get_book(isbn);
            book.printDetails();

        }

        else if(word == "PrintMember"){
            string id;
            cin >> id;

            Member mem = lib.get_member(id);
            mem.printDetails();

        }

        else if(word == "PrintLibrary") {
            lib.printLibrarydetails();
        }

        else if(word == "Done"){
            break;
        }
    }

    return 0;

}