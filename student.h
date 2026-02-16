#ifndef STUDENT_H
#define STUDENT_H

// Student class stores basic student information
class Student {
  public:
    // Creates a student with a first name, last name, ID, and GPA
    Student(const char*, const char*, int, float);

    // Frees dynamically allocated memory
    ~Student();

    // Returns the student's first name
    const char* getFirst();

    // Returns the student's last name
    const char* getLast();

    // Returns the student's ID
    int getID();

    // Returns the student's GPA
    float getGPA();

  private:
    char* first;  
    char* last;   
    int id;       
    float gpa;    
};

#endif
