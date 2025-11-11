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
        if not self.students:
            print("No students in the database.")
            return
        for student in self.students:
            print(student)

    def insertion_sort_by_roll(self):
        for i in range(1, len(self.students)):
            key = self.students[i]
            j = i - 1
            while j >= 0 and self.students[j].roll_no > key.roll_no:
                self.students[j + 1] = self.students[j]
                j -= 1
            self.students[j + 1] = key

    def insertion_sort_by_name(self):
        for i in range(1, len(self.students)):
            key = self.students[i]
            j = i - 1
            while j >= 0 and self.students[j].name.lower() > key.name.lower():
                self.students[j + 1] = self.students[j]
                j -= 1
            self.students[j + 1] = key

    def insertion_sort_by_sgpa(self):
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

    n = int(input("Enter number of students: "))
    for i in range(n):
        print(f"\nEnter details for Student {i + 1}:")
        roll_no = int(input("Enter Roll Number: "))
        name = input("Enter Name: ")
        sgpa = float(input("Enter SGPA: "))
        db.add_student(Student(roll_no, name, sgpa))

    print("\nOriginal List:")
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
