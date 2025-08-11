def compare_files(file1, file2):
    mismatch_count = 0
    with open(file1, 'r') as f1, open(file2, 'r') as f2:
        lines1 = f1.readlines()
        lines2 = f2.readlines()

    total_lines = max(len(lines1), len(lines2))
    for i in range(total_lines):
        line_num = i + 1
        line1 = lines1[i].strip() if i < len(lines1) else "<EOF>"
        line2 = lines2[i].strip() if i < len(lines2) else "<EOF>"

        if line1 != line2:
            mismatch_count += 1
            print(f"Line {line_num} mismatch:")
            print(f"  File1: {line1}")
            print(f"  File2: {line2}")

    print(f"\nTotal mismatched lines: {mismatch_count}")

if __name__ == "__main__":
    compare_files("lib.out", "compiler.out")