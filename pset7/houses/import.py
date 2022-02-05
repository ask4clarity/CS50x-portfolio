import csv
import sys
from cs50 import SQL
# access db file
db = SQL("sqlite:///students.db")
# command line must have two arguments
if len(sys.argv) != 2:
    print("Usage: python import.py data.csv")
    quit()
# opens file
with open(sys.argv[1], 'r') as file:
    reader = csv.DictReader(file)
# reads through file
    for row in reader:
        name = row["name"].split()
        if len(name) != 3:
            name.insert(1, None)
# provides easy to use identifiers
        first = name[0]
        middle = name[1]
        last = name[2]
        house = row["house"]
        birth = row["birth"]
# loads into db file
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", first, middle, last, house, birth)

