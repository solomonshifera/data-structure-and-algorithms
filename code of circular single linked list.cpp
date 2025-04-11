#include <iostream>
#include <string>
using namespace std;

class Student {
	public:
		int id, age;
		string name;
		Student *prev = nullptr, *next = nullptr;

		Student(int i, string n, int a) : id(i), name(n), age(a), prev(nullptr), next(nullptr) {}
};

class CircularDoublyLinkedList {
	private:
		Student *head = nullptr;

		// Create a new node
		Student *createNode() {
			int id, age;
			string name;
			cout << "Enter ID: ";
			cin >> id;
			cout << "Enter Name: ";
			cin.ignore();
			getline(cin, name);
			cout << "Enter Age: ";
			cin >> age;
			return new Student(id, name, age);
		}

	public:
		// Insert at the beginning
		void insertAtBeginning() {
			Student *n = createNode();
			if (!head) {
				head = n;
				head->next = head->prev = head;
			} else {
				Student *last = head->prev;
				n->next = head;
				n->prev = last;
				last->next = head->prev = n;
				head = n;
			}
			cout << "Inserted " << n->name << " at the beginning successfully!\n";
		}

		// Insert at the end
		void insertAtEnd() {
			Student *n = createNode();
			if (!head) {
				head = n;
				head->next = head->prev = head;
			} else {
				Student *last = head->prev;
				n->next = head;
				n->prev = last;
				last->next = head->prev = n;
			}
			cout << "Inserted " << n->name << " at the end successfully!\n";
		}

		// Insert at a specific position
		void insertAtPosition(int pos) {
			if (pos < 1)
				return void(cout << "Invalid position! Cannot insert.\n");
			if (pos == 1)
				return insertAtBeginning();
			Student *t = head;
			for (int i = 1; i < pos - 1 && t->next != head; i++)
				t = t->next;
			if (t->next == head)
				return void(cout << "Position out of range! Cannot insert.\n");
			Student *n = createNode();
			n->next = t->next;
			n->prev = t;
			t->next->prev = n;
			t->next = n;
			cout << "Inserted " << n->name << " at position " << pos << " successfully!\n";
		}

		// Delete from the beginning
		void deleteFromBeginning() {
			if (!head)
				return void(cout << "List is empty! Nothing to delete.\n");
			Student *t = head;
			if (head->next == head) {  // Only one node
				head = nullptr;
			} else {
				Student *last = head->prev;
				head = head->next;
				head->prev = last;
				last->next = head;
			}
			cout << "Deleted " << t->name << " from the beginning successfully!\n";
			delete t;
		}

		// Delete from the end
		void deleteFromEnd() {
			if (!head)
				return void(cout << "List is empty! Nothing to delete.\n");
			Student *t = head->prev;
			if (head->next == head) {  // Only one node
				head = nullptr;
			} else {
				t->prev->next = head;
				head->prev = t->prev;
			}
			cout << "Deleted " << t->name << " from the end successfully!\n";
			delete t;
		}

		// Delete from a specific position
		void deleteFromPosition(int pos) {
			if (!head || pos < 1)
				return void(cout << "Invalid position or empty list! Cannot delete.\n");
			if (pos == 1)
				return deleteFromBeginning();
			Student *t = head;
			for (int i = 1; i < pos && t->next != head; i++)
				t = t->next;
			if (t->next == head)
				return void(cout << "Position out of range! Cannot delete.\n");
			t->prev->next = t->next;
			t->next->prev = t->prev;
			cout << "Deleted " << t->name << " from position " << pos << " successfully!\n";
			delete t;
		}

		// Search for an element by ID
		void search(int id) {
			if (!head)
				return void(cout << "List is empty! Cannot search.\n");
			Student *t = head;
			do {
				if (t->id == id) {
					cout << "Student found: " << t->name << " with ID: " << t->id << " and Age: " << t->age << "\n";
					return;
				}
				t = t->next;
			} while (t != head);
			cout << "Student with ID: " << id << " not found.\n";
		}

		// Display the list
		void display() {
			if (!head)
				return void(cout << "List is empty!\n");
			Student *t = head;
			cout << "Student List: ";
			do {
				cout << "[" << t->id << ": " << t->name << ", " << t->age << "] <-> ";
				t = t->next;
			} while (t != head);
			cout << "(head)\n";
		}
};

int main() {
	CircularDoublyLinkedList list;
	int choice, pos, id;
	while (true) {
		cout << "\nMenu:\n1. Insert at beginning\n2. Insert at end\n3. Insert at position\n4. Delete from beginning\n5. Delete from end\n6. Delete from position\n7. Search for element\n8. Display\n9. Exit\nEnter choice: ";
		cin >> choice;
		if (choice == 9)
			return 0;
		if (choice == 3 || choice == 6) {
			cout << "Enter position: ";
			cin >> pos;
		}
		if (choice == 7) {
			cout << "Enter ID to search: ";
			cin >> id;
		}
		switch (choice) {
			case 1:
				list.insertAtBeginning();
				break;
			case 2:
				list.insertAtEnd();
				break;
			case 3:
				list.insertAtPosition(pos);
				break;
			case 4:
				list.deleteFromBeginning();
				break;
			case 5:
				list.deleteFromEnd();
				break;
			case 6:
				list.deleteFromPosition(pos);
				break;
			case 7:
				list.search(id);
				break;
			case 8:
				list.display();
				break;
			default:
				cout << "Invalid choice! Try again.\n";
		}
	}
}