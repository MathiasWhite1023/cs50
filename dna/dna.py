import csv
import sys


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python program.py database.csv sequence.txt")
        sys.exit(1)

        # TODO: Read database file into a variable
    rows = []
    with open(sys.argv[1]) as db_file:
        reader = csv.DictReader(db_file)
        for row in reader:
            rows.append(row)

        # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        file_DNA = file.read()

        # TODO: Find longest match of each STR in DNA sequence
        str_matches = {}
        for str_name in reader.fieldnames[1:]:  # [1:] Skip the first field (name)
            str_matches[str_name] = longest_match(file_DNA, str_name)
            # by using [str] you can keep track of the matches
            # cause str is incremented by 1 it time

    # TODO: Check database for matching profiles
    for row in rows:
        match = True
        for str_names in str_matches:
            if int(row[str_names]) != str_matches[str_names]:
                match = False
                break

        if match:
            print(f"{row['name']}")
            return

    print("No match")


if __name__ == "__main__":
    main()
