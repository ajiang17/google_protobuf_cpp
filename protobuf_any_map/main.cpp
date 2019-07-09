#include <iostream>
#include <unordered_map>
#include "person.pb.h"

#include <google/protobuf/any.h>
#include <google/protobuf/any.pb.h>
using namespace std;
typedef google::protobuf::Message GPMessage;
typedef google::protobuf::Any Any;

void checkAny(Test& test) {
    // if(!test.has_data()) {
    //     cout << "not has_data" <<endl;
    //     return;
    // }
    Apply_data data1;
    Apply_list list1;
    cout<< test.name() << endl;
    
    auto& map_data = *(test.mutable_data());
    for(auto& kv : map_data) {
        if(kv.second.Is<Apply_data>()) {
            if(kv.second.UnpackTo(&data1)) {
                cout << data1.apply_name() << endl;
                cout << data1.apply_time() << endl;
                cout << "unpackTo data success" << endl;
            } else {
                cout << "unpackTo data error" << endl;
            }
        }else{
            cout << "is not apply_data" << endl;
        }
    }

//    if(test.data.second.Is<Apply_list>()) {
//        if(test.data.second.UnpackTo(&list1)) {
//            cout << list1.apply_list_id() << endl;
//            cout << "unpackTo list success" << endl;
//        }else {
//            cout << "unpackTo list error" << endl;
//        }
//    }else {
//        cout << "unpackTo list error" << endl;
//    }
}

int main() {
    Test test;

    Apply_data data;
    data.set_apply_name("zhang");
    data.set_apply_time(111);
    
    Apply_list list;
    list.set_apply_list_add("liang");
    list.set_apply_list_id(222);

    // she zhi any shuju
    cout << "set apply_data data: "<< endl;
    test.set_name("eq94");
    
    auto& test_data = *(test.mutable_data());
    test_data["eq94"].PackFrom(data);
    
   
    cout<<"check ANY : "<<endl;
    // zhao dao any shuju jiexi
    checkAny(test);

    //-------------------------------

    // she zhi any shuju
//    cout << "set apply_list data: " << endl;
//    test.mutable_data()->PackFrom(list);

    // zhao dao any shuju jiexi
//    checkAny(test);

    //--------------------------------
    // clear
    cout << "clear data: "<< endl;
    test.clear_data();

    checkAny(test);

    return 0;
}
// g++ -o main  main.cpp person.pb.cc -L /usr/local/lib -lprotobuf -std=c++11 -g -lpthread
