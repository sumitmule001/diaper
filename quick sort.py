class Employee:
    def __init__(self, emp_id, emp_name, emp_salary):
        self.emp_id = emp_id
        self.emp_name = emp_name
        self.emp_salary = emp_salary

    def __str__(self):
        return f"ID: {self.emp_id}, Name: {self.emp_name}, Salary: {self.emp_salary}"


def quick_sort_employees(emp_list, low, high):
    if low < high:
        pi = partition(emp_list, low, high)
        quick_sort_employees(emp_list, low, pi - 1)
        quick_sort_employees(emp_list, pi + 1, high)


def partition(emp_list, low, high):
    pivot = emp_list[high].emp_id
    i = low - 1
    for j in range(low, high):
        if emp_list[j].emp_id <= pivot:
            i += 1
            emp_list[i], emp_list[j] = emp_list[j], emp_list[i]
    emp_list[i + 1], emp_list[high] = emp_list[high], emp_list[i + 1]
    return i + 1


def merge_sort_employees(emp_list):
    if len(emp_list) > 1:
        mid = len(emp_list) // 2
        left_half = emp_list[:mid]
        right_half = emp_list[mid:]

        merge_sort_employees(left_half)
        merge_sort_employees(right_half)

        i = j = k = 0

        # Merge by emp_name alphabetically
        while i < len(left_half) and j < len(right_half):
            if left_half[i].emp_name.lower() <= right_half[j].emp_name.lower():
                emp_list[k] = left_half[i]
                i += 1
            else:
                emp_list[k] = right_half[j]
                j += 1
            k += 1

        while i < len(left_half):
            emp_list[k] = left_half[i]
            i += 1
            k += 1

        while j < len(right_half):
            emp_list[k] = right_half[j]
            j += 1
            k += 1


def display_employees(emp_list):
    for emp in emp_list:
        print(emp)


def main():
    employees = [
        Employee(105, "John", 50000),
        Employee(101, "Alice", 70000),
        Employee(109, "Bob", 48000),
        Employee(103, "Diana", 54000),
        Employee(110, "Charlie", 60000),
        Employee(102, "Eve", 62000),
        Employee(108, "Frank", 47000),
        Employee(106, "Grace", 71000),
        Employee(107, "Hank", 53000),
        Employee(104, "Ivy", 65000),
    ]

    print("Original Employee List:")
    display_employees(employees)

    # a. Quick Sort by emp_id
    quick_sort_employees(employees, 0, len(employees) - 1)
    print("\nEmployees Sorted by EMP-ID (Ascending) using Quick Sort:")
    display_employees(employees)

    # b. Merge Sort by emp_name
    merge_sort_employees(employees)
    print("\nEmployees Sorted Alphabetically by EMP-NAME using Merge Sort:")
    display_employees(employees)


if __name__ == "__main__":
    main()
