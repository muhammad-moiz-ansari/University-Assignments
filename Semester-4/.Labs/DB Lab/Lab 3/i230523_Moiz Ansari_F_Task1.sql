CREATE Database Student_Management

CREATE Table Students(
	Student_ID INT Identity(1, 1) Primary Key,
	SName VARCHAR(60) Not Null,
	Gender VARCHAR(8) Not Null,
	DOB DATE NULL,
	Email VARCHAR(70) Not NULL,
	PhoneNo VARCHAR(20) UNIQUE Not NULL,
	City VARCHAR(40) DEFAULT 'unknown'
	);

-- Courses Table
CREATE Table Courses(
	Course_ID INT Identity(1, 1) Primary Key,
	CName VARCHAR(60) Not NULL,
	C_Description VARCHAR(300) NOT NULL,
	Credit_Hrs INT CHECK(Credit_Hrs>=0),
	Department VARCHAR(30) NOT NULL
);

-- Instructors Table
CREATE Table Instructors(
	Instructor_ID INT Identity(1, 1) Primary Key,
	IName VARCHAR(60) Not Null,
	Email VARCHAR(70) Not NULL,
	PhoneNo VARCHAR(20) UNIQUE Not NULL,
	Specialization VARCHAR(40) DEFAULT 'None',
	Hire_Date DATE NOT NULL,
	Salary INT CHECK(Salary>=0) NOT NULL
);

-- Enrollments Table
CREATE Table Enrollments(
	Std_ID INT,
	C_ID INT,
	FOREIGN KEY(Std_ID) REFERENCES Students(Student_ID),
	FOREIGN KEY(C_ID) REFERENCES Courses(Course_ID),
	PRIMARY KEY(Std_ID, C_ID),
	Enrollment_Date DATE Not NULL,
	Grade CHAR CHECK(Grade>='A' AND Grade<='F') NOT NULL,
	E_Status VARCHAR(15) DEFAULT 'Active' CHECK(E_Status = 'Active' OR E_Status = 'Completed' OR E_Status = 'Withdrawn' OR E_Status = 'active' OR E_Status = 'completed' OR E_Status = 'withdrawn')
);

-- Departments Table
CREATE Table Departments(
	Dep_ID INT Identity(1,1) PRIMARY KEY,
	Dep_Name VARCHAR(40) NOT NULL,
	HOD VARCHAR(40) NOT NULL,
	Official_Phone VARCHAR(20) NOT NULL
);

ALTER TABLE Students
DROP COLUMN Email

ALTER TABLE Students
ADD Email VARCHAR(70) NOT NULL

ALTER TABLE Instructors
ALTER COLUMN Salary DECIMAL(10, 2)

SELECT * FROM Students;
SELECT * FROM Departments;
SELECT * FROM Enrollments;
SELECT * FROM Instructors;