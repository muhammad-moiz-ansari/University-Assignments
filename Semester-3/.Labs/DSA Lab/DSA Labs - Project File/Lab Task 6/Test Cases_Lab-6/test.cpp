#include<iostream>
#include "pch.h"
//#include "D:\Documents\Semester-3\.Labs\DS Lab\Lab Task 6\Lab-6 Project File\23i-0523_Moiz Ansari_Q1.cpp"
//#include "D:\Documents\Semester-3\.Labs\DS Lab\Lab Task 6\Lab-6 Project File\23i-0523_Moiz Ansari_Q2.cpp"
#include "C:\Users\Dell\Downloads\Q2.h"

using namespace std;
//// Question 1
//TEST(AddEmployee, T1) {
//    EmployeeList company;
//
//    // Add 3 employees
//    Employee emp1("Alice", "NIC123", "2020-01-01", "F", "Married", 50000, "Manager", 17, "HR");
//    Employee emp2("Bob", "NIC456", "2019-05-15", "M", "Single", 40000, "Engineer", 14, "IT");
//    Employee emp3("Charlie", "NIC789", "2021-06-20", "M", "Married", 60000, "Director", 19, "Finance");
//
//    company.addEmployee(emp1);
//    company.addEmployee(emp2);
//    company.addEmployee(emp3);
//
//    Node<Employee>* temp = company.head;
//    EXPECT_EQ(temp->data.name, "Alice");
//    temp = temp->next;
//    EXPECT_EQ(temp->data.name, "Bob");
//    temp = temp->next;
//    EXPECT_EQ(temp->data.name, "Charlie");
//}
//TEST(SearchEmployeeByNIC, T2) 
//{
//    EmployeeList company;
//
//    Employee emp1("Alice", "NIC123", "2020-01-01", "F", "Married", 50000, "Manager", 17, "HR");
//    Employee emp2("Bob", "NIC456", "2019-05-15", "M", "Single", 40000, "Engineer", 14, "IT");
//
//    company.addEmployee(emp1);
//    company.addEmployee(emp2);
//
//    // Search for Bob by NIC
//    Employee* foundEmployee = company.searchEmployeeByNIC("NIC456");
//    EXPECT_EQ(foundEmployee->name, "Bob");
//    EXPECT_EQ(foundEmployee->salary, 40000);
//    EXPECT_EQ(foundEmployee->department, "IT");
//
//    // Check non-existent employee
//    Employee* notFoundEmployee = company.searchEmployeeByNIC("NIC999");
//    EXPECT_EQ(notFoundEmployee, nullptr);
//}
// 
//TEST(SortEmployeesBySalary, T3) {
//    EmployeeList company;
//
//    // Add 3 employees with varying salaries
//    Employee emp1("Alice", "NIC123", "2020-01-01", "F", "Married", 50000, "Manager", 17, "HR");
//    Employee emp2("Bob", "NIC456", "2019-05-15", "M", "Single", 40000, "Engineer", 14, "IT");
//    Employee emp3("Charlie", "NIC789", "2021-06-20", "M", "Married", 60000, "Director", 19, "Finance");
//
//    company.addEmployee(emp3);  // Charlie (60000)
//    company.addEmployee(emp1);  // Alice (50000)
//    company.addEmployee(emp2);  // Bob (40000)
//
//    company.sortEmployeesBySalary();
//
//    Node<Employee>* temp = company.head;
//    //EXPECT_EQ(temp->data.name, "Bob");
//    //temp = temp->next;
//    //EXPECT_EQ(temp->data.name, "Alice");
//    //temp = temp->next;
//    //EXPECT_EQ(temp->data.name, "Charlie");
//    EXPECT_EQ(temp->data.salary, 40000);
//    temp = temp->next;
//    EXPECT_EQ(temp->data.salary, 50000);
//    temp = temp->next;
//    EXPECT_EQ(temp->data.salary, 60000);
//}
// 
//TEST(ListEmployeesByDepartment, T4) {
//    EmployeeList company;
//
//    // Add employees to different departments
//    Employee emp1("Alice", "NIC123", "2020-01-01", "F", "Married", 50000, "Manager", 17, "HR");
//    Employee emp2("Bob", "NIC456", "2019-05-15", "M", "Single", 40000, "Engineer", 14, "IT");
//    Employee emp3("Charlie", "NIC789", "2021-06-20", "M", "Married", 60000, "Director", 19, "Finance");
//
//    company.addEmployee(emp1);
//    company.addEmployee(emp2);
//    company.addEmployee(emp3);
//
//    testing::internal::CaptureStdout();
//    company.listEmployeesByDepartment("IT");  // Expect only Bob
//    std::string output = testing::internal::GetCapturedStdout();
//    EXPECT_NE(output.find("Bob"), std::string::npos);
//    EXPECT_EQ(output.find("Alice"), std::string::npos);
//    EXPECT_EQ(output.find("Charlie"), std::string::npos);
//}
//
//TEST(EditEmployeeRecord, T5) {
//    EmployeeList company;
//
//    Employee emp1("Alice", "NIC123", "2020-01-01", "F", "Married", 50000, "Manager", 17, "HR");
//    Employee emp2("Bob", "NIC456", "2019-05-15", "M", "Single", 40000, "Engineer", 14, "IT");
//
//    company.addEmployee(emp1);
//    company.addEmployee(emp2);
//
//    // Edit Bob's record
//    company.editEmployeeRecord("NIC456", "Married", 45000, "Senior Engineer", 15, "IT");
//
//    Employee* editedEmp = company.searchEmployeeByNIC("NIC456");
//    EXPECT_EQ(editedEmp->maritalStatus, "Married");
//    EXPECT_EQ(editedEmp->salary, 45000);
//    EXPECT_EQ(editedEmp->designation, "Senior Engineer");
//    EXPECT_EQ(editedEmp->employeeScale, 15);
//}
//
//TEST(EmployeeListTest, EditEmployeeRecord) {
//    EmployeeList company;
//
//    Employee emp1("Alice", "NIC123", "2020-01-01", "F", "Married", 50000, "Manager", 17, "HR");
//    Employee emp2("Bob", "NIC456", "2019-05-15", "M", "Single", 40000, "Engineer", 14, "IT");
//
//    company.addEmployee(emp1);
//    company.addEmployee(emp2);
//
//    // Edit Bob's record
//    company.editEmployeeRecord("NIC456", "Married", 45000, "Senior Engineer", 15, "IT");
//
//    Employee* editedEmp = company.searchEmployeeByNIC("NIC456");
//    ASSERT_NE(editedEmp, nullptr);
//    EXPECT_EQ(editedEmp->maritalStatus, "Married");
//    EXPECT_EQ(editedEmp->salary, 45000);
//    EXPECT_EQ(editedEmp->designation, "Senior Engineer");
//    EXPECT_EQ(editedEmp->employeeScale, 15);
//}
//TEST(EmployeeListTest, ListEmployeesByJoiningDate) {
//    EmployeeList company;
//
//    Employee emp1("Alice", "NIC123", "2020-01-01", "F", "Married", 50000, "Manager", 17, "HR");
//    Employee emp2("Bob", "NIC456", "2019-05-15", "M", "Single", 40000, "Engineer", 14, "IT");
//    Employee emp3("Charlie", "NIC789", "2020-01-01", "M", "Married", 60000, "Director", 19, "Finance");
//
//    company.addEmployee(emp1);
//    company.addEmployee(emp2);
//    company.addEmployee(emp3);
//
//    testing::internal::CaptureStdout();  // Capture the output for testing
//
//    company.listEmployeesByJoiningDate("2020-01-01");
//    std::string output = testing::internal::GetCapturedStdout();
//
//    EXPECT_TRUE(output.find("Alice") != std::string::npos);
//    EXPECT_TRUE(output.find("Charlie") != std::string::npos);
//    EXPECT_FALSE(output.find("Bob") != std::string::npos);  // Bob has a different joining date
//}




