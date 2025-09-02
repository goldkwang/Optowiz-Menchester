import re
from collections import Counter, defaultdict

# Read the log file
with open('log_data.txt', 'r') as f:
    content = f.read()

# Split by whitespace to get individual tokens
tokens = content.split()

# Initialize counters
token_counter = Counter(tokens)
m_number_counter = Counter()
special_events = Counter()
corrupted_entries = []
m_number_sequences = []

# Define special events
special_event_names = ['ISR_RUN', 'M_NRDY', 'RdyOut', 'VPN_CHG', 'SOF_LO', 'SOF_HI']

# Analyze each token
for token in tokens:
    # Check for special events
    if token in special_event_names:
        special_events[token] += 1
    
    # Check for clean M-numbers (M0-M39)
    clean_m_match = re.match(r'^M(\d+)$', token)
    if clean_m_match:
        m_num = int(clean_m_match.group(1))
        if 0 <= m_num <= 39:
            m_number_counter[f'M{m_num}'] += 1
            m_number_sequences.append(f'M{m_num}')
    
    # Check for corrupted entries (containing multiple M numbers)
    if 'M' in token and len(token) > 3:
        # Look for patterns like MM1M15MM16, M1M13, etc.
        multiple_m_pattern = re.findall(r'M+\d+', token)
        if len(multiple_m_pattern) > 1:
            corrupted_entries.append(token)
        else:
            # Even single M patterns that look corrupted (like MM10)
            if token.startswith('MM') or 'MM' in token:
                corrupted_entries.append(token)

# Analyze sequences
print("=== LOG FILE ANALYSIS ===\n")

print("1. COUNT OF EACH UNIQUE PATTERN/EVENT:")
print("-" * 40)
for token, count in sorted(token_counter.items(), key=lambda x: x[1], reverse=True):
    if count > 1:  # Only show tokens that appear more than once
        print(f"{token}: {count} times")

print("\n2. SPECIAL EVENTS COUNT:")
print("-" * 40)
for event, count in special_events.items():
    print(f"{event}: {count} times")

print("\n3. M-NUMBER OCCURRENCES (M0-M39):")
print("-" * 40)
for i in range(40):
    m_key = f'M{i}'
    count = m_number_counter.get(m_key, 0)
    if count > 0:
        print(f"{m_key}: {count} times")

print("\n4. CORRUPTED/CONCATENATED ENTRIES:")
print("-" * 40)
corrupted_counter = Counter(corrupted_entries)
for entry, count in sorted(corrupted_counter.items(), key=lambda x: x[1], reverse=True):
    print(f"{entry}: {count} times")

print("\n5. SEQUENCE ANALYSIS:")
print("-" * 40)

# Check for patterns in the beginning
print("Initial sequence before corruptions:")
clean_sequence = []
for token in tokens[:50]:  # Look at first 50 tokens
    if token in special_event_names or re.match(r'^M\d+$', token):
        clean_sequence.append(token)
print(" -> ".join(clean_sequence[:20]))

# Analyze repeating patterns
print("\nRepeating patterns detected:")
# Look for M_NRDY ISR_RUN pattern
nrdy_isr_pattern = 0
for i in range(len(tokens)-1):
    if tokens[i] == 'M_NRDY' and i+1 < len(tokens) and tokens[i+1] == 'ISR_RUN':
        nrdy_isr_pattern += 1
print(f"'M_NRDY ISR_RUN' pattern: {nrdy_isr_pattern} times")

# Check for M39 repetitions at the end
m39_at_end = 0
for token in tokens[-100:]:  # Check last 100 tokens
    if 'M39' in token:
        m39_at_end += 1
print(f"M39 appearances in last 100 tokens: {m39_at_end}")

print("\n6. SUMMARY STATISTICS:")
print("-" * 40)
print(f"Total tokens: {len(tokens)}")
print(f"Unique tokens: {len(token_counter)}")
print(f"Corrupted entries: {len(set(corrupted_entries))}")
print(f"Clean M-numbers found: {sum(m_number_counter.values())}")