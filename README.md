# C Agenda Manager

A CLI-based contact management system developed in C featuring dynamic heap memory reallocation, manual resource lifecycle handling, input sanitization, and structured file persistence.

## Technical Architecture & Highlights

- **Dynamic Array Resizing:** Employs runtime heap reallocation (`realloc`) via defensive pointer assignment (`contactos *temp = realloc(...)`) to dynamically expand and shrink contact storage without memory leaks or static buffer waste.
- **Data Persistence:** Automated disk I/O routines using structured formatted streams (`fopen`, `fprintf`, `fscanf`, `fclose`) to serialize and deserialize contact records (`agenda.txt`).
- **Input Validation & Safety:** Implements character-by-character alphabetic validation (`isalpha`) and strict 9-digit telephone bounds checking (100000000–999999999) to prevent data corruption.
- **In-Memory Deletion:** Shift-left array compaction to safely remove records followed by dynamic memory deflation, releasing heap blocks when the database reaches zero items.

## Operations Supported

1. **Search Contact (`buscar_contacto`):** Exact string matching via `strcmp`.
2. **Insert Contact (`insertar_contacto`):** Dynamic growth with validation on user entries.
3. **Update Contact (`actualizar_contacto`):** In-place memory mutation upon identifier verification.
4. **Delete Contact (`eliminar_contacto`):** Array compaction and heap footprint deflation.
5. **Exit & Persist:** File writeout followed by total heap cleanup (`free()`).

## Compilation & Execution

Compile the source using GCC:

```
gcc -Wall -Wextra -std=c99 -o agenda agenda.c
```
Run the application:
```
# Windows
agenda.exe

# Linux / macOS
./agenda
```
## Memory Verification
```
valgrind --leak-check=full --show-leak-kinds=all ./agenda
``` 
## Author
- **Juan María Sánchez Escalona** - Computer Science Student
