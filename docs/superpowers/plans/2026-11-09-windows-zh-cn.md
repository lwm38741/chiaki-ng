# Windows Chinese Portable Implementation Plan

> **For agentic workers:** Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Publish a Windows x64 portable Simplified Chinese chiaki-ng v1.10.1 on lwm38741/chiaki-ng.
**Architecture:** Embed Qt TS/QM catalog; default zh_CN with --language en override. Reuse upstream MSYS2 build and deploy.
**Tech Stack:** Qt6/QML/C++, CMake, Python validation, GitHub Actions/MSYS2.
**Spec:** docs/superpowers/specs/2026-11-09-windows-zh-cn-design.md

## Global Constraints
- Windows x64 portable ZIP only, no installer or other platform builds.
- Preserve upstream behavior, license, attribution and English fallback.
- Base f30da0aaeb96fc0026cc03683153f682352e7d7c (v1.10.1).

## Review Focus
- Placeholder and rich-text integrity; compare source and target tokens.
- Missing marked/unmarked visible labels; run lupdate and audit QML text properties.
- English fallback and embedded resource loading; run real Qt test binary.
- Deployment dependency completeness; inspect ZIP and perform Windows startup smoke check.
- No PS4/PS5 hardware available; disclose untested pairing/streaming.

### Task 1: Complete catalog and load translations
- [x] Create test/translation.cpp to exercise Chinese loading and English fallback, integrate test target and watch failure without catalog/loader.
- [x] Add gui/include/guitranslator.h and gui/src/guitranslator.cpp, install after CLI parsing; add --language option.
- [x] Translate TS catalog, wrap missing QML visible strings and validate tokens with scripts/check-translations.py.
- [x] Build Qt QM and run validation, including real QTranslator lookup.

### Task 2: Build, verify and release portable archive
- [x] Add isolated Windows workflow using upstream MSYS2 dependency/build/deploy steps, Linguist tools and Qt translations.
- [x] Build application and tests, run CTest, translation checks, Windows startup smoke check, package license/readme/English launcher.
- [x] Review diff; push branch, run Actions, inspect output and fix actual failures.
- [x] Download verified ZIP, compute SHA256, publish release with explicit validation limits and source link. Read back release assets.

## Verification receipt

Published v1.10.1-zh.1 from eb0bfa868262e7725c04606d1a1206f4b7f3e861. Windows run 42610581797 succeeded: both CTest suites passed, 122 upstream cases passed with one Windows-prescribed skip, deployed Qt translations and both GUI languages passed, nine distinct settings screenshots inspected. ZIP SHA-256: 7e82d0b9bb4e94d073fcd2bfbfb22adcc170ecc5f06be5b9e1820aee35d42d03. GitHub uploaded asset digest matches.

Resolved findings: persistent mapping keys derived from translated labels; GUI test registration before enable_testing; missing merged Qt catalog loading; toolbar actions clipped at 1024 width; regression fixture missing explicit Settings profile. Narrow-window fixed settings layouts still elide/crop some content and are documented in the release. No real console, PSN, HDR, hardware decoder or controller end-to-end testing.

Release: https://github.com/lwm38741/chiaki-ng/releases/tag/v1.10.1-zh.1
