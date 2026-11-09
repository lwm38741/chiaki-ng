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
- [ ] Create test/translation.cpp to exercise Chinese loading and English fallback, integrate test target and watch failure without catalog/loader.
- [ ] Add gui/include/guitranslator.h and gui/src/guitranslator.cpp, install after CLI parsing; add --language option.
- [ ] Translate TS catalog, wrap missing QML visible strings and validate tokens with scripts/check-translations.py.
- [ ] Build Qt QM and run validation, including real QTranslator lookup.

### Task 2: Build, verify and release portable archive
- [ ] Add isolated Windows workflow using upstream MSYS2 dependency/build/deploy steps, Linguist tools and Qt translations.
- [ ] Build application and tests, run CTest, translation checks, Windows startup smoke check, package license/readme/English launcher.
- [ ] Review diff; push branch, run Actions, inspect output and fix actual failures.
- [ ] Download verified ZIP, compute SHA256, publish release with explicit validation limits and source link. Read back release assets.
