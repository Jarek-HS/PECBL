import subprocess

TOTAL_RUNS = 10000

total_correct = 0
total_incorrect = 0

for i in range(1, TOTAL_RUNS + 1):
    print(f"Running test #{i}...", flush=True)

    # 呼叫 bash script 並取得輸出
    result = subprocess.run(["./run_test.sh"], capture_output=True, text=True)

    # 從輸出中找出 Summary 區段
    lines = result.stdout.splitlines()
    summary_lines = [line for line in lines if line.startswith("Correct") or line.startswith("Incorrect")]

    # 印出這次測試的 summary
    print(f"======== Summary #{i} ========",flush=True)
    for line in summary_lines:
        print(line)

        # 累加正確/錯誤
        if line.startswith("Correct"):
            total_correct += int(line.split(":")[1].strip())
        elif line.startswith("Incorrect"):
            total_incorrect += int(line.split(":")[1].strip())

print("\n========= TOTAL SUMMARY =========", flush=True)
print(f"Total Correct  : {total_correct}")
print(f"Total Incorrect: {total_incorrect}")
