# 🏥 Hospital Patient Queue Management System

A C-based console application that implements efficient patient queue management using **FIFO (Queue)**, **LIFO (Stack)**, and **Linked List** data structures.

## 📋 Project Description

This system addresses the real-world challenge of managing patient arrivals in hospitals efficiently. The application handles:
- **Regular patients** who wait in a FIFO queue for consultation
- **Emergency patients** who receive immediate priority treatment
- **Staff undo functionality** to reverse accidental registrations

## ✨ Features

### 1. Patient Queue (FIFO)
- Register patients who wait in order of arrival for consultation
- First-In-First-Out ensures fair treatment order for non-emergency cases
- Real-time queue monitoring and display

### 2. Emergency Stack (LIFO)
- Emergency patients bypass the regular queue
- Treated immediately using Last-In-First-Out priority
- Separate tracking for critical cases

### 3. Undo Stack (LIFO)
- Track last registrations to allow staff to undo mistakes
- Prevents errors in patient data entry
- Maintains registration history

### 4. Patient Records
Each patient record includes:
- **ID**: Unique identifier
- **Name**: Patient full name
- **Age**: Patient age
- **Condition**: Medical condition/reason for visit

### 5. Statistics Dashboard
- Total patients served
- Regular consultations count
- Emergency cases handled
- Current queue size
- Active emergency cases

## 🛠️ Technologies Used

- **Language**: C
- **Data Structures**: 
  - Singly Linked List
  - Queue (FIFO)
  - Stack (LIFO)
- **Compiler**: GCC

## 🚀 Installation & Usage

### Prerequisites
- GCC compiler installed on your system
- Windows CMD, Linux Terminal, or macOS Terminal

### Compilation


## 📖 How to Use

1. **Main Menu**: Choose between registering patients, consulting, or viewing statistics
2. **Register Regular Patient**: Add patient to FIFO queue
3. **Register Emergency Patient**: Add patient to priority LIFO stack
4. **Consult Next Patient**: System automatically prioritizes emergency cases
5. **View Queues**: Monitor waiting patients in both queues
6. **Undo Registration**: Remove last registered patient
7. **View Statistics**: Check system performance metrics


