#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096
#define NUM_PAGES 4
#define PHYSICAL_MEMORY_SIZE 16 * 1024
#define NUM_PAGE_FRAMES 4

typedef struct {
    int frame_number;
} PageTableEntry;

typedef struct {
    PageTableEntry page_table[NUM_PAGES];
    char physical_memory[PHYSICAL_MEMORY_SIZE];
} MemoryManager;

void init_memory_manager(MemoryManager *mm) {
    for (int i = 0; i < NUM_PAGES; i++) {
        mm->page_table[i].frame_number = -1;
    }
    for (int i = 0; i < PHYSICAL_MEMORY_SIZE; i++) {
        mm->physical_memory[i] = 0;
    }
}

void allocate_page(MemoryManager *mm, int logical_page, int physical_frame) {
    if (logical_page >= NUM_PAGES) {
        printf("Invalid logical page number.\n");
        return;
    }
    if (physical_frame >= NUM_PAGE_FRAMES) {
        printf("Invalid physical frame number.\n");
        return;
    }
    mm->page_table[logical_page].frame_number = physical_frame;
    printf("Allocated logical page %d to physical frame %d.\n", logical_page, physical_frame);
}

int translate_address(MemoryManager *mm, int logical_page, int offset) {
    if (logical_page >= NUM_PAGES || mm->page_table[logical_page].frame_number == -1) {
        printf("Invalid page or page not allocated.\n");
        return -1;
    }
    int physical_frame = mm->page_table[logical_page].frame_number;
    int physical_address = physical_frame * PAGE_SIZE + offset;
    return physical_address;
}

void write_to_physical_memory(MemoryManager *mm, int physical_address, char value) {
    if (physical_address < 0 || physical_address >= PHYSICAL_MEMORY_SIZE) {
        printf("Invalid physical address.\n");
        return;
    }
    mm->physical_memory[physical_address] = value;
    printf("Written value '%c' to physical address %d.\n", value, physical_address);
}

char read_from_physical_memory(MemoryManager *mm, int physical_address) {
    if (physical_address < 0 || physical_address >= PHYSICAL_MEMORY_SIZE) {
        printf("Invalid physical address.\n");
        return -1;
    }
    return mm->physical_memory[physical_address];
}

int main() {
    MemoryManager mm;
    init_memory_manager(&mm);

    int choice, logical_page, physical_frame, offset, physical_address;
    char value;

    while (1) {
        printf("\n--- Paged Memory Management ---\n");
        printf("1. Allocate page\n");
        printf("2. Translate address\n");
        printf("3. Write to physical memory\n");
        printf("4. Read from physical memory\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter logical page number (0-%d): ", NUM_PAGES - 1);
                scanf("%d", &logical_page);
                printf("Enter physical frame number (0-%d): ", NUM_PAGE_FRAMES - 1);
                scanf("%d", &physical_frame);
                allocate_page(&mm, logical_page, physical_frame);
                break;

            case 2:
                printf("Enter logical page number (0-%d): ", NUM_PAGES - 1);
                scanf("%d", &logical_page);
                printf("Enter offset within the page (0-%d): ", PAGE_SIZE - 1);
                scanf("%d", &offset);
                physical_address = translate_address(&mm, logical_page, offset);
                if (physical_address != -1) {
                    printf("Physical address: %d\n", physical_address);
                }
                break;

            case 3:
                printf("Enter physical address to write to (0-%d): ", PHYSICAL_MEMORY_SIZE - 1);
                scanf("%d", &physical_address);
                printf("Enter value to write: ");
                getchar();
                scanf("%c", &value);
                write_to_physical_memory(&mm, physical_address, value);
                break;

            case 4:
                printf("Enter physical address to read from (0-%d): ", PHYSICAL_MEMORY_SIZE - 1);
                scanf("%d", &physical_address);
                value = read_from_physical_memory(&mm, physical_address);
                if (value != -1) {
                    printf("Value at physical address %d: '%c'\n", physical_address, value);
                }
                break;

            case 5:
                printf("Exiting the system.\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
