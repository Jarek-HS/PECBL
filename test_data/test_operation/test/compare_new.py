def compare_32bit_allow_1_diff(lib_path, compiler_path):
    errors = []

    with open(lib_path, "r") as f1, open(compiler_path, "r") as f2:
        lib_lines = [line.strip() for line in f1.readlines()]
        compiler_lines = [line.strip() for line in f2.readlines()]

    min_len = min(len(lib_lines), len(compiler_lines))

    for i in range(min_len):
        try:
            lib_val = int(lib_lines[i], 16)
            comp_val = int(compiler_lines[i], 16)

            if abs(lib_val - comp_val) > 1:
                errors.append({
                    "line": i + 1,
                    "lib": f"{lib_val:#010x}",
                    "compiler": f"{comp_val:#010x}",
                    "diff": abs(lib_val - comp_val)
                })

        except ValueError:
            print(f"⚠️ Line {i+1} contains invalid hex.")

    return errors


# 使用範例
lib_file = "lib_column5.out"
compiler_file = "compiler_column5.out"

errors = compare_32bit_allow_1_diff(lib_file, compiler_file)

# 顯示結果
if errors:
    print(f"⚠️ Found {len(errors)} mismatched lines (difference > 1):")
    for e in errors:
        print(f"Line {e['line']:>6}: Lib = {e['lib']}, Compiler = {e['compiler']}, Diff = {e['diff']}")
else:
    print("✅ All lines matched (difference ≤ 1 allowed).")
