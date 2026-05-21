# Security Policy

## Supported Versions

Security fixes are evaluated for the current release line. Older lines are
not actively maintained; if a vulnerability also affects them, distros and
downstream packagers are expected to backport on their own schedule.

| Version    | Status                       |
| ---------- | ---------------------------- |
| v14.x      | Active (current development) |
| v13.x      | Stable, security fixes only  |
| < v13.0    | Unsupported                  |

The current `master` branch is the development target for the next release;
fixes for confirmed vulnerabilities will land on `master` first and be
backported to v13.x where applicable.

## Reporting a Vulnerability

Please **do not** open a public GitHub issue for a suspected security
vulnerability. Use one of the following private channels instead:

1. **GitHub private vulnerability reports** (preferred): open a report at
   <https://github.com/flameshot-org/flameshot/security/advisories/new>.
   This gives maintainers a private space to coordinate the fix and
   request a CVE if appropriate.
2. **Email**: `borgman.jeremy@pm.me` (the same address used for Code of
   Conduct reports). Include "SECURITY" in the subject line.

When reporting, please include:

- A description of the issue and its impact.
- Steps to reproduce, including the affected version, platform (Linux
  distribution + desktop environment / macOS version / Windows version),
  and any relevant configuration.
- If known: a suggested fix, or a proof-of-concept.

We ask that you give maintainers a reasonable window to investigate and
release a fix before public disclosure. Flameshot is maintained by
volunteers; response time depends on maintainer availability and the
severity of the report.

## Scope

In scope:

- The `flameshot` binary itself (capture, daemon, tray, CLI, D-Bus
  interface).
- The default network uploaders (Imgur, configurable HTTP) as packaged in
  this repository.
- Build, packaging, and CI artifacts under this repository.

Out of scope:

- Vulnerabilities in third-party image hosts (e.g., Imgur itself) — please
  report those upstream.
- Vulnerabilities in third-party dependencies (Qt, KDE QHotkey, etc.) —
  please report those to the respective upstream projects. If a Flameshot
  default configuration meaningfully amplifies the impact, that *is* in
  scope here.
- User-supplied configuration that intentionally exposes a sensitive
  capability (for example, a user-configured terminal launch command that
  contains shell metacharacters is by design — see [docs/SECURITY-design.md]
  if/when it exists).

## Public Disclosure

Once a fix is available, maintainers will:

- Publish a release containing the fix.
- Credit the reporter in the release notes (unless the reporter prefers to
  remain anonymous).
- Open a GitHub Security Advisory describing the issue, affected versions,
  and remediation.
