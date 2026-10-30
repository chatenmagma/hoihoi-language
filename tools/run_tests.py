import argparse
import subprocess
import sys
import time
from pathlib import Path

ROOT        = Path(__file__).resolve().parents[1]
INTERPRET   = ROOT / "build" / "hoihoi"

SUITES      = {
    "intergration": ROOT / "tests" / "integration",
    "erros": ROOT / "tests" / "errors"
}

EXPECTED    = ROOT / "tests" / "expected"

def run_case(source, expected_file, expected_exit = 0, timeout = 5):
    start = time.perf_counter()

    try:
        res = subprocess.run(
            [str(INTERPRET), str(source)],
            capture_output=True,
            text=True,
            timeout=timeout,
            cwd=ROOT
        )
    except subprocess.TimeoutError:
        return False, "TIMEOUT", time.perf_counter() - start
    except OSError as exec:
        return False, f"LAUNCH ERROR {exec}", 0.0

    elapsed = time.perf_counter() - start
    expected_output = expected_file.read_text(encoding="utf-8")

    if res.returncode != expected_exit:
        return False, (
            f"stdout mismach\n",
            f"expected: {expected_output!r}\n",
            f"actual: {res.stdout!r}\n",
            f"stderr: {res.stderr!r}"
        ), elapsed

    return True, "OK", elapsed

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--suite",
        choices=["all", *SUITES.keys()],
        default="all"
    )

    args = parser.parse_args()

    if not INTERPRET.is_file():
        print(f"Interpreter not found: {INTERPRET}")
        print("Build the projet first")
        return 2

    selected = SUITES if args.suite == "all" else { args.suite: SUITES[args.suite] }

    cases = []

    for suite, directory in selected.items():
        if not directory.is_dir():
            print(f"[CONFIG ERROR] Do not exist tests dir: {directory}")
            return 2

        for source in sorted(directory.glob("*.hoi")):
            expected = EXPECTED / f"{source.stem}.out"

            if not expected.is_file():
                print(f"[CONFIG ERROR] Missing {expected}")
                return 2
            expected_exit = 0 if suite == "integration" else 1
            cases.append((suite, source, expected, expected_exit))

    passed = 0
    failed = 0
    total_time = 0.0

    for suite, source, expected, expected_exit in cases:
        ok, message, elapsed = run_case(
            source,
            expected,
            expected_exit=expected_exit,
        )
        total_time += elapsed

        if ok:
            passed += 1
            print(f"[PASS] {suite}/{source.name} ({elapsed:.3f}s)")
        else:
            failed += 1
            print(f"[FAIL] {suite}/{source.name}: {message}")

    print()
    print(f"Total: {passed + failed}")
    print(f"Passed: {passed}")
    print(f"Failed: {failed}")
    print(f"Wall time: {total_time:.3f}s")

    return 1 if failed else 0

if __name__ == "__main__":
    sys.exit(main())
