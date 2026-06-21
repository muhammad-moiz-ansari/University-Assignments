#include "pch.h"
#include "D:\Documents\Semester-3\.Labs\.DSA Lab\Lab Task 8\Lab-8 Project File\23i-0523_Moiz Ansari_Lab8_Q1.cpp"

// Question 1
TEST(MultiLevelFeedbackQueueSchedulerTest, BasicSchedulingTest) {
    MultiLevelFeedbackQueueScheduler scheduler;

    // Add processes to the scheduler
    scheduler.addProcess(new Process(1, 0, 5));  // High-priority process
    scheduler.addProcess(new Process(2, 1, 3));  // Medium-priority process
    scheduler.addProcess(new Process(3, 2, 2));  // Low-priority process
    scheduler.addProcess(new Process(4, 0, 4));  // High-priority process
    scheduler.addProcess(new Process(5, 1, 1));  // Medium-priority process
    scheduler.addProcess(new Process(6, 2, 6));  // Low-priority process

    // Execute processes using FCFS scheduling
    scheduler.executeProcesses();

    // Check if all processes have terminated
    EXPECT_EQ(scheduler.getTerminatedCount(), 6);  // Assuming all processes should terminate

    // Check if specific process states are correct
    Process* terminatedProcess1 = scheduler.getTerminatedProcess(1);
    EXPECT_EQ(terminatedProcess1->state, 4); // State 4 indicates termination

    Process* terminatedProcess2 = scheduler.getTerminatedProcess(2);
    EXPECT_EQ(terminatedProcess2->state, 4);

    // Additional assertions as needed
    Process* terminatedProcess3 = scheduler.getTerminatedProcess(3);
    EXPECT_EQ(terminatedProcess3->state, 4);
}
