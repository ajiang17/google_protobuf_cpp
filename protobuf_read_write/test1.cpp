#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"
using namespace std;

// This function fills in a Person Message based on user input
void PromptForAddress(tutorial::Person* person) {
    cout<<"Enter persion ID number : ";
    int id;
    cin >> id;
    person->set_id(id);
    cin.ignore(256, '\n');

    cout<<"Enter name: ";
    getline(cin, *person->mutable_name());

    cout<<"Enter email address(blank for none): ";
    string email;
    getline(cin, email);
    if(!email.empty()) {
        person->set_email(email);
    }

    while(true) {
        cout<<"Enter a phone number (or leave blank to finish: ";
        string number;
        getline(cin, number);
        if(number.empty()) {
            break;
        }
        
        tutorial::Person::PhoneNumber* phone_number = person->add_phone();
        phone_number->set_number(number);
        
        cout<<"Is this a mobile, home, or wokr phone? ";
        string type;
        getline(cin, type);
        if(type == "mobile") {
            phone_number->set_type(tutorial::Person::MOBILE);
        }else if(type == "home") {
            phone_number->set_type(tutorial::Person::HOME);
        }else if(type == "work") {
            phone_number->set_type(tutorial::Person::WORK);
        }else {
            cout<<"Unknow phone type, Using default."<<endl;
        }
    }

}

int main(int argc, char* argv[]) {

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if(argc !=2) {
        cerr<<"Usage: "<<argv[0]<<" ADDRESS_BOOK_FILE"<<endl;
        return -1;
    }
    tutorial::AddressBook address_book;

    {
        // Write the new address book to disk
        fstream output(argv[1], ios::out | ios::trunc | ios::binary);
        if(!address_book.SerializeToOstream(&output)) {
            cerr<<"Failed to write address book. "<<endl;
            return -1;
        }
    }

    //Optional: Delete all global objects allocated bu libprotobuf
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
// g++ test1.cpp addressbook.pb.cc -L /usr/lib/x86_64-linux-gnu -l protobuf -o test1
