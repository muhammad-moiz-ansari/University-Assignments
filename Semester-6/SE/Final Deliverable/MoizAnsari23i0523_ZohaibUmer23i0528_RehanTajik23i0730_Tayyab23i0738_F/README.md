# Disaster Management System
### By Remotz Systems

![Java](https://img.shields.io/badge/Java-24-ED8B00?style=for-the-badge&logo=openjdk&logoColor=white)
![JavaFX](https://img.shields.io/badge/JavaFX-21-4285F4?style=for-the-badge&logo=java&logoColor=white)
![SQL Server](https://img.shields.io/badge/SQL_Server-Express-CC2927?style=for-the-badge&logo=microsoft-sql-server&logoColor=white)
![Maven](https://img.shields.io/badge/Maven-3.9+-C71A36?style=for-the-badge&logo=apache-maven&logoColor=white)

A desktop-based Java application that centralizes disaster response coordination between **Admins, Rescue Teams, NGOs, and Citizens**. Built to minimize response times, eliminate resource misallocation, and provide real-time visibility into all active operations during natural disasters.

---

## ✨ Key Features

| Role | What They Can Do |
|---|---|
| **Admin** | Manage disaster records · Broadcast alerts · Assign NGOs & rescue teams · Allocate resources · Track teams live on map · Generate PDF/Excel reports · Review feedback |
| **Rescue Team** | View assigned missions · Update mission status (En Route → On Site → Completed) · Request resources |
| **NGO** | View disaster assignments · Manage relief distribution · Request resource packages from Admin |
| **Citizen** | Report disasters · Trigger emergency SOS · View active alerts · Submit feedback |

---

## 🛠️ Tech Stack

- **Language:** Java 24
- **Frontend:** JavaFX 21 (FXML + CSS)
- **Database:** Microsoft SQL Server Express
- **Build:** Apache Maven
- **Key Libraries:** iTextPDF · Apache POI · BCrypt · ControlsFX

---

## ⚙️ Setup & Run

### Prerequisites
- JDK 24
- Microsoft SQL Server (Express or Developer)
- Maven 3.9+

### 1. Clone
```bash
git clone https://github.com/muhammad-moiz-ansari/Disaster_Management_System.git
cd Disaster_Management_System
```

### 2. Set Up the Database
Open **SQL Server Management Studio** and run the scripts in this order:
```
database/DisasterManagementDB.sql          ← creates schema & tables
database/DMS_MapLocations.sql              ← populates city map coordinates
database/DisasterManagementDataInsertion.sql  ← (optional) loads sample data
```

### 3. Configure Connection
Edit `src/main/java/com/dms/util/DatabaseConnection.java` if your credentials differ from the default:
```java
private static final String URL = "jdbc:sqlserver://localhost:1433;databaseName=DisasterManagementDB;encrypt=false;trustServerCertificate=true";
private static final String USER = "sa";
private static final String PASSWORD = "123456789";
```

### 4. Build & Run
```bash
mvn clean install
mvn javafx:run
```

### Default Login Credentials
| Role | Field | Value |
|---|---|---|
| Admin | Username | `moiz0523` |
| Citizen | CNIC | `35202-1234567-1` |
| NGO | Registration No. | `PRC-1234` |
| Rescue Team | Team ID | `RT001` |
> All default passwords: `000000` (Admin) · `111111` (Citizen) · `222222` (Rescue Team) · `333333` (NGO)

---

## 🏗️ Architecture

```
Presentation Layer   →   JavaFX Controllers (FXML)
Business Logic       →   Controller methods + Service classes
Data Access          →   BaseDAO + concrete DAOs
Database             →   SQL Server (19 tables, stored procedures, triggers)
```

**Design Patterns used:** Singleton (`DatabaseConnection`, `LoggedInUser`) · Template Method (`BaseDAO`, `BaseController`)

---

## 📁 Project Structure

```
src/main/java/com/dms/
├── controller/     # JavaFX controllers for all views
├── dao/            # Data Access Objects (BaseDAO + 15 concrete DAOs)
├── model/          # Entity classes (Disaster, Alert, Mission, etc.)
├── service/        # ReportGenerator (PDF/Excel)
└── util/           # DatabaseConnection, LoggedInUser, TimestampFormatter

src/main/resources/com/dms/
├── fxml/           # FXML layout files for all screens
├── css/            # Stylesheet (styles.css)
└── images/         # App icons and map assets

database/
├── DisasterManagementDB.sql
├── DMS_MapLocations.sql
└── DisasterManagementDataInsertion.sql
```

---

## 👥 Contributors

| Name | GitHub | Role |
|---|---|---|
| Muhammad Moiz Ansari | [@muhammad-moiz-ansari](https://github.com/muhammad-moiz-ansari) | Team Lead · Scrum Master · Developer |
| Rehan Ali Tajik | - | Developer · Tester |
| Zohaib Umer | - | Developer · UI Designer |

---

## 🎓 Academic Context

Developed for **CS3009 - Software Engineering** at **FAST-NUCES Islamabad** (Spring 2026).
Supervised by **Ms. Rabail Zahid**.