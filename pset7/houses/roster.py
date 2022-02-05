import csv
import sys
from cs50 import SQL
# access db file
db = SQL("sqlite:///students.db")
# command line must have two arguments
if len(sys.argv) != 2:
    print("Usage: python roster.py house")
    quit()
# goes through rows using SQL query
for row in db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? GROUP BY first ORDER BY last", sys.argv[1]):
    # omits middle name NULL
    if row["middle"] == None:
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    # prints full name if middle present
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")
