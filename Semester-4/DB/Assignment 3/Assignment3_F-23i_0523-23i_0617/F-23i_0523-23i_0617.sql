--CREATE DATABASE Hospital_CaseStudy
--USE Hospital_CaseStudy

----------------------------------------------------------------------------------
---------------------------------             ------------------------------------
-------------------------------  TABLES CREATE  ----------------------------------
---------------------------------             ------------------------------------
----------------------------------------------------------------------------------

CREATE TABLE PATIENT (
    patient_id INT PRIMARY KEY,
    name VARCHAR(100),
    gender VARCHAR(10),
    dob DATE,
    contact VARCHAR(15),
	missed_count INT DEFAULT 0,
	isIrresponsible INT DEFAULT 0	-- flag
);

CREATE TABLE DOCTOR (
    doctor_id INT PRIMARY KEY,
    name VARCHAR(100),
    specialization VARCHAR(100),
    availability_status VARCHAR(20)
);

CREATE TABLE APPOINTMENTS (
    appointment_id INT PRIMARY KEY,
    patient_id INT,
    doctor_id INT,
	appointment_date DATE,
    status VARCHAR(50),		-- Booked, Cancelled, Completed
    FOREIGN KEY (patient_id) REFERENCES PATIENT(patient_id),
    FOREIGN KEY (doctor_id) REFERENCES DOCTOR(doctor_id)
);

