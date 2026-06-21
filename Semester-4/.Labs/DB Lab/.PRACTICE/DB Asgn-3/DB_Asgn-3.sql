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
    availability_status VARCHAR(20),
	missed_count INT DEFAULT 0,
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
	old_status VARCHAR(30) NULL,
	new_status VARCHAR(30) NULL,
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

DECLARE @admin1 INT = 17, @admin2 INT = 523

-- 1. Insert Trigger on Patients Table

GO
CREATE or ALTER TRIGGER Insert_Patients
ON PATIENT
AFTER INSERT
AS
BEGIN
	DECLARE @admin INT = 17
	INSERT INTO AUDIT_LOG
	SELECT 'INSERT', 'PATIENTS', i.patient_id, @admin, GETDATE()
	FROM INSERTED i
END;
GO

-- 2. Insert and Delete Triggers on Appointments Table

GO
CREATE OR ALTER TRIGGER Insert_Appointements
ON APPOINTMENTS
AFTER INSERT
AS 
BEGIN
	INSERT INTO AUDIT_LOG
	SELECT 'BOOK', 'APPOINTMENTS', i.appointment_id, 523, GETDATE()
	FROM inserted i
END;
GO

GO
CREATE OR ALTER TRIGGER Delete_Appointment
ON APPOINTMENTS
AFTER DELETE
AS
BEGIN
	INSERT INTO AUDIT_LOG
	SELECT 'CANCEL', 'APPOINTMENTS', d.appointment_id, 523, GETDATE()
	FROM deleted d
END
GO

--GO
--CREATE OR ALTER TRIGGER Delete_Appointment
--ON APPOINTMENTS
--AFTER UPDATE
--AS
--BEGIN
--	INSERT INTO AUDIT_LOG
--	SELECT 'CANCEL', 'APPOINTMENTS', d.appointment_id, 523, GETDATE()
--	FROM deleted d
--END
--GO

-- 3. Update Trigger on Doctors Table
GO
CREATE OR ALTER TRIGGER Update_Doctors
ON DOCTOR
AFTER UPDATE
AS
BEGIN
	INSERT INTO AUDIT_LOG
	SELECT 'STATUS_UPDATE', 'DOCTORS', i.doctor_id, 523, GETDATE(), d.availability_status, i.availability_status
	FROM inserted i
	JOIN deleted d ON i.doctor_id = d.doctor_id
	WHERE i.availability_status != d.availability_status
END
GO


-- 4. Conditional Trigger with Status Validation
CREATE OR ALTER TRIGGER Status_Validation
ON APPOINTMENTS
INSTEAD OF Insert
AS
BEGIN
	DECLARE @boolvar1 BIT = 0, @boolvar2 BIT = 0, @var3 INT = 0	-- Bool == 1, then No Insert

	SET @boolvar1 = (SELECT 1 
					FROM DOCTOR d
					JOIN inserted i ON i.doctor_id = d.doctor_id
					WHERE LOWER(d.availability_status) != LOWER('available'))

	SET @boolvar2 = (SELECT 1
					FROM APPOINTMENTS a
					JOIN inserted i ON i.patient_id = a.patient_id
					WHERE CAST(i.appointment_date AS DATE) = CAST(a.appointment_date AS DATE))

	-- 6. Before/After Trigger Combo
	SET @var3 = (SELECT COUNT(*)
				 FROM APPOINTMENTS a
				 WHERE LOWER(a.status) = 'active'
				 GROUP BY a.patient_id)

	IF (@boolvar1 = 1 OR @boolvar2 = 1 OR @var3 > 1)
	BEGIN
		IF (@boolvar1 = 1)
		BEGIN
			PRINT 'Doctor is unavailable'
		END

		IF (@boolvar2 = 1)
		BEGIN
			PRINT 'Appointment already booked on same day'
		END

		IF (@var3 > 1)
			PRINT 'No more than 1 active appointment per patient'

		INSERT INTO AUDIT_LOG
		SELECT 'REJECTED_INSERT', 'APPOINTMENTS', i.appointment_id, 523, GETDATE(), NULL, NULL
		FROM inserted i
	END
	ELSE
	BEGIN
		INSERT INTO APPOINTMENTS
		SELECT i.patient_id, i.doctor_id, i.appointment_date, i.status
		FROM inserted i
	END
END;


-- 5. Trigger for Automatic Prescription Issue
GO
CREATE OR ALTER TRIGGER Auto_Prescribe
ON APPOINTMENTS
AFTER UPDATE
AS 
BEGIN
	DECLARE @boolvar BIT = 0
	DECLARE @id INT
	SET @boolvar = (SELECT 1
					FROM deleted d
					JOIN inserted i ON i.appointment_id = d.appointment_id
					WHERE LOWER(i.status) = 'completed' AND i.status != d.status)
	IF (@boolvar = 1)
	BEGIN
		INSERT INTO PRESCRIPTION
		SELECT i.appointment_id, i.doctor_id, i.patient_id, 'Diagnosis pending', 'N/A', 'Awaiting diagnosis', GETDATE()
		FROM inserted i

		SET @id = (SELECT MAX(p.prescription_id) FROM PRESCRIPTION p)

		INSERT INTO AUDIT_LOG
		SELECT 'PRESCRIBE', 'PRESCRIBTION', @id, 523, GETDATE(), NULL, NULL
		FROM inserted i
	END
END
GO

-- 6. Before/After Trigger Combo
-- After
GO
CREATE OR ALTER TRIGGER Log_Appointment
ON APPOINTMENTS
AFTER INSERT
AS 
BEGIN
	INSERT INTO AUDIT_LOG
	SELECT 'Appointment', 'APPOINTMENTS', i.appointment_id, 523, GETDATE(), NULL, NULL
	FROM inserted i

END
GO

-- 7. Cascading Triggers with Logic Conflict
GO
CREATE OR ALTER TRIGGER Missed_Appointments
ON APPOINTMENTS
AFTER UPDATE
AS 
BEGIN
	-- 1.............
	UPDATE PATIENT 
	SET missed_count = missed_count + 1
	FROM PATIENT p
	JOIN inserted i ON i.patient_id = p.patient_id
	JOIN deleted d ON d.appointment_id = i.appointment_id
	WHERE LOWER(i.status) = 'missed' AND LOWER(d.status) != 'missed'

	UPDATE PATIENT 
	SET isIrresponsible = 1
	FROM PATIENT p
	WHERE p.missed_count > 3

	INSERT INTO AUDIT_LOG
	SELECT 'Missed_Appointment', 'APPOINTMENTS', i.appointment_id, 523, GETDATE(), NULL, NULL
	FROM inserted i
	JOIN deleted d ON d.appointment_id = i.appointment_id
	WHERE LOWER(i.status) = 'missed' AND LOWER(d.status) != 'missed'

	--2................
	UPDATE DOCTOR 
	SET missed_count = missed_count + 1
	FROM DOCTOR do
	JOIN inserted i ON i.doctor_id = do.doctor_id
	JOIN deleted d ON d.appointment_id = i.appointment_id
	WHERE LOWER(i.status) = 'missed' AND LOWER(d.status) != 'missed'

	UPDATE DOCTOR
	SET availability_status = 'unavailable'
	FROM DOCTOR d
	WHERE d.missed_count >= 3

END
GO

