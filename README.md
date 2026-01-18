# Cryptopals Solutions in Rust

This repository contains my solutions to the [Cryptopals Challenge](https://cryptopals.com/) written in Rust, focused on building a deep understanding of cryptography and systems programming.

## Repository Structure

This is a **virtual Cargo workspace** with the following layout:

```
cryptopals/
├── Cargo.toml              # Workspace root (no package)
├── README.md               # This file
└── crates/
    ├── common/             # Shared cryptographic utilities & implementations
    │   ├── Cargo.toml
    │   └── src/
    │       ├── lib.rs
    │       ├── xor.rs
    │       ├── aes.rs
    │       ├── encoding.rs
    │       └── ...
    │
    ├── set1/               # Set 1: Basics (6 challenges)
    │   ├── Cargo.toml
    │   └── src/lib.rs
    │
    ├── set2/               # Set 2: Block Crypto (8 challenges)
    │   ├── Cargo.toml
    │   └── src/lib.rs
    │
    └── set3/               # Set 3: Block & Stream Crypto (8 challenges)
        ├── Cargo.toml
        └── src/lib.rs
```

### Workspace Design

- **`common/`**: Contains all cryptographic implementations (AES, XOR operations, encoding utilities, etc.). This is where the actual crypto logic lives and is tested independently.

- **`set1/`, `set2/`, `set3/`, etc.**: Each set is its own library crate that depends on `common/`. These crates contain the challenge solutions and tests that verify implementations against the Cryptopals test vectors.

All member crates depend on `common/` to access shared cryptographic utilities:

```toml
[dependencies]
common = { path = "../common" }
```

## Building & Testing

### Build the entire workspace

```bash
cargo build
```

### Build a specific crate

```bash
cargo build -p common
cargo build -p set1
```

### Run all tests

```bash
cargo test --workspace
```

### Run tests for a specific set

```bash
cargo test -p set1
```

### Run tests with output

```bash
cargo test -p set1 -- --nocapture
```

### Check code without building

```bash
cargo check --workspace
```

### View dependency tree

```bash
cargo tree
```

## Learning Goals

This project was built with two primary goals:

1. **Deep Cryptography Understanding**: Working through Cryptopals forces you to understand the fundamental concepts behind modern cryptography—not just how to use libraries, but why these primitives work and how they can fail.

2. **Rust Mastery**: Building crypto implementations in Rust naturally leads to better understanding of:
   - Ownership and borrowing
   - Error handling with `Result`
   - Type safety for security-critical code
   - Testing strategies for correctness

## Challenge Sets

| Set | Topic | Challenges | Status |
|-----|-------|-----------|--------|
| 1 | Basics (Hex, Base64, XOR, English scoring) | 6 | In Progress |
| 2 | Block Crypto (ECB, CBC, PKCS#7) | 8 | Planned |
| 3 | Block & Stream Crypto (CTR mode, RC4) | 8 | Planned |
| 4 | Stream Crypto & Randomness | 8 | Planned |
| 5 | Diffie-Hellman & Friends | 8 | Planned |
| 6 | RSA & DSA | 8 | Planned |
| 7 | Hashing | 5 | Planned |
| 8 | Abstract Algebra | 6 | Planned |

## Notes

- I implement cryptographic primitives from scratch to understand them deeply—I don't use `ring`, `sodiumoxide`, or other crypto crates for the core algorithms. However, I may use standard libraries for lower-level operations where it makes sense.

- Each challenge is tested against official Cryptopals test vectors to ensure correctness.

- Comments and documentation are included to explain non-obvious cryptographic concepts and Rust patterns.

---

## ⚠️ Disclaimer

**These solutions are NOT production-ready code.** Use at your own risk.

All implementations and solutions in this repository have been written by me, **Calico Nino**. While I used Large Language Models (LLMs) to help me understand cryptographic concepts and Rust patterns, all code implementations, logic, and solutions are written by me without copy-pasting from external sources.