// Question 2
TEST(Insert, T1) {
    SLinkedList<int> obj;
    int arr[] = { 0,1,2,3,4,5,6,7 };
    for (int i = 0; i < 8; i++)
    {
        obj.insert(arr[i]);
    }

    Node<int>* temp = obj.head;
    int i = 0;
    obj.print();
    while (temp->getNext() != NULL) {
        EXPECT_EQ(arr[i], temp->getData());
        temp = temp->getNext();
        i++;
    }

}

TEST(InsertatHead, T2) {
    SLinkedList<int> obj;
    int arr[] = { 0,1,2,3,4 };
    for (int i = 0; i < 5; i++)
    {
        obj.insert(arr[i]);
    }

    Node<int>* temp = obj.head;
    int i = 0;
    while (temp->getNext() != NULL) {
        EXPECT_EQ(temp->getData(), arr[i]);
        temp = temp->getNext();
        i++;
    }
    temp = obj.head;
    obj.insertAtHead(66);
    EXPECT_EQ(66, obj.head->getData());
    temp = obj.head->getNext();
    int j = 0;
    obj.print();   //66,0,1,2,3,4 
    while (temp->getNext() != NULL) {
        EXPECT_EQ(temp->getData(), arr[j]);
        temp = temp->getNext();
        j++;
    }
}

TEST(InsertAtIndex, T3) 
{
    int arr[] = { 0, 1, 2, 3 };
    SLinkedList<int> obj1;
    for (int i = 0; i < 4; i++)
    {
        obj1.insert(arr[i]);
    }

    obj1.InsertAtIndex(5, 4); // InsertAtIndex(5 is the value to be inserted, 4 is the Index.no);
    obj1.print();  //0, 1, 2, 3, 5
    Node<int>* temp = obj1.head;
    int j = 0;

    while (temp->getNext() != nullptr) {
        EXPECT_EQ(temp->getData(), arr[j]);
        temp = temp->getNext();
        j++;
    }
}

TEST(Search, T4) {

    SLinkedList<int> obj1;
    for (int i = 0; i < 3; i++)
    {
        obj1.insert(i);
    }
    //obj1.print();
    EXPECT_EQ(2, obj1.search(2));
    ASSERT_NE(3, obj1.search(2));
}


TEST(Update, T5) {
    SLinkedList<int> obj;
    for (int i = 0; i < 5; i++)
    {
        obj.insert(i);
    }
    obj.update(3, 67);     //value to be updated=3, updated_value=67
    obj.print();   //0,1,2,67,4
    Node<int>* temp = obj.head;
    int i = 0;
    int arr[] = { 0,1,2,67,4 };
    while (temp->getNext() != NULL) {
        EXPECT_EQ(arr[i], temp->getData());
        temp = temp->getNext();
        i++;
    }

}

TEST(Delete, T6) {
    SLinkedList<int> obj;

    for (int i = 0; i < 5; i++)
    {
        obj.insert(i);
    }
    obj.remove(3);    //remove value=3
    int arr[] = { 0,1,2,4 };
    obj.print();    //0,1,2,4
    Node<int>* temp = obj.head;
    int i = 0;
    while (temp->getNext() != NULL) {
        EXPECT_EQ(temp->getData(), arr[i]);
        temp = temp->getNext();
        i++;
    }
}
