import sys
import os

def split_column5(input_file):
    base_name = os.path.splitext(input_file)[0]
    col5_file = f"{base_name}_column5.out"
    modified_file = f"{base_name}_modified.out"

    with open(input_file, "r") as f:
        lines = f.readlines()

    column5 = []
    modified_lines = []

    for line in lines:
        parts = line.strip().split()
        if len(parts) > 4:
            column5.append(parts[4] + "\n")
            del parts[4]
        modified_lines.append(" ".join(parts) + "\n")

    with open(col5_file, "w") as f:
        f.writelines(column5)

    with open(modified_file, "w") as f:
        f.writelines(modified_lines)

    print(f"✅ 第五欄已儲存至: {col5_file}")
    print(f"✅ 其餘欄位已儲存至: {modified_file}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("用法: python split_column5.py <輸入檔案>")
    else:
        split_column5(sys.argv[1])
