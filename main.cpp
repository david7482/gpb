#include <iostream>

#include "proto/test0.pb.h"

using namespace std;

int main()
{
    // Verify that the version of the library that we linked against is
    // compatible with the version of the headers we compiled against.
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    tutorial::AddressBook addressBookWrite;
    auto person = addressBookWrite.add_person();
    {
        person->set_id(0);
        person->set_name("person0");
        person->set_email("person0@gmail.com");

        tutorial::Person::PhoneNumber *phone_number = nullptr;
        phone_number = person->add_phone();
        {
            phone_number->set_number("0000");
            phone_number->set_type(tutorial::Person::HOME);
        }
        phone_number = person->add_phone();
        {
            phone_number->set_number("0001");
            phone_number->set_type(tutorial::Person::WORK);
        }
        phone_number = person->add_phone();
        {
            phone_number->set_number("0002");
            phone_number->set_type(tutorial::Person::MOBILE);
        }
    }

    person = addressBookWrite.add_person();
    {
        person->set_id(1);
        person->set_name("person1");
        person->set_email("person1@gmail.com");

        tutorial::Person::PhoneNumber *phone_number = nullptr;
        phone_number = person->add_phone();
        {
            phone_number->set_number("0000");
            phone_number->set_type(tutorial::Person::HOME);
        }
        phone_number = person->add_phone();
        {
            phone_number->set_number("0001");
            phone_number->set_type(tutorial::Person::WORK);
        }
        phone_number = person->add_phone();
        {
            phone_number->set_number("0002");
            phone_number->set_type(tutorial::Person::MOBILE);
        }
    }

    std::string address_book_string = addressBookWrite.SerializeAsString();
    cout << "ByteSize: " << addressBookWrite.ByteSize() << endl;
    cout << "ByteSize: " << address_book_string.length() << endl;

    tutorial::AddressBook addressBookRead;
    addressBookRead.ParseFromString(address_book_string);
    for (int i = 0; i < addressBookRead.person_size(); ++i) {
        const tutorial::Person& person = addressBookRead.person(i);

        cout << "Person ID: " << person.id() << endl;
        cout << "  Name: " << person.name() << endl;
        if (person.has_email()) {
            cout << "  E-mail address: " << person.email() << endl;
        }

        for (int j = 0; j < person.phone_size(); j++) {
            const tutorial::Person::PhoneNumber& phone_number = person.phone(j);

            switch (phone_number.type()) {
                case tutorial::Person::MOBILE:
                    cout << "  Mobile phone #: ";
                    break;
                case tutorial::Person::HOME:
                    cout << "  Home phone #: ";
                    break;
                case tutorial::Person::WORK:
                    cout << "  Work phone #: ";
                    break;
            }
            cout << phone_number.number() << endl;
        }
    }

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}