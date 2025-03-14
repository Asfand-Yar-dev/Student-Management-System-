#include<iostream>  
#include<string>  
#include<windows.h>  
using namespace std;  
  
class Course {  
public:  
    string courseName;  
    int Course_ID;  
};  
  
class Student {  
public:  
    int CMS_ID;  
    string first_name;  
    string last_name;  
    string DOB;  
    string Cnic;  
    string Cell_no;  
    Course* courses[6];  
  
    Student(int id, const string& fName)   
    {  
        CMS_ID = id;  
        first_name = fName;  
        for (int i = 0; i < 6; ++i)   
        {  
            courses[i] = NULL;  
        }  
    }  
};  
  
class Node {  
public:  
    Student* data;  
    Node* left;  
    Node* right;  
  
    Node(Student* el, Node* l = NULL, Node* r = NULL) {  
        data = el;  
        left = l;  
        right = r;  
    }  
};  
  
class StudentRecord {  
public:  
    Node* root;  
    bool studentAdded;  // Variable to track whether a student has been added  
  
    // Functions  
    Node* insert(Node* node, Student* student);  
    Node* search(Node* node, int studentId); 
    Node* findMin(Node* node);
    void update_Student(int studentId, Student* newStudent);  
    Node* deleteNode(Node* node, int studentId);  
    void displayInOrder(Node* node);  
    void add_courses(int studentId, const Course& course);  
    void display_courses(Node* node, int studentId); 
    Node* deleteCourses(Node* node, int studentId, int courseId);  
  
    // Constructor  
    StudentRecord() {  
        root = NULL;  
        studentAdded = false;  // Initialize to false  
    }  
      
    //calling functions
    void add_Student(Student* student);  
    void search_Student(int studentId);  
    void delete_Student(int studentId); 
	void show_Courses(int studentId); 
	void delete_courses(Node* node, int studentId, int courseId); 
	void displayAllStudents();  
};  
  
Node* StudentRecord::insert(Node* node, Student* student)   
{  
    if (node == NULL) {  
        node = new Node(student, NULL, NULL);  
    }  
    else if (student->CMS_ID < node->data->CMS_ID) {  
        node->left = insert(node->left, student);  
    }  
    else if (student->CMS_ID > node->data->CMS_ID) {  
        node->right = insert(node->right, student);  
    }  
    else {  
        cout << "\t\t\t\tStudent With the Same ID exist : " << endl;  
    }  
    return node;  
}  
  
void StudentRecord::add_Student(Student* student)   
{  
    root = insert(root, student);  
    studentAdded = true;  // Set the flag to true after adding a student  
}  
  
Node* StudentRecord::search(Node* node, int studentId)   
{  
    if (node == NULL || node->data->CMS_ID == studentId)   
    {  
        return node;  
    }  
    else if (studentId < node->data->CMS_ID)   
    {  
        return search(node->left, studentId);  
    }  
    else   
    {  
        return search(node->right, studentId);  
    }  
}  
  
void StudentRecord::search_Student(int studentId)   
{  
    Node* result = search(root, studentId);  
    if (result)   
    {  
        cout << "\t\t\t\tStudent Found " << endl;  
        cout << "\t\t\t\tName: " << result->data->first_name << " " << result->data->last_name << endl;  
        cout << "\t\t\t\tCMS: " << result->data->CMS_ID << endl;  
    }  
    else   
    {  
        cout << "\t\t\t\tStudent Not Found!!! " << endl;  
    }  
}  
  
Node* StudentRecord::findMin(Node* node)   
{  
    while (node->left != NULL)   
    {  
        node = node->left;  
    }  
    return node;  
}  
  
Node* StudentRecord::deleteNode(Node* node, int studentId)   
{  
    if (node == NULL)   
    {  
        return node;  
    }  
  
    if (studentId < node->data->CMS_ID)   
    {  
        node->left = deleteNode(node->left, studentId);  
    }   
    else if (studentId > node->data->CMS_ID)   
    {  
        node->right = deleteNode(node->right, studentId);  
    }   
    else   
    {  
        // Node with only one child or no child  
        if (node->left == NULL)   
        {  
            Node* temp = node->right;  
            delete node;  
            cout << "\t\t\t\tStudent with ID " << studentId << " deleted successfully." << endl;  
            return temp;  
        }   
        else if (node->right == NULL)   
        {  
            Node* temp = node->left;  
            delete node;  
            cout << "\t\t\t\tStudent with ID " << studentId << " deleted successfully." << endl;  
            return temp;  
        }  
  
        // Node with two children, get the inorder successor (smallest in the right subtree)  
        Node* temp = findMin(node->right);  
  
        // Copy the inorder successor's content to this node  
        node->data->CMS_ID = temp->data->CMS_ID;  
        node->data->first_name = temp->data->first_name;  
        // Copy other properties as needed  
  
        // Delete the inorder successor  
        node->right = deleteNode(node->right, temp->data->CMS_ID);  
  
        cout << "\t\t\t\tStudent with ID " << studentId << " deleted successfully." << endl;  
    }  
    return node;  
}  
  
