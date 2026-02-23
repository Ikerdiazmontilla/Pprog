# LESSONS

## 2026-02-23T10:56:39+01:00
- What failed: Reading `codex/tmp/enunciado2.txt` failed once (`No such file or directory`).
- Why it failed: The extraction and read steps were launched in parallel, so the read started before the output file existed.
- Prevention rule: Do not parallelize dependent file-generation and file-read commands; run them sequentially.

## 2026-02-23T10:57:08+01:00
- What failed: A first attempt to append lessons with a shell heredoc produced malformed text and shell errors.
- Why it failed: Markdown backticks were interpreted by the shell due an unquoted heredoc delimiter.
- Prevention rule: Use single-quoted heredoc delimiters (`<<'EOF'`) when writing markdown from shell scripts.
