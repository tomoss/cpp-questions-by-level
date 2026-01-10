#!/usr/bin/env python3
from __future__ import annotations

import argparse
from pathlib import Path
from collections import defaultdict
import sys
import re

GEN_START = "<!-- GENERATED:START -->"
GEN_END = "<!-- GENERATED:END -->"


def read_title(md_file: Path) -> str:
    for line in md_file.read_text(encoding="utf-8").splitlines():
        if line.startswith("# "):
            return line[2:].strip()
    raise RuntimeError(f"{md_file} has no top-level title (# ...)")


def extract_question_number(title: str) -> int:
    """
    Extracts a leading question number like:
    '10. Question text'
    Returns a large value if no leading number is present.
    """
    match = re.match(r"\s*(\d+)\s*\.", title)
    return int(match.group(1)) if match else 10**9


def scan_questions(root: Path):
    questions = defaultdict(list)

    for md in sorted(root.rglob("*.md")):
        if md.name.lower() == "index.md":
            continue
        category = md.parent.name.replace("-", " ").title()
        title = read_title(md)
        questions[category].append((title, md))

    for cat in questions:
        questions[cat].sort(
            key=lambda x: (extract_question_number(x[0]), x[0].lower())
        )

    return dict(sorted(questions.items()))


def render_index(questions: dict[str, list[tuple[str, Path]]]) -> str:
    lines = []
    lines.append("## Questions\n")

    for category, items in questions.items():
        lines.append(f"### {category}\n")
        for title, path in items:
            lines.append(f"- [{title}]({path.as_posix()})")
        lines.append("")

    return "\n".join(lines).rstrip() + "\n"


def replace_generated_block(readme: str, generated: str) -> str:
    if GEN_START not in readme or GEN_END not in readme:
        raise RuntimeError("README.md is missing GENERATED markers")

    before = readme.split(GEN_START)[0]
    after = readme.split(GEN_END)[1]

    return (
        before
        + GEN_START
        + "\n\n"
        + generated
        + "\n"
        + GEN_END
        + after
    )


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--questions", default="questions")
    parser.add_argument("--readme", default="README.md")
    args = parser.parse_args()

    questions_dir = Path(args.questions)
    readme_path = Path(args.readme)

    if not questions_dir.exists():
        print("questions/ directory not found", file=sys.stderr)
        return 1

    questions = scan_questions(questions_dir)
    generated = render_index(questions)

    readme = readme_path.read_text(encoding="utf-8")
    updated = replace_generated_block(readme, generated)
    readme_path.write_text(updated, encoding="utf-8")

    return 0


if __name__ == "__main__":
    sys.exit(main())
