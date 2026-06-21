import pandas as pd

# Patients
patients = pd.DataFrame([
    [101, "Alice Smith", "F", "1990-01-01", "1234567890"],
    [102, "Bob Johnson", "M", "1985-05-15", "0987654321"],
    [103, "Charlie Davis", "M", "1992-09-10", "1122334455"]
], columns=["patient_id", "name", "gender", "dob", "contact"])
patients.to_csv("Patients.csv", index=False)

# Doctors
doctors = pd.DataFrame([
    [201, "Dr. Emily Carter", "Cardiology", "Available"],
    [202, "Dr. John Adams", "Neurology", "Unavailable"]
], columns=["doctor_id", "name", "specialization", "availability_status"])
doctors.to_csv("Doctors.csv", index=False)

# Appointments
appointments = pd.DataFrame([
    [301, 101, 201, "2025-05-01", "Booked"],
    [302, 102, 202, "2025-05-02", "Booked"],
    [303, 103, 201, "2025-05-03", "Cancelled"]
], columns=["appointment_id", "patient_id", "doctor_id", "appointment_date", "status"])
appointments.to_csv("Appointments.csv", index=False)

# Prescriptions
prescriptions = pd.DataFrame([
    [401, 301, 201, 101, "Aspirin 100mg", "1 tablet twice daily", "After meals", "2025-05-01"],
    [402, 302, 202, 102, "Ibuprofen 200mg", "1 tablet every 8 hours", "With water", "2025-05-02"]
], columns=["prescription_id", "appointment_id", "doctor_id", "patient_id", "medication", "dosage", "instructions", "date_issued"])
prescriptions.to_csv("Prescriptions.csv", index=False)

# Audit_Log
audit_log = pd.DataFrame([
    [1, "INSERT", "PATIENTS", 101, "admin1", "2025-04-24 14:38:48"],
    [2, "BOOK", "APPOINTMENTS", 301, "admin1", "2025-04-24 14:38:48"],
    [3, "BOOK", "APPOINTMENTS", 302, "admin1", "2025-04-24 14:38:48"],
    [4, "CANCEL", "APPOINTMENTS", 303, "admin2", "2025-04-24 14:38:48"]
], columns=["log_id", "action_type", "table_name", "entity_id", "performed_by", "timestamp"])
audit_log.to_csv("Audit_Log.csv", index=False)

print("CSV files generated: Patients.csv, Doctors.csv, Appointments.csv, Prescriptions.csv, Audit_Log.csv")