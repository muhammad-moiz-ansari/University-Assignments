--CREATE DATABASE Hospital_CaseStudy
--USE Hospital_CaseStudy

----------------------------------------------------------------------------------
---------------------------------             ------------------------------------
-------------------------------  TABLES CREATE  ----------------------------------
---------------------------------             ------------------------------------
----------------------------------------------------------------------------------

CREATE TABLE PATIENT (
    patient_id INT IDENTITY(101, 1) PRIMARY KEY,
    name VARCHAR(100),
    gender VARCHAR(10),
    dob DATE,
    contact VARCHAR(15),
	missed_count INT DEFAULT 0,
	isIrresponsible INT DEFAULT 0	-- flag
);

CREATE TABLE DOCTOR (
    doctor_id INT IDENTITY(201, 1) PRIMARY KEY,
    name VARCHAR(100),
    specialization VARCHAR(100),
    availability_status VARCHAR(20)
);

CREATE TABLE APPOINTMENTS (
    appointment_id INT IDENTITY(301, 1) PRIMARY KEY,
    patient_id INT,
    doctor_id INT,
	appointment_date DATE,
    status VARCHAR(50),		-- Booked, Cancelled, Completed
    FOREIGN KEY (patient_id) REFERENCES PATIENT(patient_id),
    FOREIGN KEY (doctor_id) REFERENCES DOCTOR(doctor_id)
);

CREATE TABLE PRESCRIPTION (
    prescription_id INT IDENTITY(401, 1) PRIMARY KEY,
    appointment_id INT,
	doctor_id INT,
    patient_id INT,
    medication VARCHAR(200),
	dosage VARCHAR(200),
	instructions VARCHAR(200),
    date_issued DATE,
    FOREIGN KEY (appointment_id) REFERENCES APPOINTMENTS(appointment_id),
    FOREIGN KEY (patient_id) REFERENCES PATIENT(patient_id),
    FOREIGN KEY (doctor_id) REFERENCES DOCTOR(doctor_id)
);

CREATE TABLE ADMIN (
    account_id INT PRIMARY KEY,
	name VARCHAR(70),
);

CREATE TABLE AUDIT_LOG (
    log_id INT IDENTITY(1, 1) PRIMARY KEY,
    action_type VARCHAR(50),
    table_name VARCHAR(50),
    entity_id INT,
    performed_by INT,
    timestamp DATETIME,
    FOREIGN KEY (performed_by) REFERENCES ADMIN(account_id)
);

--DROP TABLE PATIENT
--DROP TABLE DOCTOR
--DROP TABLE APPOINTMENTS
--DROP TABLE PRESCRIPTION
--DROP TABLE ADMIN
--DROP TABLE AUDIT_LOG


----------------------------------------------------------------------------------
----------------------------------------------------------------------------------
---------------------------------- DATA LOAD -------------------------------------
----------------------------------------------------------------------------------
----------------------------------------------------------------------------------

BULK INSERT Admin 
FROM 'D:\Documents\Semester-4\.Labs\DB Lab\PRACTICE\DB Asgn-3\Admin.csv' 
WITH (
    FORMAT = 'CSV',
    FIRSTROW = 2,
    FIELDTERMINATOR = ',',
    ROWTERMINATOR = '0x0a'
);

BULK INSERT Appointments 
FROM 'D:\Documents\Semester-4\.Labs\DB Lab\PRACTICE\DB Asgn-3\Appointments.csv' 
WITH (
    FORMAT = 'CSV',
    FIRSTROW = 2,
    FIELDTERMINATOR = ',',
    ROWTERMINATOR = '0x0a'
);

BULK INSERT Audit_Log 
FROM 'D:\Documents\Semester-4\.Labs\DB Lab\PRACTICE\DB Asgn-3\Audit_Log.csv' 
WITH (
    FORMAT = 'CSV',
    FIRSTROW = 2,
    FIELDTERMINATOR = ',',
    ROWTERMINATOR = '0x0a'
);

BULK INSERT Doctor
FROM 'D:\Documents\Semester-4\.Labs\DB Lab\PRACTICE\DB Asgn-3\Doctors.csv' 
WITH (
    FORMAT = 'CSV',
    FIRSTROW = 2,
    FIELDTERMINATOR = ',',
    ROWTERMINATOR = '0x0a'
);

BULK INSERT Patient
FROM 'D:\Documents\Semester-4\.Labs\DB Lab\PRACTICE\DB Asgn-3\Patients.csv' 
WITH (
    FORMAT = 'CSV',
    FIRSTROW = 2,
    FIELDTERMINATOR = ',',
    ROWTERMINATOR = '0x0a'
);

BULK INSERT Prescription
FROM 'D:\Documents\Semester-4\.Labs\DB Lab\PRACTICE\DB Asgn-3\Prescriptions.csv' 
WITH (
    FORMAT = 'CSV',
    FIRSTROW = 2,
    FIELDTERMINATOR = ',',
    ROWTERMINATOR = '0x0a'
);


SELECT * FROM PATIENT
SELECT * FROM DOCTOR
SELECT * FROM APPOINTMENTS
SELECT * FROM PRESCRIPTION
SELECT * FROM AUDIT_LOG
SELECT * FROM ADMIN;

---------------------------------------------------------------------------
-----------------------                             -----------------------
--------------------            SQL QUERIES            --------------------
-----------------------                             -----------------------
---------------------------------------------------------------------------

DECLARE @admin1 INT = 17, @admin2 INT = 23

-- 1. Insert Trigger on Patients Table 

GO
CREATE or ALTER TRIGGER Insert_Pateints
ON 

GO