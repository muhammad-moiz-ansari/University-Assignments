# **Multiplayer MAN VS ZOMBIE Game with Docker Containerization

# Project Overview
This project is a multiplayer game implemented in C++ that uses inter-process communication (IPC) through pipes. The game logic, process management, and Docker containerization ensure portability and easy execution.

# How to Compile and Run the Game

# Using GCC (Without Docker)
1. Open a terminal and navigate to the project directory:
   cd /path/to/project

2. Compile the game:
   g++ -o game Q1.cpp

3. Run the game:
   ./game


# Using Docker
# Building the Docker Image
1. Ensure Docker is installed and running.
2. Build the Docker image using the provided `Dockerfile`:
   sudo docker buildx build -t asgn2 .

# Running the Container
1. Run the containerized game:
   sudo docker run --rm asgn2

# Pipes and Process Management Implementation
- The game utilizes **UNIX pipes** for IPC between processes.
- A **parent process** spawns two child processes for the different game players.
- Each child process communicates with the parent via pipes, exchanging game state updates, such as player dead or alive.
- The game logic ensures synchronization and efficient data transfer between processes.


## Unique Student Requirement Implementation
- An integer was initialized
- The formula given was used to calculate the number of zombies... and the XXXX was replaced by 0523, from my roll number.

