#!/usr/bin/env python3
from pathlib import Path
from collections import defaultdict
import sys

GEN_START = "<!-- GENERATED:START -->"
GEN_END = "<!-- GENERATED:END -->"

def read_title(md_file: Path) -> str:
    """
    Extract the title from a markdown file,
    which is the first line starting with "#"
    """
    with md_file.open(encoding="utf-8") as file:
        first_line = file.readline().rstrip("\n")
    if first_line.startswith("# "):
        return first_line[2:].strip()
    raise RuntimeError(f"{md_file} has no top-level title on the first line")

def extract_question_number(title: str) -> int:
    """
    Extracts a leading question number like:
    '10. Question text'
    Returns a large value if no leading number is present.
    """
    number_part = title.split(".", 1)[0]
    if not number_part.isdigit():
        raise ValueError(f"Invalid title format: {title}")
    return int(number_part)


def scan_questions(root: Path):
    questions = defaultdict(list)

    for md in sorted(root.rglob("*.md")):
        category = md.parent.name.replace("-", " ").title()
        title = read_title(md)
        questions[category].append((title, md))

    for cat in questions:
        questions[cat].sort(
            key=lambda x: (extract_question_number(x[0]))
        )

    return dict(sorted(questions.items()))


def render_index(questions: dict[str, list[tuple[str, Path]]]) -> str:
    lines = []

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
    questions_dir = Path("questions")
    readme_path = Path("README.md")

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
