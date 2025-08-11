import sys

def compare_files(file1, file2):
    with open(file1, "r") as f1, open(file2, "r") as f2:
        lines1 = [line.strip() for line in f1.readlines()]
        lines2 = [line.strip() for line in f2.readlines()]

    min_len = min(len(lines1), len(lines2))
    max_len = max(len(lines1), len(lines2))

    diffs = []

    for i in range(min_len):
        if lines1[i] != lines2[i]:
            diffs.append((i + 1, lines1[i], lines2[i]))

    # 如果檔案長度不同，也要提示
    if len(lines1) != len(lines2):
        print(f"⚠️ 檔案行數不同：{file1} 有 {len(lines1)} 行，{file2} 有 {len(lines2)} 行")
        for i in range(min_len, max_len):
            if i < len(lines1):
                diffs.append((i + 1, lines1[i], "<不存在>"))
            else:
                diffs.append((i + 1, "<不存在>", lines2[i]))

    # 印出差異
    if diffs:
        print(f"🔍 發現 {len(diffs)} 行不同：")
        for line_num, line1, line2 in diffs:
            print(f"Line {line_num:>6}:\n  File1: {line1}\n  File2: {line2}\n")
    else:
        print("✅ 兩個檔案完全相同")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("用法：python compare_files.py <file1> <file2>")
    else:
        compare_files(sys.argv[1], sys.argv[2])
