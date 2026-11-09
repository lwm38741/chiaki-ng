#!/usr/bin/env python3
"""Check finished Qt translations without altering the source catalog."""
from collections import Counter
from pathlib import Path
import re
import sys
import xml.etree.ElementTree as ET

catalog = Path(sys.argv[1]) if len(sys.argv) > 1 else Path(__file__).resolve().parents[1] / 'gui/translations/chiaki_zh_CN.ts'
root = ET.parse(catalog).getroot()
errors = []
count = 0
seen = set()
for context in root.findall('context'):
    for message in context.findall('message'):
        source = message.findtext('source') or ''
        target = message.find('translation')
        key = (context.findtext('name'), source, message.findtext('comment'))
        if key in seen:
            errors.append(f'Duplicate: {key}')
        seen.add(key)
        if target is None or target.get('type') in ('unfinished', 'vanished', 'obsolete') or (source and not target.text):
            errors.append(f'Missing: {key}')
            continue
        translated = target.text or ''
        for label, pattern in [('placeholders', r'%(?:L?\d+|n)'), ('HTML tags', r'</?[A-Za-z][^>]*>'), ('URLs', r'https?://[^\s<>"\']+')]:
            if Counter(re.findall(pattern, source)) != Counter(re.findall(pattern, translated)):
                errors.append(f'{label}: {key}')
        if source.count('\n') != translated.count('\n'):
            errors.append(f'Newlines: {key}')
        count += 1
if errors:
    print('\n'.join(errors), file=sys.stderr)
    sys.exit(1)
print(f'PASS: {count} finished translations; placeholders, tags, URLs and newlines preserved')
