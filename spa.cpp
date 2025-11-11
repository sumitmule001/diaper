class Student:
    def __init__(self, roll_no, name, sgpa):
        self.roll_no = roll_no
        self.name = name
        self.sgpa = sgpa

    def __str__(self):
        return f"Roll No: {self.roll_no}, Name: {self.name}, SGPA: {self.sgpa}"


class StudentDatabase:
    def __init__(self):
        self.students = []

    def add_student(self, student):
        self.students.append(student)

    def display_students(self):
        for student in self.students:
            print(student)

    def insertion_sort_by_roll(self):
        # Sort by roll number ascending
        for i in range(1, len(self.students)):
            key = self.students[i]
            j = i - 1
            while j >= 0 and self.students[j].roll_no > key.roll_no:
                self.students[j + 1] = self.students[j]
                j -= 1
            self.students[j + 1] = key

    def insertion_sort_by_name(self):
        # Sort alphabetically by name
        for i in range(1, len(self.students)):
            key = self.students[i]
            j = i - 1
            while j >= 0 and self.students[j].name.lower() > key.name.lower():
                self.students[j + 1] = self.students[j]
                j -= 1
            self.students[j + 1] = key

    def insertion_sort_by_sgpa(self):
        # Sort by SGPA descending (highest first)
        for i in range(1, len(self.students)):
            key = self.students[i]
            j = i - 1
            while j >= 0 and self.students[j].sgpa < key.sgpa:
                self.students[j + 1] = self.students[j]
                j -= 1
            self.students[j + 1] = key

    def get_top_five_toppers(self):
        self.insertion_sort_by_sgpa()
        return self.students[:5]


def main():
    db = StudentDatabase()

    # Adding at least 10 student records
    db.add_student(Student(12, "Alice", 8.5))
    db.add_student(Student(7, "Bob", 9.2))
    db.add_student(Student(3, "Charlie", 7.8))
    db.add_student(Student(18, "David", 9.0))
    db.add_student(Student(5, "Eva", 8.9))
    db.add_student(Student(10, "Frank", 7.6))
    db.add_student(Student(1, "Grace", 9.5))
    db.add_student(Student(15, "Helen", 8.2))
    db.add_student(Student(9, "Ivy", 8.7))
    db.add_student(Student(2, "Jack", 7.9))

    print("Original List:")
    db.display_students()

    print("\nSorted by Roll Number (Ascending):")
    db.insertion_sort_by_roll()
    db.display_students()

    print("\nSorted Alphabetically by Name:")
    db.insertion_sort_by_name()
    db.display_students()

    print("\nTop 5 Toppers by SGPA:")
    toppers = db.get_top_five_toppers()
    for student in toppers:
        print(student)


if __name__ == "__main__":
    main()