void StudentRecord::delete_Student(int studentId)   
{  
    root = deleteNode(root, studentId);  
}  
  
void StudentRecord::update_Student(int studentId, Student* newStudent)   
{  
    Node* updatedNode = search(root, studentId);  
  
    if(updatedNode)   
    {  
        updatedNode->data = newStudent;  
        cout << "\t\t\t\tStudent with this ID " << studentId << " updated successfully." << endl;  
    }  
    else   
    {  
        cout << "\t\t\t\tStudent with this ID " << studentId << " not found. Update failed." << endl;  
    }  
}  
  
void StudentRecord::add_courses(int studentId, const Course& course)   
{  
    Node* studentNode = search(root, studentId);  
    if (studentNode)   
    {  
        int numCourses = 6;  
        //check if there is any course before
        if (studentNode->data->courses[0] == NULL)   
        {  
            for (int i = 0; i < numCourses; ++i)   
            {  
                studentNode->data->courses[i] = new Course();  // Initialize each course pointer  
            }  
        }  
  
        // Check for duplicate course  
        bool duplicateCourse = false;  
        for (int i = 0; i < numCourses; ++i)   
        {  
            if (studentNode->data->courses[i]->Course_ID == course.Course_ID)   
            {  
                duplicateCourse = true;  
                cout << "Duplicate Course : " << endl;  
                break;  
            }  
        }  
  
        if (!duplicateCourse)   
        {  
            // Find the first empty slot in the array and add the course  
            for (int i = 0; i < numCourses; ++i)   
            {  
                if (studentNode->data->courses[i]->Course_ID == 0)   
                {  
                    *studentNode->data->courses[i] = course;  
                    cout << "\t\t\t\tCourse added successfully." << endl;  
                    break;  
                }  
            }  
        }  
        else   
        {  
            cout << "\t\t\t\tDuplicate course. Cannot add the same course again." << endl;  
        }  
    }  
    else   
    {  
        cout << "\t\t\t\tStudent not found. Cannot add course." << endl;  
    }  
}  
  
void StudentRecord::display_courses(Node* node, int studentId)   
{  
    Node* studentNode = search(node, studentId);  
    if (studentNode)   
    {  
        int numCourses = 6;  
        if (studentNode->data->courses[0] != NULL)   
        {  
            cout << "\t\t\t\tCourses for Student ID " << studentId << ":" << endl;  
            for (int i = 0; i < numCourses; ++i)   
            {  
                if (studentNode->data->courses[i] != NULL)  // Check if the Course pointer is not NULL  
                {  
                    cout << "\t\t\t\tCourse ID: " << studentNode->data->courses[i]->Course_ID << endl;  
                    cout << "\t\t\t\tCourse Name: " << studentNode->data->courses[i]->courseName << endl;  
                }  
            }  
        }  
        else   
        {  
            cout << "\t\t\t\tNo courses found for Student ID " << studentId << "." << endl;  
        }  
    }  
    else   
    {  
        cout << "\t\t\t\tStudent not found. Cannot display courses." << endl;  
    }  
}  
  
void StudentRecord::show_Courses(int studentId)   
{  
    display_courses(root, studentId);  
}  
  
Node* StudentRecord::deleteCourses(Node* node, int studentId, int courseId)  
{  
    // Find the student node  
    Node* studentNode = search(node, studentId);  
  
    if (studentNode)  
    {  
        // Display the courses before deletion  
        int numCourses = 6;  
        cout << "\t\t\t\tStudent ID: " << studentNode->data->CMS_ID << endl;  
        cout << "\t\t\t\tCurrent Courses: ";  
        for (int i = 0; i < numCourses; ++i)  
        {  
            if (studentNode->data->courses[i] != NULL)  
            {  
                cout << studentNode->data->courses[i]->courseName << " ";  
            }  
        }  
        cout << endl;  
  
        // Search for the course to delete  
        int courseIndex = -1;  
        for (int i = 0; i < numCourses; ++i)  
        {  
            if (studentNode->data->courses[i] != NULL && studentNode->data->courses[i]->Course_ID == courseId)  
            {  
                courseIndex = i;  
                break;  
            }  
        }  
  
        if (courseIndex != -1)  
        {  
            // Perform deletion of the selected course  
            delete studentNode->data->courses[courseIndex];  
            studentNode->data->courses[courseIndex] = NULL;  // Set the pointer to nullptr after deletion  
  
            // Display the courses after deletion  
            cout<<"\t\t\t\tAfter Deletion of course : "<<endl;  
            cout << "\t\t\t\tRemaining Courses: ";  
            for (int i = 0; i < numCourses; ++i)  
            {  
                if (studentNode->data->courses[i] != NULL)  
                {  
                    cout << studentNode->data->courses[i]->courseName << " ";  
                }  
            }  
            cout << endl;  
        }  
        else  
        {  
            cout << "\t\t\t\tCourse not found. Cannot delete." << endl;  
        }  
    }  
    else  
    {  
        cout << "\t\t\t\tStudent not found. Cannot delete courses." << endl;  
    }  
  
    return node;  
}  
  
