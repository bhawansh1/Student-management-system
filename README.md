# Student Management System (C++)

A high-performance, thread-safe, and persistent Student Management System built with modern C++ (C++17). Designed to demonstrate modular architecture, clean code practices, and zero-dependency deployment.

## Features

- **Core**: Thread-safe Logger, ThreadPool, and Utility classes.
- **Persistence**: Custom file-based repository (no external DB required).
- **Concurrency**: `std::shared_mutex` for Reader-Writer locking on data access.
- **Architecture**: Layered architecture (Model-View-Service-Repository).
- **UI**: Interactive Command Line Interface (CLI).

## Project Structure

```text
StudentManagementSystem/
├── src/
│   ├── core/           # Infrastructure (Logger, ThreadPool)
│   ├── model/          # Data entities (Student, Course)
│   ├── repository/     # Persistence layer (File I/O)
│   ├── service/        # Business logic
│   └── ui/             # Presentation layer (CLI)
├── CMakeLists.txt      # Build configuration
└── README.md           # Documentation
```

## Getting Started

### Prerequisites

- C++17 compatible compiler (GCC, Clang, MSVC)
- CMake 3.10+

### Build & Run

1.  Clone the repository:
    ```bash
    git clone https://github.com/yourusername/StudentManagementSystem.git
    cd StudentManagementSystem
    ```

2.  Build using CMake:
    ```bash
    cmake .
    make
    ```

3.  Run the application:
    ```bash
    ./StudentManagementSystem
    ```

## Usage Example

```text
========================================
      STUDENT MANAGEMENT SYSTEM         
========================================
1. Add Student
2. View All Students
3. Search Student
4. Update Student
5. Delete Student
0. Exit
========================================

Enter choice: 1
Enter Name: John Doe
Enter Email: john@example.com
Enter Age: 20
Enter GPA: 3.8
Student added successfully!
```

## Design Decisions

- **Zero Dependencies**: Uses standard C++ libraries only to ensure portability and ease of setup.
- **Thread Safety**: The `FileRepository` uses `std::shared_mutex` to allow multiple concurrent readers but only one writer, optimizing for read-heavy workloads.
- **Singleton Logger**: Ensures a single point of access for logging across the application.

## License

MIT License
