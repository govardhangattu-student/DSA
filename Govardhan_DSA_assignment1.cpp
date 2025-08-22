#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tab {
    int pageID;
    char URL[256];
    struct Tab* next;
    struct Tab* prev;
} Tab;

typedef struct Browser {
    Tab* currentTab;
    int pageCounter;
} Browser;

Browser* createBrowser() {
    Browser* browser = (Browser*)malloc(sizeof(Browser));
    if (!browser) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    browser->currentTab = NULL;
    browser->pageCounter = 0;
    return browser;
}

void openURLInBrowser(const char* url) {
    char command[512];
#ifdef _WIN32
    snprintf(command, sizeof(command), "start \"\" \"%s\"", url);  // Windows
#elif __APPLE__
    snprintf(command, sizeof(command), "open \"%s\"", url);       // macOS
#else
    snprintf(command, sizeof(command), "xdg-open \"%s\"", url);   // Linux
#endif
    system(command);
}

void visitNewPage(Browser* browser) {
    char url[256];
    printf("Enter URL (include https:// or http://): ");
    fgets(url, sizeof(url), stdin);
    url[strcspn(url, "\n")] = '\0';  // Remove newline

    Tab* newTab = (Tab*)malloc(sizeof(Tab));
    if (!newTab) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Clear forward history
    if (browser->currentTab) {
        Tab* temp = browser->currentTab->next;
        while (temp) {
            Tab* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
        browser->currentTab->next = NULL;
    }

    newTab->pageID = ++(browser->pageCounter);
    strncpy(newTab->URL, url, sizeof(newTab->URL));
    newTab->URL[sizeof(newTab->URL) - 1] = '\0';
    newTab->next = NULL;
    newTab->prev = browser->currentTab;

    if (browser->currentTab != NULL) {
        browser->currentTab->next = newTab;
    }

    browser->currentTab = newTab;

    printf("Visited: %s (Page ID: %d)\n", newTab->URL, newTab->pageID);
    openURLInBrowser(newTab->URL);
}

void goBack(Browser* browser) {
    if (browser->currentTab == NULL || browser->currentTab->prev == NULL) {
        printf("No previous tab.\n");
        return;
    }
    browser->currentTab = browser->currentTab->prev;
    printf("Moved back to: %s (Page ID: %d)\n", browser->currentTab->URL, browser->currentTab->pageID);
    openURLInBrowser(browser->currentTab->URL);
}

void goForward(Browser* browser) {
    if (browser->currentTab == NULL || browser->currentTab->next == NULL) {
        printf("No next tab.\n");
        return;
    }
    browser->currentTab = browser->currentTab->next;
    printf("Moved forward to: %s (Page ID: %d)\n", browser->currentTab->URL, browser->currentTab->pageID);
    openURLInBrowser(browser->currentTab->URL);
}

void showCurrentTab(Browser* browser) {
    if (browser->currentTab == NULL) {
        printf("No current tab.\n");
    } else {
        printf("Current Tab -> Page ID: %d, URL: %s\n",
               browser->currentTab->pageID, browser->currentTab->URL);
    }
}

void showHistory(Browser* browser) {
    Tab* temp = browser->currentTab;
    while (temp && temp->prev != NULL) {
        temp = temp->prev;
    }
    printf("\nBrowser History:\n");
    while (temp != NULL) {
        printf("Page ID: %d, URL: %s%s\n",
               temp->pageID, temp->URL,
               (temp == browser->currentTab) ? " <-- Current Tab" : "");
        temp = temp->next;
    }
}

void closeCurrentTab(Browser* browser) {
    if (browser->currentTab == NULL) {
        printf("No tab to close.\n");
        return;
    }
    Tab* tabToClose = browser->currentTab;
    if (tabToClose->prev) {
        tabToClose->prev->next = tabToClose->next;
    }
    if (tabToClose->next) {
        tabToClose->next->prev = tabToClose->prev;
    }
    if (tabToClose->next) {
        browser->currentTab = tabToClose->next;
    } else if (tabToClose->prev) {
        browser->currentTab = tabToClose->prev;
    } else {
        browser->currentTab = NULL;
    }
    printf("Closed Tab -> Page ID: %d, URL: %s\n", tabToClose->pageID, tabToClose->URL);
    free(tabToClose);
}

void freeBrowser(Browser* browser) {
    Tab* temp = browser->currentTab;
    while (temp && temp->prev != NULL) {
        temp = temp->prev;
    }
    while (temp != NULL) {
        Tab* toDelete = temp;
        temp = temp->next;
        free(toDelete);
    }
    free(browser);
}

int main() {
    Browser* browser = createBrowser();
    int choice;

    do {
        printf("\n===== Browser Menu =====\n");
        printf("1. Visit a New Page\n");
        printf("2. Go Back\n");
        printf("3. Go Forward\n");
        printf("4. Show Current Tab\n");
        printf("5. Close Current Tab\n");
        printf("6. Show History\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }
        while (getchar() != '\n');  // Clear input buffer

        switch (choice) {
            case 1: visitNewPage(browser); break;
            case 2: goBack(browser); break;
            case 3: goForward(browser); break;
            case 4: showCurrentTab(browser); break;
            case 5: closeCurrentTab(browser); break;
            case 6: showHistory(browser); break;
            case 7: printf("Exiting browser...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 7);

    freeBrowser(browser);
    return 0;
}
