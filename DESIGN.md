# Design & Complexity Analysis

## Architecture Overview
The system follows a strict **Layered Architecture** to ensure separation of concerns and testability.

1.  **Presentation Layer (CLI)**: Handles user input/output. Depends only on the Service Layer.
2.  **Service Layer**: Contains business logic (e.g., validation, calculations). Depends on the Repository Layer.
3.  **Repository Layer**: Handles data persistence. Hides the details of file I/O from the rest of the application.
4.  **Model Layer**: Pure data objects (POCOs) with serialization logic.
5.  **Core Layer**: Cross-cutting concerns like Logging and Threading.

## Complexity Analysis

### Time Complexity
-   **Add Student**: O(1) - Appending to the in-memory map and file is constant time (amortized).
-   **Get Student by ID**: O(1) - Hash map lookup.
-   **Search Students**: O(N) - Linear scan of all students. This is a trade-off for simplicity. For millions of records, an indexing strategy (e.g., Trie or secondary hash maps) would be required.
-   **Update/Delete**: O(1) - Hash map access.

### Space Complexity
-   **O(N)**: All students are loaded into memory for fast access.
    -   *Trade-off*: This provides extremely fast reads but limits scalability to available RAM.
    -   *Mitigation*: For a truly "large-scale" system exceeding RAM, the Repository would need to implement paging or rely on a disk-based B-Tree (like SQLite).

## Concurrency Design
-   **Reader-Writer Lock (`std::shared_mutex`)**:
    -   Multiple threads can read (`getById`, `search`) simultaneously.
    -   Only one thread can write (`add`, `update`, `delete`) at a time, blocking readers.
    -   This prevents data races while maximizing read throughput.

## Persistence Strategy
-   **Format**: Custom CSV-like format (`ID,Name,Email,Age,GPA`).
-   **Reliability**: The system writes to disk immediately on change (Write-Through).
    -   *Improvement*: A Write-Ahead Log (WAL) or periodic flush could improve write performance at the cost of potential data loss on crash.

## Future Improvements
1.  **Indexing**: Add a secondary index for Email to make email lookups O(1).
2.  **Pagination**: CLI should paginate results for large datasets.
3.  **Networking**: Replace CLI with a REST API (using a library like `crow` or `oat++`) to make it a true backend service.
