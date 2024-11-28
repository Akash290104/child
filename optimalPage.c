#include <stdio.h>
#include <stdlib.h>

#define MAX_PAGES 100

int findFarthest(int pages[], int currentIndex, int frames[], int numFrames, int n) {
    int farthest = -1;
    int farthestIndex = -1;

    for (int i = 0; i < numFrames; i++) {
        int page = frames[i];
        int j;
        for (j = currentIndex + 1; j < n; j++) {
            if (pages[j] == page) {
                break;
            }
        }
        if (j == n) {
            return i;
        }
        if (j > farthest) {
            farthest = j;
            farthestIndex = i;
        }
    }
    return farthestIndex;
}

void optimalPageReplacement(int pages[], int n, int numFrames) {
    int frames[numFrames];
    int pageFaults = 0;
    int pageFound;

    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        pageFound = 0;
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == pages[i]) {
                pageFound = 1;
                break;
            }
        }

        if (!pageFound) {
            int replaceIndex = -1;
            for (int j = 0; j < numFrames; j++) {
                if (frames[j] == -1) {
                    replaceIndex = j;
                    break;
                }
            }
            if (replaceIndex == -1) {
                replaceIndex = findFarthest(pages, i, frames, numFrames, n);
            }
            frames[replaceIndex] = pages[i];
            pageFaults++;
        }

        printf("Page %d: ", pages[i]);
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    printf("Total page faults: %d\n", pageFaults);
}

int main() {
    int numFrames, n;

    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    if (numFrames <= 0) {
        printf("Number of frames must be greater than 0.\n");
        return 1;
    }

    printf("Enter the number of page references: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_PAGES) {
        printf("Invalid number of page references.\n");
        return 1;
    }

    int pages[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    optimalPageReplacement(pages, n, numFrames);

    return 0;
}
