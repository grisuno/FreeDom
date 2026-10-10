# Security Policy

## Supported Versions

We prioritize security patches on the active development branch. Due to the independent, local-first research nature of this project, only the latest major release family receives active security tracking.

| Version | Supported          |
| ------- | ------------------ |
| 1.0.x   | :white_check_mark: |
| < 1.0   | :x:                |

## Reporting a Vulnerability

As an independent project dedicated to software freedom and technical sovereignty, we take security flaws, memory corruption bugs (e.g., in Lexbor or QuickJS integrations), and potential sandbox escapes seriously. 

If you find a security vulnerability that could compromise data privacy or escape local memory boundaries, please follow the process below:

### How to Report
Do **not** open a public GitHub issue for security flaws. Instead, please report the vulnerability privately by sending an encrypted or plain-text email to:
* **Contact:** grisun0[at]proton[dot]me

Please include the following details in your report to help us reproduce the issue:
* A brief description of the vulnerability type (e.g., Use-After-Free, Out-of-Bounds Write, Logic Flaw).
* The specific payload, HTML/JS seed, or minimal reproducible example (`.html` or `.js` file).
* The command or environment flags used (e.g., `--headless` or specific Wayland setups).
* AddressSanitizer (ASAN) or GDB stack traces, if available.

### What to Expect
* **Acknowledgment:** You will receive an initial response acknowledging your report within **48 to 72 hours**.
* **Status Updates:** We will provide status updates at least once a week while analyzing or patching the root cause.
* **Resolution:** If the vulnerability is verified, a patch will be committed directly to the main branch. We do not engage with third-party bug bounty platforms; coordination is handled purely peer-to-peer.

Thank you for helping keep this research secure and sovereign.
