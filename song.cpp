#include <iostream>
#include <string>

using namespace std;

struct Song {
    string name;
    Song* next;
};

class Playlist {
private:
    Song* tail;  // Points to last song; tail->next is head

public:
    Playlist() : tail(nullptr) {}

    // Add song to the end
    void addSong(const string& songName) {
        Song* newSong = new Song{songName, nullptr};
        if (!tail) {
            tail = newSong;
            tail->next = tail; // Circular link
        } else {
            newSong->next = tail->next;
            tail->next = newSong;
            tail = newSong;
        }
        cout << "Added song: " << songName << "\n";
    }

    // Delete song by name
    void deleteSong(const string& songName) {
        if (!tail) {
            cout << "Playlist is empty.\n";
            return;
        }

        Song* current = tail->next; // head
        Song* prev = tail;
        bool found = false;

        do {
            if (current->name == songName) {
                found = true;
                break;
            }
            prev = current;
            current = current->next;
        } while (current != tail->next);

        if (!found) {
            cout << "Song '" << songName << "' not found in the playlist.\n";
            return;
        }

        if (current == tail && current == tail->next) {
            // Only one song in the list
            delete current;
            tail = nullptr;
        } else {
            prev->next = current->next;
            if (current == tail)
                tail = prev;
            delete current;
        }
        cout << "Deleted song: " << songName << "\n";
    }

    // Display all songs
    void display() {
        if (!tail) {
            cout << "Playlist is empty.\n";
            return;
        }
        cout << "Playlist Songs:\n";
        Song* current = tail->next;
        do {
            cout << "- " << current->name << "\n";
            current = current->next;
        } while (current != tail->next);
    }

    // Simulate playing songs in a loop n times
    void playSongs(int n) {
        if (!tail) {
            cout << "Playlist is empty. No songs to play.\n";
            return;
        }
        cout << "Playing playlist " << n << " time(s):\n";
        Song* current = tail->next;
        for (int i = 0; i < n; ++i) {
            cout << "Loop " << (i+1) << ":\n";
            do {
                cout << "Playing: " << current->name << "\n";
                current = current->next;
            } while (current != tail->next);
        }
    }

    // Destructor to clean up
    ~Playlist() {
        if (!tail) return;

        Song* current = tail->next;
        tail->next = nullptr;  // Break circular link to prevent infinite loop

        while (current) {
            Song* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    Playlist myPlaylist;
    int choice;
    string songName;
    int loops;

    do {
        cout << "\n--- Music Playlist Manager ---\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Playlist\n";
        cout << "4. Play Songs in Loop\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline

        switch(choice) {
            case 1:
                cout << "Enter song name to add: ";
                getline(cin, songName);
                myPlaylist.addSong(songName);
                break;
            case 2:
                cout << "Enter song name to delete: ";
                getline(cin, songName);
                myPlaylist.deleteSong(songName);
                break;
            case 3:
                myPlaylist.display();
                break;
            case 4:
                cout << "Enter number of loops to play: ";
                cin >> loops;
                myPlaylist.playSongs(loops);
                break;
            case 5:
                cout << "Exiting playlist manager.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
