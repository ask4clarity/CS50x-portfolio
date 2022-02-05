import csv
import sys
# create dictionary
STR = {
    "AGATC": 0,
    "TTTTTTCT": 0,
    "AATG": 0,
    "TCTAG": 0,
    "GATA": 0,
    "TATC": 0,
    "GAAA": 0,
    "TCTG": 0
}

# if incorrect number of command line arguments program quits
if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    quit()
# opens csv and txt file
with open(sys.argv[1], 'r') as csvfile, open(sys.argv[2], 'r') as txtfile:
    # creates buffer for both
    csvreader = csv.DictReader(csvfile)
    txtreader = txtfile.read()
    size = len(txtreader)
# nested loop that checks occurences of dictionary keys in txtfile and adds to value
    for key in STR:
        seq = len(key)
        for character in range(size):
            count = 0
            if key == txtreader[character:seq + character]:
                for i in range(0, size - seq, seq):
                    if txtreader[character:seq + character] == txtreader[character + i:seq + character + i]:
                        count += 1
                    else:
                        break
            if count > STR[key]:
                STR[key] = count
# compares csv dictionary to txt dictionary
    for row in csvreader:
        for value in row:
            for key in STR:
                # if keys/values are same then match is true otherwise moves to next row for check
                if value == key and STR[key] == int(row[value]):
                    match = True
                if value == key and STR[key] != int(row[value]):
                    match = False
                    break
            else:
                continue
            break
# prints name of match
        if match == True:
            print(row["name"])
            quit()
# prints no match if false
    print("No match")