#!/usr/bin/env python3

from pathlib import Path
import sys

SECTION_TITLE = "## 🧪 Code example"


def build_example_link(md_path: Path) -> str:
    """
    Build relative link from questions/<level>/<name>.md
    to code/<level>/<name>/
    """
    level = md_path.parent.name
    name = md_path.stem
    rel = Path("..") / ".." / "code" / level / name
    return f"- [`{rel.as_posix()}`]({rel.as_posix()})\n"


def process_markdown(md_path: Path) -> bool:
    """
    Returns False if file has the example link already added.
    Otherwise, appends the link and returns True.
    """
    text = md_path.read_text(encoding="utf-8")

    if SECTION_TITLE in text:
        return False  # already processed

    lines = text.rstrip() + "\n\n"
    lines += SECTION_TITLE + "\n"
    lines += build_example_link(md_path)

    md_path.write_text(lines, encoding="utf-8")
    return True


def main() -> int:
    root = Path("questions")

    if not root.exists():
        print("questions/ folder not found", file=sys.stderr)
        return 1

    modified = 0

    for md in sorted(root.rglob("*.md")):
        if process_markdown(md):
            modified += 1
            print(f"Updated: {md}")

    print(f"\nDone. Modified {modified} file(s).")
    return 0


if __name__ == "__main__":
    sys.exit(main())
