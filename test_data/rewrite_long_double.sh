#!/bin/bash

# 使用方式: ./rewrite_fposit_friendly.sh /path/to/project

if [ -z "$1" ]; then
  echo "❌ 請提供目標資料夾，例如： ./rewrite_fposit_friendly.sh ./whisper.cpp"
  exit 1
fi

TARGET_DIR="$1"

if [ ! -d "$TARGET_DIR" ]; then
  echo "❌ 目標資料夾不存在: $TARGET_DIR"
  exit 1
fi

echo "🚀 處理 long double 轉換與 math 函式替換中..."
echo "📁 目標資料夾: $TARGET_DIR"

# 支援的 math.h long double 函式
FUNCS=(
  sin cos tan asin acos atan atan2
  sinh cosh tanh
  exp log log10
  pow sqrt cbrt hypot
  ceil floor trunc round
  fabs fmod remainder
  erf lgamma tgamma
)

# 找出所有 C/C++/Header 檔
FILES=$(find "$TARGET_DIR" -type f \( -name "*.c" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \))

for file in $FILES; do
  cp "$file" "$file.bak"  # 備份檔

  echo "✏️ 處理檔案: $file"

  # 替換 long double → double（或你可以改成 uint64_t）
  sed -i 's/\blong[[:space:]]\+double\b/double/g' "$file"

  # 替換 math long double 函式（sinl → sin((double)(...)))
  for fn in "${FUNCS[@]}"; do
    sed -i "s/\b${fn}l[[:space:]]*([[:space:]]*\([^)]\+\))/\n${fn}((double)(\1))/g" "$file"
  done
done

echo "✅ 完成！所有 long double 與 math 函式已轉換為 double"
echo "📝 原始檔案皆已備份為 .bak"
