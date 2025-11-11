
import time

TABLE_SIZE = 20  # Size of the hash table

class Employee:
    def __init__(self, emp_id, name):
        self.emp_id = emp_id
        self.name = name

    def __repr__(self):
        return f"({self.emp_id}, {self.name})"

# Linear Probing Hash Table
class HashTableLinearProbing:
    def __init__(self):
        self.table = [None] * TABLE_SIZE

    def hash_func(self, key):
        return key % TABLE_SIZE

    def insert(self, emp):
        idx = self.hash_func(emp.emp_id)
        start_idx = idx
        while self.table[idx] is not None:
            if self.table[idx].emp_id == emp.emp_id:
                self.table[idx].name = emp.name
                return
            idx = (idx + 1) % TABLE_SIZE
            if idx == start_idx:
                raise Exception("Hash Table is full!")
        self.table[idx] = emp

    def search(self, emp_id):
        idx = self.hash_func(emp_id)
        start_idx = idx
        while self.table[idx] is not None:
            if self.table[idx].emp_id == emp_id:
                return self.table[idx]
            idx = (idx + 1) % TABLE_SIZE
            if idx == start_idx:
                break
        return None

    def __repr__(self):
        return str([emp for emp in self.table])


# Chaining Hash Table
class Node:
    def __init__(self, emp):
        self.emp = emp
        self.next = None

class HashTableChaining:
    def __init__(self):
        self.table = [None] * TABLE_SIZE

    def hash_func(self, key):
        return key % TABLE_SIZE

    def insert(self, emp):
        idx = self.hash_func(emp.emp_id)
        head = self.table[idx]
        current = head
        # Update if exists
        while current:
            if current.emp.emp_id == emp.emp_id:
                current.emp.name = emp.name
                return
            current = current.next
        # Insert new node at head
        new_node = Node(emp)
        new_node.next = head
        self.table[idx] = new_node

    def search(self, emp_id):
        idx = self.hash_func(emp_id)
        current = self.table[idx]
        while current:
            if current.emp.emp_id == emp_id:
                return current.emp
            current = current.next
        return None

    def __repr__(self):
        result = []
        for head in self.table:
            bucket = []
            current = head
            while current:
                bucket.append(current.emp)
                current = current.next
            result.append(bucket)
        return str(result)


def test_performance():
    # Generate sample employees (IDs chosen to cause collisions)
    employees = [Employee(i, f"Emp{i}") for i in range(30)]

    # Linear Probing Hash Table
    linear_table = HashTableLinearProbing()
    start_time = time.time()
    for emp in employees:
        try:
            linear_table.insert(emp)
        except Exception as e:
            print(f"Linear Probing: {e}")
            break
    linear_insert_time = time.time() - start_time

    start_time = time.time()
    for emp in employees:
        linear_table.search(emp.emp_id)
    linear_search_time = time.time() - start_time

    # Chaining Hash Table
    chaining_table = HashTableChaining()
    start_time = time.time()
    for emp in employees:
        chaining_table.insert(emp)
    chaining_insert_time = time.time() - start_time

    start_time = time.time()
    for emp in employees:
        chaining_table.search(emp.emp_id)
    chaining_search_time = time.time() - start_time

    # Print tables and timings
    print("Linear Probing Hash Table:")
    print(linear_table)
    print(f"Insert Time: {linear_insert_time:.6f} seconds")
    print(f"Search Time: {linear_search_time:.6f} seconds\n")

    print("Chaining Hash Table:")
    print(chaining_table)
    print(f"Insert Time: {chaining_insert_time:.6f} seconds")
    print(f"Search Time: {chaining_search_time:.6f} seconds\n")


if __name__ == "__main__":
    test_performance()