CREATE TABLE PRESCRIPTION (
    prescription_id INT PRIMARY KEY,
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
    log_id INT PRIMARY KEY,
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
FROM 'D:\Documents\Semester-4\1. DB\Assignments\Assignment 3\CSV\Admin.csv' 
WITH (
    FORMAT = 'CSV',
    FIRSTROW = 2,
    FIELDTERMINATOR = ',',
    ROWTERMINATOR = '0x0a'
);

BULK INSERT Appointments 
FROM 'D:\Documents\Semester-4\1. DB\Assignments\Assignment 3\CSV\Appointments.csv' 
WITH (
    FORMAT = 'CSV',
    FIRSTROW = 2,
    FIELDTERMINATOR = ',',
    ROWTERMINATOR = '0x0a'
);

BULK INSERT Audit_Log 
FROM 'D:\Documents\Semester-4\1. DB\Assignments\Assignment 3\CSV\Audit_Log.csv' 
WITH (
    FORMAT = 'CSV',
    FIRSTROW = 2,
    FIELDTERMINATOR = ',',
    ROWTERMINATOR = '0x0a'
);

BULK INSERT Doctor
FROM 'D:\Documents\Semester-4\1. DB\Assignments\Assignment 3\CSV\Doctors.csv' 
WITH (
    FORMAT = 'CSV',
    FIRSTROW = 2,
    FIELDTERMINATOR = ',',
    ROWTERMINATOR = '0x0a'
);

BULK INSERT Patient
FROM 'D:\Documents\Semester-4\1. DB\Assignments\Assignment 3\CSV\Patients.csv' 
WITH (
    FORMAT = 'CSV',
    FIRSTROW = 2,
    FIELDTERMINATOR = ',',
    ROWTERMINATOR = '0x0a'
);

BULK INSERT Prescription
FROM 'D:\Documents\Semester-4\1. DB\Assignments\Assignment 3\CSV\Prescriptions.csv' 
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

--Task 1
GO
Create or ALTER Trigger patient_safety
on PATIENT
After Insert
as
begin
	Declare @temp INT;
	DECLARE @admin1 INT = 17, @admin2 INT = 23
	Select @temp=patient_id
	from inserted
	DECLARE @pres_id INT
	SET @pres_id = (SELECT TOP 1 pr.log_id FROM AUDIT_LOG pr ORDER BY pr.log_id DESC)
	SET @pres_id = @pres_id + 1;
	Insert into audit_log values(@pres_id,'INSERT','PATIENTS',@temp, @admin1,getdate());
end
GO

INSERT INTO PATIENT VALUES (121, 'Umar Farooq', 'M', '1990-01-01', '1990112233', 0, 0);
SELECT * FROM AUDIT_LOG


--Task 2
GO
Create or ALTER Trigger appointment_safety
on APPOINTMENTS
After Insert
as
begin
	DECLARE @admin1 INT = 17, @admin2 INT = 23
	Declare @temp INT;
	Select @temp=appointment_id
	from inserted
	DECLARE @pres_id INT
	SET @pres_id = (SELECT TOP 1 pr.log_id FROM AUDIT_LOG pr ORDER BY pr.log_id DESC)
	SET @pres_id = @pres_id + 1;
	Insert into audit_log values(@pres_id,'BOOK','APPOINTMENTS',@temp, @admin1,getdate());
end;
GO

GO
Create or ALTER Trigger appointment_safety2
on APPOINTMENTS
After DELETE
as
begin
	DECLARE @admin1 INT = 17, @admin2 INT = 23
	Declare @temp INT;
	Select @temp=appointment_id
	from deleted
	DECLARE @pres_id INT
	SET @pres_id = (SELECT TOP 1 pr.log_id FROM AUDIT_LOG pr ORDER BY pr.log_id DESC)
	SET @pres_id = @pres_id + 1;
	Insert into audit_log values(@pres_id,'CANCEL','APPOINTMENTS',@temp, @admin1,getdate());
end
GO

DECLARE @app_id INT = (SELECT ISNULL(MAX(appointment_id), 320) + 1 FROM APPOINTMENTS);
INSERT INTO APPOINTMENTS VALUES (@app_id, 120, 210, '2025-05-13', 'Booked');
SELECT * FROM AUDIT_LOG

DECLARE @app_id INT = (SELECT ISNULL(MAX(appointment_id), 320) + 1 FROM APPOINTMENTS);
DELETE FROM APPOINTMENTS WHERE appointment_id = @app_id;
SELECT * FROM AUDIT_LOG

--Task 3
GO
Create or ALTER Trigger doctor_safety
on DOCTOR
After update
as
begin
	DECLARE @admin1 INT = 17, @admin2 INT = 23
	Declare @temp int,@temp1 Varchar(50),@temp2 Varchar(50);
	Select @temp = doctor_id ----<----
	from inserted
	Select @temp1 = availability_status
	from inserted
	Select @temp2 = availability_status
	from deleted
	if @temp1 <> @temp2
		begin
			DECLARE @pres_id INT
			SET @pres_id = (SELECT TOP 1 pr.log_id FROM AUDIT_LOG pr ORDER BY pr.log_id DESC)
			SET @pres_id = @pres_id + 1;
			Insert into audit_log values(@pres_id,'STATUS_UPDATE','DOCTORS',@temp, @admin1,getdate());
		end
end;
GO

UPDATE DOCTOR SET availability_status = 'Unavailable' WHERE doctor_id = 201;
SELECT * FROM AUDIT_LOG

--Task 4
-- Given in end

--GO
--Create or ALTER Trigger appointment_safety3
--on APPOINTMENTS
--INSTEAD OF INSERT
--as
--begin
--	Declare @temp Varchar(50), @tempid int,@temp1 int, @a date, @b int,@c int;

--	Select @tempid=doctor_id,@b=patient_id,@a = appointment_date
--	from inserted

--	Select @temp=d.availability_status
--	from DOCTOR d
--	where d.doctor_id=@tempid

--	Select @c=COUNT(*)
--	from APPOINTMENTS a
--	where a.appointment_date=@a and a.patient_id=@b

--	if @temp LIKE '%Unavailable%' or @c >= 1
--	begin
--		Select @temp1=appointment_id
--		from inserted
--		DECLARE @pres_id INT
--		SET @pres_id = (SELECT TOP 1 pr.log_id FROM AUDIT_LOG pr ORDER BY pr.log_id DESC)
--		SET @pres_id = @pres_id + 1;
--		Insert into audit_log values(@pres_id,'REJECTED_INSERT','APPOINTMENTS',@temp1, @admin1,getdate());
--	end
--	else
--	begin
--		declare @t1 int,@t2 int,@t3 int,@t4 varchar(50),@t5 date

--		Select @t1=appointment_id,@t2=patient_id,@t3=doctor_id,@t4=status,@t5=appointment_date
--		from inserted

--		Insert into APPOINTMENTS values(@t1,@t2,@t3,@t5,@t4);
--	end
--end;
--GO


--5. Trigger for Automatic Prescription Issue [10 Marks]
--   Create a trigger that automatically generates a placeholder prescription entry (e.g., “Diagnosis Pending”) when an appointment is marked 
--   as 'Completed'. Log this operation in Audit_Log.

GO
CREATE or ALTER TRIGGER appointmentCompleted ON Appointments
	AFTER UPDATE
AS
BEGIN
	DECLARE @admin1 INT = 17, @admin2 INT = 23
	DECLARE @var INT = -1;
	SET @var = (SELECT TOP 1 appointment_id 
				  FROM APPOINTMENTS 
				  WHERE status = 'Completed');
	--PRINT ISNULL(@var, -1);

	DECLARE @pres_id INT = 399
	SET @pres_id = (SELECT TOP 1 pr.prescription_id FROM PRESCRIPTION pr ORDER BY pr.prescription_id DESC)
	SET @pres_id = @pres_id + 1;

	DECLARE @log_id INT = 0
	SET @log_id = (SELECT TOP 1 au.log_id FROM AUDIT_LOG au ORDER BY au.log_id DESC)
	SET @log_id = @log_id + 1;

	DECLARE @num_logs INT = (SELECT COUNT(*) FROM AUDIT_LOG);

	IF @var != -1
	BEGIN
		INSERT INTO PRESCRIPTION (prescription_id, appointment_id, doctor_id, patient_id, medication, dosage, instructions, date_issued)
		SELECT @pres_id, i.appointment_id, i.doctor_id, i.patient_id, 'Diagnosis Pending', 'N/A', 'N/A', GETDATE()
        FROM inserted i
		JOIN deleted d ON i.appointment_id = d.appointment_id
		WHERE i.status = 'Completed' AND d.status != 'Completed';

		INSERT INTO AUDIT_LOG(log_id, action_type, table_name, entity_id, performed_by, timestamp)
		VALUES(@log_id, 'PRESCRIBE', 'PRESCRIPTIONS', @pres_id, @admin2, GETDATE())
	END;
END;
GO

UPDATE APPOINTMENTS 
SET status = 'Completed'
WHERE appointment_id = 303


--6. Before/After Trigger Combo [10 Marks]
--   Implement a BEFORE trigger to verify constraints (e.g., only one active appointment per patient at a time), and an AFTER trigger to 
--   record that appointment in Audit_Log once inserted. Include OLD and NEW values.

--Before Trigger--
-- Given in end
--GO
--CREATE or ALTER TRIGGER beforeInsertAppointment ON Appointments
--	Instead of INSERT
--AS
--BEGIN
--	-- Check for two pateints booked at same time
--	DECLARE @var INT = -1;
--	SET @var = (SELECT DISTINCT TOP 1 a1.appointment_id
--				FROM APPOINTMENTS a1
--				JOIN PATIENT p1 ON p1.patient_id = a1.patient_id
--				JOIN PATIENT p2 ON p1.patient_id = p2.patient_id
--				JOIN APPOINTMENTS a2 ON p2.patient_id = a2.patient_id
--				WHERE a1.status = 'Booked' AND a2.status = 'Booked' AND a1.appointment_date = a2.appointment_date AND p1.patient_id != p2.patient_id);
--	--PRINT ISNULL(@var, -1);

--	DECLARE @log_id INT = 0
--	SET @log_id = (SELECT TOP 1 au.log_id FROM AUDIT_LOG au ORDER BY au.log_id DESC)
--	SET @log_id = @log_id + 1;

--	DECLARE @num_logs INT = (SELECT COUNT(*) FROM AUDIT_LOG);

--	IF @var != -1
--	BEGIN
--		SET @var = (SELECT DISTINCT TOP 1 p.patient_id FROM PATIENT p JOIN APPOINTMENTS a ON a.appointment_id = @var)
--		print 'Error: The patient ' + CAST((@var) AS VARCHAR(20)) + ' can not have two appointements at the same time!'

--		INSERT INTO AUDIT_LOG(log_id, action_type, table_name, entity_id, performed_by, timestamp)
--		SELECT @log_id, 'REJECTED_INSERT', 'APPOINTMENTS', NULL, @admin2, GETDATE()
--		RETURN;
--	END;

--	-- If entry is valid
--	INSERT INTO APPOINTMENTS(appointment_id, patient_id, doctor_id, appointment_date, status)
--	SELECT appointment_id, patient_id, doctor_id, appointment_date, status
--	FROM inserted

--END;
--GO


--After Trigger--
GO
CREATE or ALTER TRIGGER afterInsertAppointment ON Appointments
	AFTER INSERT
AS
BEGIN
	DECLARE @admin1 INT = 17, @admin2 INT = 23
	DECLARE @log_id INT = 0
	SET @log_id = (SELECT TOP 1 au.log_id FROM AUDIT_LOG au ORDER BY au.log_id DESC)
	SET @log_id = @log_id + 1;

	DECLARE @num_logs INT = (SELECT COUNT(*) FROM AUDIT_LOG);

	INSERT INTO AUDIT_LOG(log_id, action_type, table_name, entity_id, performed_by, timestamp)
	SELECT @log_id, 'BOOK', 'APPOINTMENTS', i.appointment_id, @admin2, GETDATE()
	FROM inserted i

END;
GO

--Test 5
DECLARE @app_id INT = 299
	SET @app_id = (SELECT TOP 1 ap.appointment_id FROM APPOINTMENTS ap ORDER BY ap.appointment_id DESC)
	SET @app_id = @app_id + 1;
INSERT INTO APPOINTMENTS(appointment_id, patient_id, doctor_id, appointment_date, status)
VALUES (@app_id, 102, 201, GETDATE(), 'Booked')

--
UPDATE APPOINTMENTS SET status = 'Completed' WHERE appointment_id = 301;
SELECT * FROM AUDIT_LOG

--7. Cascading Triggers with Logic Conflict [30 Marks]
--o Patients with more than 3 missed appointments should be flagged.

GO
CREATE or ALTER TRIGGER missedAppointment ON Appointments
	AFTER UPDATE
AS
BEGIN
	DECLARE @admin1 INT = 17, @admin2 INT = 23
	DECLARE @logid INT = 0
	SET @logid = (SELECT TOP 1 au.log_id FROM AUDIT_LOG au ORDER BY au.log_id DESC)
	SET @logid = @logid + 1;
	--print @log_id

	UPDATE PATIENT
	SET missed_count = missed_count + 1
	FROM PATIENT p
	JOIN inserted i ON i.patient_id = p.patient_id
	JOIN deleted d ON d.appointment_id = i.appointment_id
	WHERE i.status = 'Missed' AND d.status != 'Missed'

	UPDATE PATIENT
    SET isIrresponsible = 1
    FROM PATIENT p
    JOIN inserted i ON i.patient_id = p.patient_id
	WHERE p.missed_count >= 3

	INSERT INTO AUDIT_LOG(log_id, action_type, table_name, entity_id, performed_by, timestamp)
	SELECT @logid, 'MISSED', 'APPOINTMENTS', i.appointment_id, @admin2, GETDATE()
	FROM inserted i
	JOIN deleted d ON i.appointment_id = d.appointment_id
    WHERE i.status = 'Missed' AND d.status != 'Missed';

END;
GO


--o Automatically mark a doctor as “Unavailable” after 3 missed appointments in a week.

GO
CREATE or ALTER TRIGGER doctorAvailability ON Appointments
	AFTER UPDATE
AS
BEGIN
	DECLARE @admin1 INT = 17, @admin2 INT = 23
	DECLARE @logid INT = 0
	SET @logid = (SELECT TOP 1 au.log_id FROM AUDIT_LOG au ORDER BY au.log_id DESC)
	SET @logid = @logid + 1;

	DECLARE @num_logs INT = (SELECT COUNT(*) FROM AUDIT_LOG);

	UPDATE DOCTOR
    SET availability_status = 'Unavailable'
    FROM DOCTOR d
    WHERE EXISTS (SELECT 1
				  FROM Appointments a
				  WHERE a.doctor_id = d.doctor_id
				  AND a.status = 'Missed'
				  AND a.appointment_date >= DATEADD(DAY, -7, GETDATE())
				  GROUP BY a.doctor_id
				  HAVING COUNT(*) >= 3);

    INSERT INTO AUDIT_LOG (log_id, action_type, table_name, entity_id, performed_by, timestamp)
    SELECT @logid, 'STATUS_UPDATE', 'DOCTORS', d.doctor_id, @admin2, GETDATE()
    FROM DOCTOR d
	JOIN inserted i ON i.doctor_id = d.doctor_id
	WHERE d.availability_status = 'Unavailable'

END;
GO


--o TASK 4 + 6 + 7

GO
CREATE or ALTER TRIGGER AppointmentsConstraints ON Appointments
	Instead of INSERT
AS
BEGIN
	DECLARE @admin1 INT = 17, @admin2 INT = 23
	-- Task 4
	Declare @temp Varchar(50), @tempid int,@temp1 int, @a date, @b int,@c int;

	Select @tempid=doctor_id,@b=patient_id,@a = appointment_date
	from inserted

	Select @temp=d.availability_status
	from DOCTOR d
	where d.doctor_id=@tempid

	Select @c=COUNT(*)
	from APPOINTMENTS a
	where a.appointment_date=@a and a.patient_id=@b

	-- Task 6
	-- Check for two pateints booked at same time
	DECLARE @var6 INT = -1;
	SET @var6 = (SELECT DISTINCT TOP 1 a1.appointment_id
				FROM APPOINTMENTS a1
				JOIN PATIENT p1 ON p1.patient_id = a1.patient_id
				JOIN PATIENT p2 ON p1.patient_id = p2.patient_id
				JOIN APPOINTMENTS a2 ON p2.patient_id = a2.patient_id
				WHERE a1.status = 'Booked' AND a2.status = 'Booked' AND a1.appointment_date = a2.appointment_date AND p1.patient_id != p2.patient_id);

	-- Task 7
	-- Check for doctors appointments count
	DECLARE @var7 INT = -1;
	SET @var7 = (SELECT DISTINCT TOP 1 a.doctor_id
				FROM inserted i
				JOIN Appointments a ON i.doctor_id = a.doctor_id
				WHERE a.appointment_date = i.appointment_date
				GROUP BY a.doctor_id, a.appointment_date
				HAVING COUNT(*) >= 5);
	--PRINT ISNULL(@var, -1);

	DECLARE @log_id INT = 0
	SET @log_id = (SELECT TOP 1 au.log_id FROM AUDIT_LOG au ORDER BY au.log_id DESC)
	SET @log_id = @log_id + 1;

	DECLARE @num_logs INT = (SELECT COUNT(*) FROM AUDIT_LOG);

	-- Task 4
	if @temp LIKE '%Unavailable%' or @c >= 1
	begin
		Select @temp1 = appointment_id
		from inserted
		DECLARE @pres_id INT
		SET @pres_id = (SELECT TOP 1 pr.log_id FROM AUDIT_LOG pr ORDER BY pr.log_id DESC)
		SET @pres_id = @pres_id + 1;
		Insert into audit_log values(@pres_id,'REJECTED_INSERT','APPOINTMENT',@temp1, @admin1,getdate());
		RETURN;
	end

	-- Task 6
	--o Before Trigger--
	IF @var6 != -1
	BEGIN
		SET @var6 = (SELECT DISTINCT TOP 1 p.patient_id FROM PATIENT p JOIN APPOINTMENTS a ON a.appointment_id = @var6)
		print 'Error: The patient ' + CAST((@var6) AS VARCHAR(20)) + ' can not have two appointements at the same time!'

		INSERT INTO AUDIT_LOG(log_id, action_type, table_name, entity_id, performed_by, timestamp)
		SELECT @log_id, 'REJECTED_INSERT', 'APPOINTMENTS', NULL, @admin2, GETDATE()
		RETURN;
	END;

	-- Task 7
	--o A doctor should not have more than 5 appointments per day.
	IF @var7 != -1
	BEGIN
		SET @var7 = (SELECT DISTINCT TOP 1 d.doctor_id FROM DOCTOR d JOIN APPOINTMENTS a ON a.doctor_id = @var7)
		print 'Error: The doctor ' + CAST((@var7) AS VARCHAR(20)) + ' can not have more than 5 appointements in a day!'

		INSERT INTO AUDIT_LOG(log_id, action_type, table_name, entity_id, performed_by, timestamp)
		SELECT @log_id, 'REJECTED_INSERT', 'APPOINTMENTS', NULL, @admin2, GETDATE()
		RETURN;
	END;

	-- If entry is valid
	INSERT INTO Appointments (appointment_id, patient_id, doctor_id, appointment_date, status)
    SELECT appointment_id, patient_id, doctor_id, appointment_date, status
    FROM inserted;

END;
GO

-- Test 4
INSERT INTO APPOINTMENTS VALUES (321, 101, 202, '2025-05-01', 'Booked');
SELECT * FROM AUDIT_LOG

--Test 6
DECLARE @app_id INT = 299
	SET @app_id = (SELECT TOP 1 ap.appointment_id FROM APPOINTMENTS ap ORDER BY ap.appointment_id DESC)
	SET @app_id = @app_id + 1;
INSERT INTO APPOINTMENTS(appointment_id, patient_id, doctor_id, appointment_date, status)
VALUES (@app_id, 101, 201, GETDATE(), 'Booked')

INSERT INTO APPOINTMENTS VALUES (322, 101, 201, '2025-05-01', 'Booked');
INSERT INTO APPOINTMENTS VALUES (324, 120, 210, '2025-05-14', 'Booked');
SELECT * FROM AUDIT_LOG

-- Test 7
UPDATE APPOINTMENTS SET status = 'Missed' WHERE appointment_id = 302;
UPDATE APPOINTMENTS SET status = 'Missed' WHERE appointment_id = 305;
UPDATE APPOINTMENTS SET status = 'Missed' WHERE appointment_id = 306;
SELECT * FROM AUDIT_LOG

INSERT INTO APPOINTMENTS VALUES (323, 120, 201, '2025-05-01', 'Booked');
SELECT * FROM AUDIT_LOG


-----------------------------------------------------------------

SELECT * FROM PATIENT
SELECT * FROM DOCTOR
SELECT * FROM APPOINTMENTS
SELECT * FROM PRESCRIPTION
SELECT * FROM AUDIT_LOG
SELECT * FROM ADMIN

--DELETE FROM APPOINTMENTS WHERE appointment_id=305


--INSERT INTO APPOINTMENTS(appointment_id, patient_id, doctor_id, appointment_date, status)
--VALUES (305, 101, 201, GETDATE(), 'Booked')

--DECLARE @app_id INT = 299
--	SET @app_id = (SELECT TOP 1 ap.appointment_id FROM APPOINTMENTS ap ORDER BY ap.appointment_id DESC)
--	SET @app_id = @app_id + 1;

--UPDATE PATIENT
--SET isIrresponsible = 0