void StudentRecord::delete_courses(Node* node, int studentId, int courseId)   
{  
    root = deleteCourses(root, studentId, courseId);  
}  
void StudentRecord::displayInOrder(Node* node)   
{  
    if (node)   
    {  
        displayInOrder(node->left);  
        cout << "\t\t\t\tStudent Name: " << node->data->first_name << " " << node->data->last_name << " - " << node->data->CMS_ID << endl;  
        displayInOrder(node->right);  
    }  
}  
  
void StudentRecord::displayAllStudents()   
{  
    cout << "\t\t\t\tAll Students in the System:" << endl;  
    displayInOrder(root);  
}  
  
int main()  
{  
    system("Color 80");  
    StudentRecord system;  
    int choice;  
      
    do {  
        cout << "\t\t\t\t________________________________________ " << endl;  
        cout << "\n\t\t\t\t    Student Record Management System     " << endl;  
        cout << "\t\t\t\t________________________________________ " << endl;  
  
        cout << "\t\t\t\t===================== MENU =======================" << endl;  
        cout << "\t\t\t\t 1) Add Student\n";  
        if (system.studentAdded) {  
            cout << "\t\t\t\t 2) Search Student\n";  
            cout << "\t\t\t\t 3) Update Student\n";  
            cout << "\t\t\t\t 4) Delete Student\n";  
            cout << "\t\t\t\t 5) Add Course to Student\n";  
            cout << "\t\t\t\t 6) Show Courses of a Student\n";  
            cout << "\t\t\t\t 7) Delete Courses of a Student\n";  
            cout << "\t\t\t\t 8) Display All Students\n";  
        }  
        cout<<"\t\t\t\t 9) Exit : "<<endl;  
        cout << "\t\t\t\t Enter your choice: ";  
        cin >> choice;  
  
        switch (choice)   
        {  
        case 1:   
        {  
            char ch = 'y';  
            int studentId;  
            string studentName, DOB, cellNo;  
            while (ch != 'n') {  
                cout << "\t\t\t\tEnter student ID: ";  
                cin >> studentId;  
                cout << "\t\t\t\tEnter student name: ";  
                cin.ignore();  
                getline(cin, studentName);  
                cout << "\t\t\t\tEnter student Date of Birth: ";  
                getline(cin, DOB);  
                cout << "\t\t\t\tEnter student Phone No: ";  
                getline(cin, cellNo);  
                Student* newStudent = new Student(studentId, studentName);  
                system.add_Student(newStudent);  
  
                cout << "\t\t\t\tAdd another (y/n) : ";  
                cin >> ch;  
            }  
            break;  
        }  
        case 2:   
        {  
            int studentId;  
            cout << "\t\t\t\tEnter student ID to search: ";  
            cin >> studentId;  
            system.search_Student(studentId);  
            break;  
        }  
        case 3: {  
            int studentId;  
            string updatedName;  
            cout << "\t\t\t\tEnter student ID to update: ";  
            cin >> studentId;  
            cout << "\t\t\t\tEnter updated student name: ";  
            cin.ignore();  
            getline(cin, updatedName);  
            Student* updatedStudent = new Student(studentId, updatedName);  
            system.update_Student(studentId, updatedStudent);  
            break;  
        }  
        case 4: 
		{  
            int studentId;  
            cout << "\t\t\t\tEnter student ID to delete: ";  
            cin >> studentId;  
            system.delete_Student(studentId);  
            break;  
        }  
        case 5: 
		{  
            int studentId, courseId;  
            string courseName;  
            char ch = 'y';  
            while(ch != 'n')  
            {  
                cout << "\t\t\t\tEnter student ID to add course: ";  
                cin >> studentId;  
                cout << "\t\t\t\tEnter course ID: ";  
                cin >> courseId;  
                cout << "\t\t\t\tEnter course name: ";  
                cin.ignore();  
                getline(cin, courseName);  
                Course newCourse{ courseName, courseId };  
                system.add_courses(studentId, newCourse);  
                  
                cout<<"\t\t\t\tAdd another (y/n) : ";  
                cin>>ch;  
            }  
              
            break;  
        }  
        case 6: 
		{  
            int studentId;  
            cout << "\t\t\t\tEnter student ID to show courses: ";  
            cin >> studentId;  
            system.show_Courses(studentId);  
            break;  
        }  
        case 7: 
		{  
            int studentId, courseId;  
            cout << "\t\t\t\tEnter student ID: ";  
            cin >> studentId;  
            cout << "\t\t\t\tEnter course ID to delete: ";  
            cin >> courseId;  
            system.delete_courses(system.root, studentId,courseId);  
            break;  
        }  
        case 8: 
		{  
            system.displayAllStudents();  
            break;  
        }  
        case 9: 
		{  
            cout << "\t\t\t\tExiting program. Goodbye!\n";  
            break;  
        }  
        default: 
		{  
            cout << "\t\t\t\tInvalid choice. Please try again.\n";  
            break;  
        }  
        }  
    } while (choice != 9);  
  
    return 0;  
}
